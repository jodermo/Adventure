#pragma once

#include "CoreMinimal.h"
#include "Logging.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ADVENTURE_API ULogging : public UObject
{
	GENERATED_BODY()

public:
	ULogging();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logging", meta = (ToolTip = "Unique key for identifying the log."))
	int32 LogKey = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logging", meta = (ToolTip = "Color of the log message for visual distinction."))
	FColor LogColor = FColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Logging", meta = (ToolTip = "Time duration the log message will be displayed for."))
	float LogTime = 15.0f;

	UFUNCTION(BlueprintCallable, Category = "Logging")
	void Log(const FString& LogMessage);
};
