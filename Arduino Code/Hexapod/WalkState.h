#ifndef WALKSTATE_H
#define WALKSTATE_H
#include "Initialization.h"
#include "Receiver.h"
#include "Vectors.h"
#include "HexMode.h"
#include "Bezier.h"
#include "Hex.h"


float forwardAmount;
float turnAmount;
float velocityMult;
float strideLengthMult;
float liftHeightMult;
float pushFraction;
float maxStrideLength;
float maxVelocity;
float globalVelMult;
float globalRotMult;

float strideMult[6] = {1, 1, 1, -1, -1, -1};  //possible physical error
float rotMult[6] = {-1, 0, 1, 1, 0, -1};      //possible physical error

float disCenterToLeg[6] = {267.33, 250.177, 267.33, 267.33, 250.177, 267.33};
float defaultHeight = -71; // Height value based on distance to ground from lowest point of hexapod body
float height[2]; //Current and previous Height Values

float legAngle = 60;
float liftHeight = 125;       //possible physical error 
float landHeight = 30;        //possible physical error
float strideOvershoot = 10;   //possible physical error

int amountCtrlPnts;
int amountRotCtrlPnts;
Vector3D ctrlPnts[4];
Vector3D rotCtrlPnts[5];

Vector2D joy1Target = Vector2D(0,0);
float joy1TarMag = 0;
Vector2D joy1Current = Vector2D(0,0);
float joy1CurMag = 0;
Vector2D joy2Target = Vector2D(0,0);
float joy2TarMag = 0;
Vector2D joy2Current = Vector2D(0,0);
float joy2CurMag = 0;

LegState stateLeg[6];
GaitCycle appliedCycle;

float points = 1000;
int cycleProg[12];
float tArr[6];

                 // Leg 1       | Leg 2       | Leg 3
          // Slot = 10, 11, 12  |  6,  7,  8  |  2,  3,  4 
int pins[6][3] = { {31, 32, 33}, {27, 28, 29}, {23, 24, 25},
                   {44, 43, 42}, {40, 39, 38}, {36, 35, 34} };
          // Slot = 23, 22, 21  | 19, 18, 17  | 15, 14, 13
                 // Leg 4       | Leg 5       | Leg 6  

Hexapod Hex(pins);


void attachHex() {

  attach(Hex);
}


void mapInputs() {

  float Joy1Y = map(Controller.J1_Y, 0, 1023, -200, 200);
  float Joy1X = map(Controller.J1_X, 0, 1023, -200, 200);
  float Joy2X = map(Controller.J2_X, 0, 1023, -200, 200);
  float Joy2Y = map(Controller.J2_Y, 0, 1023, -200, 200);

  joy1Target = Vector2D(Joy1X, Joy1Y);
  joy1TarMag = constrain(calcHypotenuse(abs(Joy1X), abs(Joy1Y)), 0, 100);
  joy2Target = Vector2D(Joy2X, Joy2Y);
  joy2TarMag = constrain(calcHypotenuse(abs(Joy2X), abs(Joy2Y)), 0, 100);

  joy1Current = lerp(joy1Current, joy1Target, 0.08);
  joy1CurMag = lerp(joy1CurMag, joy1TarMag, 0.08);
  joy2Current = lerp(joy2Current, joy2Target, 0.12);
  joy2CurMag = lerp(joy2CurMag, joy2TarMag, 0.12);  

  Controller.S1 = map(Controller.S1, 0, 1023, 0, 100);
  Controller.S2 = map(Controller.S2, 0, 1023, 0, 100);

  height[1] = height[0];
  height[0] = Controller.S2 * -1 + defaultHeight  ;

  globalVelMult = map(Controller.S1, 0, 100, 10, 100) * 0.01;
  globalRotMult = map(Controller.S1, 0, 100, 40, 130) * 0.01;
}


