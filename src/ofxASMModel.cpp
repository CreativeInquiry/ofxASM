#include "ofxASMModel.h"

//using namespace StatModel;

ofxASM::ofxASM() {}

ofxASM::~ofxASM() {}

bool ofxASM::loadModel(const string &file) {
	if(!ofFile::doesFileExist(file)) {
		ofLogError("ofxASM") << "cannot load model, \"" << file << "\" doesn't exist";
		return false;
	}
	model.loadFromFile(file);
	return true;
}

void ofxASM::saveModel(const string &file) {
	model.saveToFile(file);
}

bool ofxASM::buildModel(const string &shapeDefFile, const string &ptsListFile) {
	if(!ofFile::doesFileExist(shapeDefFile)) {
		ofLogError("ofxASM") << "cannot load shape definition, \"" << shapeDefFile << "\" doesn't exist";
		return false;
	}
	if(!ofFile::doesFileExist(ptsListFile)) {
		ofLogError("ofxASM") << "cannot load points list, \"" << ptsListFile << "\" doesn't exist";
		return false;
	}
	model.buildModel(shapeDefFile, ptsListFile);
	return true;
}

bool ofxASM::fit(cv::Mat image) {
	
	ASMFitResult result = model.fit(image);
	
	// if transform wasn't set, assume nothing was found
	if(result.transformation.Xt == 0 && result.transformation.Yt == 0 &&
	   result.transformation.a = 1 && result.transformation.b == 0) {
		return false;
	}
	
	contours.clear();
	
	vector< Point_<int> > points;
	result.toPointList(points);
	contours.push_back(toOF(points));
	
	return true;
}

bool ofxASM::fitAll(cv::Mat image, vector<ofRectangle> &detectedObjs) {

	vector<ASMFitResult> results = model.fitAll(image, toCv(detectedObjcs));
	
	if(results.size() == 0) {
		return false;
	}
	
	contours.clear();
	
	vector< Point_<int> > points;
	for(int i = 0; i < results.size(); ++i) {
		result[i].toPointList(points);
		contours.push_back(toOF(points));
		points.clear();
	}
	
	return true;
}

void ofxASM::draw(float x=0, float y=0) {
	ofPushMatrix();
		ofTranslate(x, y, 0);
		ofSetHexColor(0xFF00FF);
		for(int i = 0; i < contours.size(); ++i) {
			contours.draw();
		}
	ofPopMatrix();
}

void ofxASM::draw(float x, float y, float w, float h) {
}
