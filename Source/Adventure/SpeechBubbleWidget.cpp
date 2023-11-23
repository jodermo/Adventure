#include "SpeechBubbleWidget.h"


void USpeechBubbleWidget::UpdateText(FText NewText)
{
	Text = NewText;
}

void USpeechBubbleWidget::UpdateFontSize(int32 NewFontSize)
{
	FontSize = NewFontSize;
}

void USpeechBubbleWidget::UpdateTextColor(FLinearColor NewTextColor)
{
	TextColor = NewTextColor;
}

void USpeechBubbleWidget::UpdateFont(UFont* NewFont)
{
	Font = NewFont;
}

