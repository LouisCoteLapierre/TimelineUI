#include "Models/TimelineModel.h"

#include "Data/HistoricPeriod.h"

#include "Enums/HistoricPeriodType.h"

#include "Helpers/EnumHelper.h"

#include "Log/LogData.h"

void UTimelineModel::AddHistoricPeriod(EHistoricPeriod HistoricPeriodType, FHistoricPeriod&& HistoricPeriod)
{
	if (HistoricPeriods.Contains(HistoricPeriodType))
	{
		UE_LOG(LogData, Log, TEXT("UTimelineModel::AddHistoricPeriod: TimelineModel already contained an HistoricPeriod of type %s, updated it."), *UEnumHelper::GetEnumName(HistoricPeriodType));
		HistoricPeriods[HistoricPeriodType] = MoveTemp(HistoricPeriod);
		return;
	}

	HistoricPeriods.Add(HistoricPeriodType, MoveTemp(HistoricPeriod));
}
