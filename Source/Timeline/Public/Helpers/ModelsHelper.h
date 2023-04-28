#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Subsystems/UISubsystem.h"

#include "ModelsHelper.generated.h"

UCLASS()
class TIMELINE_API UModelsHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static FName GetModelName(UClass* ModelClass);

	template<typename TModelClass>
	static TModelClass* GetModel(UObject* WorldContextObject);
};

template <typename TModelClass>
TModelClass* UModelsHelper::GetModel(UObject* WorldContextObject)
{
	if (UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject); IsValid(GameInstance))
	{
		if (UUISubsystem* UISubsystem = GameInstance->GetSubsystem<UUISubsystem>(); IsValid(UISubsystem))
		{
			return UISubsystem->GetModel<TModelClass>();
		}
	}

	return nullptr;
}
