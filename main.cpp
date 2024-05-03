#include "Controller.h"
#include "GlutApp.h"

int main(int argc, char **argv) {
  GlutApp *app = new GlutApp(argc, argv);

  Controller *myController = new Controller();

  app->setController(myController);

  app->setTitle("OpenGL Paint Application");

  app->run();

  return 0;
}