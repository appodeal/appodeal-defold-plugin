#include "appodeal_private.h"
#include <dmsdk/extension/extension.h>
#include <dmsdk/script/script.h>  
#include <dmsdk/dlib/log.h>
#import "Appodeal/Appodeal.h"

const int INTERSTITIAL        = 1;
const int BANNER              = 4;
const int BANNER_BOTTOM       = 8;
const int BANNER_TOP          = 16;
const int REWARDED_VIDEO      = 128;
const int NON_SKIPPABLE_VIDEO = 256;

namespace dmScript
{
    /**
     * Retrieve current instance from the global table and place it on the top of the stack, only valid when set.
     * @param lua state
     */
    void GetInstance(lua_State* L);
    /**
     * Set the value on the top of the stack as the instance into the global table and pops it from the stack.
     * @param lua state
     */
    void SetInstance(lua_State* L);
    /**
     * Check if the instance in the lua state is valid. The instance is assumed to have been previously set by SetInstance.
     * @param lua state
     * @return whether the instance is valid
     */
    bool IsInstanceValid(lua_State* L);
 
    /**
     * Retrieve the main thread lua state from any lua state (main thread or coroutine).
     * @param lua state
     * @return the main thread lua state
     */
    lua_State* GetMainThread(lua_State* L);
    
    
    
}


struct APD {
  AppodealListener listener;
} g_Apd;

APD* apd;

@interface AdsAppodealDelegate : NSObject <AppodealBannerDelegate, AppodealInterstitialDelegate, AppodealRewardedVideoDelegate, AppodealNonSkippableVideoDelegate>
@end

@implementation AdsAppodealDelegate

//send callback func

