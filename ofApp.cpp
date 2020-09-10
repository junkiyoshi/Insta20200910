#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();

	ofTrueTypeFont font;
	font.loadFont("fonts/Kazesawa-Bold.ttf", 100, true, true, true);

	for (int i = 0; i < 2; i++) {

		for (char c = 'A'; c <= 'Z'; c++) {

			this->chara_path.push_back(font.getCharacterAsPoints(c, true, false));
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	int deg = 0;
	int deg_span = 5;
	int radius = 12;
	auto center_list = vector<glm::vec2>{glm::vec2(), glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD))};
	int center_list_index = 0;
	auto center = center_list[center_list_index];
	ofColor color;

	while (radius < ofGetWidth()) {
		
		int char_index = ofMap(ofNoise(deg * 0.0015 + ofGetFrameNum() * 0.005), 0, 1, 0, this->chara_path.size());

		auto point = center + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
		auto size = (2 * radius * PI) / 360 * deg_span;
		size = size < 22 ? size : 22;
		
		ofPushMatrix();
		ofTranslate(point);
		ofRotate(deg + 90);

		auto outline = this->chara_path[char_index].getOutline();

		ofBeginShape();
		for (int line_index = 0; line_index < outline.size(); line_index++) {

			if (line_index != 0) { ofNextContour(true); }

			auto vertices = outline[line_index].getVertices();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				auto point = (vertices[vertices_index] / 100 * size) + glm::vec2(size * -0.5, size * 0.5);
				ofVertex(point);
			}
		}
		ofEndShape(true);

		ofPopMatrix();


		deg += deg_span;
		if (deg % 180 == 0) {

			center_list_index++;
			center = center_list[center_list_index % center_list.size()];

			radius = glm::distance(point, center);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}