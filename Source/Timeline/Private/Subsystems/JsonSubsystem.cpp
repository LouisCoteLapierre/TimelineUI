#include "Subsystems/JsonSubsystem.h"

#include "Data/HistoricPeriod.h"

#include "Enums/HistoricPeriodType.h"

#include "Json.h"

#include "Helpers/EnumHelper.h"
#include "Helpers/FileHelper.h"
#include "Helpers/ModelsHelper.h"

#include "Log/LogSetup.h"

#include "Models/TimelineModel.h"

#include "Misc/Paths.h"

// TODO LCLAPIERRE:
// Deserialization from C# Json seems to work
// Serialization from C++ in Unreal seems to work
// After serialization, deserialization doesn't work, doesn't seem to be the same format

void UJsonSubsystem::InitializeJsonData()
{
	UTimelineModel* TimelineModel = UModelsHelper::GetModel<UTimelineModel>(this);
	if (!IsValid(TimelineModel))
	{
		UE_LOG(LogSetup, Warning, TEXT("UJsonSubsystem::InitializeJsonData: Was not able to find a TimelineModel, make sure its registered in the HUD."));
		return;
	}

	// We first have to find the needed files to open
	const FString& ProjectDirectory = FPaths::ProjectConfigDir();
	for (const EHistoricPeriod HistoricPeriodType : TEnumRange<EHistoricPeriod>())
	{
		// We have 1 file per historic period
		const FString FilePath = GetFilePath(ProjectDirectory, HistoricPeriodType);

		// For each file, we need to parse the json string of it to get all the TimelineEvents out of it
		const FString& JsonContent = UFileHelper::ReadFileContent(FilePath);
		if (!JsonContent.IsEmpty())
		{
			TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonContent);

			if (!FJsonSerializer::Deserialize(Reader, JsonObject))
			{
				// The deserialization failed, handle this case
			}
			else
			{
				TMap<FString, TSharedPtr<FJsonValue>> JsonValues = JsonObject->Values;

				FHistoricPeriod HistoricPeriod;
				for (const TPair<FString, TSharedPtr<FJsonValue>>& HistoricPeriodPair : JsonValues)
				{
					HistoricPeriod.Deserialize(HistoricPeriodPair.Value);

					TimelineModel->AddHistoricPeriod(HistoricPeriodType, MoveTemp(HistoricPeriod));
				}
			}
		}
	}
}

void UJsonSubsystem::SaveJsonData()
{
	UTimelineModel* TimelineModel = UModelsHelper::GetModel<UTimelineModel>(this);
	if (!IsValid(TimelineModel))
	{
		UE_LOG(LogSetup, Warning, TEXT("UJsonSubsystem::SaveJsonData: Was not able to find a TimelineModel, make sure its registered in the HUD."));
		return;
	}

	// We first have to find the needed files to open
	const FString& ProjectDirectory = FPaths::ProjectConfigDir();
	for (const EHistoricPeriod HistoricPeriodType : TEnumRange<EHistoricPeriod>())
	{
		// We have 1 file per historic period
		const FString FilePath = GetFilePath(ProjectDirectory, HistoricPeriodType);

		// For each file, we need to get the corresponding HistoricPeriod in our Model and Serialize it in a FString.
		FHistoricPeriod* HistoricPeriod = TimelineModel->FindHistoricPeriod(HistoricPeriodType);
		if (HistoricPeriod == nullptr)
		{
			UE_LOG(LogSetup, Warning, TEXT("UJsonSubsystem::SaveJsonData: HistoricPeriod for Type: %s was not found in the model."), *UEnumHelper::GetEnumName(HistoricPeriodType));
			continue;
		}

		// We serialize the corresponding HistoricPeriod
		TSharedPtr<FJsonObject> HistoricPeriodJsonObject = HistoricPeriod->Serialize();
		if (!HistoricPeriodJsonObject.IsValid())
		{
			UE_LOG(LogSetup, Warning, TEXT("UJsonSubsystem::SaveJsonData: Was not able to generate a valid JsonObject for HistoricPeriod of Type: %s."), *UEnumHelper::GetEnumName(HistoricPeriodType));
			continue;
		}

		// Afterwards, we transform this object into a corresponding json string
		FString JsonContent;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonContent);

		if (!FJsonSerializer::Serialize(HistoricPeriodJsonObject.ToSharedRef(), Writer))
		{
			UE_LOG(LogSetup, Warning, TEXT("UJsonSubsystem::SaveJsonData: Was not able to properly serialize to the JsonWriter for HistoricPeriod of Type: %s."), *UEnumHelper::GetEnumName(HistoricPeriodType));
			continue;
		}

		if (!UFileHelper::SaveToFile(JsonContent, FilePath))
		{
			UE_LOG(LogSetup, Warning, TEXT("UJsonSubsystem::SaveJsonData: HistoricPeriod for Type: %s was not saved properly."), *UEnumHelper::GetEnumName(HistoricPeriodType));
			continue;
		}
	}
}

FString UJsonSubsystem::GetFilePath(const FString& ProjectDirectory, const EHistoricPeriod HistoricPeriodType)
{
	FString EnumName = UEnumHelper::GetEnumName(HistoricPeriodType);
	EnumName.Append(".txt");

	return FPaths::Combine(ProjectDirectory, EnumName);
}
