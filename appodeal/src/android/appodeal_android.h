#pragma once
#if defined(DM_PLATFORM_ANDROID)

extern int GENDER_OTHER       = 0;
extern int GENDER_FEMALE      = 1;
extern int GENDER_MALE        = 2;

extern int INTERSTITIAL        = 3;
extern int BANNER              = 4;
extern int BANNER_BOTTOM       = 8;
extern int BANNER_TOP          = 16;
extern int REWARDED_VIDEO      = 128;
extern int NON_SKIPPABLE_VIDEO = 256;

//utils
extern void Appodeal_Listen(lua_State* L);

//Appodeal Main Methods
extern void Appodeal_Initialize(lua_State* L);
extern bool Appodeal_Show(lua_State* L);
extern bool Appodeal_ShowWithPlacement(lua_State* L);
extern void Appodeal_Hide(lua_State* L);
extern void Appodeal_DisableNetwork(lua_State* L);
extern void Appodeal_DisableNetworkForAdType(lua_State* L);
extern void Appodeal_Cache(lua_State* L);
extern bool Appodeal_IsLoaded(lua_State* L);
extern bool Appodeal_CanShow(lua_State* L);
extern bool Appodeal_CanShowWithPlacement(lua_State* L);

//Appodeal Settings Methods
extern void Appodeal_SetAutoCache(lua_State* L);
extern void Appodeal_SetSmartBanners(lua_State* L);
extern void Appodeal_SetBannerBackground(lua_State* L);
extern void Appodeal_SetBannerAnimation(lua_State* L);
extern void Appodeal_SetLogging(lua_State* L);
extern void Appodeal_SetTesting(lua_State* L);
extern void Appodeal_MuteVideosIfCallsMuted(lua_State* L);
extern char const* Appodeal_GetNativeSDKVersion(lua_State* L);

//Appodeal Additional Methods
extern void Appodeal_SetCustomIntRule(lua_State* L);
extern void Appodeal_SetCustomBoolRule(lua_State* L);
extern void Appodeal_SetCustomDoubleRule(lua_State* L);
extern void Appodeal_SetCustomStringRule(lua_State* L);

//Appodeal User Settings
extern void Appodeal_SetUserId(lua_State* L);
extern void Appodeal_SetUserAge(lua_State* L);
extern void Appodeal_SetUserGender(lua_State* L);

#endif
