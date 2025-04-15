#include "UUID.h"
#include <random>

namespace rm {
    static std::random_device s_RD;
    static std::mt19937_64 s_Engine(s_RD());
    static std::uniform_int_distribution<uint64_t> s_Dist;

    UUID::UUID()
        : m_UUID(s_Dist(s_Engine)) {}
}