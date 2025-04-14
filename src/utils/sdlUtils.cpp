#include "sdlUtils.h"

SDL_GPUShader* rm::SDL_LoadShader(SDL_GPUDevice* device, const std::filesystem::path& shaderFilename, Uint32 samplerCount, Uint32 uniformBufferCount, Uint32 storageBufferCount, Uint32 storageTextureCount) {
    SDL_GPUShaderStage stage;
    if (shaderFilename.extension() == ".vert")
        stage = SDL_GPU_SHADERSTAGE_VERTEX;
    else if (shaderFilename.extension() == ".frag")
        stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
    else {
        SDL_Log("Invalid shader stage!");
        return nullptr;
    }

    SDL_GPUShaderFormat backendFormats = SDL_GetGPUShaderFormats(device);
    SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_INVALID;
    const char* entrypoint;

    static const std::filesystem::path s_BasePath = SDL_GetBasePath();
    std::filesystem::path fullPath = s_BasePath / "res/Shaders/Compiled";

    if (backendFormats & SDL_GPU_SHADERFORMAT_SPIRV) {
        fullPath /= "SPIRV" / shaderFilename;
        fullPath.concat(".spv");
        format = SDL_GPU_SHADERFORMAT_SPIRV;
        entrypoint = "main";
    }
    else if (backendFormats & SDL_GPU_SHADERFORMAT_MSL) {
        fullPath /= "MSL" / shaderFilename;
        fullPath.concat(".msl");
        format = SDL_GPU_SHADERFORMAT_MSL;
        entrypoint = "main0";
    }
    else if (backendFormats & SDL_GPU_SHADERFORMAT_DXIL) {
        fullPath /= "DXIL" / shaderFilename;
        fullPath.concat(".dxil");
        format = SDL_GPU_SHADERFORMAT_DXIL;
        entrypoint = "main";
    }
    else {
        SDL_Log("%s", "Unrecognized backend shader format!");
        return nullptr;
    }

    size_t codeSize;
    void* code = SDL_LoadFile(fullPath.c_str(), &codeSize);
    if (code == nullptr) {
        SDL_Log("Failed to load shader from disk! %s", fullPath.c_str());
        return nullptr;
    }

    SDL_GPUShaderCreateInfo shaderInfo = {};
    shaderInfo.code = static_cast<const Uint8*>(code);
    shaderInfo.code_size = codeSize;
    shaderInfo.entrypoint = entrypoint;
    shaderInfo.format = format;
    shaderInfo.stage = stage;
    shaderInfo.num_samplers = samplerCount;
    shaderInfo.num_uniform_buffers = uniformBufferCount;
    shaderInfo.num_storage_buffers = storageBufferCount;
    shaderInfo.num_storage_textures = storageTextureCount;

    SDL_GPUShader* shader = SDL_CreateGPUShader(device, &shaderInfo);
    if (shader == nullptr) {
        SDL_Log("Failed to create shader!");
        SDL_free(code);
        return nullptr;
    }

    SDL_free(code);
    return shader;
}