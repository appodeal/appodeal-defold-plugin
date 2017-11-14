#define EXTENSION_NAME Appodeal
#define LIB_NAME "Appodeal"
#define MODULE_NAME "appodeal"

#define DLIB_LOG_DOMAIN LIB_NAME
#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID)
#include "appodeal.h"

AppodealListener g_appodealListener;

static int setCallback(lua_State* L) {
    g_appodealListener.set(L, 1);
    Appodeal_SetCallback(&g_appodealListener);
    return 0;
}

static int isSupported(lua_State* L) {
    bool status = true;
    lua_pushboolean(L, status);
    return 1;
}

//common Appodeal SDK methods
static int initialize(lua_State* L) {
    Appodeal_Initialize(L);
    return 0;
}

static int show(lua_State* L) {
    bool status = Appodeal_Show(L);
    lua_pushboolean(L, status);
    return 1;
}

static int showWithPlacement(lua_State* L) {
	bool status = Appodeal_ShowWithPlacement(L);
    lua_pushboolean(L, status);
    return 1;
}

static int isLoaded(lua_State* L) {
    bool status = Appodeal_IsLoaded(L);
	lua_pushboolean(L, status);
	return 1;
}

static int cache(lua_State* L) {
	Appodeal_Cache(L);
	return 0;
}

static int hide(lua_State* L) {
    Appodeal_Hide(L);
    return 0;
}

static int setAutoCache(lua_State* L) {
    Appodeal_SetAutoCache(L);
    return 0;
}

static int isPrecache(lua_State* L) {
  	bool status = Appodeal_IsPrecache(L);
	lua_pushboolean(L, status);
	return 1;
}

static int setSmartBanners(lua_State* L) {
    Appodeal_SetSmartBanners(L);
    return 0;
}

static int setBannerBackground(lua_State* L) {
    Appodeal_SetBannerBackground(L);
    return 0;
}

static int setBannerAnimation(lua_State* L) {
    Appodeal_SetBannerAnimation(L);
    return 0;
}

static int setTabletBanners(lua_State* L) {
    Appodeal_SetTabletBanners(L);
    return 0;
}

static int setLogLevel(lua_State* L) {
    Appodeal_SetLogLevel(L);
    return 0;
}

static int setTesting(lua_State* L) {
    Appodeal_SetTesting(L);
    return 0;
}

static int setChildDirectedTreatment(lua_State* L) {
    Appodeal_SetChildDirectedTreatment(L);
    return 0;
}

static int setTriggerOnLoadedOnPrecache(lua_State* L) {
    Appodeal_SetTriggerOnLoadedOnPrecache(L);
    return 0;
}

static int disableNetwork(lua_State* L) {
    Appodeal_DisableNetwork(L);
    return 0;
}

static int disableNetworkForAdType(lua_State* L) {
    Appodeal_DisableNetworkForAdType(L);
    return 0;
}

static int disableLocationPermissionCheck(lua_State* L) {
    Appodeal_DisableLocationPermissionCheck(L);
    return 0;
}

static int disableWriteExternalStoragePermissionCheck(lua_State* L) {
    Appodeal_DisableWriteExternalStoragePermissionCheck(L);
    return 0;
}

static int requestAndroidMPermissions(lua_State* L) {
    Appodeal_RequestAndroidMPermissions(L);
    return 0;
}

static int muteVideosIfCallsMuted(lua_State* L) {
    Appodeal_MuteVideosIfCallsMuted(L);
    return 0;
}

static int showTestScreen(lua_State* L) {
    Appodeal_ShowTestScreen(L);
    return 0;
}

static int getNativeSDKVersion(lua_State* L) {
    const char *version = Appodeal_GetNativeSDKVersion(L);
    lua_pushstring(L, version);
    return 1;
}

//custom rules

static int canShow(lua_State* L) {
    bool status = Appodeal_CanShow(L);
	lua_pushboolean(L, status);
	return 1;
}

static int canShowWithPlacement(lua_State* L) {
    bool status = Appodeal_CanShowWithPlacement(L);
	lua_pushboolean(L, status);
	return 1;
}

static int setCustomIntRule(lua_State* L) {
    Appodeal_SetCustomIntRule(L);
    return 0;
}

