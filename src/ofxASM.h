/*
 * 2013 Dan Wilcox <danomatika@gmail.com>
 * CMU Studio for Creative Inquiry http://studioforcreativeinquiry.org
 */
#pragma once

#include "ofMain.h"
#include "ofxCv.h"

#include "asmmodel.h"

// wrapper around asmlib-opencv, a library for Active Shape Models
// site: https://code.google.com/p/asmlib-opencv
// docs: http://chenxing.name/docs/asmlib/index.html
// ASM: https://en.wikipedia.org/wiki/Active_shape_model
class ofxASM {

	public:
		
		ofxASM();
		
		// load an existing model file
		bool loadModel(const string &file);
		
		// build a model from a shape definition and points list,
		// see https://code.google.com/p/asmlib-opencv/wiki/BuildModel
		// for how to create these files as well as the training data set in
		// example/bin/data/training
		//
		// in addition to the individual .pts files listed in the points list,
		// you need the matching image the points refer to when training, so
		// jpg/i000qa-fn.jpg.pts must have an accompanying jpg/i000qa-fn.jpg
		//
		// note that the file extension of the .pts file is removed to find
		// the correct path to the training image
		bool buildModel(const string &shapeDefFile, const string &ptsListFile);
		
		// save the current model, use this after building ...
		bool saveModel(const string &file);
	
		// run object detection and fit the ASM model on each detected region
		bool fitAll(cv::Mat image, vector<cv::Rect> &detectedObjs);
		bool fit(cv::Mat image); // fit over the whole image
	
		// OF conversion wrappers
		bool fitAll(ofBaseHasPixels &hasPixels, vector<ofRectangle> &detectedObjs);
		bool fit(ofBaseHasPixels &hasPixels);
	
		// draw the current contours
		void draw(float x=0, float y=0);
		void draw(float x, float y, float w, float h);
	
		vector<ofPolyline> contours; // detected contours
		int width, height;			 // dimensions of the source image
	
	protected:
	
		StatModel::ASMModel model;
		bool isLoaded;
};
