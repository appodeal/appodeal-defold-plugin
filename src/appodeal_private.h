#pragma once

#include <dmsdk/extension/extension.h>

struct AppodealListener {
  AppodealListener() {
    m_L = 0;
    m_Callback = LUA_NOREF;
    m_Self = LUA_NOREF;
  }
  lua_State* m_L;
  int        m_Callback;
  int        m_Self;
};

//void
extern void Appodeal_Listen(lua_State* L);
extern void Appodeal_Initialise(lua_State* L);
extern void Appodeal_ShowAd(lua_State* L);   
extern void Appodeal_HideBanner(lua_State* L);   
extern void Appodal_DisableNetwork(lua_State* L);
extern void Appodeal_SetLocationTracking(lua_State* L);
extern void Appodeal_SetAutocache(lua_State* L);
extern void Appodeal_CacheAd(lua_State* L);
extern void Appodeal_SetDebugEnabled(lua_State* L);
extern void Appodeal_SetTestingEnabled(lua_State* L);
extern void Appodeal_SetCustomIntRule(lua_State* L);
extern void Appodeal_SetCustomBoolRule(lua_State* L);
extern void Appodeal_SetCustomDoubleRule(lua_State* L);
extern void Appodeal_SetCustomStringRule(lua_State* L);
extern void Appodeal_ConfirmUsage(lua_State* L);
extern bool Appodeal_IsAutocacheEnabled(lua_State* L);
extern bool Appodeal_IsInitalized(lua_State* L);
extern bool Appodeal_IsReadyForShowWithStyle(lua_State* L);
extern void Appodeal_SetSmartBannersEnabled(lua_State* L);
extern void Appodeal_SetBannerBackgroundVisible(lua_State* L);
extern void Appodeal_SetBannerAnimationEnabled(lua_State* L);
extern void Appodeal_DisableUserDataForNetwork(lua_State* L);
extern void Appodeal_SetUserId(lua_State* L);
extern void Appodeal_SetUserEmail(lua_State* L);
extern void Appodeal_SetUserBirthday(lua_State* L);
extern void Appodeal_SetUserAge(lua_State* L);
extern void Appodeal_SetUserGender(lua_State* L);
extern void Appodeal_SetUserOccupation(lua_State* L);
extern void Appodeal_SetUserRelationship(lua_State* L);
extern void Appodeal_SetUserSmokingAttitude(lua_State* L);
extern void Appodeal_SetUserAlcoholAttitude(lua_State* L);
extern void Appodeal_SetUserInterests(lua_State* L);
