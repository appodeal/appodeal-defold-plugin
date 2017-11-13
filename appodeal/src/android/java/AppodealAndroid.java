package com.appodeal.defold;

import android.app.Activity;
import android.util.Log;

import com.appodeal.ads.Appodeal;
import com.appodeal.ads.BannerCallbacks;
import com.appodeal.ads.InterstitialCallbacks;
import com.appodeal.ads.NonSkippableVideoCallbacks;
import com.appodeal.ads.RewardedVideoCallbacks;
import com.appodeal.ads.UserSettings;
import com.appodeal.ads.utils.PermissionsHelper;

public class AppodealAndroid {

    private static String LOG_TAG = "Appodeal Defold Plugin";
    private static UserSettings userSettings;

    public static native void onBannerLoaded();
    public static native void onBannerFailedToLoad();
    public static native void onBannerShown();
    public static native void onBannerClicked();

    public static native void onInterstitialLoaded();
    public static native void onInterstitialFiledToLoad();
    public static native void onInterstitialShown();
    public static native void onInterstitialClicked();
    public static native void onInterstitialClosed();

    public static native void onRewardedVideoLoaded();
    public static native void onRewardedVideoFiledToLoad();
    public static native void onRewardedVideoShown();
    public static native void onRewardedVideoClosed();
    public static native void onRewardedVideoFinished();

    public static native void onNonSkippableVideoLoaded();
    public static native void onNonSkippableVideoFiledToLoad();
    public static native void onNonSkippableVideoShown();
    public static native void onNonSkippableVideoClosed();
    public static native void onNonSkippableVideoFinished();

    private static int getNativeAdType(int adType) {
        int type = 0;

        if((adType & 3) > 0) {
            type |= Appodeal.INTERSTITIAL;
        }

        if((adType & 4) > 0) {
            type |= Appodeal.BANNER;
        }

        if((adType & 8) > 0) {
            type |= Appodeal.BANNER_BOTTOM;
        }

        if((adType & 16) > 0) {
            type |= Appodeal.BANNER_TOP;
        }

        if((adType & 128) > 0) {
            type |= Appodeal.REWARDED_VIDEO;
        }

        if((adType & 256) > 0) {
            type |= Appodeal.NON_SKIPPABLE_VIDEO;
        }

        return type;
    }


    public static void Appodeal_Initialize(final Activity activity, final String appKey, final int adType) {
    	activity.runOnUiThread(new Runnable() {
            public void run() {
		    	if((adType & 3) > 0) {
		            Appodeal.setInterstitialCallbacks(interstitialCallbacks);
		        }
		
		        if((adType & 4) > 0) {
		            Appodeal.setBannerCallbacks(bannerCallbacks);
				}
		
		        if((adType & 8) > 0) {
		            Appodeal.setBannerCallbacks(bannerCallbacks);
		        }
		
		        if((adType & 16) > 0) {
		            Appodeal.setBannerCallbacks(bannerCallbacks);
		        }
		
		        if((adType & 128) > 0) {
		            Appodeal.setRewardedVideoCallbacks(rewardedVideoCallbacks);
		        }
		
		        if((adType & 256) > 0) {
		            Appodeal.setNonSkippableVideoCallbacks(nonSkippableVideoCallbacks);
		        }

				Appodeal.setFramework("defold", "2.1.7", true, false);
                Appodeal.initialize(activity, appKey, getNativeAdType(adType));
            }
        });
    }

    public static boolean Appodeal_Show(final Activity activity, final int adType) {
        final boolean[] show = {false};
        activity.runOnUiThread(new Runnable(){
            public void run(){
                show[0] = Appodeal.show(activity, getNativeAdType(adType));
            }
        });
        return show[0];
    }

    public static boolean Appodeal_ShowWithPlacement(final Activity activity, final String placement, final int adType) {
        final boolean[] show = {false};
        activity.runOnUiThread(new Runnable(){
            public void run(){
                show[0] = Appodeal.show(activity, getNativeAdType(adType), placement);
            }
        });
        return show[0];
    }

    public static boolean Appodeal_IsLoaded(int adType) {
        return Appodeal.isLoaded(getNativeAdType(adType));
    }