static int setCustomBoolRule(lua_State* L) {
    Appodeal_SetCustomBoolRule(L);
    return 0;
}

static int setCustomDoubleRule(lua_State* L) {
    Appodeal_SetCustomDoubleRule(L);
    return 0;
}

static int setCustomStringRule(lua_State* L) {
    Appodeal_SetCustomStringRule(L);
    return 0;
}

static int trackInAppPurchase(lua_State* L) {
    Appodeal_TrackInAppPurchase(L);
    return 0;
}

static int getRewardName(lua_State* L) {
    const char *name = Appodeal_GetRewardName(L);
    lua_pushstring(L, name);
    return 1;
}

static int getRewardAmount(lua_State* L) {
    double amount = Appodeal_GetRewardAmount(L);
    lua_pushnumber(L, amount);
    return 0;
}

static int getRewardNameForPlacement(lua_State* L) {
    const char *name = Appodeal_GetRewardNameForPlacement(L);
    lua_pushstring(L, name);
    return 1;
}

static int getRewardAmountForPlacement(lua_State* L) {
    double amount = Appodeal_GetRewardAmountForPlacement(L);
    lua_pushnumber(L, amount);
    return 0;
}


//endof custom rules

//user settings

static int setUserId(lua_State* L) {
    Appodeal_SetUserId(L);
    return 0;
}

static int setUserAge(lua_State* L) {
    Appodeal_SetUserAge(L);
    return 0;
}

static int setUserGender(lua_State* L) {
    Appodeal_SetUserGender(L);
    return 0;
}

static const luaL_reg Module_methods[] = {
    {"setCallback", setCallback},
    {"isSupported", isSupported},
    {"initialize", initialize},
    {"show", show},
    {"showWithPlacement", showWithPlacement},
    {"isLoaded", isLoaded},
    {"cache", cache},
    {"hide", hide},
    {"setAutoCache", setAutoCache},
    {"isPrecache", isPrecache},
    {"setSmartBanners", setSmartBanners},
    {"setBannerBackground", setBannerBackground},
    {"setBannerAnimation", setBannerAnimation},
    {"setTabletBanners", setTabletBanners},
    {"setLogLevel", setLogLevel},
    {"setTesting", setTesting},
    {"setChildDirectedTreatment", setChildDirectedTreatment},
    {"setTriggerOnLoadedOnPrecache", setTriggerOnLoadedOnPrecache},
    {"disableNetwork", disableNetwork},
    {"disableNetworkForAdType", disableNetworkForAdType},
    {"disableLocationPermissionCheck", disableLocationPermissionCheck},
    {"disableWriteExternalStoragePermissionCheck", disableWriteExternalStoragePermissionCheck},
    {"requestAndroidMPermissions", requestAndroidMPermissions},
    {"muteVideosIfCallsMuted", muteVideosIfCallsMuted},
    {"showTestScreen", showTestScreen},
    {"getNativeSDKVersion", getNativeSDKVersion},
    {"canShow", canShow},
    {"canShowWithPlacement", canShowWithPlacement},
    {"setCustomIntRule", setCustomIntRule},
    {"setCustomBoolRule", setCustomBoolRule},
    {"setCustomDoubleRule", setCustomDoubleRule},
    {"setCustomStringRule", setCustomStringRule},
    {"trackInAppPurchase", trackInAppPurchase},
    {"getRewardName", getRewardName},
    {"getRewardAmount", getRewardAmount},
    {"getRewardNameForPlacement", getRewardNameForPlacement},
    {"getRewardAmountForPlacement", getRewardAmountForPlacement},
    {"setUserId", setUserId},
    {"setUserAge", setUserAge},
    {"setUserGender", setUserGender},
    {0, 0}
};

