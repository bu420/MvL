#include "mvl_input.h"

Keyboard keyboard;
Mouse mouse;

void inputInit() {
    for (int i = 0; i < keyboardKeyCount; i++) {
        keyboard.keys[i] = keyboard.pressedThisFrame[i] = false;
    }

    for (int i = 0; i < mouseButtonCount; i++) {
        mouse.buttons[i] = mouse.pressedThisFrame[i] = false;
    }
}

void inputUpdate(SDL_Event* mouseEvents, int count) {
    // Keyboard.
    uint8_t* keys = (uint8_t*)SDL_GetKeyboardState(NULL);
    for (int i = 0; i < keyboardKeyCount; i++) {
        if (keys[i]) {
            if (!keyboard.keys[i]) {
                keyboard.keys[i] = true;
                keyboard.pressedThisFrame[i] = true;
            }
            else {
                keyboard.pressedThisFrame[i] = false;
            }
        }
        else {
            keyboard.keys[i] = false;
            keyboard.pressedThisFrame[i] = false;
        }
    }

    // Mouse.
    for (int i = 0; i < mouseButtonCount; i++) {
        if (mouse.buttons[i] && mouse.pressedThisFrame[i]) {
            mouse.pressedThisFrame[i] = false;
        }
    }

    for (int i = 0; i < count; i++) {
        int button = mouseEvents[i].button.button;

        if (mouseEvents[i].type == SDL_MOUSEBUTTONDOWN) {
            mouse.buttons[button] = mouse.pressedThisFrame[button] = true;
        }
        else if (mouseEvents[i].type == SDL_MOUSEBUTTONUP) {
            mouse.buttons[button] = mouse.pressedThisFrame[button] = false;
        }
    }
}

bool keyHeld(SDL_Scancode scancode) {
    return keyboard.keys[scancode];
}

bool keyPressed(SDL_Scancode scancode) {
    return keyboard.keys[scancode] && keyboard.pressedThisFrame[scancode];
}

bool mouseHeld(uint8_t button) {
    return mouse.buttons[button];
}

bool mousePressed(uint8_t button) {
    return mouse.buttons[button] && mouse.pressedThisFrame[button];
}

Vec2i mousePos() {
    Vec2i pos;
    SDL_GetMouseState(&pos.x, &pos.y);
    return pos;
}