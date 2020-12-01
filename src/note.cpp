#include "note.h"
using namespace std;


/*note::~note()
{
	delete this;
}*/

void note::setup(string noteColor)
{
	m_Image.load(noteColor + ".png");
	m_Pos.set(0, 0);
	m_Image.setAnchorPoint(m_Image.getWidth()/2,m_Image.getHeight()/2);
	color = noteColor;
}

void note::update() 
{
	m_Pos.y += 10;
}

void note::draw()
{
	ofPushMatrix();
	ofTranslate(m_Pos);
	if (color == "green") {
		m_Image.draw(ofGetWindowWidth() / 2.0f - 150, 0);
	}
	else if (color == "red") {
		m_Image.draw(ofGetWindowWidth() / 2.0f - 50, 0);
	}
	else if (color == "yellow") {
		m_Image.draw(ofGetWindowWidth() / 2.0f + 50, 0);
	}
	else if (color == "blue") {
		m_Image.draw(ofGetWindowWidth() / 2.0f + 150, 0);
	}
	ofPopMatrix();
}