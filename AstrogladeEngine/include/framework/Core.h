#pragma once
#include <iostream>
#include <memory>
#include <map>
#include <unordered_map>

namespace ly
{
    template<typename T>
    using unique = std::unique_ptr<T>;

    template<typename T>
    using shared = std::shared_ptr<T>;

    template<typename T>
    using weak = std::weak_ptr<T>;

    template<typename T>
    using list = std::vector<T>;

    template<typename keyType, typename valType, typename Pr = std::less<keyType>>
    using map = std::map<keyType,valType,Pr>;

    template<typename keyType, typename valType, typename hasher = std::hash<keyType>>
    using dictionary = std::unordered_map<keyType,valType,hasher>;
    
    // Macro
    #define LOG(M, ...) std::cout << M; log_helper(__VA_ARGS__);

    inline void log_helper() {
        std::cout << '\n';
    }

    template<typename T, typename... Args>
    void log_helper(T value, Args... args) {
        std::cout << value << " ";
        log_helper(args...);
    }

}