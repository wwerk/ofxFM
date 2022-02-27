//
// Created by WKWerk on 30/01/2022.
//

#ifndef A1_2_FMSYNTH_H
#define A1_2_FMSYNTH_H

#include "Oscillator.h"

class FMSynth : public Oscillator {
public:
    /// CONSTRUCTOR
    FMSynth(float carFrequency, float modFrequency, float modAmplitude);

    /// SETTERS
    void setFreq(float frequency); // in case it happens
    void setCarFreq(float carFrequency);
    void setModFreq(float modFrequency);
    void setModAmp(float modAmplitude);

    void setPan(float panning);
    void setVolume(float volume);

    /// GETTERS
    float getFreq(); // in case it happens
    float getCarFreq();
    float getModFreq();
    float getModAmp();

    float getPan();
    float getVol();

    vector<float> & getModOut();

    /// SYNTHESIS
    vector<float> & nextBuffer(ofSoundBuffer &buffer);


private:
    // two oscillators used for FM
    Oscillator carrier;
    Oscillator modulator;
    // and their parameters
    float carFreq;
    float modFreq;
    float modAmp;
    // buffers
    vector<float> carOut;
    vector<float> modOut;
};


#endif //A1_2_FMSYNTH_H
