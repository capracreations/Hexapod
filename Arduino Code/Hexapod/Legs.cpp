#include "Legs.h"


Legs::Legs() {

}


void Legs::attach() {

  Joints[0].attach(coxa, 500, 2500);
  Joints[1].attach(femur, 500, 2500);
  Joints[2].attach(tibia, 500, 2500);
}


void Legs::print() {

  Serial.print("Identifier: ");
  Serial.print(identifier);
  Serial.print("\tS1: ");
  Serial.print(Joints[0].attached());
  Serial.print("\tS2: ");
  Serial.print(Joints[1].attached());
  Serial.print("\tS3: ");
  Serial.print(Joints[2].attached());
  Serial.print("\ncoxa: ");
  Serial.print(coxa);
  Serial.print("\tfemur: ");
  Serial.print(femur);
  Serial.print("\ttibia: ");
  Serial.print(tibia);
  Serial.print("\n\n");
}


void Legs::moveLeg(Vector3D Coords, int id) {

  currentPnts[id] = Coords;

  float X = Coords.x;
  float Y = Coords.y;
  float Z = Coords.z;

  X += oX;
  Y += oY;
  Z += oZ;

  float P = sqrt((Y * Y) + (X * X));
  float Q = P - L1;
  float L0 = sqrt((Q * Q) + (Z * Z));
  float J1 = atan(Y / X) * (180 / PI);
  float A = atan(Z / Q) * (180 / PI);
  float B = acos(((L0 * L0) + (L2 * L2) - (L3 * L3)) / (2 * L0 * L2)) * (180 / PI);
  float J2 = (B + A);
  float J3 = acos(((L2 * L2) + (L3 * L3) - (L0 * L0)) / (2 * L2 * L3)) * (180 / PI);

  //Serial.print(X);
  //Serial.print("\t");
  //Serial.print(Y);
  //Serial.print("\t");
  //Serial.print(Z);
  //Serial.print("\n")

  if(id >= 0 && id < 3) {
  
    Legs::newPosLeft(J1, J2, J3);
  }
  else if(id >= 3 && id < 6) {
  
    Legs::newPosRight(J1, J2, J3);
  }
}


void Legs::moveLeg(Vector3D Coords, Vector3D Base, int id) {

  currentPnts[id] = Coords;

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

  if(id >= 0 && id < 3) {
  
    Legs::newPosLeft(J1, J2, J3);
  }
  else if(id >= 3 && id < 6) {
  
    Legs::newPosRight(J1, J2, J3);
  }
}


void Legs::newPosLeft(float J1, float J2, float J3) {

  Joints[0].write(90 + J1);
  Joints[1].write(90 + J2);
  Joints[2].write(180 - J3 - J3_Off);
}


void Legs::newPosRight(float J1, float J2, float J3) {

  Joints[0].write(90 - J1);
  Joints[1].write(90 - J2);
  Joints[2].write(J3 + J3_Off);
}


Vector3D Legs::setStartPnts(int id) {
  
  walkStartPnts[id] = currentPnts[id];   

  return walkStartPnts[id];
}


void Legs::setStartPnts() {
  
  for(int i = 0; i < 6; i++){
    walkStartPnts[i] = currentPnts[i]; 
  }     
}