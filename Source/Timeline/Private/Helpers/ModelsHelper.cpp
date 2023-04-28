#include "Helpers/ModelsHelper.h"

FName UModelsHelper::GetModelName(UClass* ModelClass)
{
	if (!IsValid(ModelClass))
	{
		return NAME_None;
	}

	FString ModelName = ModelClass->GetName();
	if (ModelClass->HasAllClassFlags(EClassFlags::CLASS_CompiledFromBlueprint))
	{
		ModelName.RemoveFromStart("BP_");
		ModelName.RemoveFromEnd("_UI");
	}

	return FName(ModelName);
}
