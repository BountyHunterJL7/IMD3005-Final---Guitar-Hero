#include "ofApp.h"
#include <stdio.h>    
#include <stdlib.h>     
#include <time.h>
using namespace std;

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowShape(1280, 720);
	m_soundPlayer_Song.load("feelgloop.mp3");
	m_soundPlayer_Song.play();
	m_soundPlayer.load("feelgloop.mp3");
	m_soundPlayer.play();
	m_soundPlayer.setPositionMS(1100);
	m_soundPlayer.setVolume(0);
	m_audioAnalyser.init(&m_soundPlayer, 20);
	m_audioAnalyser_Song.init(&m_soundPlayer_Song, 20);
    
    m_font.load( "franklinGothic.otf", 16 );

	/*m_greenImage.load("green.png");
	m_greenPos.set(0,0);
	m_greenImage.setAnchorPoint(m_greenImage.getWidth() / 2, m_greenImage.getHeight() / 2);
	m_redImage.load("red.png");
	m_redPos.set(0, 0);
	m_redImage.setAnchorPoint(m_redImage.getWidth() / 2, m_redImage.getHeight() / 2);
	m_yellowImage.load("yellow.png");
	m_yellowPos.set(0, 0);
	m_yellowImage.setAnchorPoint(m_yellowImage.getWidth() / 2, m_yellowImage.getHeight() / 2);
	m_blueImage.load("blue.png");
	m_bluePos.set(0, 0);
	m_blueImage.setAnchorPoint(m_blueImage.getWidth() / 2, m_blueImage.getHeight() / 2);*/

	/*srand(time(NULL));
	random = rand() % 4 + 1;*/

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
}