int send_callback(const char * message,const char * currencyName, int rewardAmount) {
	apd = &g_Apd;
 	lua_State* L = apd->listener.m_L;
    int top = lua_gettop(L);
    lua_rawgeti(L, LUA_REGISTRYINDEX, apd->listener.m_Callback);

    // Setup self
   	lua_rawgeti(L, LUA_REGISTRYINDEX, apd->listener.m_Self);
   	lua_pushvalue(L, -1);
   	dmScript::SetInstance(L);
   	lua_pushstring(L, message);
   	lua_pushstring(L, currencyName);
   	lua_pushnumber(L, rewardAmount);
    //dmScript::PushString(L, message);
    int ret = lua_pcall(L, 4, LUA_MULTRET, 0);
    if (ret != 0) {
    	dmLogError("Error running apd callback: %s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    assert(top == lua_gettop(L));
    return 1;
}

//banner delegate

- (void)bannerDidLoadAdIsPrecache:(BOOL)precache {
	if (precache)
		send_callback("BANNER_DID_LOAD","",0);
	else
		send_callback("BANNER_DID_LOAD_PRECACHE","",0);
}

- (void)bannerDidRefresh {
	send_callback("BANNER_DID_REFRESH","",0);
}

- (void)bannerDidFailToLoadAd {
	send_callback("BANNER_DID_FAIL_TO_LOAD","",0);
}

- (void)bannerDidClick {
	send_callback("BANNER_WAS_CLICKED","",0);
}

- (void)bannerDidShow {
	send_callback("BANNER_DID_SHOW","",0);
}

//interstitial delegate

- (void)interstitialDidLoadAdisPrecache:(BOOL)precache {
	if (precache)
		send_callback("INTERSTITIAL_DID_LOAD","",0);
	else
		send_callback("INTERSTITIAL_DID_LOAD_PRECACHE","",0);
}

- (void)interstitialDidFailToLoadAd {
	send_callback("INTERSTITIAL_DID_FAIL_TO_LOAD","",0);
}

- (void)interstitialDidFailToPresent {
	send_callback("INTERSTITIAL_DID_FAIL_TO_PRESENT","",0);
}

- (void)interstitialWillPresent {
	send_callback("INTERSTITIAL_DID_PRESENT","",0);
}

- (void)interstitialDidFinish {
	send_callback("INTERSTITIAL_DID_FINISH","",0);
}

- (void)interstitialDidDismiss {
	send_callback("INTERSTITIAL_DID_CLOSE","",0);
}

- (void)interstitialDidClick {
	send_callback("INTERSTITIAL_WAS_CLICKED","",0);
}

//rewarded video delegate

- (void)rewardedVideoDidLoadAd {
	send_callback("REWARDED_VIDEO_DID_LOAD","",0);
}

- (void)rewardedVideoDidFailToLoadAd {
	send_callback("REWARDED_VIDEO_DID_FAIL_TO_LOAD","",0);
}

- (void)rewardedVideoDidFailToPresent {
	send_callback("REWARDED_VIDEO_DID_FAIL_TO_PRESENT","",0);
}

- (void)rewardedVideoDidPresent {
	send_callback("REWARDED_VIDEO_DID_SHOW","",0);
}

- (void)rewardedVideoWillDismiss {
	send_callback("REWARDED_VIDEO_DID_CLOSE","",0);
}

- (void)rewardedVideoDidFinish:(NSUInteger)rewardAmount name:(NSString *)rewardName {
	send_callback("REWARDED_VIDEO_WAS_FINISHED",  [rewardName UTF8String] , (int)rewardAmount);
}

//non skippable video delegate

- (void)nonSkippableVideoDidLoadAd {
	send_callback("NON_SKIPPABLE_VIDEO_DID_LOAD","",0);
}

- (void)nonSkippableVideoDidFailToLoadAd {
	send_callback("NON_SKIPPABLE_VIDEO_DID_FAIL_TO_LOAD","",0);
}

- (void)nonSkippableVideoDidPresent {
	send_callback("NON_SKIPPABLE_VIDEO_DID_SHOW","",0);
}

- (void)nonSkippableVideoDidFailToPresent {
	send_callback("NON_SKIPPABLE_VIDEO_DID_FAIL_TO_PRESENT","",0);
}

- (void)nonSkippableVideoWillDismiss {
	send_callback("NON_SKIPPABLE_VIDEO_DID_CLOSE","",0);
}

- (void)nonSkippableVideoDidFinish {
	send_callback("NON_SKIPPABLE_VIDEO_DID_FINISH","",0);
}

@end

//convert ad_type to apd_ad_type
int apdAdTypes(int adTypes) {
    int apdAdTypes = 0;

    if ((adTypes & INTERSTITIAL) > 0) {
        apdAdTypes |= AppodealAdTypeInterstitial;
    }

    if ((adTypes & BANNER) > 0 ||
        (adTypes & BANNER_TOP) > 0 ||
        (adTypes & BANNER_BOTTOM) > 0) {

        apdAdTypes |= AppodealAdTypeBanner;
    }
    
    if ((adTypes & REWARDED_VIDEO) > 0) {
        apdAdTypes |= AppodealAdTypeRewardedVideo;
    } 
       
    if ((adTypes & NON_SKIPPABLE_VIDEO) > 0) {
        apdAdTypes |= AppodealAdTypeNonSkippableVideo;
    } 
     
    return apdAdTypes;
}

//convert show_style to apd_show_style
int apdShowStyle(int adTypes) {

	if ((adTypes & INTERSTITIAL) > 0) {
        return AppodealShowStyleInterstitial;
    }
        
    if ((adTypes & BANNER_TOP) > 0) {
        return AppodealShowStyleBannerTop;
    }

    if ((adTypes & BANNER_BOTTOM) > 0) {
        return AppodealShowStyleBannerBottom;
    }
    
    if ((adTypes & REWARDED_VIDEO) > 0) {
        return AppodealShowStyleRewardedVideo;
    }
    
    if ((adTypes & NON_SKIPPABLE_VIDEO) > 0) {
        return AppodealShowStyleNonSkippableVideo;
    }

    return 0;
}

//create listener for callbacks
void Appodeal_Listen(lua_State* L) {	
	//creating the callback lua ref 
	apd = &g_Apd;
    
    luaL_checktype(L, 1, LUA_TFUNCTION);
    lua_pushvalue(L, 1);
    int cb = dmScript::Ref(L, LUA_REGISTRYINDEX);

    if (apd->listener.m_Callback != LUA_NOREF) {
      dmScript::Unref(apd->listener.m_L, LUA_REGISTRYINDEX, apd->listener.m_Callback);
      dmScript::Unref(apd->listener.m_L, LUA_REGISTRYINDEX, apd->listener.m_Self);
    }

    apd->listener.m_L = dmScript::GetMainThread(L);
    apd->listener.m_Callback = cb;
    dmScript::GetInstance(L);
    apd->listener.m_Self = dmScript::Ref(L, LUA_REGISTRYINDEX);
}

//initialise appodeal sdk and set callback delegates
void Appodeal_Initialise(lua_State* L) {    
	if (![Appodeal isInitalized])	{
		//parse params from Lua state (key, adType)
		const char *key_from_lua = luaL_checkstring(L, 1);	
		int adType = luaL_checkint(L, 2);   
		
		//convert char to NSString
		NSString* key = [NSString stringWithUTF8String:key_from_lua]; 
		
		//create delegate instance 
		AdsAppodealDelegate * delegateAds = [[AdsAppodealDelegate alloc] init]; 
		
		//Init appodeal SDK
		[Appodeal initializeWithApiKey:key types: (AppodealAdType)apdAdTypes(adType)];	
		
		//set delegates
		[Appodeal setBannerDelegate:(id<AppodealBannerDelegate>)delegateAds];
		[Appodeal setInterstitialDelegate:(id<AppodealInterstitialDelegate>)delegateAds];
		[Appodeal setRewardedVideoDelegate:(id<AppodealRewardedVideoDelegate>)delegateAds];
		[Appodeal setNonSkippableVideoDelegate:(id<AppodealNonSkippableVideoDelegate>)delegateAds];
	}
}

//showing ad (optional placement)
void Appodeal_ShowAd(lua_State* L) {

	//parse params from Lua state (key, adType)
	int showStyle = luaL_checkint(L, 1);
	
	//parse placement if exists
	const char *placement_name = luaL_checkstring(L, 1);	
	
	//convert placement_name to NSString
	NSString* placement = [NSString stringWithUTF8String:placement_name];
	
	//show ad
	if ([placement length] > 0)
		[Appodeal showAd:(AppodealShowStyle)apdShowStyle(showStyle) forPlacement:placement rootViewController:[UIApplication sharedApplication].keyWindow.rootViewController];
	else
   	 	[Appodeal showAd:(AppodealShowStyle)apdShowStyle(showStyle) rootViewController:[UIApplication sharedApplication].keyWindow.rootViewController];
}

//hide appodeal banner
void Appodeal_HideBanner(lua_State* L) {
	[Appodeal hideBanner];
}

