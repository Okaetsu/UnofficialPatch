#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UFunction.hpp>
#include <SDK/Classes/PalPlayerController.h>
#include <SDK/Classes/PalUtility.h>

using namespace RC;
using namespace RC::Unreal;

namespace Palworld {
    auto UPalUtility::GetDefault() -> UPalUtility*
    {
        if (!Self)
        {
            Self = UObjectGlobals::StaticFindObject<UPalUtility*>(nullptr, nullptr, STR("/Script/Pal.Default__PalUtility"));
        }
        return Self;
    }

    auto UPalUtility::SendSystemToPlayerChat(UObject* WorldContextObject, const FString& Message, const FGuid& PlayerUId) -> void
    {
        static auto Function = UObjectGlobals::StaticFindObject<UFunction*>(nullptr, nullptr, STR("/Script/Pal.PalUtility:SendSystemToPlayerChat"));

        if (!Function) {
            throw std::runtime_error{ "Function /Script/Pal.PalUtility:SendSystemToPlayerChat not found." };
        }

        struct {
            UObject* WorldContextObject;
            FString Message;
            FGuid PlayerUId;
        }params;

        params.WorldContextObject = WorldContextObject;
        params.Message = Message;
        params.PlayerUId = PlayerUId;

        GetDefault()->ProcessEvent(Function, &params);
    }

    auto UPalUtility::GetPlayerControllerByPlayerId(RC::Unreal::UObject* WorldContextObject, int PlayerId) -> APalPlayerController*
    {
        static auto Function = UObjectGlobals::StaticFindObject<UFunction*>(nullptr, nullptr, STR("/Script/Pal.PalUtility:GetPlayerControllerByPlayerId"));

        if (!Function) {
            throw std::runtime_error{ "Function /Script/Pal.PalUtility:GetPlayerControllerByPlayerId not found." };
        }

        struct {
            UObject* WorldContextObject;
            int PlayerId;
            APalPlayerController* ReturnValue;

        }params;

        params.WorldContextObject = WorldContextObject;
        params.PlayerId = PlayerId;

        GetDefault()->ProcessEvent(Function, &params);

        return params.ReturnValue;
    }
}
