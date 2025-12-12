# VoiceLab Android

A high-performance Native Android application for audio processing and DSP (Digital Signal Processing) with low-latency control.

## Features

- 🎵 **Native C++ Audio Processing**: High-performance DSP using C++17
- ⚡ **Low-Latency Audio**: Optimized for professional audio applications
- 🔧 **CMake Build System**: Efficient native code compilation
- 📦 **Dual Output**: Builds both APK and AAB artifacts
- ☁️ **Cloud-Based CI/CD**: GitHub Actions for automated builds
- 💻 **Codespaces Ready**: Full development environment in the cloud

## Architecture

This project follows **Native Android (Option A)** architecture:
- **Frontend**: Kotlin with Material Design 3
- **Backend**: Native C++ for audio/DSP processing
- **Build System**: Gradle + CMake
- **CI/CD**: GitHub Actions

## Prerequisites

### Local Development
- Android Studio Hedgehog (2023.1.1) or later
- JDK 17
- Android SDK 34
- CMake 3.22.1+
- NDK (installed via Android Studio)

### GitHub Codespaces (Recommended)
No local setup required! The repository is configured for GitHub Codespaces.

## Getting Started

### Option 1: GitHub Codespaces (No PC Needed)

1. Click the **Code** button on GitHub
2. Select **Codespaces** tab
3. Click **Create codespace on main**
4. Wait for the environment to initialize
5. Build the project:
   ```bash
   ./gradlew assembleDebug
   ```

### Option 2: Local Development

1. Clone the repository:
   ```bash
   git clone https://github.com/guicash663/voicelab-android.git
   cd voicelab-android
   ```

2. Open in Android Studio:
   - File → Open → Select the project directory
   - Wait for Gradle sync to complete

3. Build the project:
   - Build → Make Project (Ctrl+F9)
   - Or use command line: `./gradlew assembleDebug`

## Building

### Build APK (Android Package)

```bash
# Debug APK
./gradlew assembleDebug

# Release APK
./gradlew assembleRelease
```

Output: `app/build/outputs/apk/`

### Build AAB (Android App Bundle)

```bash
# Release AAB for Google Play
./gradlew bundleRelease
```

Output: `app/build/outputs/bundle/release/`

### Build Both Formats

```bash
./gradlew assembleRelease bundleRelease
```

## CI/CD - GitHub Actions

Every push and pull request triggers automated builds:

1. **Automated Compilation**: Cloud-based Android toolchain
2. **Multiple Outputs**: Debug APK, Release APK, and Release AAB
3. **Artifact Storage**: All builds saved for 30 days
4. **Build Reports**: Detailed summary in workflow runs

### Download Build Artifacts

1. Go to **Actions** tab on GitHub
2. Select the workflow run
3. Download artifacts from the **Artifacts** section

## Project Structure

```
voicelab-android/
├── app/
│   ├── src/
│   │   ├── main/
│   │   │   ├── java/com/voicelab/android/    # Kotlin code
│   │   │   ├── cpp/                           # Native C++ code
│   │   │   │   ├── CMakeLists.txt            # CMake build config
│   │   │   │   ├── native-lib.cpp            # JNI bindings
│   │   │   │   ├── audio_processor.h         # Audio DSP header
│   │   │   │   └── audio_processor.cpp       # Audio DSP implementation
│   │   │   ├── res/                          # Android resources
│   │   │   └── AndroidManifest.xml           # App manifest
│   │   └── build.gradle                      # App build config
├── .github/
│   └── workflows/
│       └── android-build.yml                 # CI/CD workflow
├── build.gradle                              # Project build config
├── settings.gradle                           # Project settings
└── README.md                                 # This file
```

## Native Audio/DSP

The app includes a complete native audio processing pipeline:

- **Audio Processor**: C++ class for DSP operations
- **JNI Bindings**: Bridge between Kotlin and C++
- **Optimizations**: `-O3`, `-ffast-math`, `-funroll-loops`
- **Low-Latency**: Configured for professional audio requirements

### Key Native Methods

```kotlin
initNativeAudio()           // Initialize audio engine
startNativeProcessing()     // Start audio processing
stopNativeProcessing()      // Stop audio processing
testNativeAudioProcessing() // Run DSP test
getNativeVersion()          // Get native library version
```

## Permissions

The app requests the following permissions:
- `RECORD_AUDIO`: For audio input
- `MODIFY_AUDIO_SETTINGS`: For audio configuration

Hardware features:
- `android.hardware.audio.low_latency`: Low-latency audio support
- `android.hardware.audio.pro`: Professional audio features

## Development Workflow

1. **Code Changes**: Edit Kotlin or C++ code
2. **Build**: `./gradlew assembleDebug`
3. **Test**: Run on emulator or device
4. **Commit**: Push changes to GitHub
5. **CI/CD**: Automatic build and artifact generation

## Troubleshooting

### Gradle Build Fails
```bash
./gradlew clean
./gradlew assembleDebug --stacktrace
```

### CMake Issues
- Ensure CMake 3.22.1+ is installed
- Check NDK installation in Android Studio

### Permission Denied on gradlew
```bash
chmod +x gradlew
```

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## License

[Your License Here]

## Support

For issues and questions:
- Open an issue on GitHub
- Check existing documentation
- Review GitHub Actions logs for build errors
