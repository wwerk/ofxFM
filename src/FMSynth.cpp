//
// Created by WKWerk on 30/01/2022.
//

#include "FMSynth.h"
/// CONSTRUCTOR
FMSynth::FMSynth(float carFrequency, float modFrequency, float modAmplitude) {
    carFreq = carFrequency;
    modFreq = modFrequency;
    modAmp = modAmplitude;
    vol = 0.5; // default volume
    pan = 0.5; // default panning
    panTarget = 0.5;
    sampRate = 44100; // default sample rate if not provided
    carrier = Oscillator(carFreq);
    modulator = Oscillator(modFreq);
    carOut.assign(512, 0.);
    modOut.assign(512, 0.);
}

/// SOUND SYNTHESIS
vector<float> & FMSynth::nextBuffer(ofSoundBuffer &buffer) {
    modOut = modulator.nextBuffer(buffer); // calculate modulator values
    modOut; // scale by modulation amplitude
    carOut = carrier.nextBuffer(buffer, modOut, modAmp); // calculate carrier values
    return carOut; // only carrier buffer is returned, mod needs a getter
}
/// SETTERS
void FMSynth::setFreq(float frequency) {
    setCarFreq(frequency);
    carrier.setFreq(carFreq);
}

void FMSynth::setCarFreq(float carFrequency) {
    carFreq = carFrequency;
    carrier.setFreq(carFreq);
}

void FMSynth::setModFreq(float modFrequency) {
    modFreq = modFrequency;
    modulator.setFreq(modFreq);
}

void FMSynth::setModAmp(float modAmplitude) {
    modAmp = modAmplitude;
}

void FMSynth::setPan(float panning) {
    pan = panning;
    carrier.setPan(pan);
}

void FMSynth::setVolume(float volume) {
    vol = volume;
}

/// GETTERS
float FMSynth::getFreq() {
    return getCarFreq();
}

float FMSynth::getCarFreq() {
    return carFreq;
}

float FMSynth::getModFreq() {
    return modFreq;
}

float FMSynth::getModAmp() {
    return modAmp;
}

float FMSynth::getPan() {
    return pan;
}

float FMSynth::getVol() {
    return vol;
}

vector<float> &FMSynth::getModOut() {
    return modOut;
}