Vector3D getGaitPoint(int id, float pushFraction) {

  float rotStrideLength = turnAmount * globalRotMult;
  joy1Current = joy1Current * Vector2D(1, strideLengthMult); 
  joy1Current.x = constrain(joy1Current.x, -maxStrideLength/2, maxStrideLength/2) * globalVelMult;
  joy1Current.y = constrain(joy1Current.y, -maxStrideLength/2, maxStrideLength/2) * globalVelMult;

  float weightSum = abs(forwardAmount) + abs(turnAmount);

  if(tArr[id] < pushFraction) {

    if(stateLeg[id] != Pushing) {

      Hex.L[id].setStartPnts(id);
      stateLeg[id] = Pushing;
    }

    amountCtrlPnts = 2;
    ctrlPnts[0] = Hex.L[id].walkStartPnts[id];
    ctrlPnts[1] = Vector3D(joy1Current.x * strideMult[id] + disCenterToLeg[id], -joy1Current.y * strideMult[id], height[0]).rotate(legAngle * rotMult[id], Vector2D(disCenterToLeg[id], 0));
    Vector3D vectorPoint = GetPointOnBezierCurve(ctrlPnts, amountCtrlPnts, mapFloat(tArr[id], 0, pushFraction, 0 ,1));

      //vectorPoint.print();

    amountRotCtrlPnts = 3;
    rotCtrlPnts[0] = Hex.L[id].walkStartPnts[id];
    rotCtrlPnts[1] = {disCenterToLeg[id] + 40, 0, height[0]};
    rotCtrlPnts[1] = {disCenterToLeg[id], rotStrideLength, height[0]};
    Vector3D angularPoint = GetPointOnBezierCurve(rotCtrlPnts, amountRotCtrlPnts, mapFloat(tArr[id], 0, pushFraction, 0 ,1));

      //angularPoint.print();

    Vector3D transformPoint;
    transformPoint.x = (vectorPoint.x * abs(forwardAmount) + angularPoint.x * abs(turnAmount)) / weightSum;
    transformPoint.y = (vectorPoint.y * abs(forwardAmount) + angularPoint.y * abs(turnAmount)) / weightSum;
    transformPoint.z = (vectorPoint.z * abs(forwardAmount) + angularPoint.z * abs(turnAmount)) / weightSum;

      //transformPoint.print();

    return transformPoint;

  }
  else { 

      Serial.print("1");

    if(stateLeg[id] != Lifting) {

      Hex.L[id].setStartPnts(id);
      stateLeg[id] = Lifting;
    }

    amountCtrlPnts = 4;
    ctrlPnts[0] = Hex.L[id].walkStartPnts[id];
    ctrlPnts[1] = Hex.L[id].walkStartPnts[id] + Vector3D(0, 0, liftHeight * liftHeightMult);
    ctrlPnts[2] = Vector3D(-joy1Current.x + strideMult[id] + disCenterToLeg[id], (joy1Current.y + strideOvershoot) * strideMult[id], height[0] + landHeight).rotate(legAngle * rotMult[id], Vector2D(disCenterToLeg[id], 0));
    ctrlPnts[3] = Vector3D(-joy1Current.x + strideMult[id] + disCenterToLeg[id], joy1Current.y * strideMult[id], height[0]).rotate(legAngle * rotMult[id], Vector2D(disCenterToLeg[id], 0));
    Vector3D vectorPoint = GetPointOnBezierCurve(ctrlPnts, amountCtrlPnts, mapFloat(tArr[id], pushFraction, 1, 0 ,1));

      //vectorPoint.print();

    amountRotCtrlPnts = 5;
    rotCtrlPnts[0] = Hex.L[id].walkStartPnts[id];
    rotCtrlPnts[1] = Hex.L[id].walkStartPnts[id] + Vector3D(0, 0, liftHeight * liftHeightMult);
    rotCtrlPnts[2] = {disCenterToLeg[id] + 40, 0, height[0] + liftHeight * liftHeightMult};
    rotCtrlPnts[3] = {disCenterToLeg[id], -(rotStrideLength + strideOvershoot), height[0] + landHeight};
    rotCtrlPnts[4] = {disCenterToLeg[id], -rotStrideLength, height[0]};
    Vector3D angularPoint = GetPointOnBezierCurve(rotCtrlPnts, amountRotCtrlPnts, mapFloat(tArr[id], pushFraction, 1, 0 ,1));

      //angularPoint.print();

    Vector3D liftPoint;
    liftPoint.x = (vectorPoint.x * abs(forwardAmount) + angularPoint.x * abs(turnAmount)) / weightSum;
    liftPoint.y = (vectorPoint.y * abs(forwardAmount) + angularPoint.y * abs(turnAmount)) / weightSum;
    liftPoint.z = (vectorPoint.z * abs(forwardAmount) + angularPoint.z * abs(turnAmount)) / weightSum;

    //if(liftPoint.z)

      //liftPoint.print();

    return liftPoint;
  }
}


void walkState() {
  
  for(int i = 0; i < 6; i++) {

    stateLeg[i] = Waiting;
  }

  appliedCycle = Tri;

  switch(appliedCycle) {

    case Neutral:
      cycleProg[0] = 0;
      cycleProg[1] = 0;
      cycleProg[2] = 0;
      cycleProg[3] = 0;
      cycleProg[4] = 0;
      cycleProg[5] = 0;

      pushFraction = 0;
      velocityMult = 0;
      strideLengthMult = 0;
      liftHeightMult = 0;
      maxStrideLength = 0;
      maxVelocity = 0;
      break;

    case Tri:
      // Phase 1
      cycleProg[0] = 0;
      cycleProg[1] = (points * 0.46);
      cycleProg[2] = 0;
      cycleProg[3] = (points / 2);
      cycleProg[4] = 0;
      cycleProg[5] = (points / 2);
      // Phase 2

      pushFraction = 3.1/6.0;
      velocityMult = 1.0;
      strideLengthMult = 1.0;
      liftHeightMult = 1.0;
      maxStrideLength = 240;
      maxVelocity = 200;
      break;
  }
  
  for(int i = 0; i < 6; i++) {

    tArr[i] = (float)cycleProg[i] / points;
  }

  forwardAmount = joy1CurMag;
  turnAmount = joy2Current.y; //possible error point, try changing to joy2Current.y

  Hex.L[0].moveLeg(getGaitPoint(0, pushFraction), 0);
  Hex.L[1].moveLeg(getGaitPoint(1, pushFraction), 1);
  //Hex.L[2].moveLeg(getGaitPoint(2, pushFraction), 2);
  //Hex.L[3].moveLeg(getGaitPoint(3, pushFraction), 3);
  //Hex.L[4].moveLeg(getGaitPoint(4, pushFraction), 4);
  //Hex.L[5].moveLeg(getGaitPoint(5, pushFraction), 5);
  
  float cycleProgAmount = (max(abs(forwardAmount), abs(turnAmount)) * velocityMult) * globalVelMult;
  cycleProgAmount = constrain(cycleProgAmount, 0, maxVelocity * globalVelMult);

  Serial.print(cycleProgAmount);
  Serial.print("\t");

  for(int i = 0; i < 6; i++){
    cycleProg[i] += cycleProgAmount;

    if(cycleProg[i] >= points){
      cycleProg[i] = cycleProg[i] - points;
    }
  } 

  Serial.print(cycleProg[0] / points);
  Serial.print("\t");
  Serial.print(cycleProg[1] / points);
  Serial.print("\n");
}


#endif