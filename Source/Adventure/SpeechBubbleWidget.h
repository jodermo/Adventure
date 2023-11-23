#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Fonts/SlateFontInfo.h"
#include "Fonts/CompositeFont.h"
#include "Styling/SlateTypes.h"
#include "Engine/Font.h"
#include "SpeechBubbleWidget.generated.h"


/**
 *
 */
UCLASS()
class ADVENTURE_API USpeechBubbleWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "Image"))
    UTexture2D* Image = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "Text"))
    FText Text = FText::GetEmpty();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "FontSize"))
    int32 FontSize = 60;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "Text Color"))
    FLinearColor TextColor = FLinearColor::Black;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game SpeechBubble", meta = (ToolTip = "Text"))
    UFont* Font;

    UFUNCTION(BlueprintCallable, Category = "Game SpeechBubble", meta = (ToolTip = "Set the Text"))
    void UpdateText(FText NewText);

    UFUNCTION(BlueprintCallable, Category = "Game SpeechBubble", meta = (ToolTip = "Update the Font Size"))
    void UpdateFontSize(int32 NewFontSize);

    UFUNCTION(BlueprintCallable, Category = "Game SpeechBubble", meta = (ToolTip = "Update the Text Color"))
    void UpdateTextColor(FLinearColor NewTextColor);

    UFUNCTION(BlueprintCallable, Category = "Game SpeechBubble", meta = (ToolTip = "Update the Text Color"))
    void UpdateFont(UFont* NewFont);

};
