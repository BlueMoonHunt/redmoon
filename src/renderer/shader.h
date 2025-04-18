#pragma once
#include "assetManager/asset.h"
#include <filesystem>
#include <SDL3/SDL.h>


namespace rm {

    class Shader : public Asset {
    public:
        Shader(const std::filesystem::path& shaderFilename, uint32_t samplerCount = 0, uint32_t uniformBufferCount = 0, uint32_t storageBufferCount = 0, uint32_t storageTextureCount = 0);
        ~Shader();

        std::filesystem::path& getPath() { return m_Path; }
        SDL_GPUShader* getHandle();

        static AssetType GetAssetType() { return AssetType::Shader; }
        virtual AssetType getType() override { return GetAssetType(); }
    private:
        std::filesystem::path m_Path;
        SDL_GPUShader* m_handle;
    };

} // namespace rm
