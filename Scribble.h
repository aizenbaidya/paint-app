#ifndef SCRIBBLE_H
#define SCRIBBLE_H

#include "Color.h"
#include "Point.h"
#include "Shape.h"

class Scribble : public Shape {
 private:
  Point points[5000];
  int pCounter;

  float left;
  float right;
  float top;
  float bottom;

 public:
  Scribble(Color color) {
    this->color = color;
    pCounter = 0;
    selected = false;
    left = 0;
    right = 0;
    top = 0;
    bottom = 0;
  }

  void addPoint(float x, float y, Color color) {
    if (pCounter == 0) {
      this->x = x;
      this->y = y;
    }

    if (this->x - x > left) left = this->x - x;
    if (x - this->x > right) right = x - this->x;
    if (y - this->y > top) top = y - this->y;
    if (this->y - y > bottom) bottom = this->y - y;

    points[pCounter] = Point(x - this->x, y - this->y, color, 7);
    pCounter++;
  }

  void draw() {
    if (selected) {
      // Draw bounding box
      glLineWidth(2);
      glColor3f(0.66, 0.66, 0.66);

      glBegin(GL_LINE_LOOP);
      glVertex2f(x - left - 0.04, y + top + 0.04);
      glVertex2f(x + right + 0.04, y + top + 0.04);
      glVertex2f(x + right + 0.04, y - bottom - 0.04);
      glVertex2f(x - left - 0.04, y - bottom - 0.04);
      glEnd();

      // Return to the original line width for all other elements.
      glLineWidth(1);
    }

    for (int i = 0; i < pCounter; i++) {
      float currX = x + points[i].getX();
      float currY = y + points[i].getY();
      Color currColor = getColor();
      Point temp(currX, currY, currColor, 7);
      temp.draw();
    }
  }

  bool contains(float x, float y) {
    return x >= this->x - left && x <= this->x + right && y <= this->y + top &&
           y >= this->y - bottom;
  }
};

#endif