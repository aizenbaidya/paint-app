#ifndef CIRCLE_H
#define CIRCLE_H

#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <cmath>

#include "Color.h"
#include "Shape.h"

class Circle : public Shape {
 private:
  float radius;

 public:
  Circle() {
    x = 0;
    y = 0;
    selected = false;
    radius = 0.1;
  }

  Circle(float x, float y, float radius, Color color) {
    this->x = x;
    this->y = y;
    selected = false;
    this->color = color;
    this->radius = radius;
  }

  void draw() {
    glColor3f(color.getR(), color.getG(), color.getB());
    float inc = (2 * M_PI) / 60;

    glBegin(GL_POLYGON);
    for (float theta = 0; theta < 2 * M_PI; theta += inc)
      glVertex2f(radius * cos(theta) + x, radius * sin(theta) + y);
    glEnd();

    if (selected) {
      Circle outer(x, y, 0.85 * radius, Color(1, 1, 1));
      Circle inner(x, y, 0.75 * radius, color);
      outer.draw();
      inner.draw();
    }
  }

  bool contains(float mx, float my) {
    return radius >= sqrt(pow(mx - x, 2) + pow(my - y, 2));
  }
};

#endif