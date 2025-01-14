#include "Vectors.h"


//  2D VECTORS
Vector2D::Vector2D() {
    
  x = 0;
   y = 0;
}


Vector2D::Vector2D(float X, float Y) {
  
  x = X;
  y = Y;
}


void Vector2D::print() {
  
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\n");
}


Vector2D Vector2D::rotate(int angle, Vector2D Pivot) {
  // Translate line so Pivot point is at the origin
  x -= Pivot.x;
  y -= Pivot.y;

  // Rotate point by angle
  int x_rotated = x * cos(angle) - y * sin(angle);
  int y_rotated = x * sin(angle) + y * cos(angle);

  // Translate point back to original position
  x = x_rotated + Pivot.x;
  y = y_rotated + Pivot.y;
  return Vector2D(x,y);
}


//  3D VECTORS
Vector3D::Vector3D() {
  
  x = 0;
  y = 0;
  z = 0;
}


Vector3D::Vector3D(float X, float Y, float Z) {
  
  x = X;
  y = Y;
  z = Z;
}


void Vector3D::print() {
  
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\n");
}


Vector3D Vector3D::rotate(int angle, Vector2D Pivot) {
  // Translate line so Pivot point is at the origin
  if(angle == 0) return Vector3D(x,y,z);

  x -= Pivot.x;
  y -= Pivot.y;
  float angleRad = radians(angle);

  // Rotate point by angle
  int x_rotated = x * cos(angleRad) - y * sin(angleRad);
  int y_rotated = x * sin(angleRad) + y * cos(angleRad);

  // Translate point back to original position
  x = x_rotated + Pivot.x;
  y = y_rotated + Pivot.y;

  return Vector3D(x,y,z);
}