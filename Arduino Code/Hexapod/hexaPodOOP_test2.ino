#include "HexMode.h"
#include "Receiver.h"
#include "WalkState.h"


HexState stateHex = Initialize;

void setup() {

  Serial.begin(9600);
  attachHex();
  radioSetup();
}

void loop() {

  bool connected = inputReceive();
 
  if (connected) {

    mapInputs();
    walkState();
    delay(25);
  } 
}