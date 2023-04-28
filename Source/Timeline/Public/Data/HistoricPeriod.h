#pragma once

#include "CoreMinimal.h"

#include "TimelineEvent.h"

#include "HistoricPeriod.generated.h"

USTRUCT()
struct TIMELINE_API FHistoricPeriod
{
	GENERATED_BODY()

public:

	void AddTimelineEvent(const FString& TimelineEventTitle, FTimelineEvent&& TimelineEvent);

	// Json Serialization
	TSharedPtr<FJsonObject> Serialize();
	void Deserialize(const TSharedPtr<FJsonValue>& HistoricPeriodJsonValue);

private:

	TMap<FString, FTimelineEvent> TimelineEvents;

	const static FString TimelineEventsJsonValueName;
};
