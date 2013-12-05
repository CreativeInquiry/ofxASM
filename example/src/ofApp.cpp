#include "ofApp.h"

using namespace ofxCv;
//using namespace cv;

//--------------------------------------------------------------
void ofApp::setup() {

	grabber.initGrabber(640, 480);

	model.loadModel("haarcascade_frontalface_alt.xml");
}

//--------------------------------------------------------------
void ofApp::update() {

	grabber.update();
	if(grabber.isFrameNew()) {
		model.fit(toCv(grabber));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	grabber.draw(0, 0);
	model.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

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
