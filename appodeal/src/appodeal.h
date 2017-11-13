#pragma once

#include <dmsdk/sdk.h>

enum {
    INTERSTITIAL        = 3,
    BANNER              = 4,
    BANNER_BOTTOM       = 8,
    BANNER_TOP          = 16,
    REWARDED_VIDEO      = 128,
    NON_SKIPPABLE_VIDEO = 256
};

enum {
    LOG_LEVEL_NONE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_VERBOSE
};

enum {
    GENDER_OTHER,
    GENDER_FEMALE,
    GENDER_MALE
};

enum {
    BANNER_LOADED,
    BANNER_FAILED_TO_LOAD,
    BANNER_SHOWN,
    BANNER_CLICKED,

    INTERSTITIAL_LOADED,
    INTERSTITIAL_FAILED_TO_LOAD,
    INTERSTITIAL_SHOWN,
    INTERSTITIAL_CLOSED,
    INTERSTITIAL_CLICKED,

    REWARDED_VIDEO_LOADED,
    REWARDED_VIDEO_FAILED_TO_LOAD,
    REWARDED_VIDEO_SHOWN,
    REWARDED_VIDEO_FISNIHED,
    REWARDED_VIDEO_CLOSED,

    NON_SKIPPABLE_VIDEO_LOADED,
    NON_SKIPPABLE_VIDEO_FAILED_TO_LOAD,
    NON_SKIPPABLE_VIDEO_SHOWN,
    NON_SKIPPABLE_VIDEO_FISNIHED,
    NON_SKIPPABLE_VIDEO_CLOSED
};

class AppodealListener {
public:
   AppodealListener() :
         m_L (NULL),
         m_Callback(LUA_NOREF),
         m_Self(LUA_NOREF) {
   }
   
   void set(lua_State *L, int paramIdx) {
      if (!lua_isfunction(L, paramIdx)) {
         dmLogError("Enhance: parameter %d is not a Lua function\n", paramIdx);
      }
      else {         
         lua_pushvalue(L, paramIdx);
         int cb = dmScript::Ref(L, LUA_REGISTRYINDEX);
         
         unset();
         
         m_L = dmScript::GetMainThread(L);
         m_Callback = cb;
         dmScript::GetInstance(L);
         m_Self = dmScript::Ref(L, LUA_REGISTRYINDEX);
      }
   }
   
   void unset() {
      if (m_Callback != LUA_NOREF) {
         dmScript::Unref(m_L, LUA_REGISTRYINDEX, m_Callback);
         dmScript::Unref(m_L, LUA_REGISTRYINDEX, m_Self);
         m_L = NULL;
         m_Callback = LUA_NOREF;
         m_Self = LUA_NOREF;
      }
   }
   
   void callWithNoParam(int type) {
      int top = lua_gettop(m_L);
      lua_rawgeti(m_L, LUA_REGISTRYINDEX, m_Callback);
      lua_rawgeti(m_L, LUA_REGISTRYINDEX, m_Self);
      lua_pushvalue(m_L, -1);
      dmScript::SetInstance(m_L);
      lua_pushnumber(m_L, type);
      int ret = lua_pcall(m_L, 2, LUA_MULTRET, 0);
      if (ret != 0) {
         dmLogError("Enhance: error calling listener: %s", lua_tostring(m_L, -1));
         lua_pop(m_L, 1);
      }
      assert(top == lua_gettop(m_L));
   }
   
   lua_State *m_L;
   int m_Callback;
   int m_Self;
};

//Appodeal Main Methods
extern void Appodeal_SetCallback(AppodealListener *appodealListener);
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