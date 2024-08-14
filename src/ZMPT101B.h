#ifndef ZMPT101B_H
#define ZMPT101B_H

#include <Arduino.h>

class ZMPT101B {
public:
    ZMPT101B(uint8_t pin);
    void begin();
    float readVoltage();
    float readFrequency();
    
private:
    uint8_t _pin;
    float _calibrationFactor;
    float _offset;
    unsigned long _sampleWindow;
    int _samples[256];
    float _sumSquares;
    int _zeroCrossings;
    bool _lastSamplePositive;
    void _updateSamples();
};

#endif // ZMPT101B_H
