#include "mvl_state_settings.h"

#include "mvl_state.h"
#include "mvl_ds.h"
#include "mvl_time.h"

void initLevelSettings(void* context) {
    LevelSettings* settings = context;

    settings->selected = 0;
    settings->okDst = (SDL_Rect){100, 156, 64, 28};
    settings->backArrowDst = (SDL_Rect){64, 64, 30, 30};
}

void onSettingsOkClickDone(void* context) {
    stateHandlerPop();
    stateHandlerPush(&select);
}

void onSettingsOkClick(void* context) {
    LevelSettings* settings = context;
    settings->okDst.x += 2;
    settings->okDst.y += 2;
    timeout(250, onSettingsOkClickDone, NULL);
}

void updateLevelSettings(void* context, float delta) {
    LevelSettings* settings = context;

    if (keyPressed(SDL_SCANCODE_UP)) {
        settings->selected = settings->selected == 0 ? 3 : settings->selected - 1;
    }
    if (keyPressed(SDL_SCANCODE_DOWN)) {
        settings->selected = settings->selected == 3 ? 0 : settings->selected + 1;
    }

    registerButton((Button){.area = settings->okDst, .callback = onSettingsOkClick, .context = context});
}

void renderLevelSettings(void* context, float delta, SDL_Renderer* renderer, Assets assets) {
    LevelSettings* settings = context;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 6; y++) {
            SDL_Rect dst = {top.x + x * 32, top.y + y * 32, 32, 32};

            Texture bg = y == 0 || y == 5 ? assets.menuDarkBg : assets.menuBg;
            SDL_RenderCopy(renderer, bg.ptr, NULL, &dst);
        }
    }

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 6; y++) {
            SDL_Rect dst = {bottom.x + x * 32, bottom.y + y * 32, 32, 32};
            SDL_RenderCopy(renderer, assets.menuBg.ptr, NULL, &dst);
        }
    }

    SDL_Color green = {64, 200, 0};
    SDL_Color gray = {152, 152, 152};

    for (int i = 0; i < 4; i++) {
        SDL_Rect src = {0, settings->selected == i ? 0 : 32, 256, 32};
        SDL_Rect dst = {bottom.x, bottom.y + 4 + i * 36, 256, 32};
        SDL_RenderCopy(renderer, assets.settings.ptr, &src, &dst);
    }

    SDL_Rect buttonDst = {bottom.x + settings->okDst.x, bottom.y + settings->okDst.y, 64, 28};
    SDL_RenderCopy(renderer, assets.button.ptr, NULL, &buttonDst);

    SDL_Rect okTextSrc = {96, 0, 32, 16};
    SDL_Rect okTextDst = {buttonDst.x + 16, buttonDst.y + 4, 32, 16};
    SDL_RenderCopy(renderer, assets.text.ptr, &okTextSrc, &okTextDst);
}