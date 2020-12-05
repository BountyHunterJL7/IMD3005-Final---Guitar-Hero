#include "ofApp.h"
#include <stdio.h>    
#include <stdlib.h>     
#include <time.h>
using namespace std;

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowShape(1280, 720);
	m_soundPlayer_Song.load("feel_gloop_grid.mp3");
	m_soundPlayer.load("feel_gloop_grid.mp3");
	//playing both sound players
	m_soundPlayer_Song.play();
	m_soundPlayer.play();
	m_soundPlayer.setPositionMS(1100);
	m_soundPlayer.setVolume(0);
	//m_soundPlayer_Song.setVolume(0);
	m_audioAnalyser.init(&m_soundPlayer, 20);
	m_audioAnalyser_Song.init(&m_soundPlayer_Song, 20);



    
    m_font.load( "franklinGothic.otf", 16 );

	m_greenCheckImage.load("check.png");
	m_greenCheckPos.set(0, 630);
	m_greenCheckImage.setAnchorPoint(m_greenCheckImage.getWidth() / 2, m_greenCheckImage.getHeight() / 2);
	m_redCheckImage.load("check.png");
	m_redCheckPos.set(0, 630);
	m_redCheckImage.setAnchorPoint(m_redCheckImage.getWidth() / 2, m_redCheckImage.getHeight() / 2);
	m_yellowCheckImage.load("check.png");
	m_yellowCheckPos.set(0, 630);
	m_yellowCheckImage.setAnchorPoint(m_yellowCheckImage.getWidth() / 2, m_yellowCheckImage.getHeight() / 2);
	m_blueCheckImage.load("check.png");
	m_blueCheckPos.set(0, 630);
	m_blueCheckImage.setAnchorPoint(m_blueCheckImage.getWidth() / 2, m_blueCheckImage.getHeight() / 2);

	//setup Arduino
	// replace the string below with the serial port for your Arduino board
	// you can get this from the Arduino application (Tools Menu -> Port) 
	//m_arduino.connect("COM4", 57600);
    m_arduino.connect(config::ARDUINO_DEVICE_NAME, 57600);

	m_input_val	= 0.0f;
	m_input_val_button = 254.0f;

	// Listen for EInitialized notification. this indicates that
	// the arduino is ready to receive commands and it is safe to
	// call setupArduino()
	ofAddListener(m_arduino.EInitialized, this, &ofApp::setupArduino);

	m_bSetup = false;


	//setting up BPM beats in MS
	m_metronome.load("click.wav");
	m_bpm = 214;
}

