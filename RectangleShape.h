#ifndef RECTANGLE_SHAPE_H
#define RECTANGLE_SHAPE_H

#include <GL/freeglut.h>

#include "Color.h"
#include "Shape.h"

class RectangleShape : public Shape {
 private:
  float w;
  float h;
  bool outlined;

 public:
  RectangleShape() {
    x = 0;
    y = 0;
    selected = false;
    w = 0.4;
    h = 0.2;
    outlined = false;
  }

  RectangleShape(float x, float y, float w, float h, Color color) {
    this->x = x;
    this->y = y;
    selected = false;
    this->color = color;
    this->w = w;
    this->h = h;
    outlined = false;
  }

  void draw() {
    glColor3f(color.getR(), color.getG(), color.getB());

    glBegin(GL_POLYGON);
    glVertex2f(x - w / 2, y - h / 2);
    glVertex2f(x + w / 2, y - h / 2);
    glVertex2f(x + w / 2, y + h / 2);
    glVertex2f(x - w / 2, y + h / 2);
    glEnd();

    if (selected) {
      RectangleShape outer(x, y, 0.85 * w, 0.85 * h, Color(1, 1, 1));
      RectangleShape inner(x, y, 0.75 * w, 0.75 * h, color);
      outer.draw();
      inner.draw();
    }

    if (outlined) {
      glColor3f(0, 0, 0);

      glBegin(GL_LINE_LOOP);
      glVertex2f(x - w / 2, y - h / 2);
      glVertex2f(x + w / 2, y - h / 2);
      glVertex2f(x + w / 2, y + h / 2);
      glVertex2f(x - w / 2, y + h / 2);
      glEnd();
    }
  }

  bool contains(float mx, float my) {
    return mx >= x - w / 2 && mx <= x + w / 2 && my <= y + h / 2 &&
           my >= y - h / 2;
  }

  float getW() { return w; }
  float getH() { return h; }

  void setW(float w) { this->w = w; }
  void setH(float h) { this->h = h; }

  void outline() { outlined = true; }
};

#endif