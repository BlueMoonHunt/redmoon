#pragma once
#include "asset.h"
#include "core/application.h"

namespace rm {

    class AssetManager {
    public:
        template<typename T>
        static ref<T> GetAsset(AssetHandle handle) {
            ref<Asset> asset = Application::Get()->getAssetManager()->getAsset(handle);
            return std::static_pointer_cast<T>(asset);
        }
    };
} // namespace rm