    public static void Appodeal_Cache(Activity activity, int adType) {
        Appodeal.cache(activity, getNativeAdType(adType));
    }

    public static void Appodeal_Hide(Activity activity, int adType) {
        Appodeal.hide(activity, getNativeAdType(adType));
    }

    public static void Appodeal_SetAutoCache(int adType, boolean flag) {
        Appodeal.setAutoCache(getNativeAdType(adType), flag);
    }

    public static boolean Appodeal_IsPrecache(int adType) {
        return Appodeal.isPrecache(getNativeAdType(adType));
    }

    public static void Appodeal_SetBannerAnimation(boolean flag) {
        Appodeal.setBannerAnimation(flag);
    }

    public static void Appodeal_SetSmartBanners(boolean flag) {
        Appodeal.setSmartBanners(flag);
    }

    public static void Appodeal_SetBannerBackground(boolean flag) {
        Log.e(LOG_TAG, "setBannerBackground not supported for Android Platform");
    }

    public static void Appodeal_SetTabletBanners(boolean flag) {
        Appodeal.set728x90Banners(flag);
    }

    public static void Appodeal_SetLogLevel(int level) {
        switch (level) {
            case 0: Appodeal.setLogLevel(com.appodeal.ads.utils.Log.LogLevel.none);
                break;
            case 1: Appodeal.setLogLevel(com.appodeal.ads.utils.Log.LogLevel.debug);
                break;
            case 2: Appodeal.setLogLevel(com.appodeal.ads.utils.Log.LogLevel.verbose);
                break;
        }
    }

    public static void Appodeal_SetTesting(boolean flag) {
        Appodeal.setTesting(flag);
    }

    public static void Appodeal_SetChildDirectedTreatment(boolean flag) {
        Appodeal.setChildDirectedTreatment(flag);
    }

    public static void Appodeal_SetTriggerOnLoadedOnPrecache(int type, boolean flag) {
        Appodeal.setTriggerOnLoadedOnPrecache(type, flag);
    }

    public static void Appodeal_DisableNetwork(Activity activity, String network) {
        Appodeal.disableNetwork(activity, network);
    }

    public static void Appodeal_DisableNetworkForAdType(Activity activity, String network, int adType) {
        Appodeal.disableNetwork(activity, network, adType);
    }
    
    public static void Appodeal_DisableLocationPermissionCheck() {
        Appodeal.disableLocationPermissionCheck();
    }

    public static void Appodeal_DisableWriteExternalStoragePermissionCheck() {
        Appodeal.disableWriteExternalStoragePermissionCheck();
    }

    public static void Appodeal_MuteVideosIfCallsMuted(boolean flag) {
        Appodeal.muteVideosIfCallsMuted(flag);
    }
    
    public static void Appodeal_RequestAndroidMPermissions(Activity activity) {
        Appodeal.requestAndroidMPermissions(activity, new PermissionsHelper.AppodealPermissionCallbacks() {
            @Override
            public void writeExternalStorageResponse(int result) {
                
            }

            @Override
            public void accessCoarseLocationResponse(int result) {

            }
        });
    }

    public static void Appodeal_ShowTestScreen(Activity activity) {
        Appodeal.startTestActivity(activity);
    }

    public static String Appodeal_GetNativeSDKVersion() {
        return Appodeal.getVersion();
    }

    public static boolean Appodeal_CanShow(int adType) {
        return Appodeal.canShow(getNativeAdType(adType));
    }

    public static boolean Appodeal_CanShowWithPlacement(int adType, String placement) {
        return Appodeal.canShow(getNativeAdType(adType), placement);
    }

    //region additional SDK calls
    public static void Appodeal_SetCustomIntRule(String name, int value) {
        Appodeal.setCustomRule(name, value);
    }

    public static void Appodeal_SetCustomBoolRule(String name, boolean value) {
        Appodeal.setCustomRule(name, value);
    }

    public static void Appodeal_SetCustomDoubleRule(String name, float value) {
        Appodeal.setCustomRule(name, value);
    }

    public static void Appodeal_SetCustomStringRule(String name, String value) {
        Appodeal.setCustomRule(name, value);
    }

    public static void Appodeal_TrackInAppPurchase(Activity activity, int amount, String currency) {
        Appodeal.trackInAppPurchase(activity, amount, currency);
    }

