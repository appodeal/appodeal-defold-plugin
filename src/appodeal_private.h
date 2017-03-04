#pragma once

#include <dmsdk/extension/extension.h>

//enums 

enum APDDefoldUserGender
{
	GENDER_OTHER,
	GENDER_FEMALE,
	GENDER_MALE
};

enum APDDefoldUserOccupation
{
	OCCUPATION_OTHER,
	OCCUPATION_WORK,
	OCCUPATION_SCHOOL,
	OCCUPATION_UNIVERSITY
};

enum APDDefoldUserRelationship
{
	RELATIONSHIP_OTHER,
	RELATIONSHIP_SINGLE,
	RELATIONSHIP_DATING,
	RELATIONSHIP_ENGAGED,
	RELATIONSHIP_MARRIED,
	RELATIONSHIP_SEARCHING
};

enum APDDefoldUserSmokingAttitude
{
	SMOKING_NEGATIVE,
	SMOKING_NEUTRAL,
	SMOKING_POSITIVE
};

enum APDDefoldUserAlcoholAttitude
{
	ALCOHOL_NEGATIVE,
	ALCOHOL_NEUTRAL,
	ALCOHOL_POSITIVE
};

//listener for callbacks

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

//extension func-s

extern void Appodeal_Listen(lua_State* L);
extern void Appodeal_Initialise(lua_State* L);
extern void Appodeal_ShowAd(lua_State* L);   
extern void Appodeal_HideBanner(lua_State* L);   
extern void Appodeal_DisableNetwork(lua_State* L);
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
extern void Appodeal_IsAutocacheEnabled(lua_State* L);
extern void Appodeal_IsInitalized(lua_State* L);
extern void Appodeal_IsReadyForShowWithStyle(lua_State* L);
extern void Appodeal_SetSmartBannersEnabled(lua_State* L);
extern void Appodeal_SetBannerBackgroundVisible(lua_State* L);
extern void Appodeal_SetBannerAnimationEnabled(lua_State* L);
extern void Appodeal_DisableUserDataForNetwork(lua_State* L);
extern void Appodeal_SetUserId(lua_State* L);
extern void Appodeal_SetUserEmail(lua_State* L);
extern void Appodeal_SetUserBirthday(lua_State* L);
extern void Appodeal_SetUserAge(lua_State* L);
extern void Appodeal_SetUserGender(APDDefoldUserGender gender);
extern void Appodeal_SetUserOccupation(APDDefoldUserOccupation occupation);
extern void Appodeal_SetUserRelationship(APDDefoldUserRelationship relationship);
extern void Appodeal_SetUserSmokingAttitude(APDDefoldUserSmokingAttitude smokingAttitude);
extern void Appodeal_SetUserAlcoholAttitude(APDDefoldUserAlcoholAttitude alcoholAttitude);
extern void Appodeal_SetUserInterests(lua_State* L);