static void LuaInit(lua_State* L) {

    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);

    #define SETCONSTANT(name) \
    lua_pushnumber(L, (lua_Number) name); \
    lua_setfield(L, -2, #name);\

    SETCONSTANT(BANNER_LOADED)
    SETCONSTANT(BANNER_FAILED_TO_LOAD)
    SETCONSTANT(BANNER_SHOWN)
    SETCONSTANT(BANNER_CLICKED)

    SETCONSTANT(INTERSTITIAL_LOADED)
    SETCONSTANT(INTERSTITIAL_FAILED_TO_LOAD)
    SETCONSTANT(INTERSTITIAL_SHOWN)
    SETCONSTANT(INTERSTITIAL_CLOSED)
    SETCONSTANT(INTERSTITIAL_CLICKED)

    SETCONSTANT(REWARDED_VIDEO_LOADED)
    SETCONSTANT(REWARDED_VIDEO_FAILED_TO_LOAD)
    SETCONSTANT(REWARDED_VIDEO_SHOWN)
    SETCONSTANT(REWARDED_VIDEO_FISNIHED)
    SETCONSTANT(REWARDED_VIDEO_CLOSED)

    SETCONSTANT(NON_SKIPPABLE_VIDEO_LOADED)
    SETCONSTANT(NON_SKIPPABLE_VIDEO_FAILED_TO_LOAD)
    SETCONSTANT(NON_SKIPPABLE_VIDEO_SHOWN)
    SETCONSTANT(NON_SKIPPABLE_VIDEO_FISNIHED)
    SETCONSTANT(NON_SKIPPABLE_VIDEO_CLOSED)

    SETCONSTANT(LOG_LEVEL_NONE)
    SETCONSTANT(LOG_LEVEL_DEBUG)
    SETCONSTANT(LOG_LEVEL_VERBOSE)

    SETCONSTANT(GENDER_OTHER)
    SETCONSTANT(GENDER_FEMALE)
    SETCONSTANT(GENDER_MALE)

    SETCONSTANT(INTERSTITIAL)
    SETCONSTANT(BANNER)
    SETCONSTANT(BANNER_BOTTOM)
    SETCONSTANT(BANNER_TOP)
    SETCONSTANT(REWARDED_VIDEO)
    SETCONSTANT(NON_SKIPPABLE_VIDEO)

    #undef SETCONSTANT
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

dmExtension::Result AppInitializeAppodeal(dmExtension::AppParams* params) {
    return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeAppodeal(dmExtension::Params* params) {
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeAppodeal(dmExtension::AppParams* params) {
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeAppodeal(dmExtension::Params* params) {
    return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateAppodeal(dmExtension::Params* params) {
    return dmExtension::RESULT_OK;
}

#else // unsupported platforms

static int setCallback(lua_State* L) { return 0; }
static int isSupported(lua_State* L) { 
	lua_pushboolean(L, false);
    return 1;
}
//common Appodeal SDK methods
static int initialize(lua_State* L) { return 0; }
static int show(lua_State* L) {
    lua_pushboolean(L, false);
    return 1;
}
static int showWithPlacement(lua_State* L) {
	lua_pushboolean(L, false);
    return 1; 
}
static int isLoaded(lua_State* L) {
 	lua_pushboolean(L, false);
	return 1;
}
static int сache(lua_State* L) { return 0; }
static int hide(lua_State* L) { return 0; }
static int setAutoCache(lua_State* L) { return 0; }
static int isPrecache(lua_State* L) {
	lua_pushboolean(L, false);
	return 1;
}
static int setSmartBanners(lua_State* L) { return 0; }
static int setBannerBackground(lua_State* L) { return 0; }
static int setBannerAnimation(lua_State* L) { return 0; }
static int setTabletBanners(lua_State* L) { return 0; }
static int setLogLevel(lua_State* L) { return 0; }
static int setTesting(lua_State* L) { return 0; }
static int setChildDirectedTreatment(lua_State* L) { return 0; }
static int setTriggerOnLoadedOnPrecache(lua_State* L) { return 0; }
static int disableNetwork(lua_State* L) { return 0; }
static int disableNetworkForAdType(lua_State* L) { return 0; }
static int disableLocationPermissionCheck(lua_State* L) { return 0; }
static int disableWriteExternalStoragePermissionCheck(lua_State* L) { return 0; }
static int requestAndroidMPermissions(lua_State* L) { return 0; }
static int muteVideosIfCallsMuted(lua_State* L) { return 0; }
static int showTestScreen(lua_State* L) { return 0; }
static int getNativeSDKVersion(lua_State* L) {
    lua_pushstring(L, "0.0.0");
    return 1;
}
static int canShow(lua_State* L) {
    lua_pushboolean(L, false);
	return 1;
}
static int canShowWithPlacement(lua_State* L) {
    lua_pushboolean(L, false);
	return 1;
}
static int setCustomIntRule(lua_State* L) { return 0; }
static int setCustomBoolRule(lua_State* L) { return 0; }
static int setCustomDoubleRule(lua_State* L) { return 0; }
static int setCustomStringRule(lua_State* L) { return 0; }
static int trackInAppPurchase(lua_State* L) { return 0; }
static int getRewardName(lua_State* L) {
    lua_pushstring(L, "");
    return 1;
}
static int getRewardAmount(lua_State* L) {
    lua_pushnumber(L, 0);
    return 0;
}
static int getRewardNameForPlacement(lua_State* L) {
    lua_pushstring(L, "");
    return 1;
}
static int getRewardAmountForPlacement(lua_State* L) {
    lua_pushnumber(L, 0);
    return 0;
}
//user settings
static int setUserId(lua_State* L) { return 0; }
static int setUserAge(lua_State* L) { return 0; }
static int setUserGender(lua_State* L) { return 0; }

static const luaL_reg Module_methods[] = {
    {"setCallback", setCallback},
    {"isSupported", isSupported},
    {"initialize", initialize},
    {"show", show},
    {"showWithPlacement", showWithPlacement},
    {"isLoaded", isLoaded},
    {"cache", сache},
    {"hide", hide},
    {"setAutoCache", setAutoCache},
    {"isPrecache", isPrecache},
    {"setSmartBanners", setSmartBanners},
    {"setBannerBackground", setBannerBackground},
    {"setBannerAnimation", setBannerAnimation},
    {"setTabletBanners", setTabletBanners},
    {"setLogLevel", setLogLevel},
    {"setTesting", setTesting},
    {"setChildDirectedTreatment", setChildDirectedTreatment},
    {"setTriggerOnLoadedOnPrecache", setTriggerOnLoadedOnPrecache},
    {"disableNetwork", disableNetwork},
    {"disableNetworkForAdType", disableNetworkForAdType},
    {"disableLocationPermissionCheck", disableLocationPermissionCheck},
    {"disableWriteExternalStoragePermissionCheck", disableWriteExternalStoragePermissionCheck},
    {"requestAndroidMPermissions", requestAndroidMPermissions},
    {"muteVideosIfCallsMuted", muteVideosIfCallsMuted},
    {"showTestScreen", showTestScreen},
    {"getNativeSDKVersion", getNativeSDKVersion},
    {"canShow", canShow},
    {"canShowWithPlacement", canShowWithPlacement},
    {"setCustomIntRule", setCustomIntRule},
    {"setCustomBoolRule", setCustomBoolRule},
    {"setCustomDoubleRule", setCustomDoubleRule},
    {"setCustomStringRule", setCustomStringRule},
    {"trackInAppPurchase", trackInAppPurchase},
    {"getRewardName", getRewardName},
    {"getRewardAmount", getRewardAmount},
    {"getRewardNameForPlacement", getRewardNameForPlacement},
    {"getRewardAmountForPlacement", getRewardAmountForPlacement},
    {"setUserId", setUserId},
    {"setUserAge", setUserAge},
    {"setUserGender", setUserGender},
    {0, 0}
};

static void LuaInit(lua_State* L) {
  int top = lua_gettop(L);
  luaL_register(L, MODULE_NAME, Module_methods);
  lua_pop(L, 1);
  assert(top == lua_gettop(L));
}

dmExtension::Result AppInitializeAppodeal(dmExtension::AppParams* params) {
    return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeAppodeal(dmExtension::Params* params) {
    LuaInit(params->m_L);
    printf("Registered %s Extension\n", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeAppodeal(dmExtension::AppParams* params) {
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeAppodeal(dmExtension::Params* params) {
    return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateAppodeal(dmExtension::Params* params) {
    return dmExtension::RESULT_OK;
}

#endif //Platforms


DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeAppodeal, AppFinalizeAppodeal, InitializeAppodeal, UpdateAppodeal, 0, FinalizeAppodeal)
