#include "Subsystems/UISubsystem.h"

#include "Helpers/ModelsHelper.h"

#include "Log/LogSetup.h"

#include "Models/BaseModel.h"

void UUISubsystem::RegisterModels(const TArray<TSubclassOf<UBaseModel>>& ModelClasses)
{
	for (TSubclassOf<UBaseModel> ModelClass : ModelClasses)
	{
		if (!IsValid(ModelClass.Get()))
		{
			UE_LOG(LogSetup, Warning, TEXT("UUISubsystem::RegisterModels: ModelClass was nullptr, please check the RegisterModels caller to verify that all ModelClasses are valid."));
			continue;
		}

		const FName& ModelName = UModelsHelper::GetModelName(ModelClass);
		if (Models.Contains(ModelName))
		{
			UE_LOG(LogSetup, Warning, TEXT("UUISubsystem::RegisterModels: ModelClass : %s already registered."), *ModelClass.Get()->GetName());
			continue;
		}

		UBaseModel* NewModel = NewObject<UBaseModel>(this, ModelClass.Get());
		if (!IsValid(NewModel))
		{
			UE_LOG(LogSetup, Warning, TEXT("UUISubsystem::RegisterModels: Was not able to create a Model from Class: %s"), *ModelClass.Get()->GetName());
			continue;
		}

		Models.Add(ModelName, NewModel);
	}
}

void UUISubsystem::UnregisterModels(const TArray<TSubclassOf<UBaseModel>>& ModelClasses)
{
	for (TSubclassOf<UBaseModel> ModelClass : ModelClasses)
	{
		if (!IsValid(ModelClass.Get()))
		{
			UE_LOG(LogSetup, Warning, TEXT("UUISubsystem::UnregisterModels: ModelClass was nullptr, please check the UnregisterModels caller to verify that all ModelClasses are valid."));
			continue;
		}

		const FName& ModelName = UModelsHelper::GetModelName(ModelClass);
		if (!Models.Contains(ModelName))
		{
			UE_LOG(LogSetup, Warning, TEXT("UUISubsystem::UnregisterModels: ModelClass : %s was never registered."), *ModelClass.Get()->GetName());
			continue;
		}

		if (UBaseModel* ModelToUnregister = Models[ModelName]; IsValid(ModelToUnregister))
		{
			ModelToUnregister->ConditionalBeginDestroy();
			ModelToUnregister = nullptr;
		}
		else
		{
			UE_LOG(LogSetup, Warning, TEXT("UUISubsystem::UnregisterModels: There was an entry for ModelName %s but Model was not valid for some reason, issue arose at Model creation."), *ModelClass.Get()->GetName());
		}

		Models.Remove(ModelName);
	}
}
