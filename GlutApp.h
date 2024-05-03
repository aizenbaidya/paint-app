#ifndef GLUT_APP_H
#define GLUT_APP_H

#include <GL/freeglut.h>

#include <stdexcept>

#include "AppController.h"

class GlutApp;

void cleanup();

static GlutApp *singleton = nullptr;

class GlutApp {
 private:
  int height;
  int width;
  std::string title;
  AppController *controller;

  static void windowToScene(float &x, float &y) {
    x = (2 * (x / float(singleton->width))) - 1;
    y = 1 - (2 * (y / float(singleton->height)));
  }

  static void drawScene() {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_POINT_SMOOTH);
    glPointSize(5);

    singleton->controller->render();

    glutSwapBuffers();
  }

  static void mouse(int button, int state, int x, int y) {
    float mx = x;
    float my = y;

    windowToScene(mx, my);

    if (button == 0 && state == 0)
      singleton->controller->leftMouseDown(mx, my);
    else if (button == 0 && state == 1)
      singleton->controller->leftMouseUp(mx, my);
    else if (button == 2 && state == 0)
      singleton->controller->rightMouseDown(mx, my);
    else if (button == 2 && state == 1)
      singleton->controller->rightMouseUp(mx, my);

    glutPostRedisplay();
  }

  static void motion(int x, int y) {
    float mx = x;
    float my = y;

    windowToScene(mx, my);

    singleton->controller->mouseMotion(mx, my);

    glutPostRedisplay();
  }

  static void keyboard(unsigned char key, int x, int y) {
    float mx = x;
    float my = y;

    windowToScene(mx, my);

    singleton->controller->keyboardDown(key, mx, my);

    glutPostRedisplay();
  }

 public:
  GlutApp(int argc, char **argv) {
    height = 400;
    width = 400;
    title = "GLUT App";

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(150, 10);
    glutCreateWindow(title.c_str());

    glutDisplayFunc(drawScene);

    glutMouseFunc(mouse);

    glutMotionFunc(motion);

    glutKeyboardFunc(keyboard);

    singleton = this;

    controller = nullptr;

    std::atexit(cleanup);
  }

  void setController(AppController *controller) {
    this->controller = controller;
  }

  void setTitle(std::string title) {
    this->title = title;
    glutSetWindowTitle(this->title.c_str());
  }

  void run() {
    if (controller == nullptr) throw std::logic_error("Controller not set");
    glutMainLoop();
  }

  ~GlutApp() { delete controller; }
};

void cleanup() {
  if (singleton != nullptr) delete singleton;
}

#endif