//--------------------------------------------------------------
void ofApp::update()
{
    updateArduino();
	m_audioAnalyser.update();
	m_audioAnalyser_Song.update();
	/*m_greenPos.y = m_greenPos.y+1;
	m_redPos.y = m_redPos.y + 1;
	m_yellowPos.y = m_yellowPos.y + 1;
	m_bluePos.y = m_bluePos.y + 1;*/
	//newNote->update();
	for (int i = 0; i < noteList.size(); i++) {
		noteList[i]->update();
	}
	for (int i = 0; i < noteList.size(); i++) {
		if (noteList[i]->m_Pos.y >= height) {
			noteList.erase(noteList.begin());
			temp--;
		}
	}
	for (int i = 0; i < noteListr.size(); i++) {
		noteListr[i]->update();
	}
	for (int i = 0; i < noteListr.size(); i++) {
		if (noteListr[i]->m_Pos.y >= height) {
			noteListr.erase(noteListr.begin());
			tempr--;
		}
	}
	for (int i = 0; i < noteListy.size(); i++) {
		noteListy[i]->update();
	}
	for (int i = 0; i < noteListy.size(); i++) {
		if (noteListy[i]->m_Pos.y >= height) {
			noteListy.erase(noteListy.begin());
			tempy--;
		}
	}
	for (int i = 0; i < noteListb.size(); i++) {
		noteListb[i]->update();
	}
	for (int i = 0; i < noteListb.size(); i++) {
		if (noteListb[i]->m_Pos.y >= height) {
			noteListb.erase(noteListb.begin());
			tempb--;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground( 0, 0, 0 );

    
   /* ofEnableAlphaBlending();
    ofSetColor( 0, 0, 0, 127 );
    ofDrawRectangle( 510, 15, 275, 150 );
    ofDisableAlphaBlending();
    
    ofSetColor( 255, 255, 255 );
    
    // Draw sensor input values
    m_font.drawString( "Sensor Value: " + ofToString( m_input_val_button ), 530, 105 );
	m_font.drawString("Sensor Value: " + ofToString(m_input_val), 530, 120);*/
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
	//green
	if (greenSpawn >= 200.0f && !greenMax) {
		noteList.push_back(new note());
		noteList[temp]->setup("green");
		greenMax = true;
		temp++;
	}
	else if (greenSpawn < 1) {
		greenMax = false;
	}
	for (int i = 0; i < noteList.size(); i++) {
		noteList[i]->draw();
	}
	//red
	if ((redSpawn >= 40 && redSpawn <= 50) && !redMax) {
		noteListr.push_back(new note());
		noteListr[tempr]->setup("red");
		redMax = true;
		tempr++;
	}
	else if (redSpawn < 1) {
		redMax = false;
	}
	for (int i = 0; i < noteListr.size(); i++) {
		noteListr[i]->draw();
	}
	//yellow
	if ((yellowSpawn >= 15 && yellowSpawn <= 20) && !yellowMax && !blueMax) {
		noteListy.push_back(new note());
		noteListy[tempy]->setup("yellow");
		yellowMax = true;
		tempy++;
	}
	else if (yellowSpawn < 1) {
		yellowMax = false;
	}
	for (int i = 0; i < noteListy.size(); i++) {
		noteListy[i]->draw();
	}
	//blue
	if ((blueSpawn >= 10 && blueSpawn <= 23)&& !blueMax && !yellowMax) {
		noteListb.push_back(new note());
		noteListb[tempb]->setup("blue");
		blueMax = true;
		tempb++;
	}
	else if (blueSpawn < 1) {
		blueMax = false;
	}
	for (int i = 0; i < noteListb.size(); i++) {
		noteListb[i]->draw();
	}

	/*
	if (random == 1) {
		newNote->setup("green");
	}
	else if (random == 2) {
		newNote->setup("red");
	}
	else if (random == 3) {
		newNote->setup("yellow");
	}
	else if (random == 4) {
		newNote->setup("blue");
	}
	newNote->draw();
	*/

	/*ofPushMatrix();
	ofTranslate(m_greenPos);
	m_greenImage.draw(ofGetWindowWidth() / 2.0f - 150, 0);
	ofPopMatrix();
	ofPushMatrix();
	ofTranslate(m_redPos);
	m_redImage.draw(ofGetWindowWidth() / 2.0f - 50, 0);
	ofPopMatrix();
	ofPushMatrix();
	ofTranslate(m_yellowPos);
	m_yellowImage.draw(ofGetWindowWidth() / 2.0f + 50, 0);
	ofPopMatrix();
	ofPushMatrix();
	ofTranslate(m_bluePos);
	m_blueImage.draw(ofGetWindowWidth() / 2.0f + 150, 0);
	ofPopMatrix();*/

	//m_audioAnalyser.drawLinearAverages(40, 200, 1200, 128);

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
	if (noteList.size() > 0 && !isStrum && ((m_input_val_button > 180 && m_input_val_button < 200) && (m_input_val > 140 || m_input_val < 110)) && ((noteList[temp - 1]->m_Pos.y < m_greenCheckPos.y + 40) && (noteList[temp - 1]->m_Pos.y > m_greenCheckPos.y - 40)) && ((noteList[temp - 1]->m_Pos.x < m_greenCheckPos.x + 40) && (noteList[temp - 1]->m_Pos.x > m_greenCheckPos.x - 40))) { // checks red strum
		cout << "GREEN POINT" << endl;
		bump = 150;
		score += 100;
		isStrum = true;
		noteList[temp - 1]->m_Pos.y = 720;
	}
	else if (noteListr.size() > 0 && !isStrum && ((m_input_val_button > 150 && m_input_val_button < 180) && (m_input_val > 140 || m_input_val < 110)) && ((noteListr[tempr - 1]->m_Pos.y < m_redCheckPos.y + 40) && (noteListr[tempr - 1]->m_Pos.y > m_redCheckPos.y - 40)) && ((noteListr[tempr - 1]->m_Pos.x < m_redCheckPos.x + 40) && (noteListr[tempr - 1]->m_Pos.x > m_redCheckPos.x - 40))) { // checks red strum
		cout << "RED POINT" << endl;
		bumpr = 150;
		score += 100;
		isStrum = true;
		noteListr[tempr - 1]->m_Pos.y = 720;
	}
	else if (noteListy.size() > 0 && !isStrum && ((m_input_val_button > 100 && m_input_val_button < 140) && (m_input_val > 140 || m_input_val < 110)) && ((noteListy[tempy - 1]->m_Pos.y < m_yellowCheckPos.y + 40) && (noteListy[tempy - 1]->m_Pos.y > m_yellowCheckPos.y - 40)) && ((noteListy[tempy - 1]->m_Pos.x < m_yellowCheckPos.x + 40) && (noteListy[tempy - 1]->m_Pos.x > m_yellowCheckPos.x - 40))) { // checks red strum
		cout << "YELLOW POINT" << endl;
		bumpy = 150;
		score += 100;
		isStrum = true;
		noteListy[tempy - 1]->m_Pos.y = 720;
	}
	else if (noteListb.size() > 0 && !isStrum && ((m_input_val_button >= 0 && m_input_val_button < 25) && (m_input_val > 140 || m_input_val < 100)) && ((noteListb[tempb -1]->m_Pos.y < m_blueCheckPos.y + 40) && (noteListb[tempb - 1]->m_Pos.y > m_blueCheckPos.y - 40)) && ((noteListb[tempb - 1]->m_Pos.x < m_blueCheckPos.x + 40) && (noteListb[tempb - 1]->m_Pos.x > m_blueCheckPos.x - 40))) { // checks red strum
		cout << "BLUE POINT" << endl;
		bumpb = 150;
		score += 100;
		isStrum = true;
		noteListb[tempb-1]->m_Pos.y = 720;
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

//!!convert voltage signal into a readable result distance in cm (convenience function for for distance sensor - from IR sensor specs)
float ofApp::getIRDistance(int & val)
{
	if (val < 16)
	{
		val = 16;
	}

	return 2076.0f / (val - 11.0f);
}