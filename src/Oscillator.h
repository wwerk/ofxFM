//
// Created by WKWerk on 30/01/2022.
//

#ifndef A1_2_OSCILLATOR_H
#define A1_2_OSCILLATOR_H

#include "ofMain.h"


class Oscillator {
public:
    /// CONSTRUCTORS
    Oscillator();
    Oscillator(float frequency);
    Oscillator(float frequency, float volume);
    Oscillator(float frequency, float volume, float panning, int sampleRate);
    /// SETTERS
    virtual void setFreq(float frequency);
    void setVol(float volume);
    void setPan(float panorama);
    /// GETTERS
    virtual float getFreq();
    float getVol();
    float getPan();
    /// SOUND SYNTHESIS
    virtual vector<float> &nextBuffer(ofSoundBuffer &buffer);
    virtual vector<float> &nextBuffer(ofSoundBuffer &buffer, vector<float> &modBuf, float modAmp);

protected:
    float freq;
    float phase;
    float phaseAdder;
    float phaseAdderTarget;
    float vol;
    float pan;
    float panTarget;
    int sampRate;
    vector<float> out;
};


#endif //A1_2_OSCILLATOR_H
