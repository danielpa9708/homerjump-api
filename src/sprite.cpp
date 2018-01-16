#include <SDL2/SDL.h>
#include "sprite.h"
#include "common.h"
#include "animation.h"
#include "api.h"

void Sprite::set_animation(Animation * anim) {
  done_animation = false;
  animation = anim;
  frame = 0;
}

void Sprite::get_offset(Rect * rect) {
  rect->x = x - draw_xos;
  rect->y = y - draw_yos;
  rect->w = width;
  rect->h = height;
}

void Sprite::update() {
  const Animation &anim = *animation;
  if(!done_animation) {
    frame += anim.frames_speed;
    if(frame >= anim.frames) {
      if(anim.loop) {
        frame -= anim.frames;
      } else {
        frame = anim.frames-1;
        done_animation = true;
      }
    }
  }
}

void Sprite::draw() {
  Rect rect;
  get_offset(&rect);
  animation->draw(frame, &rect);
}

Sprite::~Sprite() {
}
