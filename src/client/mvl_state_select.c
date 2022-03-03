#include "mvl_state_select.h"

#include "mvl_state.h"
#include "mvl_ds.h"
#include "mvl_time.h"

void initSelectState(void* context) {
    SelectState* select = context;

    select->backArrowDst = (SDL_Rect){224, 160, 30, 30};
    select->selected = 0;
    select->levelIcons[0] = (LevelIcon){(SDL_Rect){0, 0, 48, 48}, (SDL_Rect){32, 56, 48, 48}};
    select->levelIcons[1] = (LevelIcon){(SDL_Rect){0, 48, 48, 48}, (SDL_Rect){104, 56, 48, 48}};
    select->levelIcons[2] = (LevelIcon){(SDL_Rect){0, 96, 48, 48}, (SDL_Rect){176, 56, 48, 48}};
    select->levelIcons[3] = (LevelIcon){(SDL_Rect){0, 144, 48, 48}, (SDL_Rect){66, 124, 48, 48}};
    select->levelIcons[4] = (LevelIcon){(SDL_Rect){0, 192, 48, 48}, (SDL_Rect){140, 124, 48, 48}};
}

void onLevelIconClick(void* context) {
    stateHandlerPop();
    stateHandlerPush(&game);
}

void onSelectBackArrowClickDone(void* context) {
    stateHandlerPop();
    stateHandlerPush(&settings);
}

void onSelectBackArrowClick(void* context) {
    SelectState* select = context;
    select->backArrowDst.x += 2;
    select->backArrowDst.y += 2;
    timeout(250, onSelectBackArrowClickDone, NULL);
}

void updateSelectState(void* context, float delta) {
    SelectState* select = context;

    if (keyPressed(SDL_SCANCODE_RIGHT)) {
        select->selected = select->selected == 4 ? 0 : select->selected + 1;
    }
    if (keyPressed(SDL_SCANCODE_LEFT)) {
        select->selected = select->selected == 0 ? 4 : select->selected - 1;
    }

    for (int i = 0; i < levelCount; i++) {
        registerButton((Button){.area = select->levelIcons[i].dst, .callback = onLevelIconClick, .context = context});
    }

    registerButton((Button){.area = select->backArrowDst, .callback = onSelectBackArrowClick, .context = context});
}

void renderSelectState(void* context, float delta, SDL_Renderer* renderer, Assets assets) {
    SelectState select = *(SelectState*)context;
    
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