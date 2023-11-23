#include "InteractionActor.h"
#include "TaskActor.h"
#include "AnswerActor.h"
#include "AdventureCharacter.h"


AInteractionActor::AInteractionActor()
{

    PrimaryActorTick.bCanEverTick = true;


    InteractionTaskMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractionTaskMesh"));
    InteractionTaskMesh->SetupAttachment(RootComponent);

    InteractionAnswerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractionAnswerMesh"));
    InteractionAnswerMesh->SetupAttachment(RootComponent);

    SpeechComponent = CreateDefaultSubobject<USpeechComponent>(TEXT("SpeechComponent"));
    SpeechComponent->Character = Character;
}


void AInteractionActor::BeginPlay()
{
    Super::BeginPlay();
    if (AskQuestion)
    {
        CreateAnswers();
    }
    SpeechComponent->Character = Character;
}


void AInteractionActor::SetCharacter(AAdventureCharacter* ItemCharacter)
{
    Super::SetCharacter(ItemCharacter);
    SpeechComponent->Character = Character;
}

void AInteractionActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    for (ATaskActor* InteractionTask : InteractionTasks)
    {
        InteractionTask->Character = Character;
        if (TargetCharacter && !InteractionTask->TargetCharacter) 
        {
            InteractionTask->TargetCharacter = TargetCharacter;
        }
    }
    for (AAnswerActor* InteractionAnswer : InteractionAnswers)
    {
        InteractionAnswer->Character = Character;
        if (TargetCharacter && !InteractionAnswer->TargetCharacter) 
        {
            InteractionAnswer->TargetCharacter = TargetCharacter;
        }

    }
    
}


void AInteractionActor::TriggerNextTask() {

    TriggerTask(NextTasksIndex);

}

void AInteractionActor::TriggerTask(float TasksIndex) {

    if (CurrentTasksIndex != TasksIndex && InteractionTaskClasses.Num() > TasksIndex) {
        CurrentTasksIndex = TasksIndex;
        TSubclassOf<ATaskActor> InteractionTaskClass = InteractionTaskClasses[CurrentTasksIndex];

        if (InteractionTaskClass && InteractionTaskClass.Get())
        {
            ATaskActor* InteractionTask = GetWorld()->SpawnActor<ATaskActor>(InteractionTaskClass, FVector::ZeroVector, FRotator::ZeroRotator);

            InteractionTask->SetActorEnableCollision(false);
            InteractionTask->SetActorTickEnabled(false);
            InteractionTask->Character = Character;
            InteractionTask->TargetCharacter = TargetCharacter;
            InteractionTask->ParentInteractionActor = this;
            InteractionTask->AttachToComponent(InteractionTaskMesh, FAttachmentTransformRules::KeepRelativeTransform);
            SetActorEnableCollision(true);
            SetActorTickEnabled(true);

            InteractionTasks.Add(InteractionTask);


        }
        NextTasksIndex = TasksIndex + 1;

    }
}



void AInteractionActor::CreateAnswers() 
{

    for (TSubclassOf<AAnswerActor> InteractionAnswerClass : InteractionAnswerClasses)
    {
        AAnswerActor* InteractionAnswer = GetWorld()->SpawnActor<AAnswerActor>(InteractionAnswerClass, FVector::ZeroVector, FRotator::ZeroRotator);

        InteractionAnswer->SetActorEnableCollision(false);
       // InteractionAnswer->SetActorTickEnabled(false);
        InteractionAnswer->Character = Character;
        InteractionAnswer->TargetCharacter = TargetCharacter;
        InteractionAnswer->AttachToComponent(InteractionAnswerMesh, FAttachmentTransformRules::KeepRelativeTransform);
        InteractionAnswer->ParentInteractionActor = this;
        InteractionAnswers.Add(InteractionAnswer);
    }
    SetActorEnableCollision(true);
    SetActorTickEnabled(true);

}

void AInteractionActor::TriggerInteractionClass(AAdventureCharacter* FromCharacter, AAdventureCharacter* ToCharacter, TSubclassOf<AInteractionActor> NewInteractionActorClass)
{
    if (NewInteractionActorClass && NewInteractionActorClass.Get()) {
        FromCharacter = FromCharacter ? FromCharacter : ToCharacter;
        ToCharacter = ToCharacter ? ToCharacter : FromCharacter;
        AInteractionActor* NewInteractionActor = GetWorld()->SpawnActor<AInteractionActor>(NewInteractionActorClass, FVector::ZeroVector, FRotator::ZeroRotator);
        NewInteractionActor->Character = FromCharacter;
        NewInteractionActor->TargetCharacter = ToCharacter;
        NewInteractionActor->ParentInteractionActor = this;
        if (ToCharacter) {
            ToCharacter->TriggerInteractionActor(FromCharacter, NewInteractionActor);
            if (ShowInteraction)
            {
                ToCharacter->AddInteractionActor(NewInteractionActor);
                if (ForceInteraction) {
                    ToCharacter->SelectInteractionActor(NewInteractionActor);
                }
            }
        }
    } 
}



void AInteractionActor::AcceptInteraction() {



}


void AInteractionActor::DenyInteraction() {



}

