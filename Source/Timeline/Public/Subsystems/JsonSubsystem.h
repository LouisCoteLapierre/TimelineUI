#pragma once

#include "CoreMinimal.h"

#include "Subsystems/GameInstanceSubsystem.h"

#include "JsonSubsystem.generated.h"

enum class EHistoricPeriod : uint8;

UCLASS()
class TIMELINE_API UJsonSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	void InitializeJsonData();
	void SaveJsonData();

private:

	FString GetFilePath(const FString& ProjectDirectory, const EHistoricPeriod HistoricPeriodType);
};
