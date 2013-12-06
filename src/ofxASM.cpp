/*
 * 2013 Dan Wilcox <danomatika@gmail.com>
 * CMU Studio for Creative Inquiry http://studioforcreativeinquiry.org
 */
#include "ofxASM.h"

using namespace cv;
using namespace ofxCv;
using namespace StatModel;

ofxASM::ofxASM() {
	isLoaded = false;
}

bool ofxASM::loadModel(const string &file) {
	if(!ofFile::doesFileExist(ofToDataPath(file))) {
		ofLogError("ofxASM") << "cannot load model, \"" << file << "\" doesn't exist";
		isLoaded = false;
		return false;
	}
	model.loadFromFile(ofToDataPath(file));
	isLoaded = true;
	return true;
}

bool ofxASM::buildModel(const string &shapeDefFile, const string &ptsListFile) {
	if(!ofFile::doesFileExist(ofToDataPath(shapeDefFile))) {
		ofLogError("ofxASM") << "cannot load shape definition, \"" << shapeDefFile << "\" doesn't exist";
		return false;
	}
	if(!ofFile::doesFileExist(ofToDataPath(ptsListFile))) {
		ofLogError("ofxASM") << "cannot load points list, \"" << ptsListFile << "\" doesn't exist";
		return false;
	}
	model.buildModel(ofToDataPath(shapeDefFile), ofToDataPath(ptsListFile));
	isLoaded = true;
	return true;
}

bool ofxASM::saveModel(const string &file) {
	if(!isLoaded) {
		ofLogWarning("ofxASM") << "ignoring save, model not loaded";
		return false;
	}
	model.saveToFile(ofToDataPath(file));
	if(!ofFile::doesFileExist(ofToDataPath(file))) {
		return false;
	}
	return true;
}

bool ofxASM::fit(cv::Mat image) {
	
	if(!isLoaded) {
		return false;
	}
	
	width = image.cols;
	height = image.rows;
	
	ASMFitResult result = model.fit(image);
	
	// if transform wasn't set, assume nothing was found
	if(result.transformation.Xt == 0 && result.transformation.Yt == 0 &&
	   result.transformation.a == 1 && result.transformation.b == 0) {
		return false;
	}
	
	contours.clear();
	
	vector< Point_<int> > points;
	result.toPointList(points);
	contours.push_back(toOf(points));
	
	return true;
}

bool ofxASM::fitAll(cv::Mat image, vector<cv::Rect> &detectedObjs) {
	
	if(!isLoaded) {
		return false;
	}
	
	width = image.cols;
	height = image.rows;

	vector<ASMFitResult> results = model.fitAll(image, detectedObjs);
	
	if(results.size() == 0) {
		return false;
	}
	
	contours.clear();
	
	vector< Point_<int> > points;
	for(int i = 0; i < results.size(); ++i) {
		results[i].toPointList(points);
		contours.push_back(toOf(points));
		points.clear();
	}
	
	return true;
}

bool ofxASM::fitAll(ofBaseHasPixels &hasPixels, vector<ofRectangle> &detectedObjs) {
	vector<cv::Rect> rects;
	for(int i = 0; i < detectedObjs.size(); ++i) {
		rects.push_back(toCv(detectedObjs[i]));
	}
	return fitAll(toCv(hasPixels), rects);
}

bool ofxASM::fit(ofBaseHasPixels &hasPixels) {
	return fit(toCv(hasPixels));
}

void ofxASM::draw(float x, float y) {
	ofPushMatrix();
		ofTranslate(x, y, 0);
		ofNoFill();
		for(int i = 0; i < contours.size(); ++i) {
			contours[i].draw();
		}
	ofPopMatrix();
}

void ofxASM::draw(float x, float y, float w, float h) {
	ofPushMatrix();
		ofTranslate(x, y, 0);
		ofScale((float) (w/width), (float) (h/height), 1);
		ofNoFill();
		for(int i = 0; i < contours.size(); ++i) {
			contours[i].draw();
		}
	ofPopMatrix();
}
