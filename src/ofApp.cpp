#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    ofSetVerticalSync(true);
    ofBackground(0);

    /// audio setup
    int bufferSize = 512;
    sampleRate = 44100;

    // these are used for
    modOut.assign(bufferSize, 0.0);
    carOut.assign(bufferSize, 0.0);

    soundStream.printDeviceList();
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);

    modAmpRange = 100.f;

    // These are to save some typing
    midw = ofGetWidth() * 0.5;
    midh = ofGetHeight() * 0.5;


    // Set oscilloscope color
    brushColor = ofColor(255, 20);

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofPushMatrix();
    ofTranslate(midw, midh);
    ofNoFill();
    ofBeginShape();
    for (int i = 0; i < carOut.size(); i++) {
        float ix = carOut[i]; // same as above
        ix *= midw;

        float iy = modOut[i];
        iy *= midh;
        drawScope(ix, iy, 1., brushColor, carOut, modOut);
//        can also draw it with regular vertices
//        ofVertex(ix, iy);
    }
    ofEndShape();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::drawScope(float x, float y, float weight, ofColor color,
        vector<float> &xAmps, vector<float> &yAmps) {
    // first move to the destined coordinates
    ofPushMatrix();
    ofTranslate(x, y);
    // setup drawing parameters
    ofSetColor(color);
    ofNoFill();
    ofSetLineWidth(weight);
    // actual drawing happens here
    ofBeginShape();
    for (int i = 0; i < xAmps.size(); i++) {
        // ix - modulator channel
        float ix = xAmps[i]; // it's normalised already
        ix *= midw; // scaled to given width

        // iy - carrier channel
        float iy = yAmps[i]; // same as above
        iy *= midh;

        ofVertex(ix, iy); // entire shape scaled to fit the window
    }
    ofEndShape();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer &buffer) {
    carOut = synth.nextBuffer(buffer);
    modOut = synth.getModOut();
//    carOut = osc.nextBuffer(buffer);
    buffer.copyFrom(carOut, 1, 44100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == ' ') {
        randomize();
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    float p = (float) x / (float) ofGetWidth();
    synth.setPan(p); // panning left-right mapped to mouse X
//    cout << p << endl;
    float a = map(y, 0.f, ofGetHeight(), modAmpRange, 0.f, 1.4);
    synth.setModAmp(a); // amplitude of modulation mapped to mouse Y
//    cout << a << endl;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    randomize();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

//--------------------------------------------------------------
/// RANDOMIZE SYNTH PARAMETERS
void ofApp::randomize() {
    float c = 50 * int(ofRandom(1, 40));
    synth.setFreq(c); //randomise carrier
    float m = c * int(ofRandom(1, 40)) / 80.f;
    synth.setModFreq(m); //randomise modulator
    float a = ofRandom(m/10, m*5);
    modAmpRange = a; // randomise range of modulation amplitude

    cout
    << "CARRIER: " << synth.getFreq()
    << " MODULATOR: " << synth.getModFreq()
    << " MAX MODULATOR AMPLITUDE: " << modAmpRange
    << endl;
}

//--------------------------------------------------------------
/// NON-LINEAR MAPPING FUNCTION by zach
// https://forum.openframeworks.cc/t/non-linear-ofmap/13508
float ofApp::map(float in, float inMin, float inMax, float outMin, float outMax, float shaper) {
// (1) convert to pct (0-1)
    float pct = ofMap (in, inMin, inMax, 0, 1, true);
// raise this number to a power
    pct = powf(pct, shaper);
    float out = ofMap(pct, 0,1, outMin, outMax, true);
    return out;
}



