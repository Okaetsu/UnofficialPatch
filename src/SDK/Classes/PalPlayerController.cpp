#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UFunction.hpp>
#include <SDK/Classes/PalPlayerController.h>

using namespace RC;
using namespace RC::Unreal;

namespace Palworld {
    FGuid APalPlayerController::GetPlayerUId()
    {
        static auto Function = UObjectGlobals::StaticFindObject<UFunction*>(nullptr, nullptr, STR("/Script/Pal.PalPlayerController:GetPlayerUId"));

        if (!Function) {
            throw std::runtime_error{ "Function /Script/Pal.PalPlayerController:GetPlayerUId not found." };
        }

        struct {
            FGuid ReturnValue;
        }params;

        this->ProcessEvent(Function, &params);

        return params.ReturnValue;
    }
}