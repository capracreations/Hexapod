#ifndef RECEIVER_H
#define RECEIVER_H
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h> 


#define R_CE 47   // Receiver Radio CE Pin [D47]
#define R_CSN 46  // Receiver Radio CSN Pin [D46]

struct RCInputs {
    
    long J1_X;    // Left Joystick X Potentiometer
    long J1_Y;    // Left Joystick Y Potentiometer
    bool J1_P;    // Left Joystick Push Button
    long J2_X;    // Right Joystick X Potentiometer
    long J2_Y;    // Right Joystick Y Potentiometer
    bool J2_P;    // Right Joystick Push Button
    long S1;      // Left Slide Potentiometer
    long S2;      // Right Slide Potentiometer
    bool P_1;     // Left Push Button 1
    bool P_2;     // Center Push Button 2
    bool P_3;     // Right Push Button 3
};

RCInputs Controller;

unsigned long timeLastInput;
unsigned long timeout = 1000;

RF24 Radio(R_CE, R_CSN); // CE, CSN
uint8_t address[][6] = {"00001", "00002"};


void radioSetup() {

  Radio.begin();
  Radio.openReadingPipe(0, address[0]);
  Radio.setPALevel(RF24_PA_MIN);
  Radio.startListening();
}


void printStates() {

  Serial.print("L Joy X: ");
  Serial.print(Controller.J1_X);
  Serial.print("\tL Joy Y: ");
  Serial.print(Controller.J1_Y);
  Serial.print("\tL Joy SW: ");
  Serial.print(Controller.J1_P);
  Serial.print("\tR Joy X: ");  
  Serial.print(Controller.J2_X);
  Serial.print("\tR Joy Y: ");
  Serial.print(Controller.J2_Y);
  Serial.print("\tR Joy SW: ");
  Serial.print(Controller.J2_P);
  Serial.print("\tL Slide: ");
  Serial.print(Controller.S1);
  Serial.print("\tR Slide: ");
  Serial.print(Controller.S2);
  Serial.print("\tPush 1: ");
  Serial.print(Controller.P_1);
  Serial.print("\tPush 2: ");
  Serial.print(Controller.P_2);
  Serial.print("\tPush 3: ");
  Serial.print(Controller.P_3);
  Serial.print("\n");
}


bool inputReceive() {
  
  if(Radio.available()) {

    Radio.read(&Controller, sizeof(Controller));

    timeLastInput = millis();
  }
  
  if(millis() - timeLastInput > timeout) {
    return false;
  }
  else {
    //printStates();
    return true;
  }
}


#endif