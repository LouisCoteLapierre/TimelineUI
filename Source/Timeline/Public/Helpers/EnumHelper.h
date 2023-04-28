#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "EnumHelper.generated.h"

UCLASS()
class TIMELINE_API UEnumHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	template<typename TEnumClass>
	static FString GetEnumName(TEnumClass EnumValue);

	template<typename TEnumClass>
	static TEnumClass GetEnumFromString(const FString& EnumString);

	template<typename TEnumClass>
	static TEnumClass GetEnumFromIntString(const FString& IntEnumString);
};

template <typename TEnumClass>
FString UEnumHelper::GetEnumName(TEnumClass EnumValue)
{
	FString EnumString;
	StaticEnum<TEnumClass>()->GetValueAsString(EnumValue).Split(TEXT("::"), nullptr, &EnumString);

	return EnumString;
}

template <typename TEnumClass>
TEnumClass UEnumHelper::GetEnumFromString(const FString& EnumString)
{
	return static_cast<TEnumClass>(StaticEnum<TEnumClass>()->GetValueByNameString(EnumString));
}

template<typename TEnumClass>
inline TEnumClass UEnumHelper::GetEnumFromIntString(const FString& IntEnumString)
{
	return static_cast<TEnumClass>(FCString::Atoi(*IntEnumString));
}
