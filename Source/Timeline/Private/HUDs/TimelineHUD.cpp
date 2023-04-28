#include "HUDs/TimelineHud.h"

#include "Engine/GameInstance.h"

#include "Log/LogSetup.h"

#include "Subsystems/JsonSubsystem.h"
#include "Subsystems/UISubsystem.h"

void ATimelineHUD::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = GetGameInstance();
	if (!IsValid(GameInstance))
	{
		UE_LOG(LogSetup, Warning, TEXT("ATimelineHUD::BeginPlay(): GameInstance not valid, can't setup the HUD."));
		return;
	}

	UISubsystem = GameInstance->GetSubsystem<UUISubsystem>();
	if (!IsValid(UISubsystem))
	{
		UE_LOG(LogSetup, Warning, TEXT("ATimelineHUD::BeginPlay(): UISubsystem not valid, can't setup the HUD."));
		return;
	}

	// Register models
	UISubsystem->RegisterModels(ModelClasses);

	// Tell the JsonSubsystem it can do its thing
	if (UJsonSubsystem* JsonSubsystem = GameInstance->GetSubsystem<UJsonSubsystem>(); IsValid(JsonSubsystem))
	{
		JsonSubsystem->InitializeJsonData();
	}
	else
	{
		UE_LOG(LogSetup, Warning, TEXT("ATimelineHUD::BeginPlay(): JsonSubsystem not valid, can't properly initialize json data."));
	}
}

void ATimelineHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Tell the JsonSubsystem it can do its thing, the Subsystem needs Models, so Unregister them afterwards only
	if (UJsonSubsystem* JsonSubsystem = GameInstance->GetSubsystem<UJsonSubsystem>(); IsValid(JsonSubsystem))
	{
		JsonSubsystem->SaveJsonData();
	}
	else
	{
		UE_LOG(LogSetup, Warning, TEXT("ATimelineHUD::EndPlay(): JsonSubsystem not valid, can't properly save json data."));
	}

	// Unregister models
	UISubsystem->UnregisterModels(ModelClasses);

	GameInstance = nullptr;
	UISubsystem = nullptr;

	Super::EndPlay(EndPlayReason);
}
