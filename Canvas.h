#ifndef CANVAS_H
#define CANVAS_H

#include "Circle.h"
#include "NSidedPolygon.h"
#include "Point.h"
#include "RectangleShape.h"
#include "Scribble.h"
#include "Toolbar.h"

class Canvas {
 private:
  RectangleShape area;

  Shape *shapes[1000];
  int shapeCounter;
  int selectedShape;

  float offsetX;
  float offsetY;

  void eraseAt(float x, float y) {
    for (int i = shapeCounter - 1; i >= 0; i--) {
      if (shapes[i]->contains(x, y)) {
        delete shapes[i];
        for (int j = i; j < shapeCounter; j++) shapes[j] = shapes[j + 1];
        shapeCounter--;
        return;
      }
    }
  }

 public:
  Canvas() {
    area = RectangleShape(0.1, 0.1, 1.8, 1.8, Color(1, 1, 1));
    shapeCounter = 0;
    selectedShape = -1;
    offsetX = 0;
    offsetY = 0;
  }

  void draw() {
    area.draw();
    for (int i = 0; i < shapeCounter; i++) shapes[i]->draw();
  }

  void handleClick(float x, float y, Tool tool, Color color) {
    if (tool == PENCIL) {
      shapes[shapeCounter] = new Scribble(color);
      shapeCounter++;
      static_cast<Scribble *>(shapes[shapeCounter - 1])->addPoint(x, y, color);
    } else if (tool == ERASER) {
      eraseAt(x, y);
    } else if (tool == SQUARE) {
      shapes[shapeCounter] = new RectangleShape(x, y, 0.3, 0.3, color);
      shapeCounter++;
    } else if (tool == CIRCLE) {
      shapes[shapeCounter] = new Circle(x, y, 0.15, color);
      shapeCounter++;
    } else if (tool == TRIANGLE) {
      shapes[shapeCounter] = new NSidedPolygon(x, y, 0.15, 3, M_PI / 2, color);
      shapeCounter++;
    } else if (tool == HEXAGON) {
      shapes[shapeCounter] = new NSidedPolygon(x, y, 0.15, 6, 0, color);
      shapeCounter++;
    } else if (tool == MOUSE) {
      for (int i = 0; i < shapeCounter; i++) shapes[i]->deselect();
      selectedShape = -1;
      for (int i = shapeCounter - 1; i >= 0; i--) {
        if (shapes[i]->contains(x, y)) {
          shapes[i]->select();
          selectedShape = i;
          offsetX = x - shapes[i]->getX();
          offsetY = shapes[i]->getY() - y;
          return;
        }
      }
    }
  }

  void handleDrag(float x, float y, Tool tool, Color color) {
    if (tool == PENCIL) {
      static_cast<Scribble *>(shapes[shapeCounter - 1])->addPoint(x, y, color);
    } else if (tool == ERASER) {
      eraseAt(x, y);
    } else if (tool == MOUSE) {
      if (selectedShape != -1) {
        shapes[selectedShape]->setX(x - offsetX);
        shapes[selectedShape]->setY(y + offsetY);
      }
    }
  }

  void recolorSelectedShape(Color color) {
    if (selectedShape != -1) shapes[selectedShape]->setColor(color);
  }

  void moveSelectedShapeBack() {
    if (selectedShape != -1 && selectedShape > 0) {
      Shape *temp = shapes[selectedShape];
      for (int i = selectedShape; i > 0; i--) shapes[i] = shapes[i - 1];
      shapes[0] = temp;
      selectedShape = 0;
    }
  }

  void moveSelectedShapeFront() {
    if (selectedShape != -1 && selectedShape < shapeCounter - 1) {
      Shape *temp = shapes[selectedShape];
      for (int i = selectedShape; i < shapeCounter; i++)
        shapes[i] = shapes[i + 1];
      shapes[shapeCounter - 1] = temp;
      selectedShape = shapeCounter - 1;
    }
  }

  void clear() {
    for (int i = 0; i < shapeCounter; i++) delete shapes[i];
    shapeCounter = 0;
  }

  bool contains(float x, float y) { return area.contains(x, y); }
};

#endif