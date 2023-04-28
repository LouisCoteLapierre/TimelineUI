#include "Data/TimelineEvent.h"

#include "Enums/HistoricPeriodType.h"

#include "Helpers/EnumHelper.h"
#include "Helpers/JsonHelper.h"

#include "Log/LogData.h"

#include "Misc/DateTime.h"

const FString FTimelineEvent::TitleJsonValueName = "Title";
const FString FTimelineEvent::DescriptionJsonValueName = "Description";
const FString FTimelineEvent::StartJsonValueName = "Start";
const FString FTimelineEvent::EndJsonValueName = "End";
const FString FTimelineEvent::GeographyJsonValueName = "Geography";
const FString FTimelineEvent::TypeJsonValueName = "Type";
const FString FTimelineEvent::WikilinkJsonValueName = "WikiLink";
const FString FTimelineEvent::WorksJsonValueName = "Works";
const FString FTimelineEvent::RelatedLinksJsonValueName = "RelatedLinks";
const FString FTimelineEvent::PeriodJsonValueName = "Period";
const FString FTimelineEvent::LastModifiedJsonValueName = "LastModified";

TSharedPtr<FJsonObject> FTimelineEvent::Serialize() const
{
	TSharedPtr<FJsonObject> TimelineEventJsonObject = MakeShareable(new FJsonObject);
	if (!TimelineEventJsonObject.IsValid())
	{
		UE_LOG(LogData, Error, TEXT("FTimelineEvent::Serialize: Could not properly MakeShareable a new FJsonObject."));
		return nullptr;
	}

	TimelineEventJsonObject->SetStringField(TitleJsonValueName, GetTitle());
	TimelineEventJsonObject->SetStringField(DescriptionJsonValueName, GetDescription());
	TimelineEventJsonObject->SetStringField(StartJsonValueName, GetStart());
	TimelineEventJsonObject->SetStringField(EndJsonValueName, GetEnd());
	TimelineEventJsonObject->SetStringField(GeographyJsonValueName, GetGeography());
	TimelineEventJsonObject->SetStringField(TypeJsonValueName, GetType());
	TimelineEventJsonObject->SetStringField(WikilinkJsonValueName, GetWikiLink());

	UJsonHelper::SerializeJsonStringArray(TimelineEventJsonObject, WorksJsonValueName, Works);
	UJsonHelper::SerializeJsonStringArray(TimelineEventJsonObject, RelatedLinksJsonValueName, RelatedLinks);

	TimelineEventJsonObject->SetStringField(PeriodJsonValueName, UEnumHelper::GetEnumName(Period));
	TimelineEventJsonObject->SetStringField(LastModifiedJsonValueName, LastModified.ToIso8601());

	return TimelineEventJsonObject;
}

void FTimelineEvent::Deserialize(const TSharedPtr<FJsonValue>& TimelineEventJsonValue)
{
	TSharedPtr<FJsonObject> TimelineEventJsonObject = TimelineEventJsonValue->AsObject();
	if (!TimelineEventJsonObject.IsValid())
	{
		UE_LOG(LogData, Error, TEXT("FTimelineEvent::Deserialize: Trying to deserialize a TimelineEvent which is not a JsonObject, should never happen."));
		return;
	}

	if (!TimelineEventJsonObject->TryGetStringField(TitleJsonValueName, Title))
	{
		UE_LOG(LogData, Error, TEXT("FTimelineEvent::Deserialize: Could not find a Title property on the TimelineEvent, should never happen."));
	}

	if (!TimelineEventJsonObject->TryGetStringField(DescriptionJsonValueName, Description))
	{
		UE_LOG(LogData, Error, TEXT("FTimelineEvent::Deserialize: Could not find a Description property on the TimelineEvent, should never happen."));
	}

	if (!TimelineEventJsonObject->TryGetStringField(StartJsonValueName, Start))
	{
		UE_LOG(LogData, Error, TEXT("FTimelineEvent::Deserialize: Could not find a Start property on the TimelineEvent, should never happen."));
	}

	if (!TimelineEventJsonObject->TryGetStringField(EndJsonValueName, End))
	{
		UE_LOG(LogData, Error, TEXT("FTimelineEvent::Deserialize: Could not find a End property on the TimelineEvent, should never happen."));
	}

	if (!TimelineEventJsonObject->TryGetStringField(GeographyJsonValueName, Geography))
	{
		UE_LOG(LogData, Error, TEXT("FTimelineEvent::Deserialize: Could not find a Geography property on the TimelineEvent, should never happen."));
	}

	if (!TimelineEventJsonObject->TryGetStringField(TypeJsonValueName, Type))
	{
		UE_LOG(LogData, Error, TEXT("FTimelineEvent::Deserialize: Could not find a Type property on the TimelineEvent, should never happen."));
	}

	if (!TimelineEventJsonObject->TryGetStringField(WikilinkJsonValueName, WikiLink))
	{
		UE_LOG(LogData, Error, TEXT("FTimelineEvent::Deserialize: Could not find a WikiLink property on the TimelineEvent, should never happen."));
	}

	if (!TimelineEventJsonObject->TryGetStringArrayField(WorksJsonValueName, Works))
	{
		UE_LOG(LogData, Error, TEXT("FTimelineEvent::Deserialize: Could not find a Works property on the TimelineEvent, should never happen."));
	}

	if (!TimelineEventJsonObject->TryGetStringArrayField(RelatedLinksJsonValueName, RelatedLinks))
	{
		UE_LOG(LogData, Error, TEXT("FTimelineEvent::Deserialize: Could not find a RelatedLinks property on the TimelineEvent, should never happen."));
	}

	FString HistoricPeriodTypeString;
	if (TimelineEventJsonObject->TryGetStringField(PeriodJsonValueName, HistoricPeriodTypeString))
	{
		Period = UEnumHelper::GetEnumFromIntString<EHistoricPeriod>(HistoricPeriodTypeString);
	}
	else 
	{
		UE_LOG(LogData, Error, TEXT("FTimelineEvent::Deserialize: Could not find a Period property on the TimelineEvent, should never happen."));
	}

	FString LastModifiedString;
	if (TimelineEventJsonObject->TryGetStringField(LastModifiedJsonValueName, LastModifiedString))
	{
		if (!FDateTime::ParseIso8601(*LastModifiedString, LastModified))
		{
			UE_LOG(LogData, Error, TEXT("FTimelineEvent::Deserialize: Not able to parse a FDateTime from received string: %s."), *LastModifiedString);
		}
	}
	else
	{
		UE_LOG(LogData, Error, TEXT("FTimelineEvent::Deserialize: Could not find a LastModified property on the TimelineEvent, should never happen."));
	}
}
