#ifndef COLOR_H
#define COLOR_H

#include <GL/freeglut.h>

class Color {
 private:
  float r;
  float g;
  float b;

 public:
  Color() {
    r = 0;
    g = 0;
    b = 0;
  }

  Color(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
  }

  float getR() const { return r; }
  float getG() const { return g; }
  float getB() const { return b; }
};

#endif