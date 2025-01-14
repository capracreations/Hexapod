#include "Hex.h"


Hexapod::Hexapod(int pin[6][3]) {
  
  for(int i = 0; i < 6; i++ ) {
    
    L[i].coxa = pin[i][0];
    L[i].femur = pin[i][1];
    L[i].tibia = pin[i][2];
    L[i].identifier = i;
  }
}


void Hexapod::moveHex(Vector3D Coords, Vector3D Base) {

  float X = Coords.x;
  float Y = Coords.y;
  float Z = Coords.z;

  float hX = Base.x;
  float hY = Base.y;
  float hZ = Base.z;

  hX = hX / 0.5;
  X += (oX + hX);
  Y += (oY + hY);
  Z += (oZ - hZ);

  float P = sqrt((Y * Y) + (X * X));
  float Q = P - L1;
  float L0 = sqrt((Q * Q) + (Z * Z));
  float J1 = atan(Y / X) * (180 / PI);
  float A = atan(Z / Q) * (180 / PI);
  float B = acos(((L0 * L0) + (L2 * L2) - (L3 * L3)) / (2 * L0 * L2)) * (180 / PI);
  float J2 = (B + A);
  float J3 = acos(((L2 * L2) + (L3 * L3) - (L0 * L0)) / (2 * L2 * L3)) * (180 / PI);

  for(int i = 0; i < 6; i++) {

    if(L[i].identifier >= 0 && L[i].identifier < 3) {

      L[i].newPosLeft(J1, J2, J3);
    }
    else if(L[i].identifier >= 3 && L[i].identifier < 6) {

      L[i].newPosRight(J1, J2, J3);
    }
  }
}