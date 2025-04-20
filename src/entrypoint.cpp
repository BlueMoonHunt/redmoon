#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include <iostream>
#include <print>

#include "utils/base.h"
#include "core/application.h"

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
        std::println(std::cerr, "Faild to initialize SDL3: {}", SDL_GetError());

    rm::ApplicationSpecifications specs {
        .width = 900,
        .height = 700,
        .name = "Redmoon",
        .resizable = true,
        .createRMAssetFile = false
    };
    
    rm::Application* app = new rm::Application(specs);

    if (!app) {
        std::println(std::cerr, "Faild to initialize SDL3: {}", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    *appstate = app;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    rm::Application* app = static_cast<rm::Application*>(appstate);
    if (app)
        app->onUpdate();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    rm::Application* app = static_cast<rm::Application*>(appstate);
    
    if (event->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS;

    if (app)
        app->onEvent(event);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    rm::Application* app = static_cast<rm::Application*>(appstate);

    if (app)
        delete app;

    SDL_Quit();
}