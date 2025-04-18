#include "application.h"
#include "utils/base.h"
#include "utils/sdlUtils.h"
#include "renderer/renderer.h"
#include "assetManager/assetManager.h"

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

        AssetManager::Init();
        
        SDL_Renderer* renderer = nullptr;
        SDL_Validate(SDL_CreateWindowAndRenderer(m_Specs.name, m_Specs.width, m_Specs.height, m_Specs.flags, &m_WindowHandle, &renderer));

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
