#pragma once

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_IOS)

//utils
extern void Appodeal_Listen(lua_State* L);

//Appodeal Main Methods
extern void Appodeal_Initialize(lua_State* L);
extern bool Appodeal_Show(lua_State* L);
extern bool Appodeal_ShowWithPlacement(lua_State* L);
extern bool Appodeal_IsLoaded(lua_State* L);
extern void Appodeal_Cache(lua_State* L);
extern void Appodeal_Hide(lua_State* L);
extern void Appodeal_SetAutoCache(lua_State* L);
extern bool Appodeal_IsPrecache(lua_State* L);

extern void Appodeal_SetBannerAnimation(lua_State* L);
extern void Appodeal_SetSmartBanners(lua_State* L);
extern void Appodeal_SetBannerBackground(lua_State* L);
extern void Appodeal_SetTabletBanners(lua_State* L);
extern void Appodeal_SetLogLevel(lua_State* L);
extern void Appodeal_SetTesting(lua_State* L);
extern void Appodeal_SetChildDirectedTreatment(lua_State* L);
extern void Appodeal_SetTriggerOnLoadedOnPrecache(lua_State* L);
extern void Appodeal_DisableNetwork(lua_State* L);
extern void Appodeal_DisableNetworkForAdType(lua_State* L);
extern void Appodeal_DisableLocationPermissionCheck(lua_State* L);
extern void Appodeal_DisableWriteExternalStoragePermissionCheck(lua_State* L);
extern void Appodeal_RequestAndroidMPermissions(lua_State* L);
extern void Appodeal_MuteVideosIfCallsMuted(lua_State* L);
extern void Appodeal_ShowTestScreen(lua_State* L);
extern char const* Appodeal_GetNativeSDKVersion(lua_State* L);

extern bool Appodeal_CanShow(lua_State* L);
extern bool Appodeal_CanShowWithPlacement(lua_State* L);
extern void Appodeal_SetCustomIntRule(lua_State* L);
extern void Appodeal_SetCustomBoolRule(lua_State* L);
extern void Appodeal_SetCustomDoubleRule(lua_State* L);
extern void Appodeal_SetCustomStringRule(lua_State* L);
extern void Appodeal_TrackInAppPurchase(lua_State* L);
extern char const* Appodeal_GetRewardName(lua_State* L);
extern int Appodeal_GetRewardAmount(lua_State* L);
extern char const* Appodeal_GetRewardNameForPlacement(lua_State* L);
extern int Appodeal_GetRewardAmountForPlacement(lua_State* L);

extern void Appodeal_SetUserId(lua_State* L);
extern void Appodeal_SetUserAge(lua_State* L);
extern void Appodeal_SetUserGender(lua_State* L);

#endif
