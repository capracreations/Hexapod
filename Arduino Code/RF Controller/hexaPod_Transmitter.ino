#include "Transmitter.h"


void setup() {

  Serial.begin(9600);
  radioSetup();
  pinModeSetup();
}

void loop() {

  if(!Radio.begin() && !Radio.isChipConnected()) {

    Serial.println("Radio Not Responding :/");
    while(1) {}
  }
  else {

    timeLastInput = millis();
    bool connected = outputRead();

    if(connected) {
  
      outputSend();
    }

    //delay();
  }
}



