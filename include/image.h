#pragma once

#include <SDL2/SDL.h>
#include "common.h"

class Rect;
class SDL_Texture;
class SDL_Surface;

class Image {
 public:
  SDL_Texture *texture;

  //methods use this
  bool is_ok();
  bool load( const char * path );
  void draw( const Rect * pos, const Rect * clip );
  void drawex(const Rect *pos, const Rect *clip,
              double angle, const Point *center, Flip flip);

  Image();
  ~Image();

 protected:
  //internal fuck you dont look ha
  void load( SDL_Surface * surface );
};
