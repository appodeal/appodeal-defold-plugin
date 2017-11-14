#if defined(DM_PLATFORM_ANDROID)

#include "../appodeal.h"
#include "com_appodeal_defold_AppodealAndroid.h"

#include <dmsdk/sdk.h>
#include <dmsdk/extension/extension.h>
#include <dmsdk/script/script.h>  
#include <dmsdk/dlib/log.h>

const char* appodeal_jar_path = "com/appodeal/defold/AppodealAndroid";

static AppodealListener *g_appodealListener;

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
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)BANNER_LOADED);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onBannerFailedToLoad(JNIEnv *env, jclass jcls) {
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)BANNER_FAILED_TO_LOAD);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onBannerShown(JNIEnv *env, jclass jcls) {
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)BANNER_SHOWN);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onBannerClicked(JNIEnv *env, jclass jcls) {
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)BANNER_CLICKED);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onInterstitialLoaded(JNIEnv *env, jclass jcls) {
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)INTERSTITIAL_LOADED);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onInterstitialFiledToLoad(JNIEnv *env, jclass jcls) {
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)INTERSTITIAL_FAILED_TO_LOAD);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onInterstitialShown(JNIEnv *env, jclass jcls) {
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)INTERSTITIAL_SHOWN);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onInterstitialClicked(JNIEnv *env, jclass jcls) {
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)INTERSTITIAL_CLICKED);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onInterstitialClosed(JNIEnv *env, jclass jcls) {
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)INTERSTITIAL_CLOSED);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onRewardedVideoLoaded(JNIEnv *env, jclass jcls) {
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)REWARDED_VIDEO_LOADED);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onRewardedVideoFiledToLoad(JNIEnv *env, jclass jcls) {
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)REWARDED_VIDEO_FAILED_TO_LOAD);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onRewardedVideoShown(JNIEnv *env, jclass jcls) {
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)REWARDED_VIDEO_SHOWN);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onRewardedVideoClosed(JNIEnv *env, jclass jcls) {
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)REWARDED_VIDEO_CLOSED);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onRewardedVideoFinished(JNIEnv *env, jclass jcls) {
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)REWARDED_VIDEO_FISNIHED);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onNonSkippableVideoLoaded(JNIEnv *env, jclass jcls) {
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)NON_SKIPPABLE_VIDEO_LOADED);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onNonSkippableVideoFiledToLoad(JNIEnv *env, jclass jcls) {
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)NON_SKIPPABLE_VIDEO_FAILED_TO_LOAD);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onNonSkippableVideoShown(JNIEnv *env, jclass jcls) {
    if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)NON_SKIPPABLE_VIDEO_SHOWN);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onNonSkippableVideoClosed(JNIEnv *env, jclass jcls) {
	if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)NON_SKIPPABLE_VIDEO_CLOSED);
}

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onNonSkippableVideoFinished(JNIEnv *env, jclass jcls) {
    if (g_appodealListener)
        g_appodealListener->callWithNoParam((int)NON_SKIPPABLE_VIDEO_FISNIHED);
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
    
    switch (vm->GetEnv((void**)&env, JNI_VERSION_1_6)) {
    case JNI_OK:
        break;
    case JNI_EDETACHED:
        vm->DetachCurrentThread();
        break;
    }
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

static jclass GetClass(JNIEnv* env, const char* classname) {
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

void Appodeal_SetCallback(AppodealListener *appodealListener) {
   g_appodealListener = appodealListener;
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

    int adType = luaL_checkint(L, 1);
    bool flag = get_lua_bool(L, 2);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetAutoCache", "(IZ)V");
    env->CallStaticVoidMethod(cls, method, adType, flag? JNI_TRUE : JNI_FALSE);
}

bool Appodeal_IsPrecache(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    
    int adType = luaL_checkint(L, 1);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_IsPrecache", "(I)Z");
    jboolean return_value = (jboolean)env->CallStaticBooleanMethod(cls, method, adType);
    return JNI_TRUE == return_value;
}

void Appodeal_SetBannerAnimation(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

    bool flag = get_lua_bool(L, 1);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetBannerAnimation", "(Z)V");
    env->CallStaticVoidMethod(cls, method, flag? JNI_TRUE : JNI_FALSE);
}

void Appodeal_SetSmartBanners(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

    bool flag = get_lua_bool(L, 1);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetSmartBanners", "(Z)V");
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

void Appodeal_SetTabletBanners(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

    bool flag = get_lua_bool(L, 1);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetTabletBanners", "(Z)V");
    env->CallStaticVoidMethod(cls, method, flag? JNI_TRUE : JNI_FALSE);
}

void Appodeal_SetLogLevel(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    
    int logLevel = luaL_checkint(L, 1);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetLogLevel", "(I)V");
    env->CallStaticVoidMethod(cls, method, logLevel);
}

void Appodeal_SetTesting(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    
    bool flag = get_lua_bool(L, 1);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetTesting", "(Z)V");
    env->CallStaticVoidMethod(cls, method, flag? JNI_TRUE : JNI_FALSE);
}

void Appodeal_SetChildDirectedTreatment(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    
    bool flag = get_lua_bool(L, 1);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetChildDirectedTreatment", "(Z)V");
    env->CallStaticVoidMethod(cls, method, flag? JNI_TRUE : JNI_FALSE);
}

void Appodeal_SetTriggerOnLoadedOnPrecache(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    
    int adType = luaL_checkint(L, 1);
    bool flag = get_lua_bool(L, 2);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetTriggerOnLoadedOnPrecache", "(IZ)V");
    env->CallStaticVoidMethod(cls, method, adType, flag? JNI_TRUE : JNI_FALSE);
}

void Appodeal_DisableNetwork(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

    const char *network = luaL_checkstring(L, 1);
    jstring jnetwork = env->NewStringUTF(network);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_DisableNetwork", "(Landroid/app/Activity;Ljava/lang/String;)V");
    env->CallStaticVoidMethod(cls, method, dmGraphics::GetNativeAndroidActivity(), jnetwork);
}

void Appodeal_DisableNetworkForAdType(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

    const char *network = luaL_checkstring(L, 1);
    int adType = luaL_checkint(L, 2);
    jstring jnetwork = env->NewStringUTF(network);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_DisableNetworkForAdType", "(Landroid/app/Activity;Ljava/lang/String;I)V");
    env->CallStaticVoidMethod(cls, method, dmGraphics::GetNativeAndroidActivity(), jnetwork, adType);
}

void Appodeal_DisableLocationPermissionCheck(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_DisableLocationPermissionCheck", "()V");
    env->CallStaticVoidMethod(cls, method);
}

void Appodeal_DisableWriteExternalStoragePermissionCheck(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_DisableWriteExternalStoragePermissionCheck", "()V");
    env->CallStaticVoidMethod(cls, method);
}

void Appodeal_RequestAndroidMPermissions(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_RequestAndroidMPermissions", "(Landroid/app/Activity;)V");
    env->CallStaticVoidMethod(cls, method, dmGraphics::GetNativeAndroidActivity());
}

void Appodeal_MuteVideosIfCallsMuted(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    
    bool flag = get_lua_bool(L, 1);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_MuteVideosIfCallsMuted", "(Z)V");
    env->CallStaticVoidMethod(cls, method, flag? JNI_TRUE : JNI_FALSE);
}

void Appodeal_ShowTestScreen(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_ShowTestScreen", "()V");
    env->CallStaticVoidMethod(cls, method);
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
	jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetCustomBoolRule", "(Ljava/lang/String;Z)V");
    env->CallStaticVoidMethod(cls, method, jname, lua_rule? JNI_TRUE : JNI_FALSE);
}

void Appodeal_SetCustomDoubleRule(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

	const char *rule_name_lua = luaL_checkstring(L, 1);
	float rule_double = luaL_checknumber(L, 2);
	jstring jname = env->NewStringUTF(rule_name_lua);
	jmethodID method = env->GetStaticMethodID(cls, "Appodeal_SetCustomDoubleRule", "(Ljava/lang/String;F)V");
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

void Appodeal_TrackInAppPurchase(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

    int amount = luaL_checkint(L, 1);
    const char *name_lua = luaL_checkstring(L, 2);
    jstring jname = env->NewStringUTF(name_lua);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_TrackInAppPurchase", "(Landroid/app/Activity;ILjava/lang/String;)V");
    env->CallStaticVoidMethod(cls, method, dmGraphics::GetNativeAndroidActivity(), amount, jname);
}

char const* Appodeal_GetRewardName(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_GetRewardName", "()Ljava/lang/String;");
    jstring return_value = (jstring)env->CallStaticObjectMethod(cls, method);
    const char* new_char = env->GetStringUTFChars(return_value, 0);
    env->DeleteLocalRef(return_value);
    return new_char;
}

int Appodeal_GetRewardAmount(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_GetRewardAmount", "()I");
    jint val = env->CallIntMethod(cls, method);
    return val;
}

char const* Appodeal_GetRewardNameForPlacement(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

    const char *placement = luaL_checkstring(L, 1);
    jstring jplacement = env->NewStringUTF(placement);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_GetRewardNameForPlacement", "(Ljava/lang/String;)Ljava/lang/String;");
    jstring return_value = (jstring)env->CallStaticObjectMethod(cls, method, jplacement);
    const char* new_char = env->GetStringUTFChars(return_value, 0);
    env->DeleteLocalRef(return_value);
    return new_char;
}

int Appodeal_GetRewardAmountForPlacement(lua_State* L) {
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;
    jclass cls = GetClass(env, appodeal_jar_path);

    const char *placement = luaL_checkstring(L, 1);
    jstring jplacement = env->NewStringUTF(placement);
    jmethodID method = env->GetStaticMethodID(cls, "Appodeal_GetRewardAmountForPlacement", "(Ljava/lang/String;)I");
    jint val = env->CallIntMethod(cls, method, jplacement);
    return val;
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
