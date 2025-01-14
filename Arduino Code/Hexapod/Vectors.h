#ifndef VECTORS_H
#define VECTORS_H
#include <Arduino.h>


class Vector2D {
public:
  float x;
  float y;

  Vector2D();
  Vector2D(float X, float Y);

  void print();

  Vector2D rotate(int angle, Vector2D Pivot);

  bool operator==(Vector2D vec) {

    return(x == vec.x && y == vec.y);
  }

  bool operator!=(Vector2D vec) {

    return(x == vec.x || y == vec.y);
  }

  Vector2D operator+(Vector2D vec) {

    return(Vector2D(x + vec.x, y + vec.y));
  }

  Vector2D operator*(Vector2D vec) {

    return(Vector2D(x * vec.x, y * vec.y));
  }

  Vector2D operator*(float val) {

    Vector2D vec;
    vec.x *= val;
    vec.y *= val;
    return vec;
  }
};


class Vector3D {
public:
  float x;
  float y;
  float z;

  Vector3D();
  Vector3D(float X, float Y, float Z);

  void print();

  Vector3D rotate(int angle, Vector2D Pivot);

  bool operator==(Vector3D vec) {

    return(x == vec.x && y == vec.y && z == vec.z);
  }

  bool operator!=(Vector3D vec) {

    return(x == vec.x || y == vec.y || z == vec.z);
  }

  Vector3D operator+(Vector3D vec) {

    return(Vector3D(x + vec.x, y + vec.y, z + vec.z));
  }

  Vector3D operator*(Vector3D vec) {

    return(Vector3D(x * vec.x, y * vec.y, z * vec.z));
  }

  Vector3D operator*(float val) {

    Vector3D vec;
    vec.x *= val;
    vec.y *= val;
    vec.z *= val;
    return vec;
  }

  Vector3D operator/(float val) {

    Vector3D vec;
    vec.x /= val;
    vec.y /= val;
    vec.z /= val;
    return vec;
  }
};


#endif