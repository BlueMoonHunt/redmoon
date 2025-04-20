#pragma once
#include "utils/base.h"
#include <SDL3/SDL.h>
#include "assetManager/editorAssetManager.h"
#include "assetManager/runtimeAssetManager.h"

namespace rm {

    struct ApplicationSpecifications {
        int width = 0;
        int height = 0;
        const char* name = "TITLE";
        bool resizable = true;
        bool createRMAssetFile = false;
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

        ref<AssetManagerBase> getAssetManager() { return m_AssetManager; }
        ref<RuntimeAssetManager> getRuntimeAssetManager() { return std::static_pointer_cast<RuntimeAssetManager>(m_AssetManager); }
        ref<EditorAssetManager> getEditorAssetManager() { return std::static_pointer_cast<EditorAssetManager>(m_AssetManager); }

    private:
        void init();
        void shutdown();
    private:
        SDL_Window* m_WindowHandle;
        ApplicationSpecifications m_Specs;
        static Application* s_Instance;

        ref<AssetManagerBase> m_AssetManager;
    };
} // namespace rm
