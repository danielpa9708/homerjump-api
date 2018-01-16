#pragma once

#include "sprite.h"

class SpriteEx : public Sprite {
  double angle;
  Point center;
  Flip flip;
 public:
  virtual void draw();
};
