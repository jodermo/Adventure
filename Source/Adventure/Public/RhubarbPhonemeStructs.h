#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "RhubarbPhonemeStructs.generated.h"



USTRUCT(BlueprintType)
struct FRhubarbPhonemeCueMetadata
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SoundFile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;
};


USTRUCT(BlueprintType)
struct FRhubarbPhonemeCue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float End;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Value;
};


USTRUCT(BlueprintType)
struct FRhubarbPhonemeData: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRhubarbPhonemeCueMetadata Metadata;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRhubarbPhonemeCue> MouthCues;
};

USTRUCT(BlueprintType)
struct FRhubarbAudio
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (RowType = "RhubarbPhonemeData"))
	FRhubarbPhonemeData RhubarbPhonemeData;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (RequiredAssetDataTags = "RowStructure=/Script/Adventure.RhubarbPhonemeData"))
	FDataTableRowHandle RhubarbPhonemeDataRow;

};


USTRUCT(BlueprintType)
struct FAudioPhoneme
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Phoneme")
	FString Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Phoneme")
	UTexture2D* MouthImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio Phoneme")
	UStaticMeshComponent* MouthMesh;
};