//
// Created by WKWerk on 30/01/2022.
//

#include "Oscillator.h"
/// CONSTRUCTORS
Oscillator::Oscillator() {
    freq = 440; // default frequency
    vol = 0.5; // default volume
    pan = 0.5; // default panning
    sampRate = 44100; // default sample rate if not provided

    //calculate how much phase will have to be added to get wanted frequency
    phaseAdderTarget = static_cast<float>((freq / (float) sampRate) * TWO_PI);
    out.assign(512, 0.);
}

Oscillator::Oscillator(float frequency) {
    freq = frequency;
    vol = 0.5; // default volume
    pan = 0.5; // default panning
    panTarget = 0.5;
    sampRate = 44100; // default sample rate if not provided

    //calculate how much phase will have to be added to get wanted frequency
    phaseAdderTarget = static_cast<float>((freq / (float) sampRate) * TWO_PI);
    out.assign(512, 0.);
}

Oscillator::Oscillator(float frequency, float volume) {
    freq = frequency;
    vol = volume;
    pan = 0.5; // default panning
    sampRate = 44100; // set default sample rate if not provided

    //calculate how much phase will have to be added to get wanted frequency
    phaseAdderTarget = static_cast<float>((freq / (float) sampRate) * TWO_PI);
    out.assign(512, 0.);
}

Oscillator::Oscillator(float frequency, float volume, float panning, int sampleRate) {
    freq = frequency;
    vol = volume;
    pan = panning;
    sampRate = sampleRate;
    out.assign(512, 0.);
}
/// GETTERS
float Oscillator::getFreq() {
    return freq;
};

float Oscillator::getVol() {
    return vol;
}

float Oscillator::getPan() {
    return pan;
}
/// SETTERS
void Oscillator::setFreq(float frequency) {
    freq = frequency;
    phaseAdderTarget = static_cast<float>((freq / (float) sampRate) * TWO_PI);
}

void Oscillator::setVol(float volume) {
    vol = volume;
}

void Oscillator::setPan(float panorama) {
    panTarget = panorama; // this will be smoothed later to prevent clicks
}



/// SOUND SYNTHESIS
vector<float> & Oscillator::nextBuffer(ofSoundBuffer &buffer) {
    sampRate = buffer.getSampleRate(); // update sample rate just in case
    // keep phase in the range of 0-TWO_PI so sin(n) doesn't break
    while (phase > TWO_PI) {
        phase -= TWO_PI;
    }
    // some basic smoothing for panning and (not) frequency changes
    // the latter needs to go since it would make FM impossible
    pan = 0.95f * pan + 0.05f * panTarget;
//    phaseAdder = 0.95f * phaseAdder + 0.05f * phaseAdderTarget;
    phaseAdder = phaseAdderTarget;
    for (size_t i = 0; i < buffer.getNumFrames(); i++) {
        phase += phaseAdder; // progress through the phase cycle at appropriate pace
        float sample = sin(phase);
//        buffer[i * buffer.getNumChannels()    ] = sample * (1.f - pan); // left channel
//        buffer[i * buffer.getNumChannels() + 1] = sample * (pan); // right channel
        out[i] = sample;
    }
//    buffer *= vol; // return after gain scaling
    return out;
}

/// SOUND SYNTHESIS WITH MODULATION OF FREQUENCY
vector<float> & Oscillator::nextBuffer(ofSoundBuffer &buffer, vector<float> &modBuf, float modAmp) {
    sampRate = buffer.getSampleRate(); // update sample rate just in case
    // keep phase in the range of 0-TWO_PI so sin(n) doesn't break
    while (phase > TWO_PI) {
        phase -= TWO_PI;
    }
    // some basic smoothing for panning and (maybe) frequency changes
    // the latter needs to go since it would make FM impossible
    pan = 0.95f * pan + 0.05f * panTarget;
//    phaseAdder = 0.95f * phaseAdder + 0.05f * phaseAdderTarget;
    for (size_t i = 0; i < buffer.getNumFrames(); i++) {
        phaseAdder = static_cast<float>((freq + modBuf[i] * modAmp / (double) sampRate) * TWO_PI);
        phase += phaseAdder; // progress through the phase cycle at appropriate pace
        float sample = sin(phase); // calculate sample value
//        buffer[i * buffer.getNumChannels()    ] = sample * (1.f - pan); // left out
//        buffer[i * buffer.getNumChannels() + 1] = sample * pan; // right out
        out[i] = sample;
    }
//    return buffer *= vol;
    return out;
}


