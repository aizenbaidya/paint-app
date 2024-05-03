#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/freeglut.h>

#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

struct Texture {
 private:
  std::string imagePath;
  float x;
  float y;
  float w;
  float h;
  bool selected;

  unsigned char *imageData;
  int imageWidth;
  int imageHeight;
  int bitDepth;
  GLuint texture;

  void loadTexture() {
    stbi_set_flip_vertically_on_load(true);
    imageData = stbi_load(imagePath.c_str(), &imageWidth, &imageHeight,
                          &bitDepth, STBI_rgb_alpha);
    if (imageData == NULL)
      std::cerr << "Failed to load the texture file" << std::endl;
    else
      std::cout << "The texture file loaded successfully." << std::endl;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, imageData);
  }

 public:
  Texture() {}

  Texture(std::string imagePath, float x, float y, float w, float h) {
    this->imagePath = imagePath;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    selected = false;
    loadTexture();
  }

  void select() { selected = true; }

  void deselect() { selected = false; }

  void draw() {
    if (selected)
      glColor3f(1, 1, 1);
    else
      glColor3f(0.8, 0.8, 0.8);

    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y - h);
    glVertex2f(x, y - h);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y - h);
    glVertex2f(x, y - h);
    glEnd();

    // Display texture
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Map texture to a polygon
    glBegin(GL_POLYGON);
    // Bottom left corner
    glTexCoord2f(0, 0);
    glVertex2f(x, y - h);

    // Top left corner
    glTexCoord2f(0, 1);
    glVertex2f(x, y);

    // Top right corner
    glTexCoord2f(1, 1);
    glVertex2f(x + w, y);

    // Bottom right corner
    glTexCoord2f(1, 0);
    glVertex2f(x + w, y - h);
    glEnd();

    glDisable(GL_TEXTURE_2D);
  }

  bool contains(float mx, float my) {
    return mx >= x && mx <= x + w && my <= y && my >= y - h;
  }
};

#endif