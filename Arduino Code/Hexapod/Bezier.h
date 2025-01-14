#ifndef BEZIER_H
#define BEZIER_H
#include "Vectors.h"


Vector2D GetPointOnBezierCurve(Vector2D* points, int numPoints, float t);

Vector3D GetPointOnBezierCurve(Vector3D* points, int numPoints, float t);

int binomCoef(int n, int k);

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);

float lerp(float a, float b, float f);

Vector2D lerp(Vector2D a, Vector2D b, float f);

float calcHypotenuse(float x, float y);


#endif