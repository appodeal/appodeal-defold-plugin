#if defined(DM_PLATFORM_ANDROID)

#include "com_appodeal_defold_AppodealAndroid.h"

#include <dmsdk/sdk.h>
#include <dmsdk/extension/extension.h>
#include <dmsdk/script/script.h>  
#include <dmsdk/dlib/log.h>

const char* appodeal_jar_path = "com/appodeal/defold/AppodealAndroid";

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

struct APD {
  AppodealListener listener;
} g_Apd;

APD* apd;

int send_callback(const char * message, const char * currencyName, int rewardAmount) {
	apd = &g_Apd;
 	lua_State* L = apd->listener.m_L;
    int top = lua_gettop(L);
    lua_rawgeti(L, LUA_REGISTRYINDEX, apd->listener.m_Callback);

    // Setup self
   	lua_rawgeti(L, LUA_REGISTRYINDEX, apd->listener.m_Self);
   	lua_pushvalue(L, -1);
   	dmScript::SetInstance(L);
   	lua_pushstring(L, message);
   	lua_pushstring(L, currencyName);
   	lua_pushnumber(L, rewardAmount);
    //dmScript::PushString(L, message);
    int ret = lua_pcall(L, 4, LUA_MULTRET, 0);
    if (ret != 0) {
    	dmLogError("Error running apd callback: %s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    assert(top == lua_gettop(L));
    return 1;
}

bool get_lua_bool (lua_State* L, int index) {
	if (lua_isboolean(L, index))
        if (lua_toboolean(L, index) == 1)
        	return true;
        else
        	return false;
    else
        return false;
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onBannerLoaded(JNIEnv *env, jclass jcls) {
	send_callback("BANNER_LOADED","",0);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onBannerFailedToLoad(JNIEnv *env, jclass jcls) {
	send_callback("BANNERL_FAILED_TO_LOAD","",0);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onBannerShown(JNIEnv *env, jclass jcls) {
	send_callback("BANNER_SHOWN","",0);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onBannerClicked(JNIEnv *env, jclass jcls) {
	send_callback("BANNER_CLICKED","",0);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onInterstitialLoaded(JNIEnv *env, jclass jcls) {
	send_callback("INTERSTITIAL_LOADED","",0);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onInterstitialFiledToLoad(JNIEnv *env, jclass jcls) {
	send_callback("INTERSTITIAL_FAILED_TO_LOAD","",0);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onInterstitialShown(JNIEnv *env, jclass jcls) {
	send_callback("INTERSTITIAL_SHOWN","",0);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onInterstitialClicked(JNIEnv *env, jclass jcls) {
	send_callback("INTERSTITIAL_CLICKED","",0);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onInterstitialClosed(JNIEnv *env, jclass jcls) {
	send_callback("INTERSTITIAL_CLOSED","",0);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onRewardedVideoLoaded(JNIEnv *env, jclass jcls) {
	send_callback("REWARDED_VIDEO_LOADED","",0);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onRewardedVideoFiledToLoad(JNIEnv *env, jclass jcls) {
	send_callback("REWARDED_VIDEO_FAILED_TO_LOAD","",0);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onRewardedVideoShown(JNIEnv *env, jclass jcls) {
	send_callback("REWARDED_VIDEO_SHOWN","",0);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onRewardedVideoClosed(JNIEnv *env, jclass jcls) {
	send_callback("REWARDED_VIDEO_CLOSED","",0);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onRewardedVideoFinished(JNIEnv *env, jclass jcls,  jint amount, jstring name) {
	const char* rewardName = env->GetStringUTFChars(name, 0);
	send_callback("REWARDED_VIDEO_FINISHED", (char*)rewardName, (int)amount);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onNonSkippableVideoLoaded(JNIEnv *env, jclass jcls) {
	send_callback("NON_SKIPPABLE_VIDEO_LOADED","",0);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onNonSkippableVideoFiledToLoad(JNIEnv *env, jclass jcls) {
	send_callback("NON_SKIPPABLE_VIDEO_FAILED_TO_LOAD","",0);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onNonSkippableVideoShown(JNIEnv *env, jclass jcls) {
	send_callback("NON_SKIPPABLE_VIDEO_SHOWN","",0);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onNonSkippableVideoClosed(JNIEnv *env, jclass jcls) {
	send_callback("NON_SKIPPABLE_VIDEO_CLOSED","",0);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onNonSkippableVideoFinished(JNIEnv *env, jclass jcls) {
	send_callback("NON_SKIPPABLE_VIDEO_FINISHED","",0);
}

void Appodeal_Listen(lua_State* L) {	
	//creating the callback lua ref 
	apd = &g_Apd;
    
    luaL_checktype(L, 1, LUA_TFUNCTION);
    lua_pushvalue(L, 1);
    int cb = dmScript::Ref(L, LUA_REGISTRYINDEX);

    if (apd->listener.m_Callback != LUA_NOREF) {
      dmScript::Unref(apd->listener.m_L, LUA_REGISTRYINDEX, apd->listener.m_Callback);
      dmScript::Unref(apd->listener.m_L, LUA_REGISTRYINDEX, apd->listener.m_Self);
    }

    apd->listener.m_L = dmScript::GetMainThread(L);
    apd->listener.m_Callback = cb;
    dmScript::GetInstance(L);
    apd->listener.m_Self = dmScript::Ref(L, LUA_REGISTRYINDEX);
}


static JNIEnv* Attach() {
	JNIEnv *env;
	JavaVM* vm = dmGraphics::GetNativeAndroidJavaVM();
	vm->AttachCurrentThread(&env, NULL);
	return env;
}

static bool Detach(JNIEnv* env) {
	bool exception = (bool) env->ExceptionCheck();
	env->ExceptionClear();
	JavaVM* vm = dmGraphics::GetNativeAndroidJavaVM();
	vm->DetachCurrentThread();
	return !exception;
}

namespace {
	struct AttachScope {
		JNIEnv* m_Env;
		AttachScope() : m_Env(Attach()) { }
		~AttachScope() {
			Detach(m_Env);
		}
	};
}

static jclass GetClass(JNIEnv* env, const char* classname)
{
    jclass activity_class = env->FindClass("android/app/NativeActivity");
    jmethodID get_class_loader = env->GetMethodID(activity_class,"getClassLoader", "()Ljava/lang/ClassLoader;");
    jobject cls = env->CallObjectMethod(dmGraphics::GetNativeAndroidActivity(), get_class_loader);
    jclass class_loader = env->FindClass("java/lang/ClassLoader");
    jmethodID find_class = env->GetMethodID(class_loader, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
    
    jstring str_class_name = env->NewStringUTF(classname);
    jclass outcls = (jclass)env->CallObjectMethod(cls, find_class, str_class_name);
    env->DeleteLocalRef(str_class_name);
    return outcls;
}

void Appodeal_Initialize(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    
    const char *key_from_lua = luaL_checkstring(L, 1);
    int adType = luaL_checkint(L, 2); 

	jstring japp_key = env->NewStringUTF(key_from_lua);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_Initialize", "(Landroid/app/Activity;Ljava/lang/String;I)V");
    env->CallStaticVoidMethod(cls, method, dmGraphics::GetNativeAndroidActivity(), japp_key, adType);
}

bool Appodeal_Show(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    
    int adType = luaL_checkint(L, 1); 
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_Show", "(Landroid/app/Activity;I)Z");
    jboolean return_value = (jboolean)env->CallStaticBooleanMethod(cls, method, dmGraphics::GetNativeAndroidActivity(), adType);
    return JNI_TRUE == return_value;
}

bool Appodeal_ShowWithPlacement(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    
    int adType = luaL_checkint(L, 1);
    const char *placement = luaL_checkstring(L, 2);
    jstring jplacement = env->NewStringUTF(placement);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_ShowWithPlacement", "(Landroid/app/Activity;Ljava/lang/String;I)Z");
    jboolean return_value = (jboolean)env->CallStaticBooleanMethod(cls, method, dmGraphics::GetNativeAndroidActivity(), jplacement, adType);
    return JNI_TRUE == return_value;
}

bool Appodeal_IsLoaded(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    
    int adType = luaL_checkint(L, 1);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_IsLoaded", "(I)Z");
    jboolean return_value = (jboolean)env->CallStaticBooleanMethod(cls, method, adType);
    return JNI_TRUE == return_value;
}

bool Appodeal_CanShow(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    
    int adType = luaL_checkint(L, 1);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_CanShow", "(I)Z");
    jboolean return_value = (jboolean)env->CallStaticBooleanMethod(cls, method, adType);
    return JNI_TRUE == return_value;
}

bool Appodeal_CanShowWithPlacement(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    
    int adType = luaL_checkint(L, 1);
    const char *placement = luaL_checkstring(L, 2);
    jstring jplacement = env->NewStringUTF(placement);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_CanShowWithPlacement", "(ILjava/lang/String;)Z");
    jboolean return_value = (jboolean)env->CallStaticBooleanMethod(cls, method, adType, jplacement);
    return JNI_TRUE == return_value;
}

void Appodeal_Hide(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

	int adType = luaL_checkint(L, 1);
	jmethodID method = env->GetStaticMethodID(cls, "Appodeal_Hide", "(Landroid/app/Activity;I)V");
    env->CallStaticVoidMethod(cls, method, dmGraphics::GetNativeAndroidActivity(), adType);
}

void Appodeal_Cache(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

	int adType = luaL_checkint(L, 1);
	jmethodID method = env->GetStaticMethodID(cls, "Appodeal_Cache", "(Landroid/app/Activity;I)V");
    env->CallStaticVoidMethod(cls, method, dmGraphics::GetNativeAndroidActivity(), adType);
}

void Appodeal_SetAutoCache(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

	bool flag = get_lua_bool(L, 1);
	int adType = luaL_checkint(L, 2);
	jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetAutoCache", "(IZ)V");
    env->CallStaticVoidMethod(cls, method, adType, flag? JNI_TRUE : JNI_FALSE);
}

void Appodeal_SetSmartBanners(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

	bool flag = get_lua_bool(L, 1);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetSmartBanners", "(Z)V");
    env->CallStaticVoidMethod(cls, method, flag? JNI_TRUE : JNI_FALSE);
}

void Appodeal_SetBannerAnimation(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

	bool flag = get_lua_bool(L, 1);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetBannerAnimation", "(Z)V");
    env->CallStaticVoidMethod(cls, method, flag? JNI_TRUE : JNI_FALSE);
}

void Appodeal_SetBannerBackground(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

	bool flag = get_lua_bool(L, 1);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetBannerBackground", "(Z)V");
    env->CallStaticVoidMethod(cls, method, flag? JNI_TRUE : JNI_FALSE);
}

void Appodeal_DisableNetwork(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

	const char *network = luaL_checkstring(L, 1);
	jstring jnetwork = env->NewStringUTF(network);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_DisableNewtork", "(Landroid/app/Activity;Ljava/lang/String;)V");
    env->CallStaticVoidMethod(cls, method, dmGraphics::GetNativeAndroidActivity(), jnetwork);
}

void Appodeal_DisableNetworkForAdType(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

	const char *network = luaL_checkstring(L, 1);
	int adType = luaL_checkint(L, 2);
	jstring jnetwork = env->NewStringUTF(network);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_DisableNewtork", "(Landroid/app/Activity;Ljava/lang/String;I)V");
    env->CallStaticVoidMethod(cls, method, dmGraphics::GetNativeAndroidActivity(), jnetwork, adType);
}

void Appodeal_MuteVideosIfCallsMuted(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

	bool flag = get_lua_bool(L, 1);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_MuteVideosIfCallsMuted", "(Z)V");
    env->CallStaticVoidMethod(cls, method, flag? JNI_TRUE : JNI_FALSE);
}

void Appodeal_SetTesting(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
	
	bool flag = get_lua_bool(L, 1);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetTesting", "(Z)V");
    env->CallStaticVoidMethod(cls, method, flag? JNI_TRUE : JNI_FALSE);
}

void Appodeal_SetLogging(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
	
	bool flag = get_lua_bool(L, 1);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetLogging", "(Z)V");
    env->CallStaticVoidMethod(cls, method, flag? JNI_TRUE : JNI_FALSE);
}

void Appodeal_SetCustomIntRule(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

	const char *rule_name_lua = luaL_checkstring(L, 1);
	int rule_int = luaL_checkint(L, 2);
	jstring jname = env->NewStringUTF(rule_name_lua);
	jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetCustomIntRule", "(Ljava/lang/String;I)V");
    env->CallStaticVoidMethod(cls, method, jname, rule_int);
}

void Appodeal_SetCustomBoolRule(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

	bool lua_rule = get_lua_bool(L, 2);
	const char *rule_name_lua = luaL_checkstring(L, 1);
	jstring jname = env->NewStringUTF(rule_name_lua);
	jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetCustomBoolRule", "(Ljava/lang/String;I)V");
    env->CallStaticVoidMethod(cls, method, jname, lua_rule? JNI_TRUE : JNI_FALSE);
}

void Appodeal_SetCustomDoubleRule(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

	const char *rule_name_lua = luaL_checkstring(L, 1);
	double rule_double = luaL_checknumber(L, 2);
	jstring jname = env->NewStringUTF(rule_name_lua);
	jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetCustomDoubleRule", "(Ljava/lang/String;D)V");
    env->CallStaticVoidMethod(cls, method, jname, rule_double);
}

void Appodeal_SetCustomStringRule(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

	const char *rule_name_lua = luaL_checkstring(L, 1);
	const char *rule_lua = luaL_checkstring(L, 2);
	jstring jvalue = env->NewStringUTF(rule_lua);
	jstring jname = env->NewStringUTF(rule_name_lua);
	jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetCustomStringRule", "(Ljava/lang/String;Ljava/lang/String;)V");
    env->CallStaticVoidMethod(cls, method, jname, jvalue);
}

char const* Appodeal_GetNativeSDKVersion(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_GetNativeSDKVersion", "()Ljava/lang/String;");
    jstring return_value = (jstring)env->CallStaticObjectMethod(cls, method);
    const char* new_char = env->GetStringUTFChars(return_value, 0);
    env->DeleteLocalRef(return_value);
    return new_char;
}

void Appodeal_SetUserAge(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
	
	int user_age = luaL_checkint(L, 1);
	jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetUserAge", "(Landroid/app/Activity;I)V");
    env->CallStaticVoidMethod(cls, method, dmGraphics::GetNativeAndroidActivity(), user_age);
}

void Appodeal_SetUserId(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
	
	const char *user_id = luaL_checkstring(L, 1);
	jstring jvalue = env->NewStringUTF(user_id);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetUserId", "(Landroid/app/Activity;Ljava/lang/String;)V");
    env->CallStaticVoidMethod(cls, method, dmGraphics::GetNativeAndroidActivity(), jvalue);
}

void Appodeal_SetUserGender(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
	
    int gender = luaL_checkint(L, 1);
	jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetUserGender", "(Landroid/app/Activity;I)V");
    env->CallStaticVoidMethod(cls, method, dmGraphics::GetNativeAndroidActivity(), gender);
}

#endif
