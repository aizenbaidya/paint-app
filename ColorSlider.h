#ifndef COLOR_SLIDER_H
#define COLOR_SLIDER_H

#include "Circle.h"
#include "RectangleShape.h"

class ColorSlider {
 private:
  RectangleShape area;
  Circle indicator;
  float intensity;

 public:
  ColorSlider() {}

  ColorSlider(float x, float y, Color color) {
    area = RectangleShape(x, y, 0.475, 0.05, color);
    area.outline();
    indicator = Circle(x, y, 0.035, Color(0, 0, 0));
    intensity = 0.5;
  }

  void draw() {
    area.draw();
    indicator.draw();
  }

  void handleClick(float x, float y) {
    if (indicator.contains(x, y)) {
      if (indicator.getX() >= area.getX() - area.getW() / 2 &&
          indicator.getX() <= area.getX() + area.getW() / 2) {
        indicator.setX(x);
        intensity = (x - area.getX() + area.getW() / 2) / area.getW();
      }
    }
  }

  float getIntensity() { return intensity; }

  bool contains(float x, float y) { return area.contains(x, y); }
};

#endif