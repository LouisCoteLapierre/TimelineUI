#include "Helpers/JsonHelper.h"

void UJsonHelper::SerializeJsonStringArray(TSharedPtr<FJsonObject>& JsonObjectToAddTo, const FString& JsonValueName, const TArray<FString>& StringArray)
{
	TArray<TSharedPtr<FJsonValue>> JsonValueArray;
	JsonValueArray.Reserve(StringArray.Num());

	for (const FString& StringToAdd : StringArray)
	{
		JsonValueArray.Add(MakeShareable(new FJsonValueString(StringToAdd)));
	}
	JsonObjectToAddTo->SetArrayField(JsonValueName, JsonValueArray);
}
