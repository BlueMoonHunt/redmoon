#pragma once
#include "assetManager/asset.h"

namespace rm {
    class Texture : public Asset {
    public:
        Texture();
        ~Texture();
    private:
        static AssetType GetAssetType() { return AssetType::Texture; }
        virtual AssetType getType() override { return GetAssetType(); }
    };

} // namespace rm
