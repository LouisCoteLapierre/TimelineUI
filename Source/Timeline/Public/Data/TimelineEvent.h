#pragma once

#include "CoreMinimal.h"

#include "TimelineEvent.generated.h"

enum class EHistoricPeriod : uint8;

USTRUCT(BlueprintType)
struct TIMELINE_API FTimelineEvent
{
	GENERATED_BODY()

	void SetTitle(const FString& InTitle) { Title = InTitle; }
	const FString& GetTitle() const { return Title;  }

	void SetDescription(const FString& InDescription) { Description = InDescription; }
	const FString& GetDescription() const { return Description; }

	void SetStart(const FString& InStart) { Start = InStart; }
	const FString& GetStart() const { return Start; }

	void SetEnd(const FString& InEnd) { End = InEnd; }
	const FString& GetEnd() const { return End; }

	void SetGeography(const FString& InGeography) { Geography = InGeography; }
	const FString& GetGeography() const { return Geography; }

	void SetType(const FString& InType) { Type = InType; }
	const FString& GetType() const { return Type; }

	void SetWikiLink(const FString& InWikiLink) { WikiLink = InWikiLink; }
	const FString& GetWikiLink() const { return WikiLink; }

	// Json Serialization
	TSharedPtr<FJsonObject> Serialize() const;
	void Deserialize(const TSharedPtr<FJsonValue>& TimelineEventJsonValue);

private:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString Title = "";

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString Description = "";

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString Start = "";

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString End = "";

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString Geography = "";

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString Type = "";

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString WikiLink = "";

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FString> Works;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<FString> RelatedLinks;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EHistoricPeriod Period;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FDateTime LastModified;

	const static FString TitleJsonValueName;
	const static FString DescriptionJsonValueName;
	const static FString StartJsonValueName;
	const static FString EndJsonValueName;
	const static FString GeographyJsonValueName;
	const static FString TypeJsonValueName;
	const static FString WikilinkJsonValueName;
	const static FString WorksJsonValueName;
	const static FString RelatedLinksJsonValueName;
	const static FString PeriodJsonValueName;
	const static FString LastModifiedJsonValueName;
};