    public static String Appodeal_GetRewardName() {
        return Appodeal.getRewardParameters().second;
    }

    public static int Appodeal_GetRewardAmount() {
        return Appodeal.getRewardParameters().first;
    }

    public static String Appodeal_GetRewardNameForPlacement(String placement) {
        return Appodeal.getRewardParameters(placement).second;
    }

    public static int Appodeal_GetRewardAmountForPlacement(String placement) {
        return Appodeal.getRewardParameters(placement).first;
    }

    //region User Settings
    private static UserSettings getUserSettings(Activity activity) {
        if(userSettings == null) {
            userSettings = Appodeal.getUserSettings(activity);
        }
        return userSettings;
    }

    public static void Appodeal_SetUserAge(Activity activity, int age) {
        getUserSettings(activity).setAge(age);
    }

    public static void Appodeal_SetUserGender(Activity activity, int gender) {
        switch (gender) {
            case 0: getUserSettings(activity).setGender(UserSettings.Gender.OTHER);
                break;
            case 1: getUserSettings(activity).setGender(UserSettings.Gender.FEMALE);
                break;
            case 2: getUserSettings(activity).setGender(UserSettings.Gender.MALE);
                break;
        }
    }

    public static void Appodeal_SetUserId(Activity activity, String id) {
        getUserSettings(activity).setUserId(id);
    }

    private static BannerCallbacks bannerCallbacks = new BannerCallbacks() {
        @Override
        public void onBannerLoaded(int height, boolean isPrecache) {
            AppodealAndroid.onBannerLoaded();
        }

        @Override
        public void onBannerFailedToLoad() {
            AppodealAndroid.onBannerFailedToLoad();
        }

        @Override
        public void onBannerShown() {
            AppodealAndroid.onBannerShown();
        }

        @Override
        public void onBannerClicked() {
            AppodealAndroid.onBannerClicked();
        }
    };

    private static InterstitialCallbacks interstitialCallbacks = new InterstitialCallbacks() {
        @Override
        public void onInterstitialLoaded(boolean isPrecache) {
            AppodealAndroid.onInterstitialLoaded();
        }

        @Override
        public void onInterstitialFailedToLoad() {
            AppodealAndroid.onInterstitialFiledToLoad();
        }

        @Override
        public void onInterstitialShown() {
            AppodealAndroid.onInterstitialShown();
        }

        @Override
        public void onInterstitialClicked() {
            AppodealAndroid.onInterstitialClicked();
        }

        @Override
        public void onInterstitialClosed() {
            AppodealAndroid.onInterstitialClosed();
        }
    };


    private static RewardedVideoCallbacks rewardedVideoCallbacks = new RewardedVideoCallbacks() {
        @Override
        public void onRewardedVideoLoaded() {
            AppodealAndroid.onRewardedVideoLoaded();
        }

        @Override
        public void onRewardedVideoFailedToLoad() {
            AppodealAndroid.onRewardedVideoFiledToLoad();
        }

        @Override
        public void onRewardedVideoShown() {
            AppodealAndroid.onRewardedVideoShown();
        }

        @Override
        public void onRewardedVideoFinished(int amount, String name) {
            AppodealAndroid.onRewardedVideoFinished();
        }

        @Override
        public void onRewardedVideoClosed(boolean finished) {
            AppodealAndroid.onRewardedVideoClosed();
        }
    };

    private static NonSkippableVideoCallbacks nonSkippableVideoCallbacks = new NonSkippableVideoCallbacks() {
        @Override
        public void onNonSkippableVideoLoaded() {
            AppodealAndroid.onNonSkippableVideoLoaded();
        }

        @Override
        public void onNonSkippableVideoFailedToLoad() {
            AppodealAndroid.onNonSkippableVideoFiledToLoad();
        }

        @Override
        public void onNonSkippableVideoShown() {
            AppodealAndroid.onNonSkippableVideoShown();
        }

        @Override
        public void onNonSkippableVideoFinished() {
            AppodealAndroid.onNonSkippableVideoFinished();
        }

        @Override
        public void onNonSkippableVideoClosed(boolean finished) {
            AppodealAndroid.onNonSkippableVideoClosed();
        }
    };

}
