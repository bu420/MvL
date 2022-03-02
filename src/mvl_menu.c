#include "mvl_menu.h"

#include <assert.h>
#include <stdio.h>

#include "mvl_input.h"
#include "mvl_ds.h"
#include "mvl_state.h"
#include "mvl_time.h"

Button buttons[maxButtonCount];
int buttonCount = 0;

void registerButton(Button button) {
    assert(buttonCount < maxButtonCount);
    buttons[buttonCount++] = button;
}

void handleButtons() {
    if (mousePressed(SDL_BUTTON_LEFT)) {
        Vec2i pos = subVec2i(mousePos(), bottom);
        SDL_Point point = {pos.x, pos.y};

        for (int i = 0; i < buttonCount; i++) {
            if (SDL_PointInRect(&point, &buttons[i].area)) {
                if (buttons[i].callback) {
                    buttons[i].callback(buttons[i].context);
                }
                break;
            }
        }
    }

    buttonCount = 0;
}

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

void initLevelSelect(void* context) {
    LevelSelect* select = context;

    select->backArrowDst = (SDL_Rect){224, 160, 30, 30};
    select->selected = 0;
    select->levelIcons[0] = (LevelIcon){(SDL_Rect){0, 0, 48, 48}, (SDL_Rect){32, 56, 48, 48}};
    select->levelIcons[1] = (LevelIcon){(SDL_Rect){0, 48, 48, 48}, (SDL_Rect){104, 56, 48, 48}};
    select->levelIcons[2] = (LevelIcon){(SDL_Rect){0, 96, 48, 48}, (SDL_Rect){176, 56, 48, 48}};
    select->levelIcons[3] = (LevelIcon){(SDL_Rect){0, 144, 48, 48}, (SDL_Rect){66, 124, 48, 48}};
    select->levelIcons[4] = (LevelIcon){(SDL_Rect){0, 192, 48, 48}, (SDL_Rect){140, 124, 48, 48}};
}

void onLevelIconClick(void* context) {
    
}

void onSelectBackArrowClickDone(void* context) {
    stateHandlerPop();
    stateHandlerPush(&settings);
}

void onSelectBackArrowClick(void* context) {
    LevelSelect* select = context;
    select->backArrowDst.x += 2;
    select->backArrowDst.y += 2;
    timeout(250, onSelectBackArrowClickDone, NULL);
}

void updateLevelSelect(void* context, float delta) {
    LevelSelect* select = context;

    if (keyPressed(SDL_SCANCODE_RIGHT)) {
        select->selected = select->selected == 4 ? 0 : select->selected + 1;
    }
    if (keyPressed(SDL_SCANCODE_LEFT)) {
        select->selected = select->selected == 0 ? 4 : select->selected - 1;
    }

    for (int i = 0; i < levelCount; i++) {
        registerButton((Button){.area = select->levelIcons[i].dst, .callback = onLevelIconClick, .context = NULL});
    }

    registerButton((Button){.area = select->backArrowDst, .callback = onSelectBackArrowClick, .context = context});
}

void renderLevelSelect(void* context, float delta, SDL_Renderer* renderer, Assets assets) {
    LevelSelect select = *(LevelSelect*)context;
    
    // Top background.
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 6; y++) {
            SDL_Rect dst = {top.x + x * 32, top.y + y * 32, 32, 32};

            Texture bg = y == 0 || y == 5 ? assets.menuDarkBg : assets.menuBg;
            SDL_RenderCopy(renderer, bg.ptr, NULL, &dst);
        }
    }

    // Bottom background.
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 6; y++) {
            SDL_Rect dst = {bottom.x + x * 32, bottom.y + y * 32, 32, 32};
            SDL_RenderCopy(renderer, assets.menuBg.ptr, NULL, &dst);
        }
    }

    // Banner.
    {
        SDL_Rect src = {24, 0, 24, 32};
        SDL_Rect dst = {bottom.x, bottom.y + 8, 24, 32};

        SDL_RenderCopy(renderer, assets.banner.ptr, &src, &dst);
        dst.x += 24;
        SDL_RenderCopy(renderer, assets.banner.ptr, &src, &dst);
        
        src.x -= 24;
        for (int x = 0; x < 7; x++) {
            dst.x += 24;
            SDL_RenderCopy(renderer, assets.banner.ptr, &src, &dst);
        }

        src.x += 24;
        dst.x = bottom.x + resolution.x - 2 * 24;
        SDL_RenderCopy(renderer, assets.banner.ptr, &src, &dst);
        dst.x += 24;
        SDL_RenderCopy(renderer, assets.banner.ptr, &src, &dst);
    }
    
    // Level icons.
    for (int i = 0; i < levelCount; i++) {
        SDL_Rect borderSrc = {0, select.selected == i ? 0 : 64, 64, 64};
        SDL_Rect borderDst = {bottom.x + select.levelIcons[i].dst.x - 8, bottom.y + select.levelIcons[i].dst.y - 8, 64, 64};
        SDL_RenderCopy(renderer, assets.borders.ptr, &borderSrc, &borderDst);
        
        SDL_Rect iconSrc = {0, select.levelIcons[i].src.y, 48, 48};
        SDL_Rect iconDst = {borderDst.x + 8, borderDst.y + 8, 48, 48};
        SDL_RenderCopy(renderer, assets.levelIcons.ptr, &iconSrc, &iconDst);
    }

    // Back arrow.
    SDL_Rect dst = {bottom.x + select.backArrowDst.x, bottom.y + select.backArrowDst.y, 30, 30};
    SDL_RenderCopy(renderer, assets.backArrow.ptr, NULL, &dst);
}