#ifndef HEX_H
#define HEX_H
#include "Legs.h"


class Hexapod {
private:
  float L1 = 36.5;
  float L2 = 100.00;
  float L3 = 186.35;

public:
  float oX = 185.0;
  float oY = 0;
  float oZ = -120.923;
  
  Legs L[6];


  Hexapod(int pin[6][3]);

  void moveHex(Vector3D Coords, Vector3D Base);
};


#endif