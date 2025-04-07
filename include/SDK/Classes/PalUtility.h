#pragma once

#include <Unreal/UObject.hpp>

namespace RC::Unreal {
    class UScriptStruct;
}

namespace Palworld {
    class APalPlayerController;

    class UPalUtility : public RC::Unreal::UObject {
    public:
        static auto GetDefault() -> UPalUtility*;

        static auto SendSystemToPlayerChat(RC::Unreal::UObject* WorldContextObject, const RC::Unreal::FString& Message, const RC::Unreal::FGuid& PlayerUId) -> void;

        static auto GetPlayerControllerByPlayerId(RC::Unreal::UObject* WorldContextObject, int PlayerId) -> APalPlayerController*;
    private:
        static inline UPalUtility* Self = nullptr;
    };
}
