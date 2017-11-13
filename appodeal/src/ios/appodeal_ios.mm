#if defined(DM_PLATFORM_IOS)

#include "../appodeal.h"

#include <AVFoundation/AVFoundation.h>
#include <UIKit/UIKit.h>

#import <Appodeal/Appodeal.h>

static AppodealListener *g_appodealListener;

@interface AppodealAdsDelegate : NSObject <AppodealBannerDelegate, AppodealInterstitialDelegate, AppodealRewardedVideoDelegate, AppodealNonSkippableVideoDelegate>
@end

@interface AppodealAdsDelegate ()
@end

@implementation AppodealAdsDelegate

//banner callbacks
- (void)bannerDidLoadAdIsPrecache:(BOOL)precache { 
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)BANNER_LOADED); 
}
- (void)bannerDidFailToLoadAd { 
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)BANNER_FAILED_TO_LOAD);
}
- (void)bannerDidClick { 
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)BANNER_CLICKED);
}
- (void)bannerDidShow {	
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)BANNER_SHOWN);
}

//interstitial callbacks
- (void)interstitialDidLoadAdisPrecache:(BOOL)precache { 
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)INTERSTITIAL_LOADED);
}
- (void)interstitialDidFailToLoadAd { 
    if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)INTERSTITIAL_FAILED_TO_LOAD);
}
- (void)interstitialWillPresent { 
    if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)INTERSTITIAL_SHOWN);
}
- (void)interstitialDidDismiss { 
    if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)INTERSTITIAL_CLOSED);
}
- (void)interstitialDidClick { 
    if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)INTERSTITIAL_CLICKED);
}

//rewarded video callbacks
- (void)rewardedVideoDidLoadAd {
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)REWARDED_VIDEO_LOADED);
}
- (void)rewardedVideoDidFailToLoadAd {
    if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)REWARDED_VIDEO_FAILED_TO_LOAD);
}
- (void)rewardedVideoDidPresent {
    if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)REWARDED_VIDEO_SHOWN);
}
- (void)rewardedVideoWillDismiss {
    if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)REWARDED_VIDEO_CLOSED);
}
- (void)rewardedVideoDidFinish:(NSUInteger)rewardAmount name:(NSString *)rewardName {
    if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)REWARDED_VIDEO_FISNIHED);
}

//non skippable video callbacks
- (void)nonSkippableVideoDidLoadAd {
    if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)NON_SKIPPABLE_VIDEO_LOADED);
}
- (void)nonSkippableVideoDidFailToLoadAd {
    if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)NON_SKIPPABLE_VIDEO_FAILED_TO_LOAD);
}
- (void)nonSkippableVideoDidPresent {
    if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)NON_SKIPPABLE_VIDEO_SHOWN);
}
- (void)nonSkippableVideoWillDismiss {
    if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)NON_SKIPPABLE_VIDEO_CLOSED);
}
- (void)nonSkippableVideoDidFinish {
    if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)NON_SKIPPABLE_VIDEO_FISNIHED);
}

@end

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
	if (lua_isboolean(L, index)) {
        if (lua_toboolean(L, index) == 1) {
        	return YES;
        } else {
        	return NO;
        }
    } else {
        return NO;
	}
}

UIViewController *uiViewController;

void Appodeal_Initialize(lua_State* L) {    
	const char *key_from_lua = luaL_checkstring(L, 1);	
	NSString* key = [NSString stringWithUTF8String:key_from_lua]; 
	int adType = luaL_checkint(L, 2);   
		
	[Appodeal setPluginVersion:@"2.1.7"];
	[Appodeal setFramework:APDFrameworkDefold];
	[Appodeal initializeWithApiKey:key types: (AppodealAdType)apdAdTypes(adType)];

	AppodealAdsDelegate * delegateAds = [[AppodealAdsDelegate alloc] init];
	[Appodeal setBannerDelegate:(id<AppodealBannerDelegate>)delegateAds];
	[Appodeal setInterstitialDelegate:(id<AppodealInterstitialDelegate>)delegateAds];
	[Appodeal setRewardedVideoDelegate:(id<AppodealRewardedVideoDelegate>)delegateAds];
	[Appodeal setNonSkippableVideoDelegate:(id<AppodealNonSkippableVideoDelegate>)delegateAds];

	UIWindow* window = dmGraphics::GetNativeiOSUIWindow();
	uiViewController = window.rootViewController;
}

void Appodeal_SetCallback(AppodealListener *appodealListener) {
   g_appodealListener = appodealListener;
}

bool Appodeal_Show(lua_State* L) {
	BOOL status;
	int showStyle = luaL_checkint(L, 1);
   	status = [Appodeal showAd:(AppodealShowStyle)apdShowStyle(showStyle) rootViewController:[[UIApplication sharedApplication] keyWindow].rootViewController];
	return status == YES;
}

bool Appodeal_ShowWithPlacement(lua_State* L) {
	BOOL status = false;
	int showStyle = luaL_checkint(L, 1);
	const char *placement_name = luaL_checkstring(L, 2);	
	NSString* placement = [NSString stringWithUTF8String:placement_name];
	if ([placement length] > 0) {
		status = [Appodeal showAd:(AppodealShowStyle)apdShowStyle(showStyle) forPlacement:placement rootViewController:uiViewController];
	} else {
   	 	status = [Appodeal showAd:(AppodealShowStyle)apdShowStyle(showStyle) rootViewController:uiViewController];
	}
	return status == YES;
}

