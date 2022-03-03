#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>

#include "mvl_menu.h"

#define gKeyboardKeyCount 322
#define gMouseButtonCount 16

typedef struct {
    bool keys[gKeyboardKeyCount];
    bool pressedThisFrame[gKeyboardKeyCount];
} Keyboard;

typedef struct {
    bool buttons[gMouseButtonCount];
    bool pressedThisFrame[gMouseButtonCount];
} Mouse;

extern Keyboard gKeyboard;
extern Mouse gMouse;

void inputInit();
void inputUpdate(SDL_Event* mouseEvents, int count);

bool keyHeld(SDL_Scancode scancode);
bool keyPressed(SDL_Scancode scancode);

bool mouseHeld(uint8_t button);
bool mousePressed(uint8_t button);
Vec2i mousePos();