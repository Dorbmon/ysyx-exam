#include <NDL.h>
#include <SDL.h>
#include <sdl-event.h>
#include <stdlib.h>
#include <string.h>
#define keyname(k) #k,

static const char *keyname[] = {
  "NONE",
  _KEYS(keyname)
};

int SDL_PushEvent(SDL_Event *ev) {
  return 0;
}
int keyToIndex(char* key) {
  for (int i = 0;i < sizeof(keyname) / sizeof(char*);++ i) {
    if (strcmp(key, keyname[i]) == 0) return i;
  }
  return 0;
}
int SDL_PollEvent(SDL_Event *ev) {
  static char buf[64];
  if (NDL_PollEvent(buf, sizeof(buf))) {
    if (buf [1] == 'd') { //kd
      ev->type = SDL_KEYDOWN;
      ev->key.keysym.sym = keyToIndex(buf + 3);
    } else {
      ev->type = SDL_KEYUP;
      ev->key.keysym.sym = keyToIndex(buf + 3);
    }
    return 1;
  } else {
    return 0;
  }
}

int SDL_WaitEvent(SDL_Event *event) {
  while (SDL_PollEvent(event) == 0) ;
  return 1;
}

int SDL_PeepEvents(SDL_Event *ev, int numevents, int action, uint32_t mask) {
  return 0;
}

uint8_t* SDL_GetKeyState(int *numkeys) {
  return NULL;
}
