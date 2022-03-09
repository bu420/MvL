#include "mvl_asset.h"

#include <SDL2/SDL_image.h>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace mvl;

void Assets::load() {
    font = loadFont("asset/Nintendo-DS-BIOS (Edited).ttf", 24);
    icon = loadSurface("asset/icon.png");
    numbers = loadSurface("asset/menu/numbers.png");
    text = loadSurface("asset/menu/text.png");
    menuBg = loadSurface("asset/menu/bg.png");
    banner = loadSurface("asset/menu/banner.png");
    backArrow = loadSurface("asset/menu/back_arrow.png");
    settings = loadSurface("asset/menu/settings.png");
    button = loadSurface("asset/menu/button.png");
    arrows = loadSurface("asset/menu/arrows.png");
    borders = loadSurface("asset/menu/borders.png");
    boxes = loadSurface("asset/menu/boxes.png");
    levelIcons = loadSurface("asset/menu/level_icons.png");
    net = loadSurface("asset/menu/net.png");
    blueBricks = loadSurface("asset/blue_bricks.png");
}

SDL_Surface* Assets::loadSurface(std::string path) {
    SDL_Surface* surface = IMG_Load(path.c_str());

    if (!surface) {
        throw std::runtime_error("Could not load: " + path);
    }

    return surface;
}

TTF_Font* Assets::loadFont(std::string path, int size) {
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);

    if (!font) {
        throw std::runtime_error("Could not load: " + path);
    }

    return font;
}

Mix_Chunk* Assets::loadSound(std::string path) {
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());

    if (!sound) {
        throw std::runtime_error("Could not load: " + path);
    }

    return sound;
}

std::string Assets::readFile(std::string path) {
    std::ifstream file(path);
    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}
