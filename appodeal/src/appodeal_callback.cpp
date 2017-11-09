#if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID)
#include "appodeal_callback.h"

DispatchToLua g_DefAppodealAds;
DispatchToLua* defAtoLua;

struct CallbackData {
    int msg_type;
};

dmArray<CallbackData> m_callbacksQueue;

void finalize() {
    if(defAtoLua) {
        defAtoLua->listener.m_Callback = LUA_NOREF;
    }
}

void set_callback(lua_State* L, int pos) {
    defAtoLua = &g_DefAppodealAds;
    luaL_checktype(L, pos, LUA_TFUNCTION);
    lua_pushvalue(L, pos);
    int cb = dmScript::Ref(L, LUA_REGISTRYINDEX);
    
    if (defAtoLua->listener.m_Callback != LUA_NOREF) {
        dmScript::Unref(defAtoLua->listener.m_L, LUA_REGISTRYINDEX, defAtoLua->listener.m_Callback);
        dmScript::Unref(defAtoLua->listener.m_L, LUA_REGISTRYINDEX, defAtoLua->listener.m_Self);
    }
    
    defAtoLua->listener.m_L = dmScript::GetMainThread(L);
    defAtoLua->listener.m_Callback = cb;
    dmScript::GetInstance(L);
    defAtoLua->listener.m_Self = dmScript::Ref(L, LUA_REGISTRYINDEX);
}

void send_callback(int type) {
    lua_State* L = defAtoLua->listener.m_L;
    int top = lua_gettop(L);
    lua_rawgeti(L, LUA_REGISTRYINDEX, defAtoLua->listener.m_Callback);
    lua_rawgeti(L, LUA_REGISTRYINDEX, defAtoLua->listener.m_Self);
    lua_pushvalue(L, -1);
    dmScript::SetInstance(L);
    lua_pushnumber(L, type);
    
    int ret = lua_pcall(L, 3, LUA_MULTRET, 0);
    if (ret != 0) {
        dmLogError("Error running defAtoLua callback: %s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    assert(top == lua_gettop(L));
}

void add_to_queue(int type) {
    CallbackData data;
    data.msg_type = type;
    if(m_callbacksQueue.Full()) {
        m_callbacksQueue.OffsetCapacity(32);
    }
    m_callbacksQueue.Push(data);
}

void lua_appodealBannerLoaded() {
    add_to_queue((int)BANNER_LOADED);
}
void lua_appodealBannerFailed() {
    add_to_queue((int)BANNER_FAILED_TO_LOAD);
}
void lua_appodealBannerShown() {
    add_to_queue((int)BANNER_SHOWN);
}
void lua_appodealBannerClicked() {
    add_to_queue((int)BANNER_CLICKED);
}

void lua_appodealInterstitialLoaded() {
    add_to_queue((int)INTERSTITIAL_LOADED);
}
void lua_appodealInterstitialFailed() {
    add_to_queue((int)INTERSTITIAL_FAILED_TO_LOAD);
}
void lua_appodealInterstitialShown() {
    add_to_queue((int)INTERSTITIAL_SHOWN);
}
void lua_appodealInterstitialClosed() {
    add_to_queue((int)INTERSTITIAL_CLOSED);
}
void lua_appodealInterstitialClicked() {
    add_to_queue((int)INTERSTITIAL_CLICKED);
}

void lua_appodealRewardedLoaded() {
    add_to_queue((int)REWARDED_VIDEO_LOADED);
}
void lua_appodealRewardedFailed() {
    add_to_queue((int)REWARDED_VIDEO_FAILED_TO_LOAD);
}
void lua_appodealRewardedClosed() {
    add_to_queue((int)REWARDED_VIDEO_CLOSED);
}
void lua_appodealRewardedFinished() {
    add_to_queue((int)REWARDED_VIDEO_FISNIHED);
}
void lua_appodealRewardedShown() {
    add_to_queue((int)REWARDED_VIDEO_SHOWN);
}

void lua_appodealNonSkippableLoaded() {
    add_to_queue((int)NON_SKIPPABLE_VIDEO_LOADED);
}
void lua_appodealNonSkippableFailed() {
    add_to_queue((int)NON_SKIPPABLE_VIDEO_FAILED_TO_LOAD);
}
void lua_appodealNonSkippableClosed() {
    add_to_queue((int)NON_SKIPPABLE_VIDEO_CLOSED);
}
void lua_appodealNonSkippableFinished() {
    add_to_queue((int)NON_SKIPPABLE_VIDEO_FISNIHED);
}
void lua_appodealNonSkippableShown() {
    add_to_queue((int)NON_SKIPPABLE_VIDEO_SHOWN);
}

void callback_updates() {
    for(uint32_t i = 0; i != m_callbacksQueue.Size(); ++i) {
        CallbackData* data = &m_callbacksQueue[i];
        send_callback(data->msg_type);
        m_callbacksQueue.EraseSwap(i--);
    }
}

bool luaL_checkbool(lua_State *L, int numArg) {
    bool b = false;
    if (lua_isboolean(L, numArg)) {
        b = lua_toboolean(L, numArg);
    } else {
        luaL_typerror(L, numArg, lua_typename(L, LUA_TBOOLEAN));
    }
    return b;
}

void luaL_push_pair_str_num(lua_State *L, char *key, int value) {
    lua_pushstring(L, key);
    lua_pushnumber(L, value);
    lua_settable(L, -3);
}

void luaL_push_pair_str_str(lua_State *L, char *key, char *value) {
    lua_pushstring(L, key);
    lua_pushstring(L, value);
    lua_settable(L, -3);
}
#endif
