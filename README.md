# Appodeal Defold Extension

## How To Update Extension Manually

### Android Part

+ Download new Appodeal Android SDK from [Appodeal Docs](https://www.appodeal.com/sdk/choose_framework) -> Android. Choose `not using MultiDex` build. Unzip it somewhere.
+ Copy new AndroidManifest.xml tags from [Appodeal Docs](https://www.appodeal.com/sdk/choose_framework) -> Android. And replace content between `<!-- For Appodeal [version] -->` and `</application>` with copied tags.
+ Replace old jars with new inside [appodeal/lib/android](/appodeal/lib/android/).
+ For `aar` libraries you should do following:

```
1. Unzip aar somewhere
2. Rename classes.jar and copy it to [appodeal/lib/android](/appodeal/lib/android/)
3. If files exists inside `res` folder, copy all the content of `res` into [appodeal/res/android/res](/appodeal/res/android/res/)
4. If files exists inside `jni` folder, copy only `armeabi-v7a` into [appodeal/res/android/lib](/appodeal/res/android/lib/)
5. Unzip `appodeal-[version].jar` somewhere and copy content of `assets` folder into [appodeal/res/android/assets](/appodeal/res/android/assets/)
```

+ Check [appodeal/src/android/java/AppodealAndroid.java](/appodeal/src/android/java/AppodealAndroid.java) for any native SDK APi changes.

### iOS Part

+ Download new Appodeal Android SDK from [Appodeal Docs](https://www.appodeal.com/sdk/choose_framework) -> iOS -> Objective-C. Unzip it somewhere.
+ Copy Appodeal.framework into [appodeal/lib/arm64-ios](/appodeal/lib/arm64-ios/) and once more into [appodeal/lib/armv7-ios](/appodeal/lib/armv7-ios/).
+ Open `Terminal App` and execute following commands one by one:

```bash
cd [path_to_extension]/appodeal/lib/armv64-ios/Appodeal.framework
lipo -remove armv7 Appodeal -o Appodeal
lipo -remove armv7s Appodeal -o Appodeal
lipo -remove i386 Appodeal -o Appodeal
lipo -remove x86_64 Appodeal -o Appodeal
lipo -info Appodeal
# should output: Architectures in the fat file: Appodeal are: arm64 

cd [path_to_extension]/appodeal/lib/armv7-ios/Appodeal.framework
lipo -remove armv64 Appodeal -o Appodeal
lipo -remove armv7s Appodeal -o Appodeal
lipo -remove i386 Appodeal -o Appodeal
lipo -remove x86_64 Appodeal -o Appodeal
lipo -info Appodeal
# should output: Architectures in the fat file: Appodeal are: armv7 
```

+ Copy content of `Resources` folder from unzipped archive into [appodeal/res/ios](/appodeal/res/ios/)
+ Check [ext.manifest](/ext.manifest) for any changes due to changes in 3 step of 5.3. Manual Integration in [Appodeal Docs](https://www.appodeal.com/sdk/choose_framework) -> iOS -> Objective-C.
+ Check [appodeal/src/ios/appodeal_ios.mm](/appodeal/src/ios/appodeal_ios.mm) for any native SDK API changes.
+ iOS ready for build.

## Defold Integration

Please check this [readme](https://github.com/appodeal/appodeal-defold-demo).



