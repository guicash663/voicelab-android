#include "audio_processor.h"
#include <android/log.h>
#include <cstring>

// Define M_PI for cross-platform compatibility
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define LOG_TAG "VoiceLabNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

AudioProcessor::AudioProcessor()
    : isInitialized(false)
    , isProcessing(false)
    , sampleRate(48000)
    , bufferSize(256)
    , prevSample(0.0f)
{
}

AudioProcessor::~AudioProcessor() {
    shutdown();
}

bool AudioProcessor::initialize(int sr, int bs) {
    if (isInitialized) {
        LOGI("AudioProcessor already initialized");
        return true;
    }
    
    sampleRate = sr;
    bufferSize = bs;
    prevSample = 0.0f;
    
    isInitialized = true;
    LOGI("AudioProcessor initialized: sampleRate=%d, bufferSize=%d", sampleRate, bufferSize);
    return true;
}

void AudioProcessor::shutdown() {
    if (!isInitialized) {
        return;
    }
    
    stopProcessing();
    isInitialized = false;
    LOGI("AudioProcessor shutdown");
}

bool AudioProcessor::startProcessing() {
    if (!isInitialized) {
        LOGE("Cannot start processing: not initialized");
        return false;
    }
    
    isProcessing = true;
    LOGI("Processing started");
    return true;
}

void AudioProcessor::stopProcessing() {
    isProcessing = false;
    LOGI("Processing stopped");
}

float AudioProcessor::processBuffer(const float* input, float* output, int numSamples) {
    if (!isProcessing || !isInitialized) {
        return 0.0f;
    }
    
    // Apply gain
    const float gain = 0.8f;
    applyGain(input, output, numSamples, gain);
    
    // Apply simple low-pass filter
    applySimpleFilter(output, numSamples);
    
    // Calculate RMS for monitoring
    float sum = 0.0f;
    for (int i = 0; i < numSamples; i++) {
        sum += output[i] * output[i];
    }
    
    return std::sqrt(sum / numSamples);
}

void AudioProcessor::applyGain(const float* input, float* output, int numSamples, float gain) {
    for (int i = 0; i < numSamples; i++) {
        output[i] = input[i] * gain;
    }
}

void AudioProcessor::applySimpleFilter(float* buffer, int numSamples) {
    // Simple one-pole low-pass filter
    const float alpha = 0.1f;  // Filter coefficient
    
    for (int i = 0; i < numSamples; i++) {
        buffer[i] = alpha * buffer[i] + (1.0f - alpha) * prevSample;
        prevSample = buffer[i];
    }
}

float AudioProcessor::testProcessing() {
    if (!isInitialized) {
        initialize(48000, 256);
    }
    
    // Create test signal (sine wave)
    const int testSize = 1024;
    std::vector<float> inputBuffer(testSize);
    std::vector<float> outputBuffer(testSize);
    
    const float frequency = 440.0f; // A4 note
    const float amplitude = 0.5f;
    
    for (int i = 0; i < testSize; i++) {
        float t = static_cast<float>(i) / static_cast<float>(sampleRate);
        inputBuffer[i] = amplitude * std::sin(2.0f * M_PI * frequency * t);
    }
    
    // Process the buffer
    float rms = processBuffer(inputBuffer.data(), outputBuffer.data(), testSize);
    
    LOGI("Test processing completed: RMS=%.4f", rms);
    return rms;
}
