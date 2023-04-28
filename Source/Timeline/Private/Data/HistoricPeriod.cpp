#include "Data/HistoricPeriod.h"

#include "Log/LogData.h"

#include "Json.h"

const FString FHistoricPeriod::TimelineEventsJsonValueName = "TimelineEvents";

void FHistoricPeriod::AddTimelineEvent(const FString& TimelineEventTitle, FTimelineEvent&& TimelineEvent)
{
	if (TimelineEvents.Contains(TimelineEventTitle))
	{
		TimelineEvents[TimelineEventTitle] = MoveTemp(TimelineEvent);
		UE_LOG(LogData, Log, TEXT("FHistoricPeriod::AddTimelineEvent: TimelineEvent with Title %s was already there, updating it."), *TimelineEventTitle);
		return;
	}

	TimelineEvents.Add(TimelineEventTitle, MoveTemp(TimelineEvent));
}

TSharedPtr<FJsonObject> FHistoricPeriod::Serialize()
{
	TSharedPtr<FJsonObject> HistoricPeriodJsonObject = MakeShareable(new FJsonObject);
	if (!HistoricPeriodJsonObject.IsValid())
	{
		UE_LOG(LogData, Error, TEXT("FHistoricPeriod::Serialize: Could not properly MakeShareable a new FJsonObject."));
		return nullptr;
	}

	TSharedPtr<FJsonObject> TimelineEventsJsonObject = MakeShareable(new FJsonObject);
	if (!TimelineEventsJsonObject.IsValid())
	{
		UE_LOG(LogData, Error, TEXT("FHistoricPeriod::Serialize: Could not properly MakeShareable a new FJsonObject."));
		return nullptr;
	}

	// Cannot use a JsonValueArray here because the original json export was done in another software 
	// and the serialization from a map created a number of values instead of putting them all in an array
	for (const TPair<FString, FTimelineEvent>& TimelineEventPair : TimelineEvents)
	{
		const FTimelineEvent& TimelineEvent = TimelineEventPair.Value;
		TimelineEventsJsonObject->SetObjectField(TimelineEvent.GetTitle(), TimelineEvent.Serialize());
	}
	
	HistoricPeriodJsonObject->SetObjectField(TimelineEventsJsonValueName, TimelineEventsJsonObject);

	return HistoricPeriodJsonObject;
}

void FHistoricPeriod::Deserialize(const TSharedPtr<FJsonValue>& HistoricPeriodJsonValue)
{
	TSharedPtr<FJsonObject> HistoricPeriodJsonObject = HistoricPeriodJsonValue->AsObject();
	for (const TPair<FString, TSharedPtr<FJsonValue>>& TimelineEventPair : HistoricPeriodJsonObject->Values)
	{
		FTimelineEvent TimelineEvent;
		TimelineEvent.Deserialize(TimelineEventPair.Value);

		AddTimelineEvent(TimelineEvent.GetTitle(), MoveTemp(TimelineEvent));
	}
}
