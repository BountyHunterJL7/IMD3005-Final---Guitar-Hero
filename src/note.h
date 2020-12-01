#pragma once
#include "ofMain.h"
#include "ofEvents.h"

class note : public ofBaseApp
{
public:
	void setup(string noteColor);
	void update();
	void draw();
	string color;

	ofImage m_Image;
	ofVec2f m_Pos;
};