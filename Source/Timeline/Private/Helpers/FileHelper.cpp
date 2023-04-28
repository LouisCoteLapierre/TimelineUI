#include "Helpers/FileHelper.h"

#include "Log/LogHelpers.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

FString UFileHelper::ReadFileContent(const FString& FilePath)
{
	const bool bFileExists = FPaths::FileExists(FilePath);
	if (!bFileExists)
	{
		// Create empty file
		FFileHelper::SaveStringToFile(TEXT(""), *FilePath);

		return "";
	}

	FString FileContent;
	if (FFileHelper::LoadFileToString(FileContent, *FilePath))
	{
		return FileContent;
	}
	else
	{
		UE_LOG(LogHelpers, Warning, TEXT("UFileHelper::ReadFileContent: Error happened trying to read from file: %s"), *FilePath);
	}

	return "";
}

bool UFileHelper::SaveToFile(const FString& FileContent, const FString& FilePath)
{
	const bool bFileExists = FPaths::FileExists(FilePath);
	if (!bFileExists)
	{
		// Create empty file
		FFileHelper::SaveStringToFile(TEXT(""), *FilePath);
	}
	else
	{
		FString CurrentFileContent;
		FFileHelper::LoadFileToString(CurrentFileContent, *FilePath);

		// Don't write file if its content hasn't changed
		if (CurrentFileContent == FileContent)
		{
			return false;
		}
	}

	return FFileHelper::SaveStringToFile(FileContent, *FilePath);
}
