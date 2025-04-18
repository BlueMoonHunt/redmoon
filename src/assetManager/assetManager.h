#pragma once
#include "asset.h"
#include <unordered_map>
#include <filesystem>
namespace rm {
    class AssetManager {
    public:
        static void Init();
        static void Load();
        static void LoadAsset();
        static const std::filesystem::path& GetBasePath();
        static void Reset();
        static void Save();
    };
} // namespace rm
