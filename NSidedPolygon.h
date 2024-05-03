#ifndef N_SIDED_POLYGON_H
#define N_SIDED_POLYGON_H

#include <GL/freeglut.h>

#include <cmath>

#include "Color.h"
#include "Shape.h"

class NSidedPolygon : public Shape {
 private:
  int n;
  float radius;
  float rot;

 public:
  NSidedPolygon() {
    x = 0;
    y = 0;
    selected = false;
    n = 3;
    radius = 0.1;
    rot = 0;
  }

  NSidedPolygon(float x, float y, float radius, int n, float rot, Color color) {
    this->x = x;
    this->y = y;
    selected = false;
    this->color = color;
    this->n = n;
    this->radius = radius;
    this->rot = rot;
  }

  void draw() {
    glColor3f(color.getR(), color.getG(), color.getB());
    float inc = (2 * M_PI) / n;

    glBegin(GL_POLYGON);
    for (float theta = 0; theta < 2 * M_PI; theta += inc)
      glVertex2f(radius * cos(theta + rot) + x, radius * sin(theta + rot) + y);
    glEnd();

    if (selected) {
      NSidedPolygon outer(x, y, 0.85 * radius, n, rot, Color(1, 1, 1));
      NSidedPolygon inner(x, y, 0.75 * radius, n, rot, color);
      outer.draw();
      inner.draw();
    }
  }

  bool contains(float mx, float my) {
    int numIntersections = 0;

    for (int i = 0; i < n; i++) {
      float x1 = radius * cos(2 * M_PI * i / n + rot) + x;
      float y1 = radius * sin(2 * M_PI * i / n + rot) + y;
      float x2 = radius * cos(2 * M_PI * (i + 1) / n + rot) + x;
      float y2 = radius * sin(2 * M_PI * (i + 1) / n + rot) + y;

      if ((my < y1) != (my < y2) &&
          mx < x1 + ((my - y1) / (y2 - y1)) * (x2 - x1)) {
        numIntersections++;
      }
    }

    return numIntersections % 2 == 1;
  }
};

#endif