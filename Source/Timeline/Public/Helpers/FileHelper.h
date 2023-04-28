#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "FileHelper.generated.h"

UCLASS()
class TIMELINE_API UFileHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static FString ReadFileContent(const FString& FilePath);

	static bool SaveToFile(const FString& FileContent, const FString& FilePath);
};
