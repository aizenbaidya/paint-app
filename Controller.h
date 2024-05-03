#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/freeglut.h>

#include "AppController.h"
#include "Canvas.h"
#include "ColorPicker.h"
#include "Toolbar.h"

class Controller : public AppController {
 private:
  Canvas canvas;
  ColorPicker colorPicker;
  Toolbar toolbar;

  void leftMouseDown(float x, float y) {
    if (toolbar.contains(x, y)) {
      toolbar.handleClick(x, y);
      if (toolbar.getTool() == TRASH) {
        canvas.clear();
        return;
      }
      if (toolbar.getMove() == BACK)
        canvas.moveSelectedShapeBack();
      else if (toolbar.getMove() == FRONT)
        canvas.moveSelectedShapeFront();
    } else if (canvas.contains(x, y)) {
      canvas.handleClick(x, y, toolbar.getTool(), colorPicker.getColor());
    }
  }

  void mouseMotion(float x, float y) {
    if (canvas.contains(x, y)) {
      canvas.handleDrag(x, y, toolbar.getTool(), colorPicker.getColor());
    } else if (colorPicker.contains(x, y)) {
      colorPicker.handleClick(x, y);
      if (toolbar.getTool() == MOUSE)
        canvas.recolorSelectedShape(colorPicker.getColor());
    }
  }

  void keyboardDown(unsigned char key, float x, float y) {
    if (key == 27) exit(0);
  }

  void render() {
    canvas.draw();
    colorPicker.draw();
    toolbar.draw();
  }

 public:
  Controller() {}
};

#endif