#define EXTENSION_NAME Appodeal
#define LIB_NAME "Appodeal"
#define MODULE_NAME "appodeal"

#define DLIB_LOG_DOMAIN LIB_NAME

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID)

#if defined(DM_PLATFORM_IOS)
#include "ios/appodeal_ios.h"
#elif defined(DM_PLATFORM_ANDROID)
#include "android/appodeal_android.h"
#endif

//custom listener for callbacks
static int Listen(lua_State* L) {
    Appodeal_Listen(L);
    return 0;
}

static int IsSupported(lua_State* L) {
    bool status = true;
    lua_pushboolean(L, status);
    return 1;
}

//common Appodeal SDK methods
static int Initialize(lua_State* L) {
    Appodeal_Initialize(L);
    return 0;
}

static int Show(lua_State* L) {
    bool status = Appodeal_Show(L);
    lua_pushboolean(L, status);
    return 1;
}

static int ShowWithPlacement(lua_State* L) {
	bool status = Appodeal_ShowWithPlacement(L);
    lua_pushboolean(L, status);
    return 1;
}

static int CanShow(lua_State* L) {
    int status = Appodeal_CanShow(L);
	lua_pushboolean(L, status > 0);
	return 1;
}

static int CanShowWithPlacement(lua_State* L) {
    int status = Appodeal_CanShowWithPlacement(L);
	lua_pushboolean(L, status > 0);
	return 1;
}

static int IsLoaded(lua_State* L) {
    int status = Appodeal_IsLoaded(L);
	lua_pushboolean(L, status > 0);
	return 1;
}

static int Hide(lua_State* L) {
    Appodeal_Hide(L);
    return 0;
}

static int Cache(lua_State* L) {
    Appodeal_Cache(L);
    return 0;
}

static int DisableNetwork(lua_State* L) {
    Appodeal_DisableNetwork(L);
    return 0;
}

static int DisableNetworkForAdType(lua_State* L) {
    Appodeal_DisableNetworkForAdType(L);
    return 0;
}

static int SetAutoCache(lua_State* L) {
    Appodeal_SetAutoCache(L);
    return 0;
}

static int SetSmartBanners(lua_State* L) {
    Appodeal_SetSmartBanners(L);
    return 0;
}

static int SetBannerBackground(lua_State* L) {
    Appodeal_SetBannerBackground(L);
    return 0;
}

static int SetBannerAnimation(lua_State* L) {
    Appodeal_SetBannerAnimation(L);
    return 0;
}

static int SetLogging(lua_State* L) {
    Appodeal_SetLogging(L);
    return 0;
}

static int SetTesting(lua_State* L) {
    Appodeal_SetTesting(L);
    return 0;
}

static int GetNativeSDKVersion(lua_State* L) {
    const char *version = Appodeal_GetNativeSDKVersion(L);
    lua_pushstring(L, version);
    return 1;
}

//custom rules

static int SetCustomIntRule(lua_State* L) {
    Appodeal_SetCustomIntRule(L);
    return 0;
}

static int SetCustomBoolRule(lua_State* L) {
    Appodeal_SetCustomBoolRule(L);
    return 0;
}

static int SetCustomDoubleRule(lua_State* L) {
    Appodeal_SetCustomDoubleRule(L);
    return 0;
}

static int SetCustomStringRule(lua_State* L) {
    Appodeal_SetCustomStringRule(L);
    return 0;
}
//endof custom rules

//user settings

static int SetUserId(lua_State* L) {
    Appodeal_SetUserId(L);
    return 0;
}

static int SetUserAge(lua_State* L) {
    Appodeal_SetUserAge(L);
    return 0;
}

static int SetUserGender(lua_State* L) {
    Appodeal_SetUserGender(L);
    return 0;
}

