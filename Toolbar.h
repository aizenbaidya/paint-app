#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <array>

#include "RectangleShape.h"
#include "Texture.h"

enum Tool { TRASH, ERASER, PENCIL, MOUSE, CIRCLE, HEXAGON, SQUARE, TRIANGLE };
enum Move { FRONT, BACK };

class Toolbar {
 private:
  RectangleShape area;

  std::array<Texture, 8> toolButtons;
  Tool selectedTool;

  std::array<Texture, 2> moveButtons;
  Move selectedMove;

  void deselectAllTools() {
    for (auto &toolButton : toolButtons) toolButton.deselect();
  }

  void deselectAllMoves() {
    for (auto &moveButton : moveButtons) moveButton.deselect();
  }

  void setSelectedTool(Tool tool) {
    deselectAllTools();
    toolButtons[static_cast<int>(tool)].select();
    selectedTool = tool;
  }

  void setSelectedMove(Move move) {
    deselectAllMoves();
    moveButtons[static_cast<int>(move)].select();
    selectedMove = move;
  }

 public:
  Toolbar() {
    area = RectangleShape(-0.9, 0, 0.2, 2, Color(0.83, 0.83, 0.83));
    toolButtons[0] = Texture("assets/trash.png", -1, 1, 0.2, 0.2);
    toolButtons[1] = Texture("assets/eraser.png", -1, 0.8, 0.2, 0.2);
    toolButtons[2] = Texture("assets/pencil.png", -1, 0.6, 0.2, 0.2);
    toolButtons[3] = Texture("assets/mouse.png", -1, 0.4, 0.2, 0.2);
    toolButtons[4] = Texture("assets/circle.png", -1, 0.2, 0.2, 0.2);
    toolButtons[5] = Texture("assets/hexagon.png", -1, 0, 0.2, 0.2);
    toolButtons[6] = Texture("assets/square.png", -1, -0.2, 0.2, 0.2);
    toolButtons[7] = Texture("assets/triangle.png", -1, -0.4, 0.2, 0.2);
    setSelectedTool(PENCIL);

    moveButtons[0] = Texture("assets/move-to-front.png", -1, -0.6, 0.2, 0.2);
    moveButtons[1] = Texture("assets/move-to-back.png", -1, -0.8, 0.2, 0.2);
  }

  void draw() {
    area.draw();
    for (auto &toolButton : toolButtons) toolButton.draw();
    for (auto &moveButton : moveButtons) moveButton.draw();

    // Outlining the tools
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.999, 1);
    glVertex2f(-0.8, 1);
    glVertex2f(-0.8, -0.599);
    glVertex2f(-0.999, -0.599);
    glEnd();

    // Outlining the moveButtons
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.999, -0.6);
    glVertex2f(-0.8, -0.6);
    glVertex2f(-0.8, -0.999);
    glVertex2f(-0.999, -0.999);
    glEnd();
  }

  void handleClick(float x, float y) {
    for (int i = 0; i < toolButtons.size(); i++)
      if (toolButtons[i].contains(x, y)) setSelectedTool(static_cast<Tool>(i));
    for (int i = 0; i < moveButtons.size(); i++)
      if (moveButtons[i].contains(x, y)) setSelectedMove(static_cast<Move>(i));
  }

  bool contains(float x, float y) { return area.contains(x, y); }

  Tool getTool() { return selectedTool; }
  Move getMove() { return selectedMove; }
};

#endif