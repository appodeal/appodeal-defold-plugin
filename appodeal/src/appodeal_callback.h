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

struct DispatchToLua {
    AppodealListener listener;
};

void set_callback(lua_State* L, int pos);
void send_callback(int type);
void callback_updates();
void finalize();

void lua_appodealBannerLoaded();
void lua_appodealBannerFailed();
void lua_appodealBannerShown();
void lua_appodealBannerClicked();

void lua_appodealInterstitialLoaded();
void lua_appodealInterstitialFailed();
void lua_appodealInterstitialShown();
void lua_appodealInterstitialClosed();
void lua_appodealInterstitialClicked();

void lua_appodealRewardedLoaded();
void lua_appodealRewardedFailed();
void lua_appodealRewardedClosed();
void lua_appodealRewardedFinished();
void lua_appodealRewardedShown();

void lua_appodealNonSkippableLoaded();
void lua_appodealNonSkippableFailed();
void lua_appodealNonSkippableClosed();
void lua_appodealNonSkippableFinished();
void lua_appodealNonSkippableShown();

bool luaL_checkbool(lua_State *L, int numArg);
void luaL_push_pair_str_num(lua_State *L, char *key, int value);
void luaL_push_pair_str_str(lua_State *L, char *key, char *value);
