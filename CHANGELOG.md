# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2025-08-11

### Added
- Support for React Native 0.80+
- Migration guide in README
- Fixed Gradle task dependency issues for modern Android builds

### Changed
- **BREAKING**: Minimum React Native version is now 0.80.0
- **BREAKING**: Minimum iOS version is now 12.4
- **BREAKING**: Minimum Android API level is now 21
- Updated to ES6 import/export syntax
- Updated iOS native code to use direct event callbacks instead of deprecated RCTEventDispatcher
- Updated Android native code to use AndroidX instead of Support Library
- Updated Android build tools and SDK versions
- Updated podspec to use React-Core dependency
- Migrated from Java 8 to Java 11 for Android compilation
- Removed deprecated Facebook Infer annotations
- Updated Gradle wrapper from 2.8 to 8.3
- Added namespace declaration for Android builds

### Fixed
- Compatibility with React Native 0.80+ event system
- Modern Android build configuration
- Updated native dependencies
- Gradle task dependency resolution for packageDebugResources
- Android build compatibility with newer Gradle versions

### Removed
- Support for React Native versions below 0.80
- Deprecated iOS and Android APIs
- Old buildToolsVersion specifications

## [0.4.11] - Previous Release
- Last version supporting React Native 0.47+
