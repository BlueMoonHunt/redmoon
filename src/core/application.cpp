#include "application.h"
#include "utils/base.h"
#include "utils/sdlUtils.h"
#include "renderer/renderer.h"

namespace rm {
    Application* Application::s_Instance = nullptr;

    Application::Application(ApplicationSpecifications& specs)
        : m_Specs(specs) {
        s_Instance = this;
        init();
    }

    Application::~Application() {
        shutdown();
    }

    void Application::init() {

        SDL_Renderer* renderer = nullptr;
        SDL_WindowFlags flags;
        if(m_Specs.resizable)
            flags = SDL_WINDOW_RESIZABLE;
        SDL_Validate(SDL_CreateWindowAndRenderer(m_Specs.name, m_Specs.width, m_Specs.height, flags, &m_WindowHandle, &renderer));

        SDL_HideWindow(m_WindowHandle);

        Renderer::Init(renderer);

        SDL_ShowWindow(m_WindowHandle);
    }

    void Application::onEvent(SDL_Event* event) {
    }

    void Application::onUpdate() {
        Renderer::Present();
    }

    void Application::shutdown() {
        Renderer::Shutdown();
        SDL_DestroyWindow(m_WindowHandle);
    }


} // namespace rm
