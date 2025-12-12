#ifndef VOICELAB_AUDIO_PROCESSOR_H
#define VOICELAB_AUDIO_PROCESSOR_H

#include <cstdint>
#include <vector>
#include <cmath>

class AudioProcessor {
public:
    AudioProcessor();
    ~AudioProcessor();
    
    bool initialize(int sampleRate, int bufferSize);
    void shutdown();
    
    bool startProcessing();
    void stopProcessing();
    
    // DSP processing function
    float processBuffer(const float* input, float* output, int numSamples);
    
    // Test function for DSP performance
    float testProcessing();
    
    const char* getVersion() const { return "1.0.0-native"; }
    
private:
    bool isInitialized;
    bool isProcessing;
    int sampleRate;
    int bufferSize;
    
    // Simple DSP example: apply gain and simple filter
    void applyGain(const float* input, float* output, int numSamples, float gain);
    void applySimpleFilter(float* buffer, int numSamples);
    
    // Filter state
    float prevSample;
};

#endif // VOICELAB_AUDIO_PROCESSOR_H