//--------------------------------------------------------------
void ofApp::update()
{
    updateArduino();
	m_audioAnalyser.update();
	m_audioAnalyser_Song.update();
	for (int i = 0; i < noteListG.size(); i++) {
		noteListG[i]->update();
	}
	for (int i = 0; i < noteListG.size(); i++) {
		if (noteListG[i]->m_Pos.y >= height) {
			noteListG.erase(noteListG.begin());
			temp--;
		}
	}
	for (int i = 0; i < noteListR.size(); i++) {
		noteListR[i]->update();
	}
	for (int i = 0; i < noteListR.size(); i++) {
		if (noteListR[i]->m_Pos.y >= height) {
			noteListR.erase(noteListR.begin());
			tempr--;
		}
	}
	for (int i = 0; i < noteListY.size(); i++) {
		noteListY[i]->update();
	}
	for (int i = 0; i < noteListY.size(); i++) {
		if (noteListY[i]->m_Pos.y >= height) {
			noteListY.erase(noteListY.begin());
			tempy--;
		}
	}
	for (int i = 0; i < noteListB.size(); i++) {
		noteListB[i]->update();
	}
	for (int i = 0; i < noteListB.size(); i++) {
		if (noteListB[i]->m_Pos.y >= height) {
			noteListB.erase(noteListB.begin());
			tempb--;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground( 0, 0, 0 );

	ofPushMatrix();
	ofSetColor(255,255,255,255);
	m_font.drawString("Score: " + ofToString(score), 1000, 120);
	ofPopMatrix();
    
    // remap our flex values (can check on arduino sketch as values will always vary between sensors)
    /*float radius = ofMap( m_input_val, 0.0f, 255.0f, 20.0f, 150.0f);
    ofDrawCircle( 640, 400, radius );

	float button = ofMap(m_input_val_button, 0.0f, 255.0f, 20.0f, 150.0f);
	ofDrawCircle(200, 400, button);*/

	ofPushMatrix();
	ofSetColor(255, 255, 255, 90);
	ofDrawRectangle(width / 2 - 75, 0, 405, height);
	ofPopMatrix();

	ofPushMatrix();
	ofTranslate(m_greenCheckPos);
	m_greenCheckImage.draw(ofGetWindowWidth() / 2.0f - 150, 0, bump, bump);
	ofPopMatrix();
	ofPushMatrix();
	ofTranslate(m_redCheckPos);
	m_redCheckImage.draw(ofGetWindowWidth() / 2.0f - 50, 0, bumpr, bumpr);
	ofPopMatrix();
	ofPushMatrix();
	ofTranslate(m_yellowCheckPos);
	m_yellowCheckImage.draw(ofGetWindowWidth() / 2.0f + 50, 0, bumpy, bumpy);
	ofPopMatrix();
	ofPushMatrix();
	ofTranslate(m_blueCheckPos);
	m_blueCheckImage.draw(ofGetWindowWidth() / 2.0f + 150, 0, bumpb, bumpb);
	ofPopMatrix();

	float greenSpawn = m_audioAnalyser.getLinearAverage(1);
	float redSpawn = m_audioAnalyser.getLinearAverage(5);
	float yellowSpawn = m_audioAnalyser.getLinearAverage(10);
	float blueSpawn = m_audioAnalyser.getLinearAverage(23);
	float extra = m_audioAnalyser_Song.getLinearAverage(0);
	float extra1 = m_audioAnalyser_Song.getLinearAverage(1);
	float extra2 = m_audioAnalyser_Song.getLinearAverage(2);
	float extra3 = m_audioAnalyser_Song.getLinearAverage(3);
	ofPushMatrix();
	ofSetColor(255, 255, 255, 100);
	ofDrawRectangle(width / 2 - 350, height, 50, -extra); 
	ofDrawRectangle(width / 2 - 300, height, 50, -extra1);
	ofDrawRectangle(width / 2 - 250, height, 50, -extra2);
	ofDrawRectangle(width / 2 - 200, height, 50, -extra3);
	ofDrawRectangle(width / 2 + 550, height, 50, -extra);
	ofDrawRectangle(width / 2 + 500, height, 50, -extra1);
	ofDrawRectangle(width / 2 + 450, height, 50, -extra2);
	ofDrawRectangle(width / 2 + 400, height, 50, -extra3);
	ofSetColor(255, 255, 255, 255);
	ofPopMatrix();

	//triggers only on beat
	if ((m_soundPlayer.getPositionMS() - 80) % m_bpm <= 30 && m_soundPlayer.getPositionMS() - lastMS > 100) {
		cout << m_soundPlayer.getPositionMS() % m_bpm << "!\n";
		m_metronome.play();
		lastMS = m_soundPlayer.getPositionMS();
		bool noteMax = false; //used to make sure 2 notes aren't generated at the same time

		//generating notes 
		if (greenSpawn >= 100.0f && !greenMax && !noteMax) {
			noteListG.push_back(new note());
			noteListG[temp]->setup("green");
			greenMax = true;
			temp++;
			noteMax = true; //our note for this beat has been generated
		} 
		else if ((redSpawn >= 40.0f) && !redMax && !noteMax) {
			noteListR.push_back(new note());
			noteListR[tempr]->setup("red");
			redMax = true;
			tempr++;
			noteMax = true;
		} 
		else if ((yellowSpawn >= 15 && yellowSpawn <= 20) && !yellowMax && !blueMax && !noteMax) {
			noteListY.push_back(new note());
			noteListY[tempy]->setup("yellow");
			yellowMax = true;
			tempy++;
			noteMax = true;
		} 
		else if ((blueSpawn >= 10 && blueSpawn <= 23) && !blueMax && !yellowMax && !noteMax) {
			noteListB.push_back(new note());
			noteListB[tempb]->setup("blue");
			blueMax = true;
			tempb++;
			noteMax = true;
		}
	}
	//resetting the note generator bools if selected frequency volume is less than a specified value 
	if (greenSpawn < 50.0f) {
		cout << "green below!\n";
		greenMax = false;
	}

	if (redSpawn < 10.0f) {
		cout << "red below!\n";
		redMax = false;
	}

	if (yellowSpawn < 10.0f) {
		yellowMax = false;
	}

	if (blueSpawn < 10.0f) {
		blueMax = false;
	}



	//looping through all note lists and updating their positions
	for (int i = 0; i < noteListG.size(); i++) {
		noteListG[i]->draw();
	}
	for (int i = 0; i < noteListR.size(); i++) {
		noteListR[i]->draw();
	}
	for (int i = 0; i < noteListY.size(); i++) {
		noteListY[i]->draw();
	}
	for (int i = 0; i < noteListB.size(); i++) {
		noteListB[i]->draw();
	}

}

//--------------------------------------------------------------
void ofApp::setupArduino(const int & _version)
{
    /**
     Look under examples/communication/firmata for more examples ..
     **/
    
    m_bSetup = true;
    
	// remove listener because we don't need it anymore
	ofRemoveListener(m_arduino.EInitialized, this, &ofApp::setupArduino);

	// print firmware name and version to the console
	ofLogNotice() << m_arduino.getFirmwareName();
	ofLogNotice() << "firmata v" << m_arduino.getMajorFirmwareVersion() << "." << m_arduino.getMinorFirmwareVersion();

	//analog input
	m_arduino.sendAnalogPinReporting(PIN_ANALOG_INPUT, ARD_ANALOG);
	m_arduino.sendAnalogPinReporting(PIN_ANALOG_INPUTBUT, ARD_ANALOG);
    
    //PMW/digital output
    m_arduino.sendDigitalPinMode(PIN_PWM_OUTPUT, ARD_PWM);
    
    ofAddListener(m_arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
    ofAddListener(m_arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

//--------------------------------------------------------------
void ofApp::updateArduino() {

	// update the arduino, get any data or messages.
	// the call to m_arduino.update() is required
	m_arduino.update();
}

void ofApp::digitalPinChanged(const int & pinNum) {
    //cout  << "digital pin: " + ofToString(pinNum) + " : " + ofToString(m_arduino.getDigital(pinNum)) << std::endl;
}

void ofApp::analogPinChanged(const int & pinNum) {
    //std::cout  << "analog pin: " + ofToString(pinNum) + " : " + ofToString(m_arduino.getAnalog(pinNum)) << std::endl;
    if (pinNum == PIN_ANALOG_INPUT) {
        
        //get analog value
        m_input_val = m_arduino.getAnalog(pinNum);
        m_input_val = (int)ofMap( m_input_val, 0, 1024, 0, 255 );
        
        //send out pmw value
        m_arduino.sendPwm(PIN_PWM_OUTPUT, (int)m_input_val);
    }
	if (pinNum == PIN_ANALOG_INPUTBUT) {

		//get analog value
		m_input_val_button = m_arduino.getAnalog(pinNum);
		m_input_val_button = (int)ofMap(m_input_val_button, 0, 1024, 0, 255);

		//send out pmw value
		m_arduino.sendPwm(PIN_PWM_OUTPUT, (int)m_input_val_button);
	}
	if (noteListG.size() > 0 && !isStrum && ((m_input_val_button > 180 && m_input_val_button < 200) 
		&& (m_input_val > 140 || m_input_val < 110)) 
		&& ((noteListG[0]->m_Pos.y < m_greenCheckPos.y + 40) && (noteListG[0]->m_Pos.y > m_greenCheckPos.y - 40)) 
		&& ((noteListG[0]->m_Pos.x < m_greenCheckPos.x + 40) && (noteListG[0]->m_Pos.x > m_greenCheckPos.x - 40))) { // checks red strum

		cout << "GREEN POINT" << endl;
		bump = 150;
		score += 100;
		isStrum = true;
		noteListG[0]->m_Pos.y = 720;
	}
	else if (noteListR.size() > 0 && !isStrum && ((m_input_val_button > 150 && m_input_val_button < 180) 
		&& (m_input_val > 140 || m_input_val < 110)) 
		&& ((noteListR[0]->m_Pos.y < m_redCheckPos.y + 40) && (noteListR[0]->m_Pos.y > m_redCheckPos.y - 40)) 
		&& ((noteListR[0]->m_Pos.x < m_redCheckPos.x + 40) && (noteListR[0]->m_Pos.x > m_redCheckPos.x - 40))) { // checks red strum

		cout << "RED POINT" << endl;
		bumpr = 150;
		score += 100;
		isStrum = true;
		noteListR[0]->m_Pos.y = 720;
	}
	else if (noteListY.size() > 0 && !isStrum && ((m_input_val_button > 100 && m_input_val_button < 140) 
		&& (m_input_val > 140 || m_input_val < 110)) 
		&& ((noteListY[0]->m_Pos.y < m_yellowCheckPos.y + 40) && (noteListY[0]->m_Pos.y > m_yellowCheckPos.y - 40)) 
		&& ((noteListY[0]->m_Pos.x < m_yellowCheckPos.x + 40) && (noteListY[0]->m_Pos.x > m_yellowCheckPos.x - 40))) { // checks red strum

		cout << "YELLOW POINT" << endl;
		bumpy = 150;
		score += 100;
		isStrum = true;
		noteListY[0]->m_Pos.y = 720;
	}
	else if (noteListB.size() > 0 && !isStrum && ((m_input_val_button >= 0 && m_input_val_button < 25) 
		&& (m_input_val > 140 || m_input_val < 100)) 
		&& ((noteListB[0]->m_Pos.y < m_blueCheckPos.y + 40) && (noteListB[0]->m_Pos.y > m_blueCheckPos.y - 40)) 
		&& ((noteListB[0]->m_Pos.x < m_blueCheckPos.x + 40) && (noteListB[0]->m_Pos.x > m_blueCheckPos.x - 40))) { // checks red strum

		cout << "BLUE POINT" << endl;
		bumpb = 150;
		score += 100;
		isStrum = true;
		noteListB[0]->m_Pos.y = 720;
	}
	if (m_input_val <= 130 && m_input_val >= 105) {
		isStrum = false;
		bump = 100;
		bumpr = 100;
		bumpy = 100;
		bumpb = 100;
	}
	else if ((m_input_val_button > 210) && (m_input_val > 150 || m_input_val < 100)) { // checks blank strum
		cout << "MISS" << endl;
	}		
}