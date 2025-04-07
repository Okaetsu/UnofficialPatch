#pragma once

#include <Unreal/AActor.hpp>

namespace Palworld {
    class APalPlayerController : public RC::Unreal::AActor {
    public:
        RC::Unreal::FGuid GetPlayerUId();
    };
}