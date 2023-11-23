

#include "AnswerActor.h"
#include "AdventureCharacter.h"

AAnswerActor::AAnswerActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAnswerActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAnswerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAnswerActor::TriggerAnswer(AAdventureCharacter* QuestionCharacter, AAdventureCharacter* AnswerCharacter)
{
	if (ParentInteractionActor && ParentInteractionActor->SelectedAnswer)
	{
		return;
	}
	else if(ParentInteractionActor)
	{
		ParentInteractionActor->SelectedAnswer = this;
	}
	Character = QuestionCharacter ? QuestionCharacter : AnswerCharacter;
	TargetCharacter = AnswerCharacter ? AnswerCharacter : QuestionCharacter;
	if (Character) 
	{
		Character->TriggerInteractionActor(TargetCharacter, this);
	}
	OnAnswerTriggered();
}

void AAnswerActor::OnAnswerTriggered_Implementation()
{
	// can be overwitten by blueprint
}