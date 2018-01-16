#pragma once

#include <SDL2/SDL.h>
#include "common.h"

class Image;
class Rect;
class Point;

class Animation {
 public:
  Image * image;
  int width, height;
  int frames;
  int frames_offset;
  double frames_speed;
  bool loop;
  void draw(int frame, const Rect *pos);
  void drawex(int frame, const Rect *pos, double angle, const Point *center, Flip flip);
 protected:
  void get_offset(Rect * rect, int frame);
};
