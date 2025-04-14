#pragma once
#include "utils/base.h"
#include <SDL3/SDL.h>

namespace rm {

    struct ApplicationSpecifications {
        int width = 0;
        int height = 0;
        const char* name = "TITLE";
        SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE;
    };

    class Application {
    public:
        Application(ApplicationSpecifications& specs);
        ~Application();

        void onEvent(SDL_Event* event);
        void onUpdate();

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;
        SDL_Window* getWindowHandle() { return m_WindowHandle; }
        ApplicationSpecifications& getSpecs() { return m_Specs; }
        inline static Application* Get() { return s_Instance; }
    private:
        void init();
        void shutdown();
    private:
        SDL_Window* m_WindowHandle;
        ApplicationSpecifications m_Specs;
        static Application* s_Instance;
    };
} // namespace rm
