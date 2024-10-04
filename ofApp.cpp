#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 1.44);

	int v_span = 8;
	int u_span = 90;
	int R = 200;

	ofMesh face, line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	ofColor color;

	float noise_seed = ofRandom(1000);
	float len = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.01), 0, 1, -180, 360 * 4);
	for (int v = 0; v <= 360 + len; v += v_span * 1) {

		color.setHsb((int)ofMap(v, 0, 360 * 4, 0, 512) % 255, 150, 255);

		int u_start = ofMap(ofNoise(noise_seed, cos(v * DEG_TO_RAD) * 0.35, sin(v * DEG_TO_RAD) * 0.35, ofGetFrameNum() * 0.015), 0, 1, -360, 360);
		int next_u = ofMap(ofNoise(noise_seed, cos((v + v_span * 0.9) * DEG_TO_RAD) * 0.35, sin((v + v_span * 0.9) * DEG_TO_RAD) * 0.35, ofGetFrameNum() * 0.015), 0, 1, -360, 360);

		int r = v * 0.1;

		for (int u = u_start; u < u_start + 360; u += u_span) {

			face.addVertex(this->make_point(R, r, u, v));
			face.addVertex(this->make_point(R, r, u + u_span, v));
			face.addVertex(this->make_point(R, r, next_u + u_span, v + v_span * 0.85));
			face.addVertex(this->make_point(R, r, next_u, v + v_span * 0.85));

			line.addVertex(this->make_point(R, r, u, v));
			line.addVertex(this->make_point(R, r, u + u_span, v));
			line.addVertex(this->make_point(R, r, next_u + u_span, v + v_span * 0.85));
			line.addVertex(this->make_point(R, r, next_u, v + v_span * 0.85));

			ofColor face_color = ofColor(0);
			ofColor line_color = ofColor(color);

			face.addColor(face_color);
			face.addColor(face_color);
			face.addColor(face_color);
			face.addColor(face_color);

			line.addColor(line_color);
			line.addColor(line_color);
			line.addColor(line_color);
			line.addColor(line_color);

			face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
			face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

			line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
			line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);

			line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 2);
			line.addIndex(line.getNumVertices() - 3); line.addIndex(line.getNumVertices() - 4);

			if (v > 0) {

				line.addIndex(line.getNumVertices() - 4); line.addIndex(line.getNumVertices() - 17);
			}

			next_u += u_span;

		}
	}

	face.drawFaces();
	line.drawWireframe();

	this->cam.end();

	/*
	int start = 16;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// ���w�f�b�T������ �`���Ċy���ސ��w�����@P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}