#pragma once
#include "asset.h"

namespace rm {
    class AssetManagerBase {
    public:
        virtual ref<Asset> getAsset(AssetHandle handle) const = 0;
        virtual bool isAssetHandleValid(AssetHandle handle) const = 0;
    };
}