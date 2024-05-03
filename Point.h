#ifndef POINT_H
#define POINT_H

#include "Color.h"
#include "Shape.h"

class Point : public Shape {
 private:
  int thickness;

  // A Point cannot contain a click, even though it inherits Shape.
  bool contains(float mx, float my) { return false; }

 public:
  Point() {
    x = 0;
    y = 0;
    thickness = 5;
  }

  Point(float x, float y, Color color, int thickness) {
    this->x = x;
    this->y = y;
    this->color = color;
    this->thickness = thickness;
  }

  void draw() {
    glColor3f(color.getR(), color.getG(), color.getB());
    glPointSize(thickness);
    glEnable(GL_POINT_SMOOTH);

    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
  }
};

#endif