#pragma once

#include "CoreMinimal.h"

#include "BaseModel.h"

#include "Data/HistoricPeriod.h"

#include "TimelineModel.generated.h"

enum class EHistoricPeriod:uint8;

UCLASS()
class TIMELINE_API UTimelineModel : public UBaseModel
{
	GENERATED_BODY()

public:

	void AddHistoricPeriod(EHistoricPeriod HistoricPeriodType, FHistoricPeriod&& HistoricPeriod);

	FHistoricPeriod* FindHistoricPeriod(const EHistoricPeriod HistoricPeriodType) { return HistoricPeriods.Find(HistoricPeriodType); }
	const FHistoricPeriod* FindHistoricPeriod(const EHistoricPeriod HistoricPeriodType) const { return HistoricPeriods.Find(HistoricPeriodType); }

private:

	TMap<EHistoricPeriod, FHistoricPeriod> HistoricPeriods;
};
