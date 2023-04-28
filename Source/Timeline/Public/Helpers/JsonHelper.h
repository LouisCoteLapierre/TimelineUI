#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "JsonHelper.generated.h"

UCLASS()
class TIMELINE_API UJsonHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static void SerializeJsonStringArray(TSharedPtr<FJsonObject>& JsonObjectToAddTo, const FString& JsonValueName, const TArray<FString>& StringArray);
};