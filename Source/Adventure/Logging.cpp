#include "Logging.h"

ULogging::ULogging()
{
}

void ULogging::Log(const FString& LogMessage) {
	GEngine->AddOnScreenDebugMessage(LogKey, LogTime, LogColor, LogMessage);
}