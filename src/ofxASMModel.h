#pragma once

#include "ofMain.h"
#include "ofxCv.h"

#include "asmmodel.h"
#include "modelfile.h"

class ofxASM {

	public:
	
		ofxASM();
		~ofxASM();
		
		bool loadModel(const string &file);
		void saveModel(const string &file);
		
		// see data/muct/README.txt
		// and https://code.google.com/p/asmlib-opencv/wiki/BuildModel
		void buildModel(const string &shapeDefFile, const string &ptsListFile);
		
		//vector<ofxASMFitResult> fitAll(const cv::Mat &img, const vector<ofRectangle> &detectedObjs);
		//ofxASMFitResult fit(const cv::Mat &img);
	
		bool fit(cv::Mat image);
		bool fitAll(cv::Mat image, vector<ofRectangle> &detectedObjs);
	
		void draw(float x=0, float y=0);
		void draw(float x, float y, float w, float h);
	
		vector<ofPolyline> contours;
	
	protected:
	
		StatModel::ASMModel model;
};
