#pragma once

#include "CoreMinimal.h"

#include "HistoricPeriodType.generated.h"

UENUM()
enum class EHistoricPeriod : uint8
{
    None,
    Prehistoric,
    Antiquity,
    MiddleAges,
    Renaissance,
    Modern,
    Contemporary,
};
ENUM_RANGE_BY_FIRST_AND_LAST(EHistoricPeriod, EHistoricPeriod::None, EHistoricPeriod::Contemporary);