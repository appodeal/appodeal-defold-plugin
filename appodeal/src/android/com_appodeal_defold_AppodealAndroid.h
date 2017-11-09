#include <jni.h>

#ifndef _Included_com_appodeal_defold_AppodealAndroid
#define _Included_com_appodeal_defold_AppodealAndroid
#ifdef __cplusplus

extern "C" {

#endif

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onBannerLoaded
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onBannerFailedToLoad
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onBannerShown
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onBannerClicked
  (JNIEnv *, jclass);
  
JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onInterstitialLoaded
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onInterstitialFiledToLoad
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onInterstitialShown
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onInterstitialClicked
  (JNIEnv *, jclass);
  
JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onInterstitialClosed
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onRewardedVideoLoaded
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onRewardedVideoFiledToLoad
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onRewardedVideoShown
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onRewardedVideoClosed
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onRewardedVideoFinished
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onNonSkippableVideoLoaded
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onNonSkippableVideoFiledToLoad
  (JNIEnv *, jclass);
  
JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onNonSkippableVideoShown
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onNonSkippableVideoClosed
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_appodeal_defold_AppodealAndroid_onNonSkippableVideoFinished
  (JNIEnv *, jclass);

#ifdef __cplusplus
}

#endif

#endif