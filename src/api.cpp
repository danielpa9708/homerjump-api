#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "api.h"
#include <cstdio>

void start();
void step();
void draw();

//gvars
static SDL_Window *window;
static SDL_Renderer *renderer;
static bool quit;
static SDL_Event event;
static int miliseconds;
//keyboard
static keyboard_handler_func keyboard_handler;
static bool keyboard_state[1<<30];
//prototypes
static bool input();
static void screen_clear();
static void screen_draw();
static bool init();
static void destroy();
static bool init_window(int width, int height);
static void destroy_window();
//draw off set
int draw_xos;
int draw_yos;

int main( int argv, char ** args ) {
  int time;
  if( init() ) {
    screen_clear();
    screen_draw();
    start();
    while( input() ) {
      step();
      screen_clear();
      draw();
      screen_draw();
      while( SDL_GetTicks() - time < miliseconds ) ;
      time = SDL_GetTicks();
    }
    destroy();
    end();
    return 0;
  } else {
    destroy();
    return 1;
  }
}

bool * get_keyboard_state() {
  return keyboard_state;
}
void set_keyboard_handler( keyboard_handler_func func) {
  keyboard_handler = func;
}

void close() {
  quit = true;
}

bool init_window( int width, int height ) {
  keyboard_handler = NULL;
  window = SDL_CreateWindow( "SDL_App",
                             SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                             640, 480,
                             SDL_WINDOW_SHOWN
                             );
  if(window == NULL) {
    destroy_window();
    return false;
  }
  renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
  if(renderer == NULL) {
    destroy_window();
    return false;
  }
  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
  return true;
}

void destroy_window() {
  if( window ) {
    SDL_DestroyWindow( window );
    window = NULL;
  }
  if( renderer ) {
    SDL_DestroyRenderer( renderer );
    renderer = NULL;
  }
}

bool init() {
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) return false;
  if( IMG_Init( IMG_INIT_PNG ) < 0 ) return false;
  if( !init_window( 640, 480 ) ) return false;
  miliseconds = 33;
  return true;
}

void destroy() {
  destroy_window();
  SDL_Quit();
}

bool input() {
  while( SDL_PollEvent( &event ) ) {
    switch( event.type ) {
    case SDL_QUIT:
      quit = true;
      break;
    case SDL_KEYDOWN:
      keyboard_state[event.key.keysym.sym] = true;
      if( keyboard_handler ) {
        keyboard_handler( KEYBOARD_EVENT_DOWN, event.key.keysym.sym );
      }
      break;
    case SDL_KEYUP:
      keyboard_state[event.key.keysym.sym] = false;
      if( keyboard_handler ) {
        keyboard_handler( KEYBOARD_EVENT_UP, event.key.keysym.sym );
      }
      break;
    }
  }
  return !quit;
}

void screen_clear() {
  SDL_RenderClear(renderer);
}
void screen_draw() {
  SDL_RenderPresent(renderer);
}

bool fullscreen = false;
bool is_fullscreen() {
  return fullscreen;
}
void set_fullscreen(bool full) {
  SDL_SetWindowFullscreen(window, (full ? SDL_TRUE : SDL_FALSE));
  fullscreen = full;
}
//Image definitions
bool Image::is_ok() {
  return texture;
}

void Image::load( SDL_Surface *surface ) {
  texture = SDL_CreateTextureFromSurface(renderer, surface);
}

bool Image::load( const char *path ) {
  SDL_Surface * surface;
  surface = IMG_Load( path );
  load( surface );
  SDL_FreeSurface( surface );
  return is_ok();
}

void Image::draw( const Rect *pos, const Rect *clip ) {
  SDL_RenderCopy( renderer, texture, clip, pos );
}

Image::Image() {
  texture = NULL;
}

void Image::drawex(const Rect *pos, const Rect *clip,
                   double angle, const Point *center, Flip flip) {
  SDL_RenderCopyEx(renderer, texture, clip, pos,
                   angle, center, flip);
}

Image::~Image() {
  SDL_DestroyTexture( texture );
}
