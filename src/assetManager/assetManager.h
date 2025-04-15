#pragma once
#include "asset.h"

namespace rm {
    class AssetManager {
    public:
        ref<Asset> getAssets();
    private:
        ref<Asset> m_Assets;
    };
} // namespace rm
