#pragma once
#include "asset.h"
#include <filesystem>

namespace rm {
    struct AssetMetadata {
        AssetType type = AssetType::None;
        std::filesystem::path path;
    };
} // namespace rm
