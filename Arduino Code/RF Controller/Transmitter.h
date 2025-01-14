#ifndef TRANSMITTER_H
#define TRANSMITTER_H
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define R_CE 7    // Transmitter Radio CE Pin [D7]
#define R_CSN 8   // Transmitter Radio CSN Pin [D8]
#define j1_x A3   // Joystick 1 X Pin [A3]
#define j1_y A4   // Joystick 1 Y Pin [A4]
#define j1_p 2    // Joystick 1 Push Button Pin [D2]
#define j2_x A6   // Joystick 2 X Pin [A6]
#define j2_y A5   // Joystick 2 Y Pin [A5]
#define j2_p 3    // Joystick 2 Push Button Pin [D3]
#define s1 A0     // Slide Potentiometer 1 Pin [A0]
#define s2 A1     // Slide Potentiometer 2 Pin [A1]
#define p1 6      // Push Button 1 Pin [D6]
#define p2 5      // Push Button 2 Pin [D5]
#define p3 4      // Push Button 3 Pin [D4]

struct RCInputs {
    
    long J1_X;    // Left Joystick X Potentiometer
    long J1_Y;    // Left Joystick Y Potentiometer
    bool J1_P;    // Left Joystick Push Button
    long J2_X;    // Right Joystick X Potentiometer
    long J2_Y;    // Right Joystick X Potentiometer
    bool J2_P;    // Right Joystick Push Button
    long S1;      // Left Slide Potentiometer
    long S2;      // Right Slide Potentiometer
    bool P_1;     // Left Push Button 1
    bool P_2;     // Center Push Button 2
    bool P_3;     // Right Push Button 3

    bool operator!=(RCInputs In) {

      return(J1_X != In.J1_X && J1_Y != In.J1_Y && J1_P != In.J1_P
          && J2_X != In.J2_X && J2_Y != In.J2_Y && J2_P != In.J2_P
          && S1 != In.S1 && S2 != In.S2
          && P_1 != In.P_1 && P_2 != In.P_2 && P_3 != In.P_3);
    }
};

RCInputs Controller;
RCInputs Previous;

unsigned long timeLastInput;
unsigned long timeout = 1000;

RF24 Radio(R_CE, R_CSN); // CE, CSN
uint8_t address[][6] = {"00001", "00002"};


void radioSetup() {

  Radio.begin();
  Radio.openWritingPipe(address[0]);
  Radio.setPALevel(RF24_PA_MIN);
  Radio.stopListening();
  pinMode(LED_BUILTIN, OUTPUT);
}


void pinModeSetup() {

  pinMode(j1_p, INPUT);
  pinMode(j2_p, INPUT);
  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  pinMode(p3, INPUT);

  digitalWrite(j1_p, HIGH);
  digitalWrite(j2_p, HIGH);
  digitalWrite(p1, HIGH);
  digitalWrite(p2, HIGH);
  digitalWrite(p3, HIGH);
}


void outputSend() {

  Radio.write(&Controller, sizeof(Controller));
}


bool outputRead() {
 
  Controller.J1_X = map(analogRead(j1_x), 0, 1023, 1023, 0);
  Controller.J1_Y = map(analogRead(j1_y), 0, 1023, 1023, 0);
  Controller.J1_P = digitalRead(j1_p);
  Controller.J2_X = map(analogRead(j2_x), 0, 1023, 1023, 0);
  Controller.J2_Y = map(analogRead(j2_y), 0, 1023, 1023, 0);
  Controller.J2_P = digitalRead(j2_p);
  Controller.S1 = analogRead(s1);
  Controller.S2 = analogRead(s2);
  Controller.P_1 = digitalRead(p1);
  Controller.P_2 = digitalRead(p2);
  Controller.P_3 = digitalRead(p3);

  if(millis() - timeLastInput > timeout) {
    return false;
  }
  else {
    return true;
  }
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


#endif