#include <jni.h>
#include <string>
#include <android/log.h>
#include "audio_processor.h"

#define LOG_TAG "VoiceLabNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// Global audio processor instance
static AudioProcessor* g_audioProcessor = nullptr;

extern "C" {

JNIEXPORT jboolean JNICALL
Java_com_voicelab_android_MainActivity_initNativeAudio(
    JNIEnv* env,
    jobject /* this */) {
    
    LOGI("Initializing native audio engine");
    
    if (g_audioProcessor == nullptr) {
        g_audioProcessor = new AudioProcessor();
    }
    
    // Initialize with default parameters
    bool result = g_audioProcessor->initialize(48000, 256);
    
    if (result) {
        LOGI("Native audio engine initialized successfully");
    } else {
        LOGE("Failed to initialize native audio engine");
    }
    
    return result;
}

JNIEXPORT void JNICALL
Java_com_voicelab_android_MainActivity_shutdownNativeAudio(
    JNIEnv* env,
    jobject /* this */) {
    
    LOGI("Shutting down native audio engine");
    
    if (g_audioProcessor != nullptr) {
        g_audioProcessor->shutdown();
        delete g_audioProcessor;
        g_audioProcessor = nullptr;
    }
}

JNIEXPORT jboolean JNICALL
Java_com_voicelab_android_MainActivity_startNativeProcessing(
    JNIEnv* env,
    jobject /* this */) {
    
    LOGI("Starting native audio processing");
    
    if (g_audioProcessor == nullptr) {
        LOGE("Audio processor not initialized");
        return false;
    }
    
    return g_audioProcessor->startProcessing();
}

JNIEXPORT void JNICALL
Java_com_voicelab_android_MainActivity_stopNativeProcessing(
    JNIEnv* env,
    jobject /* this */) {
    
    LOGI("Stopping native audio processing");
    
    if (g_audioProcessor != nullptr) {
        g_audioProcessor->stopProcessing();
    }
}

JNIEXPORT jfloat JNICALL
Java_com_voicelab_android_MainActivity_testNativeAudioProcessing(
    JNIEnv* env,
    jobject /* this */) {
    
    LOGI("Testing native audio processing");
    
    if (g_audioProcessor == nullptr) {
        LOGE("Audio processor not initialized");
        return 0.0f;
    }
    
    float result = g_audioProcessor->testProcessing();
    LOGI("Test result: %.4f", result);
    
    return result;
}

JNIEXPORT jstring JNICALL
Java_com_voicelab_android_MainActivity_getNativeVersion(
    JNIEnv* env,
    jobject /* this */) {
    
    if (g_audioProcessor == nullptr) {
        g_audioProcessor = new AudioProcessor();
    }
    
    const char* version = g_audioProcessor->getVersion();
    return env->NewStringUTF(version);
}

} // extern "C"
