#include "Initialization.h"


void attach(Hexapod Hex) {

  for(int i = 0; i < 6; i++) {
    Hex.L[i].attach();
  }

  Vector3D Zero(0, 0, 0);
  Vector3D Origin(0, 0, -96.078);

  for(int i = 0; i <= 2; i++) {

    switch(i) {
      case 1:
        Hex.L[0].moveLeg(Zero, Origin, 0);
        Hex.L[1].moveLeg(Zero, Origin, 1);
        Hex.L[2].moveLeg(Zero, Origin, 2);
        Hex.L[3].moveLeg(Zero, Origin, 3);
        Hex.L[4].moveLeg(Zero, Origin, 4);
        Hex.L[5].moveLeg(Zero, Origin, 5);
        delay(1000);
      break;
      case 2:
        for(double i = 50; i >= 0; i--) {

          double H = (-96.078 / 50) * i;
          Vector3D Rise(0, 0, H);

          Hex.L[0].moveLeg(Zero, Rise, 0);
          Hex.L[1].moveLeg(Zero, Rise, 1);
          Hex.L[2].moveLeg(Zero, Rise, 2);
          Hex.L[3].moveLeg(Zero, Rise, 3);
          Hex.L[4].moveLeg(Zero, Rise, 4);
          Hex.L[5].moveLeg(Zero, Rise, 5);
          delay(25);  
        } 
        delay(1000);
      break;
    }
  }
}