#pragma once
#include "utils/base.h"
#include "core/UUID.h"


namespace rm
{
    using AssetHandle = UUID;

    enum class AssetType {
        None = 0,
        Scene,
        Texture,
        Shader

    };

    class Asset
    {
        AssetHandle handle;
        virtual AssetType getType() = 0;
    };
    
} // namespace rm
