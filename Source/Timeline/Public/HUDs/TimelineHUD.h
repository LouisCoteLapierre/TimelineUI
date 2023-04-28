#pragma once

#include "CoreMinimal.h"

#include "GameFramework/HUD.h"

#include "Models/BaseModel.h"

#include "TimelineHUD.generated.h"

class UGameInstance;
class UUISubsystem;

UCLASS()
class ATimelineHUD : public AHUD
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UBaseModel>> ModelClasses;

	UPROPERTY(Transient)
	TObjectPtr<UGameInstance> GameInstance = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UUISubsystem> UISubsystem = nullptr;
};
