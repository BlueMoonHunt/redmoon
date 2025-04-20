#pragma once
#include <memory>

template<typename T>
using ref = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr ref<T> createRef(Args&& ... args) { return std::make_shared<T>(std::forward<Args>(args)...); }

template<typename T>
using scope = std::unique_ptr<T>;

template<typename T, typename ... Args>
constexpr scope<T> createScope(Args&& ... args) { return std::make_unique<T>(std::forward<Args>(args)...); }


namespace rm {

#ifndef Validate
#define Validate(condition, message) { \
        if (!condition) { \
            fprintf(stderr, "Validation Failed!\n"); \
            fprintf(stderr, "  Condition: %s\n", #condition); \
            fprintf(stderr, "  Error: %s\n", message); \
            fprintf(stderr, "  Location: %s:%d\n", __FILE__, __LINE__); \
            abort();\
        }\
    }
#endif // Validate

} // namespace rm
