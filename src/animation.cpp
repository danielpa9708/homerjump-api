#include "animation.h"
#include "image.h"


void Animation::get_offset(Rect * clip, int frame) {
  frame += frames_offset;
  clip->x = frame*width;
  clip->y = 0;
  clip->w = width;
  clip->h = height;
}

void Animation::draw(int frame, const Rect *pos) {
  Rect clip;
  get_offset(&clip, frame);
  image->draw(pos, &clip);
}
void Animation::drawex(int frame, const Rect *pos, double angle, const Point *center, Flip flip) {
  Rect clip;
  get_offset(&clip, frame);
  image->drawex(pos, &clip, angle, center, flip);
}
