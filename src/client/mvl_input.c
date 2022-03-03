#include "mvl_input.h"

Keyboard gKeyboard;
Mouse gMouse;

void inputInit() {
    for (int i = 0; i < gKeyboardKeyCount; i++) {
        gKeyboard.keys[i] = gKeyboard.pressedThisFrame[i] = false;
    }

    for (int i = 0; i < gMouseButtonCount; i++) {
        gMouse.buttons[i] = gMouse.pressedThisFrame[i] = false;
    }
}

void inputUpdate(SDL_Event* mouseEvents, int count) {
    // gKeyboard.
    uint8_t* keys = (uint8_t*)SDL_GetKeyboardState(NULL);
    for (int i = 0; i < gKeyboardKeyCount; i++) {
        if (keys[i]) {
            if (!gKeyboard.keys[i]) {
                gKeyboard.keys[i] = true;
                gKeyboard.pressedThisFrame[i] = true;
            }
            else {
                gKeyboard.pressedThisFrame[i] = false;
            }
        }
        else {
            gKeyboard.keys[i] = false;
            gKeyboard.pressedThisFrame[i] = false;
        }
    }

    // Mouse.
    for (int i = 0; i < gMouseButtonCount; i++) {
        if (gMouse.buttons[i] && gMouse.pressedThisFrame[i]) {
            gMouse.pressedThisFrame[i] = false;
        }
    }

    for (int i = 0; i < count; i++) {
        int button = mouseEvents[i].button.button;

        if (mouseEvents[i].type == SDL_MOUSEBUTTONDOWN) {
            gMouse.buttons[button] = gMouse.pressedThisFrame[button] = true;
        }
        else if (mouseEvents[i].type == SDL_MOUSEBUTTONUP) {
            gMouse.buttons[button] = gMouse.pressedThisFrame[button] = false;
        }
    }
}

bool keyHeld(SDL_Scancode scancode) {
    return gKeyboard.keys[scancode];
}

bool keyPressed(SDL_Scancode scancode) {
    return gKeyboard.keys[scancode] && gKeyboard.pressedThisFrame[scancode];
}

bool mouseHeld(uint8_t button) {
    return gMouse.buttons[button];
}

bool mousePressed(uint8_t button) {
    return gMouse.buttons[button] && gMouse.pressedThisFrame[button];
}

Vec2i mousePos() {
    Vec2i pos;
    SDL_GetMouseState(&pos.x, &pos.y);
    return pos;
}