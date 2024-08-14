#include "ZMPT101B.h"

ZMPT101B::ZMPT101B(uint8_t pin) 
    : _pin(pin), _calibrationFactor(575.6), _offset(2048), _sampleWindow(2000) {
    // Constructor vacío
}

void ZMPT101B::begin() {
    pinMode(_pin, INPUT);
}

void ZMPT101B::_updateSamples() {
    _sumSquares = 0;
    _zeroCrossings = 0;
    _lastSamplePositive = false;
    unsigned long startTime = millis();

    for (int i = 0; i < 256; i++) {
        int sample = analogRead(_pin) - _offset;
        _sumSquares += sample * sample;

        if (sample > 0 && !_lastSamplePositive) {
            _zeroCrossings++;
            _lastSamplePositive = true;
        } else if (sample < 0) {
            _lastSamplePositive = false;
        }

        delay(_sampleWindow / 256); // Intervalo de muestreo
    }
}

float ZMPT101B::readVoltage() {
    _updateSamples();
    float rms = sqrt(_sumSquares / 256);
    return rms * (3.3 / 4095.0) * _calibrationFactor;
}

float ZMPT101B::readFrequency() {
    _updateSamples();
    float duration = _sampleWindow / 1000.0;
    return (_zeroCrossings / 2.0) / (duration / 2.0);
}
