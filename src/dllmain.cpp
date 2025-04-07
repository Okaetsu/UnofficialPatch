#include <Mod/CppUserModBase.hpp>
#include <UE4SSProgram.hpp>
#include <Unreal/UFunction.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/Property/NumericPropertyTypes.hpp>
#include <SDK/Classes/PalUtility.h>
#include <SDK/Classes/PalPlayerController.h>
#include <SDK/Structs/Guid.h>

using namespace RC;
using namespace RC::Unreal;
using namespace Palworld;

const auto NOTIFICATION_COOLDOWN = std::chrono::seconds(60);

class UnofficialPatch : public RC::CppUserModBase
{
public:
    UnofficialPatch() : CppUserModBase()
    {
        ModName = STR("UnofficialPatch");
        ModVersion = STR("1.0.0");
        ModDescription = STR("Fixes & Prevention measures for certain bugs/exploits.");
        ModAuthors = STR("Okaetsu");

        Output::send<LogLevel::Verbose>(STR("{} v{} by {} loaded.\n"), ModName, ModVersion, ModAuthors);
    }

    ~UnofficialPatch() override
    {
    }

    auto can_send_message(const RC::Unreal::FGuid& PlayerUId) -> bool
    {
        auto now = std::chrono::steady_clock::now();

        auto it = m_playerMessageCooldownMap.find(PlayerUId);
        if (it == m_playerMessageCooldownMap.end()) {
            m_playerMessageCooldownMap[PlayerUId] = now;
            return true;
        }

        auto durationSinceLast = now - it->second;
        if (durationSinceLast >= NOTIFICATION_COOLDOWN) {
            it->second = now;
            return true;
        }

        return false;
    }

    auto on_update() -> void override
    {
    }

    auto on_unreal_init() -> void override
    {
        Output::send<LogLevel::Verbose>(STR("[{}] loaded successfully!\n"), ModName);

        UObjectGlobals::RegisterHook(STR("/Script/Pal.PalMapObjectPalBoothModel:RequestRemoveTradeInfo_ServerInternal"),
        [&](UnrealScriptFunctionCallableContext& Context, void* CustomData) {
            auto FunctionData = Context.TheStack.Node();
            auto Property = FunctionData->GetPropertyByName(STR("RequestPlayerId"));
            if (auto RequestPlayerIdProperty = CastField<FNumericProperty>(Property))
            {
                auto OriginalPlayerId = RequestPlayerIdProperty->GetSignedIntPropertyValue(Context.TheStack.Locals());
                int64 NewValue = -1;
                RequestPlayerIdProperty->SetIntPropertyValue(Context.TheStack.Locals(), NewValue);

                if (!Context.Context) return;

                auto PlayerController = UPalUtility::GetPlayerControllerByPlayerId(Context.Context, OriginalPlayerId);
                if (PlayerController)
                {
                    auto PlayerUId = PlayerController->GetPlayerUId();
                    if (can_send_message(PlayerUId))
                    {
                        UPalUtility::SendSystemToPlayerChat(Context.Context,
                            FString(STR("Removing Pals from Stalls currently cause crashes, please dismantle the Stall instead until this is officially fixed.")),
                            PlayerUId);
                    }
                }
            }
        },
        [&](UnrealScriptFunctionCallableContext& Context, void* CustomData) {
        }, nullptr);
    }
private:
    std::unordered_map<RC::Unreal::FGuid, std::chrono::time_point<std::chrono::steady_clock>> m_playerMessageCooldownMap;
};


#define UNOFFICIALPATCH_API __declspec(dllexport)
extern "C"
{
    UNOFFICIALPATCH_API RC::CppUserModBase* start_mod()
    {
        return new UnofficialPatch();
    }

    UNOFFICIALPATCH_API void uninstall_mod(RC::CppUserModBase* mod)
    {
        delete mod;
    }
}
