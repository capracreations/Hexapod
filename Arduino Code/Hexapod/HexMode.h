#ifndef HEXMODE_H
#define HEXMODE_H


  enum HexState {

    Initialize,
    Stand,
    Walk,
    Calibrate,
    Terminate
  };


  enum LegState {

    Pushing,
    Lifting,
    Waiting,
    Home
  };


  enum GaitCycle {

    Tri,
    Neutral
  };


#endif