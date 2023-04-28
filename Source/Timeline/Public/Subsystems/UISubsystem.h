#pragma once

#include "CoreMinimal.h"

#include "Subsystems/GameInstanceSubsystem.h"

#include "UISubsystem.generated.h"

class UBaseModel;

UCLASS()
class TIMELINE_API UUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	void RegisterModels(const TArray<TSubclassOf<UBaseModel>>& ModelClasses);
	void UnregisterModels(const TArray<TSubclassOf<UBaseModel>>& ModelClasses);
	
	template<typename TModelClass>
	TModelClass* GetModel();

private:

	UPROPERTY(Transient)
	TMap<FName, TObjectPtr<UBaseModel>> Models;
};

template<typename TModelClass>
TModelClass* UUISubsystem::GetModel()
{
	FName ModelName = UModelsHelper::GetModelName(TModelClass::StaticClass());
	if (ModelName == NAME_None)
	{
		return nullptr;
	}

	if (Models.Contains(ModelName))
	{
		return Cast<TModelClass>(Models[ModelName]);
	}

	return nullptr;
}
