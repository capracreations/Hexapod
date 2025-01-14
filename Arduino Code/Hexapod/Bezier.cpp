#include "Bezier.h"


Vector2D GetPointOnBezierCurve(Vector2D* points, int numPoints, float t) {
  
  Vector2D pos;

  for (int i = 0; i < numPoints; i++) {
    float b = binomCoef(numPoints - 1, i) * pow(1 - t, numPoints - 1 - i) * pow(t, i);
    pos.x += b * points[i].x;
    pos.y += b * points[i].y;
  }

  return pos;
}


Vector3D GetPointOnBezierCurve(Vector3D* points, int numPoints, float t) {
  
  Vector3D pos;

  for (int i = 0; i < numPoints; i++) {
    float b = binomCoef(numPoints - 1, i) * pow(1 - t, numPoints - 1 - i) * pow(t, i);
    pos.x += b * points[i].x;
    pos.y += b * points[i].y;
    pos.z += b * points[i].z;
  }

  return pos;
}





int binomCoef(int n, int k) {
  
  int result = 1;

  // Calculate the binomial coefficient using the formula:
  // (n!) / (k! * (n - k)!)
  for (int i = 1; i <= k; i++) {
    result *= (n - (k - i));
    result /= i;
  }

  return result;
}


float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {

  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


float lerp(float a, float b, float f) {

  return a * (1.0 - f) + (b * f);
}


Vector2D lerp(Vector2D a, Vector2D b, float f) {

  return Vector2D(lerp(a.x, b.x, f), lerp(a.y, b.y, f));
}


float calcHypotenuse(float x, float y) {
  
  float result = sqrt(pow(x, 2) + pow(y, 2));
  return result;
}