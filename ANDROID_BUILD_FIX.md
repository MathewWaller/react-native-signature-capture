# React Native Signature Capture - Android Build Fix

If you encounter the following error when building your React Native project:

```
Task ':reactnativesignaturecapture:packageDebugResources' uses this output of task ':react-native-signature-capture:generateDebugResValues' without declaring an explicit or implicit dependency.
```

## Solution 1: Add to your main project's android/build.gradle

Add this configuration to your main project's `android/build.gradle` file (not the app-level build.gradle):

```gradle
allprojects {
    afterEvaluate { project ->
        if (project.hasProperty("android")) {
            // Fix for react-native-signature-capture task dependency issue
            project.tasks.withType(com.android.build.gradle.internal.tasks.MergeResources) { mergeTask ->
                if (mergeTask.path.contains('reactnativesignaturecapture')) {
                    project.rootProject.allprojects { otherProject ->
                        otherProject.tasks.withType(com.android.build.gradle.tasks.GenerateResValues) { generateTask ->
                            if (generateTask.path.contains('react-native-signature-capture')) {
                                def mergeVariant = mergeTask.name.replaceAll('package|Resources', '').toLowerCase()
                                def generateVariant = generateTask.name.replaceAll('generate|ResValues', '').toLowerCase()
                                if (mergeVariant == generateVariant) {
                                    mergeTask.dependsOn generateTask
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
```

## Solution 2: Update Gradle settings.gradle

In your main project's `android/settings.gradle`, ensure the include statement uses consistent naming:

```gradle
include ':react-native-signature-capture'
project(':react-native-signature-capture').projectDir = new File(rootProject.projectDir, '../node_modules/react-native-signature-capture/android')
```

## Solution 3: Clean and rebuild

After applying either solution:

1. Clean your project:
   ```bash
   cd android && ./gradlew clean
   ```

2. Clear React Native cache:
   ```bash
   npx react-native start --reset-cache
   ```

3. Rebuild:
   ```bash
   cd android && ./gradlew assembleDebug
   ```
