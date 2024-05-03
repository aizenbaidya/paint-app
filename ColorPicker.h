#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include "Color.h"
#include "ColorSlider.h"
#include "RectangleShape.h"

class ColorPicker {
 private:
  RectangleShape area;
  RectangleShape displayColor;
  ColorSlider redSlider;
  ColorSlider greenSlider;
  ColorSlider blueSlider;

 public:
  ColorPicker() {
    area = RectangleShape(0.1, -0.9, 1.8, 0.2, Color(0.66, 0.66, 0.66));
    redSlider = ColorSlider(-0.52, -0.9, Color(1, 0, 0));
    greenSlider = ColorSlider(0, -0.9, Color(0, 1, 0));
    blueSlider = ColorSlider(0.52, -0.9, Color(0, 0, 1));
    displayColor = RectangleShape(0.9, -0.9, 0.2, 0.2, getColor());
    displayColor.outline();
  }

  void draw() {
    area.draw();
    displayColor.draw();
    redSlider.draw();
    greenSlider.draw();
    blueSlider.draw();

    // Borders for the area:
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    // Top:
    glVertex2f(-0.8, -0.8);
    glVertex2f(0.8, -0.8);
    // Bottom:
    glVertex2f(-0.8, -0.999);
    glVertex2f(1, -0.999);
    glEnd();
  }

  void handleClick(float x, float y) {
    if (redSlider.contains(x, y))
      redSlider.handleClick(x, y);
    else if (greenSlider.contains(x, y))
      greenSlider.handleClick(x, y);
    else if (blueSlider.contains(x, y))
      blueSlider.handleClick(x, y);
    displayColor.setColor(getColor());
  }

  bool contains(float x, float y) { return area.contains(x, y); }

  Color getColor() {
    return Color(redSlider.getIntensity(), greenSlider.getIntensity(),
                 blueSlider.getIntensity());
  }
};

#endif