#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>

#include "mvl_menu.h"

#define keyboardKeyCount 322
#define mouseButtonCount 16

typedef struct {
    bool keys[keyboardKeyCount];
    bool pressedThisFrame[keyboardKeyCount];
} Keyboard;

typedef struct {
    bool buttons[mouseButtonCount];
    bool pressedThisFrame[mouseButtonCount];
} Mouse;

extern Keyboard keyboard;
extern Mouse mouse;

void inputInit();
void inputUpdate(SDL_Event* mouseEvents, int count);

bool keyHeld(SDL_Scancode scancode);
bool keyPressed(SDL_Scancode scancode);

bool mouseHeld(uint8_t button);
bool mousePressed(uint8_t button);
Vec2i mousePos();