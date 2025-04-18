#include "assetManager.h"
#include <SDL3/SDL.h>

#include "utils/base.h"

namespace rm
{
    struct Assets {
        std::filesystem::path path;
    };

    static Assets s_Data;

    void AssetManager::Init() {
        s_Data.path = SDL_GetBasePath();
        Validate(s_Data.path.c_str(), "Could not retrieve Path");
    }

const std::filesystem::path& AssetManager::GetBasePath() {
        return s_Data.path;
    }

} // namespace rm

