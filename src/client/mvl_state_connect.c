#include "mvl_state_connect.h"

#include "mvl_state.h"
#include "mvl_ds.h"
#include "mvl_time.h"

void initConnectState(void* context) {
    ConnectState* connect = context;

    connect->okDst = (SDL_Rect){100, 156, 64, 28};
}

void onConnectOkClickDone(void* context) {
    stateHandlerPop();
    stateHandlerPush(&gSettingsState);
}

void onConnectOkClick(void* context) {
    ConnectState* connect = context;
    connect->okDst.x += 2;
    connect->okDst.y += 2;
    timeout(250, onConnectOkClickDone, NULL);
}

void updateConnectState(void* context, float delta) {
    ConnectState* connect = context;

    registerButton((Button){.area = connect->okDst, .callback = onConnectOkClick, .context = context});
}

void renderConnectState(void* context, float delta, SDL_Renderer* renderer, Assets assets) {
    ConnectState connect = *(ConnectState*)context;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 6; y++) {
            SDL_Rect dst = {gTop.x + x * 32, gTop.y + y * 32, 32, 32};

            Texture bg = y == 0 || y == 5 ? assets.menuDarkBg : assets.menuBg;
            SDL_RenderCopy(renderer, bg.ptr, NULL, &dst);
        }
    }

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 6; y++) {
            SDL_Rect dst = {gBottom.x + x * 32, gBottom.y + y * 32, 32, 32};
            SDL_RenderCopy(renderer, assets.menuBg.ptr, NULL, &dst);
        }
    }

    SDL_Rect textBgDst = {32, 64, 224, 96};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &textBgDst);

    SDL_Surface* textSurface = TTF_RenderText_Blended(assets.font, "Connect To Server", (SDL_Color){200, 200, 200, SDL_ALPHA_OPAQUE});
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textDst = {70, 100, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &textDst);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);

    SDL_Rect buttonDst = {gBottom.x + connect.okDst.x, gBottom.y + connect.okDst.y, 64, 28};
    SDL_RenderCopy(renderer, assets.button.ptr, NULL, &buttonDst);

    SDL_Rect okTextSrc = {96, 0, 32, 16};
    SDL_Rect okTextDst = {buttonDst.x + 16, buttonDst.y + 4, 32, 16};
    SDL_RenderCopy(renderer, assets.text.ptr, &okTextSrc, &okTextDst);
}