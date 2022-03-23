#include "mvl_input.h"

using namespace mvl;

void Input::update(std::vector<SDL_Event> events) {
    updateKeyboard(events);
    updateMouse(events);
}

bool Input::keyHeld(SDL_Scancode scancode) {
    if (keyboard.count(scancode)) {
        return keyboard.at(scancode).first;
    }
    
    return false;
}

bool Input::keyPressed(SDL_Scancode scancode) {
    if (keyboard.count(scancode)) {
        return keyboard.at(scancode).first && keyboard.at(scancode).second;
    }

    return false;
}

bool Input::buttonHeld(uint8_t button) {
    if (mouse.count(button)) {
        return mouse.at(button).first;
    }

    return false;
}

bool Input::buttonClicked(uint8_t button) {
    if (mouse.count(button)) {
        return mouse.at(button).first && mouse.at(button).second;
    }

    return false;
}

Vec2i Input::mousePos() {
    Vec2i pos;
    SDL_GetMouseState(&pos.x, &pos.y);
    return pos;
}

void Input::updateKeyboard(std::vector<SDL_Event> events) {
    for (auto it = keyboard.begin(); it != keyboard.end(); it++) {
        if (it->second.first && it->second.second) {
            it->second.second = false;
        }
    }

    for (SDL_Event event : events) {
        SDL_Scancode scancode = event.key.keysym.scancode;

        if (event.type == SDL_KEYDOWN) {
            if (!getKey(scancode).first) {
                getKey(scancode).first = getKey(scancode).second = true;
            }
        }
        else if (event.type == SDL_KEYUP) {
            getKey(scancode).first = getKey(scancode).second = false;
        }
    }
}

void Input::updateMouse(std::vector<SDL_Event> events) {
    for (auto it = mouse.begin(); it != mouse.end(); it++) {
        if (it->second.first && it->second.second) {
            it->second.second = false;
        }
    }

    for (SDL_Event event : events) {
        uint8_t button = event.button.button;

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            getButton(button).first = getButton(button).second = true;
        }
        else if (event.type == SDL_MOUSEBUTTONUP) {
            getButton(button).first = getButton(button).second = false;
        }
    }
}

std::pair<bool, bool>& Input::getKey(SDL_Scancode scancode) {
    if (!keyboard.count(scancode)) {
        keyboard.insert(std::make_pair(scancode, std::make_pair(false, false)));
    }

    return keyboard.at(scancode);
}

std::pair<bool, bool>& Input::getButton(uint8_t button) {
    if (!mouse.count(button)) {
        mouse.insert(std::make_pair(button, std::make_pair(false, false)));
    }

    return mouse.at(button);
}