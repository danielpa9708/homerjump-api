#pragma once

#include <SDL2/SDL.h>
#include "common.h"
#include "image.h"
#include "animation.h"
#include "sprite.h"
#include "spriteex.h"

enum {
  KEYBOARD_EVENT_DOWN = SDL_KEYDOWN,
  KEYBOARD_EVENT_UP = SDL_KEYUP
};

typedef void ( *keyboard_handler_func )( Sint32, Sint32);

#define VKEY( key ) SDLK_##key

bool * get_keyboard_state();
void set_keyboard_handler( keyboard_handler_func );

bool is_fullscreen();
void set_fullscreen(bool full);

extern int draw_xos;
extern int draw_yos;

void close();

void start();
void step();
void draw();
void end();
