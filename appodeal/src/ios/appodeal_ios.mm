#include "appodeal_ios.h"
#include <dmsdk/extension/extension.h>
#include <dmsdk/script/script.h>  
#include <dmsdk/dlib/log.h>

#if defined(DM_PLATFORM_IOS)

#import "Appodeal/Appodeal.h"


namespace dmScript {
    void GetInstance(lua_State* L);
    void SetInstance(lua_State* L);
    bool IsInstanceValid(lua_State* L);
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

int send_callback(const char * message, const char * currencyName, int rewardAmount) {
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

//banner callbacks

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

//interstitial callbacks

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

//rewarded video callbacks

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

//non skippable video callbacks

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
int apdShowStyle(int showStyles) {

	if ((showStyles & INTERSTITIAL) > 0) {
        return AppodealShowStyleInterstitial;
    }
        
    if ((showStyles & BANNER_TOP) > 0) {
        return AppodealShowStyleBannerTop;
    }

    if ((showStyles & BANNER_BOTTOM) > 0) {
        return AppodealShowStyleBannerBottom;
    }
    
    if ((showStyles & REWARDED_VIDEO) > 0) {
        return AppodealShowStyleRewardedVideo;
    }
    
    if ((showStyles & NON_SKIPPABLE_VIDEO) > 0) {
        return AppodealShowStyleNonSkippableVideo;
    }

    return 0;
}

//parse boolean 

BOOL get_lua_bool (lua_State* L, int index) {
	if (lua_isboolean(L, index))
        if (lua_toboolean(L, index) == 1)
        	return YES;
        else
        	return NO;
    else
        return NO;
}

//create listener for callbacks
void Appodeal_Listen(lua_State* L) {	
	//create delegate instance 
	AdsAppodealDelegate * delegateAds = [[AdsAppodealDelegate alloc] init];
	
	//set delegates
	[Appodeal setBannerDelegate:(id<AppodealBannerDelegate>)delegateAds];
	[Appodeal setInterstitialDelegate:(id<AppodealInterstitialDelegate>)delegateAds];
	[Appodeal setRewardedVideoDelegate:(id<AppodealRewardedVideoDelegate>)delegateAds];
	[Appodeal setNonSkippableVideoDelegate:(id<AppodealNonSkippableVideoDelegate>)delegateAds];
		
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

//extension methods
void Appodeal_Initialize(lua_State* L) {    
	if (![Appodeal isInitalized])	{
		//parse params from Lua state (key, adType)
		const char *key_from_lua = luaL_checkstring(L, 1);	
		int adType = luaL_checkint(L, 2);   
		
		//convert char to NSString
		NSString* key = [NSString stringWithUTF8String:key_from_lua]; 

		//Init appodeal SDK
		
		[Appodeal setPluginVersion:@"2.1.0"];
    	[Appodeal setFramework:APDFrameworkDefold];
		[Appodeal initializeWithApiKey:key types: (AppodealAdType)apdAdTypes(adType)];	
	}
}

bool Appodeal_Show(lua_State* L) {
	BOOL status;
	int showStyle = luaL_checkint(L, 1);
   	status = [Appodeal showAd:(AppodealShowStyle)apdShowStyle(showStyle) rootViewController:[UIApplication sharedApplication].keyWindow.rootViewController];
	return status == YES;
}

bool Appodeal_ShowWithPlacement(lua_State* L) {
	BOOL status = false;
	int showStyle = luaL_checkint(L, 1);
	const char *placement_name = luaL_checkstring(L, 2);	
	NSString* placement = [NSString stringWithUTF8String:placement_name];
	if ([placement length] > 0)
		status = [Appodeal showAd:(AppodealShowStyle)apdShowStyle(showStyle) forPlacement:placement rootViewController:[UIApplication sharedApplication].keyWindow.rootViewController];
	else
   	 	status = [Appodeal showAd:(AppodealShowStyle)apdShowStyle(showStyle) rootViewController:[UIApplication sharedApplication].keyWindow.rootViewController];
	return status == YES;
}

bool Appodeal_CanShow(lua_State* L) {
	BOOL status = false;
	int showStyle = luaL_checkint(L, 1);
   	status = [Appodeal canShowAd:(AppodealShowStyle)apdShowStyle(showStyle) forPlacement:@""];
   	return status == YES;
}

bool Appodeal_CanShowWithPlacement(lua_State* L) {
	BOOL status = false;
	int showStyle = luaL_checkint(L, 1);
	const char *placement_name = luaL_checkstring(L, 2);	
	NSString* placement = [NSString stringWithUTF8String:placement_name];
	if ([placement length] > 0)
		status = [Appodeal canShowAd:(AppodealShowStyle)apdShowStyle(showStyle) forPlacement:placement];
	else
   	 	status = [Appodeal canShowAd:(AppodealShowStyle)apdShowStyle(showStyle) forPlacement:@""];
   	return status == YES; 	
}

void Appodeal_Hide(lua_State* L) {
	[Appodeal hideBanner];
}

void Appodeal_DisableNetwork(lua_State* L) {
	const char *network = luaL_checkstring(L, 1);
	NSString* network_name = [NSString stringWithUTF8String:network];
	[Appodeal disableNetworkForAdType:AppodealAdTypeInterstitial name: network_name];
	[Appodeal disableNetworkForAdType:AppodealAdTypeBanner name: network_name];
	[Appodeal disableNetworkForAdType:AppodealAdTypeRewardedVideo name: network_name];
	[Appodeal disableNetworkForAdType:AppodealAdTypeNonSkippableVideo name: network_name];
}

void Appodeal_DisableNetworkForAdType(lua_State* L) {
	const char *network = luaL_checkstring(L, 1);
	int adType = luaL_checkint(L, 2);
	NSString* network_name = [NSString stringWithUTF8String:network];
	[Appodeal disableNetworkForAdType:(AppodealAdType)apdAdTypes(adType) name: network_name];
}

void Appodeal_DisableLocationTracking(lua_State* L) {
    [Appodeal setLocationTracking:get_lua_bool(L, 1)];
}

void Appodeal_SetAutoCache(lua_State* L) {
	int adType = luaL_checkint(L, 2);
	[Appodeal setAutocache:get_lua_bool(L, 1) types:(AppodealAdType)apdAdTypes(adType)];
}

void Appodeal_Cache(lua_State* L) {
	int adType = luaL_checkint(L, 1);
	[Appodeal cacheAd:(AppodealAdType)apdAdTypes(adType)];
}

void Appodeal_SetLogging(lua_State* L) {
	[Appodeal setDebugEnabled:get_lua_bool(L, 1)];
}

void Appodeal_SetTesting(lua_State* L) {
	[Appodeal setTestingEnabled:get_lua_bool(L, 1)];
}

void Appodeal_SetCustomIntRule(lua_State* L) {
	const char *rule_name_lua = luaL_checkstring(L, 1);
	int rule_int = luaL_checkint(L, 2);
	NSString* rule_name = [NSString stringWithUTF8String:rule_name_lua];
    NSDictionary *dict = @{
                               rule_name : [NSNumber numberWithInt:rule_int]};
    [Appodeal setCustomRule:dict];
}

void Appodeal_SetCustomBoolRule(lua_State* L) {
	const char *rule_name_lua = luaL_checkstring(L, 1);
	BOOL rule_bool = NO;
	NSString* rule_name = [NSString stringWithUTF8String:rule_name_lua];
    NSDictionary *dict = @{
                               rule_name : [NSNumber numberWithBool:get_lua_bool(L, 2)]};
    [Appodeal setCustomRule:dict];
}

void Appodeal_SetCustomDoubleRule(lua_State* L) {
	const char *rule_name_lua = luaL_checkstring(L, 1);
	double rule_double = luaL_checknumber(L, 2);
	NSString* rule_name = [NSString stringWithUTF8String:rule_name_lua];
    NSDictionary *dict = @{
                               rule_name : [NSNumber numberWithDouble:rule_double]};
    [Appodeal setCustomRule:dict];
}

void Appodeal_SetCustomStringRule(lua_State* L) {
	const char *rule_name_lua = luaL_checkstring(L, 1);
	const char *rule_lua = luaL_checkstring(L, 2);
	NSString* rule_name = [NSString stringWithUTF8String:rule_name_lua];
	NSString* rule_string = [NSString stringWithUTF8String:rule_lua];
    NSDictionary *dict = @{
                               rule_name : rule_string};
    [Appodeal setCustomRule:dict];
}

bool Appodeal_IsLoaded(lua_State* L) {
	int showStyle = luaL_checkint(L, 1);
	BOOL status = [Appodeal isReadyForShowWithStyle:(AppodealShowStyle)apdShowStyle(showStyle)];
	return status ? 1 : 0;
}

void Appodeal_SetSmartBanners(lua_State* L) {
	[Appodeal setSmartBannersEnabled:get_lua_bool(L, 1)];
}

void Appodeal_SetBannerBackground(lua_State* L) {
	[Appodeal setBannerBackgroundVisible:get_lua_bool(L, 1)];
}

void Appodeal_SetBannerAnimation(lua_State* L) {
	[Appodeal setBannerAnimationEnabled:get_lua_bool(L, 1)];
}

void Appodeal_SetUserId(lua_State* L) {
	const char *user_id = luaL_checkstring(L, 1);
	NSString* user_id_string = [NSString stringWithUTF8String:user_id];
	[Appodeal setUserId:user_id_string];
}

void Appodeal_SetUserAge(lua_State* L) {
	int user_age = luaL_checkint(L, 1);
	[Appodeal setUserAge:user_age];
}

void Appodeal_SetUserGender(lua_State* L) {
	int gender = luaL_checkint(L, 1);
	
	switch(gender)
    {
    	 case 0:
    	 	[Appodeal setUserGender:AppodealUserGenderOther];
    	 	break;
    	 case 1:
    	 	[Appodeal setUserGender:AppodealUserGenderFemale];
    	 	break;
    	 case 2:
    	 	[Appodeal setUserGender:AppodealUserGenderMale]; 
    	 	break;
    	 default: 
    	 	break;
    }
}

#endif
