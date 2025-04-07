#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <ios>
#include <format>
#include <cstdint>
#include <Unreal/UnrealCoreStructs.hpp>

namespace std
{
    template <>
    struct hash<RC::Unreal::FGuid>
    {
        std::size_t operator()(const RC::Unreal::FGuid &Guid) const noexcept
        {
            std::size_t h1 = std::hash<uint32_t>()(Guid.A);
            std::size_t h2 = std::hash<uint32_t>()(Guid.B);
            std::size_t h3 = std::hash<uint32_t>()(Guid.C);
            std::size_t h4 = std::hash<uint32_t>()(Guid.D);
            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
        }
    };
}