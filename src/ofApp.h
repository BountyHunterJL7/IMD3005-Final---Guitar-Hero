#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "note.h"
#include "AudioAnalyser.h"

namespace config {
	static const std::string ARDUINO_DEVICE_NAME = "COM4";		//WIN
	//static const std::string ARDUINO_DEVICE_NAME = "/dev/cu.usbmodem144101";	//MAC
};

class ofApp : public ofBaseApp 
{
public:
    static const int PIN_ANALOG_INPUT   = 0; //joystick input up/down
	static const int PIN_ANALOG_INPUTLR = 1; //joystick input left/right
	static const int PIN_ANALOG_INPUTBUT = 2; //button inputs
    static const int PIN_PWM_OUTPUT     = 9;

    void setup();
    void update();
    void draw();

	/*ofImage m_greenImage;
	ofVec2f m_greenPos;
	ofImage m_redImage;
	ofVec2f m_redPos;
	ofImage m_yellowImage;
	ofVec2f m_yellowPos;
	ofImage m_blueImage;
	ofVec2f m_bluePos;*/

	ofImage m_greenCheckImage;
	ofVec2f m_greenCheckPos;
	ofImage m_redCheckImage;
	ofVec2f m_redCheckPos;
	ofImage m_yellowCheckImage;
	ofVec2f m_yellowCheckPos;
	ofImage m_blueCheckImage;
	ofVec2f m_blueCheckPos;

	ofFmodSoundPlayer m_soundPlayer;
	ofFmodSoundPlayer m_soundPlayer_Song;
	ofSoundPlayer m_soundPlayer_OF;
	AudioAnalyser m_audioAnalyser;

	int random;
	note* newNote = new note();
	vector<note*>noteList;
	bool greenMax = false;
	int temp = 0;
	int nextNote = 0;

	int score = 0;

	//Arduino stuff
	ofArduino				m_arduino;
    ofTrueTypeFont          m_font;
	int					    m_input_val;	//sensor value
	int						m_input_val_button;
	bool					m_bSetup;       //is Arduinio initialized yet
	void setupArduino(const int & _version);
	void updateArduino();
    void digitalPinChanged(const int & pinNum);
    void analogPinChanged(const int & pinNum);
	float getIRDistance(int & val);
};