bool Appodeal_IsLoaded(lua_State* L) {
	int showStyle = luaL_checkint(L, 1);
	BOOL status = [Appodeal isReadyForShowWithStyle:(AppodealShowStyle)apdShowStyle(showStyle)];
	return status ? 1 : 0;
}

void Appodeal_Cache(lua_State* L) {
	int adType = luaL_checkint(L, 1);
	[Appodeal cacheAd:(AppodealAdType)apdAdTypes(adType)];
}

void Appodeal_Hide(lua_State* L) {
	[Appodeal hideBanner];
}

void Appodeal_SetAutoCache(lua_State* L) {
	int adType = luaL_checkint(L, 1);
	[Appodeal setAutocache:get_lua_bool(L, 2) types:(AppodealAdType)apdAdTypes(adType)];
}

bool Appodeal_IsPrecache(lua_State* L) {
	return false;
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

void Appodeal_SetTabletBanners(lua_State* L) {
	// handled by OS, supported by Android SDK only
}

void Appodeal_SetLogLevel(lua_State* L) {
	int logLevel = luaL_checkint(L, 1);
	switch(logLevel) {
    	case 0:
            [Appodeal setLogLevel:APDLogLevelOff];
            break;
        case 1:
            [Appodeal setLogLevel:APDLogLevelDebug];
            break;
        case 2:
            [Appodeal setLogLevel:APDLogLevelVerbose];
            break;
        default:
            [Appodeal setLogLevel:APDLogLevelOff];
            break;
    }
}

void Appodeal_SetTesting(lua_State* L) {
	[Appodeal setTestingEnabled:get_lua_bool(L, 1)];
}

void Appodeal_SetChildDirectedTreatment(lua_State* L) {
	[Appodeal setChildDirectedTreatment:get_lua_bool(L, 1)];
}

void Appodeal_SetTriggerOnLoadedOnPrecache(lua_State* L) {
	NSLog(@"not supported by iOS SDK yet");
	// not supported by iOS SDK yet
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

void Appodeal_DisableLocationPermissionCheck(lua_State* L) {
    [Appodeal setLocationTracking:get_lua_bool(L, 1)];
}

void Appodeal_DisableWriteExternalStoragePermissionCheck(lua_State* L) {
    // not supported by OS
}

void Appodeal_RequestAndroidMPermissions(lua_State* L) {
    // not supported by OS
}

void Appodeal_MuteVideosIfCallsMuted(lua_State* L) {
    // not supported by OS
}

void Appodeal_ShowTestScreen(lua_State* L) {
    // not supported by iOS SDK yet
}

char const* Appodeal_GetNativeSDKVersion(lua_State* L) {
    NSString *version = [Appodeal getVersion];
    const char *version_lua = [version UTF8String];
    return version_lua;
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
	float rule_double = luaL_checknumber(L, 2);
	NSString* rule_name = [NSString stringWithUTF8String:rule_name_lua];
    NSDictionary *dict = @{
                               rule_name : [NSNumber numberWithFloat:rule_double]};
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

void Appodeal_TrackInAppPurchase(lua_State* L) {
	int amount_int = luaL_checkint(L, 1);
	NSNumber *amount = [NSNumber numberWithInt:amount_int];
	const char *currency_lua = luaL_checkstring(L, 2);
	NSString* currency = [NSString stringWithUTF8String:currency_lua];
    [[APDSdk sharedSdk] trackInAppPurchase:amount currency:currency];
}

char const* Appodeal_GetRewardName(lua_State* L) {
    NSString *rewardName = [[Appodeal rewardForPlacement:@"default"] currencyName];
    const char *rewardName_lua = [rewardName UTF8String];
    return rewardName_lua;
}

char const* Appodeal_GetRewardNameForPlacement(lua_State* L) {
	NSString *rewardName = NULL;
	const char *placement_name = luaL_checkstring(L, 1);	
	NSString* placement = [NSString stringWithUTF8String:placement_name];
	if ([placement length] > 0) {
		rewardName = [[Appodeal rewardForPlacement:placement] currencyName];
	} else {
   	 	rewardName = [[Appodeal rewardForPlacement:@"default"] currencyName];
	}
    const char *rewardName_lua = [rewardName UTF8String];
    return rewardName_lua;
}

int Appodeal_GetRewardAmount(lua_State* L) {
	NSNumber *rewardAmount = [NSNumber numberWithUnsignedInteger:[[Appodeal rewardForPlacement:@"default"] amount]];
	return [rewardAmount intValue];
}

int Appodeal_GetRewardAmountForPlacement(lua_State* L) {
	NSNumber *rewardAmount = @0;
	const char *placement_name = luaL_checkstring(L, 1);	
	NSString* placement = [NSString stringWithUTF8String:placement_name];
	if ([placement length] > 0) {
		rewardAmount = [NSNumber numberWithUnsignedInteger:[[Appodeal rewardForPlacement:placement] amount]];
	} else {
   	 	rewardAmount = [NSNumber numberWithUnsignedInteger:[[Appodeal rewardForPlacement:@"default"] amount]];
	}
    return [rewardAmount intValue];
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
	
	switch(gender) {
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