static const luaL_reg Module_methods[] = {
  {"isSupported", IsSupported},
  {"initialize", Initialize},
  {"show", Show},
  {"showWithPlacement", ShowWithPlacement},
  {"listen", Listen},
  {"hide", Hide},
  {"disableNetwork", DisableNetwork},
  {"disableNetworkForAdType", DisableNetworkForAdType},
  {"setAutoCache", SetAutoCache},
  {"cache", Cache},
  {"setLogging", SetLogging},
  {"setTesting", SetTesting},
  {"setCustomIntRule", SetCustomIntRule},
  {"setCustomBoolRule", SetCustomBoolRule},
  {"setCustomDoubleRule", SetCustomDoubleRule},
  {"setCustomStringRule", SetCustomStringRule},
  {"getNativeSDKVersion", GetNativeSDKVersion},
  {"isLoaded", IsLoaded},
  {"setSmartBanners", SetSmartBanners},
  {"setBannerBackground", SetBannerBackground},
  {"setBannerAnimation", SetBannerAnimation},
  {"setUserId", SetUserId},
  {"setUserAge", SetUserAge},
  {"setUserGender", SetUserGender},
  {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);

#define SETCONSTANT(name) \
lua_pushnumber(L, (lua_Number) name); \
lua_setfield(L, -2, #name);\

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
    printf("Registered %s Extension\n", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeAppodeal(dmExtension::AppParams* params) {
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeAppodeal(dmExtension::Params* params) {
    return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateAppodeal(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#else // unsupported platforms

static int IsSupported(lua_State* L) {
    bool status = false;
    lua_pushboolean(L, status);
    return 1;
}

//custom listener for callbacks
static int Listen(lua_State* L) {
    return 0;
}

//common Appodeal SDK methods
static int Initialize(lua_State* L) {
    return 0;
}

static int Show(lua_State* L) {
	bool status = false;
	lua_pushboolean(L, status);
    return 0;
}

static int ShowWithPlacement(lua_State* L) {
	bool status = false;
	lua_pushboolean(L, status);
    return 0;
}

static int CanShow(lua_State* L) {
	bool status = false;
	lua_pushboolean(L, status);
    return 0;
}

static int CanShowWithPlacement(lua_State* L) {
	bool status = false;
	lua_pushboolean(L, status);
    return 0;
}

static int IsLoaded(lua_State* L) {
	bool status = false;
	lua_pushboolean(L, status);
    return 0;
}

static int Hide(lua_State* L) {
    return 0;
}

static int Cache(lua_State* L) {
    return 0;
}

static int DisableNetwork(lua_State* L) {
    return 0;
}

static int DisableNetworkForAdType(lua_State* L) {
    return 0;
}

static int SetAutocache(lua_State* L) {
    return 0;
}

static int SetSmartBanners(lua_State* L) {
    return 0;
}

static int SetBannerBackground(lua_State* L) {
    return 0;
}

static int SetBannerAnimation(lua_State* L) {
    return 0;
}

static int SetLogging(lua_State* L) {
    return 0;
}

static int SetTesting(lua_State* L) {
    return 0;
}

static int GetNativeSDKVersion(lua_State* L) {
	lua_pushstring(L, "0.0.0");
    return 1;
}

//custom rules

static int SetCustomIntRule(lua_State* L) {
    return 0;
}

static int SetCustomBoolRule(lua_State* L) {
    return 0;
}

static int SetCustomDoubleRule(lua_State* L) {
    return 0;
}

static int SetCustomStringRule(lua_State* L) {
    return 0;
}
//endof custom rules

//user settings

static int SetUserId(lua_State* L) {
    return 0;
}

static int SetUserAge(lua_State* L) {
    return 0;
}

static int SetUserGender(lua_State* L) {
    return 0;
}

static const luaL_reg Module_methods[] = {
  {"isSupported", IsSupported},
  {"initialize", Initialize},
  {"show", Show},
  {"showWithPlacement", ShowWithPlacement},
  {"listen", Listen},
  {"hide", Hide},
  {"disableNetwork", DisableNetwork},
  {"disableNetworkForAdType", DisableNetworkForAdType},
  {"setAutoCache", SetAutoCache},
  {"cache", Cache},
  {"setLogging", SetLogging},
  {"setTesting", SetTesting},
  {"setCustomIntRule", SetCustomIntRule},
  {"setCustomBoolRule", SetCustomBoolRule},
  {"setCustomDoubleRule", SetCustomDoubleRule},
  {"setCustomStringRule", SetCustomStringRule},
  {"isLoaded", IsLoaded},
  {"setSmartBanners", SetSmartBanners},
  {"setBannerBackground", SetBannerBackground},
  {"setBannerAnimation", SetBannerAnimation},
  {"setUserId", SetUserId},
  {"setUserAge", SetUserAge},
  {"setUserGender", SetUserGender},
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

static dmExtension::Result UpdateAppodeal(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#endif //Platforms


DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeAppodeal, AppFinalizeAppodeal, InitializeAppodeal, UpdateAppodeal, 0, FinalizeAppodeal)