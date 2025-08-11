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
            project.tasks.matching { it.name.contains('package') && it.name.contains('Resources') }.all { packageTask ->
                project.rootProject.allprojects { otherProject ->
                    otherProject.tasks.matching { it.name.contains('generate') && it.name.contains('ResValues') }.all { generateTask ->
                        // Match variants (debug/release)
                        def packageVariant = packageTask.name.replaceAll('package|Resources', '').toLowerCase()
                        def generateVariant = generateTask.name.replaceAll('generate|ResValues', '').toLowerCase()
                        if (packageVariant == generateVariant) {
                            packageTask.dependsOn generateTask
                        }
                    }
                }
            }
        }
    }
}
```

## Solution 2: Specific fix for the exact error

If the above doesn't work, add this more specific fix to your main project's `android/build.gradle`:

```gradle
gradle.projectsEvaluated {
    tasks.matching { it.path.contains('reactnativesignaturecapture') && it.name.contains('packageDebugResources') }.all { task ->
        task.dependsOn tasks.matching { it.path.contains('react-native-signature-capture') && it.name.contains('generateDebugResValues') }
    }
    tasks.matching { it.path.contains('reactnativesignaturecapture') && it.name.contains('packageReleaseResources') }.all { task ->
        task.dependsOn tasks.matching { it.path.contains('react-native-signature-capture') && it.name.contains('generateReleaseResValues') }
    }
}
```

## Solution 3: Update Gradle settings.gradle

In your main project's `android/settings.gradle`, ensure the include statement uses consistent naming:

```gradle
include ':react-native-signature-capture'
project(':react-native-signature-capture').projectDir = new File(rootProject.projectDir, '../node_modules/react-native-signature-capture/android')
```

## Solution 4: Clean and rebuild

After applying any solution:

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

## Additional Notes

- This issue occurs because newer versions of Gradle are stricter about task dependencies
- The library has been updated to work with React Native 0.80+, but some consuming projects may need additional configuration
- If you're still having issues, try updating your main project's Gradle version to 8.3 or higher
