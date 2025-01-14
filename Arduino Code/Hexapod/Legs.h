#ifndef LEGS_H
#define LEGS_H
#include <Servo.h>
#include "Vectors.h"


class Legs {
private:
  float L1 = 36.5;
  float L2 = 100.00;
  float L3 = 186.35;

public:
  Vector3D currentPnts[6];
  Vector3D walkStartPnts[6];

  float oX = 185.0;
  float oY = 0;
  float oZ = -120.923;

  Servo Joints[3];
  int coxa;
  int femur;
  int tibia;
  int identifier;
  float J3_Off = 15;


  Legs();

  void attach();
  void print();

  void moveLeg(Vector3D Coords, int id);
  void moveLeg(Vector3D Coords, Vector3D Base, int id);

  void newPosLeft(float J1, float J2, float J3);
  void newPosRight(float J1, float J2, float J3);

  Vector3D setStartPnts(int leg);
  void setStartPnts();
};


#endif