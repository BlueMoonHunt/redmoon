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

    };

    struct Asset
    {
        AssetHandle handle = 0;

    };
    
} // namespace rm
