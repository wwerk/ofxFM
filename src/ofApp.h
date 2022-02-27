#pragma once

#include "ofMain.h"
#include "Oscillator.h"
#include "FMSynth.h"

class ofApp : public ofBaseApp {

public:

    void setup();
    void update();
    void draw();

    void keyPressed(int key);

    void keyReleased(int key);

    void mouseMoved(int x, int y);

    void mouseDragged(int x, int y, int button);

    void mousePressed(int x, int y, int button);

    void mouseReleased(int x, int y, int button);

    void mouseEntered(int x, int y);

    void mouseExited(int x, int y);

    void windowResized(int w, int h);

    void dragEvent(ofDragInfo dragInfo);

    void gotMessage(ofMessage msg);

    // non-linear mapping function
    float map(float in, float inMin, float inMax, float outMin, float outMax, float shaper);

    // randomize parameters
    void randomize();

    // spectroscope drawing function
    void drawScope(float x, float y, float weight, ofColor color,
           vector<float> &xAmps, vector<float> &yAmps);



    /// audio stuff
    void audioOut(ofSoundBuffer &buffer);
    ofSoundStream soundStream;

    int sampleRate;
    float volume;
    float pan;

    vector<float> modOut;
    vector<float> carOut;


    //------------------- for FM synthesis

    FMSynth synth{400.f, 1111.f, 3.f};
//    Oscillator osc{};

    float modAmpRange;

    /// variables for the visual
    float midw;
    float midh;

    ofColor brushColor;


};
