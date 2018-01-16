#pragma once

#include "common.h"

class Animation;
class Rect;

class Sprite {
 public:
  Animation * animation;
  double x, y;
  int width, height;
  double frame;
 /* protected: */
  bool done_animation;

 public:
  void set_animation(Animation * anim);
  void get_offset(Rect * rect);
  virtual ~Sprite();
  virtual void update();
  virtual void draw();
};
