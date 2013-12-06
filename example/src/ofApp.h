/*
 * 2013 Dan Wilcox <danomatika@gmail.com>
 * CMU Studio for Creative Inquiry http://studioforcreativeinquiry.org
 */
#pragma once

#include "ofMain.h"

#include "ofxASM.h"

// build a model from raw data, save and load it
//#define BUILD_MODEL

// keys:
//   1: FIT_ALL mode
//	 2: FIT mode
class ofApp : public ofBaseApp {

	public:
	
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
		ofVideoGrabber grabber;
		
		cv::CascadeClassifier faceCascade;
		ofxASM model;
		
		enum Mode {
			FIT_ALL, // uses the face finder then fits to the bounding box
			FIT		 // no face finder, tries to fit to the whole image
		} mode;
};
