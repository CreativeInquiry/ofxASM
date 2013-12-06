/*
 * 2013 Dan Wilcox <danomatika@gmail.com>
 * CMU Studio for Creative Inquiry http://studioforcreativeinquiry.org
 */
#include "ofApp.h"

using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetVerticalSync(true);
	ofBackground(0);

	grabber.initGrabber(640, 480);

	faceCascade.load(ofToDataPath("haarcascade_frontalface_alt.xml"));
	
	#ifdef BUILD_MODEL
		if(model.buildModel("training/muct76.def", "training/camA_Q.list")) {
			ofLogNotice() << "built model from muct76.def & camA_Q.list";
		}
		if(model.saveModel("models/muct76.model")) {
			ofLogNotice() << "saved current model to muct76.model";
		}
		if(model.loadModel("models/muct76.model")) {
			ofLogNotice() << "loaded model from muct76.model";
		}
	#else
		model.loadModel("models/color_asm75.model");
	#endif
	
	mode = FIT_ALL;
}

//--------------------------------------------------------------
void ofApp::update() {

	// grabber & asm fitting
	grabber.update();
	if(grabber.isFrameNew()) {
	
		if(mode == FIT_ALL) {
			
			// do face detection first
			// note: ONLY the largest face is processed
			//       (otherwise face detection would be too slow)
			vector<cv::Rect> faces;
			faceCascade.detectMultiScale(toCv(grabber), faces, 1.2, 2,
				CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE,
				cv::Size(60, 60));
				
			// fit the model to the given set of bounding boxes
			model.fitAll(toCv(grabber), faces);
		}
		else {
			// fit the model to the whole image
			model.fit(grabber);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetColor(255);
	grabber.draw(0, 0);
	
	ofSetHexColor(0xFF00FF);
	model.draw(0, 0);
	
	ofSetColor(255);
	ofDrawBitmapString(ofToString((int)ofGetFrameRate()), 12, ofGetHeight()-14);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	switch(key) {
	
		case '1':
			mode = FIT_ALL;
			ofLogNotice() << "mode: FIT_ALL";
			break;
			
		case '2':
			mode = FIT;
			ofLogNotice() << "mode: FIT";
			break;
	}
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
