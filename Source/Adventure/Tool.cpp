#include "Tool.h"
#include "AdventureCharacter.h"


ATool::ATool()
{
	InitTool();
}

void ATool::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	InitTool();
}

void ATool::BeginPlay()
{
	Super::BeginPlay();
	AGameModeBase* CurrentGameMode = GetWorld()->GetAuthGameMode();
	GameMode = Cast<AAdventureGameModeBase>(CurrentGameMode);
	InitTool();
}

void ATool::InitTool()
{

}

void ATool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateApply(DeltaTime);
	UpdateUse(DeltaTime);

}

void ATool::UpdateApply(float DeltaTime)
{
	if (IsApplying && ApplyActor)
	{
		if (Charge > 0.0f)
		{
			Charge -= Consumption * DeltaTime;
		}
		else 
		{
			Charge = 0.0f;
			if (DetroyIfEmpty) {

			}
			if (DropIfEmpty && Character){
				Character = nullptr;
			}
		}
	}
}

void ATool::UpdateUse(float DeltaTime)
{
	if (IsUsing)
	{
		if (Charge > 0.0f)
		{
			Charge -= Consumption * DeltaTime;
		}
		else
		{
			Charge = 0.0f;
		}
	}
}

void ATool::UpdateCharge(float DeltaTime)
{
	if (Charge <= 0.0f)
	{
		Charge = 0.0f;
		if (DetroyIfEmpty) {
			if (Character && Character->Tools.Contains(this))
			{
				Character->Tools.Remove(this);
			}
			Destroy();
		}
		else
		{
			if (DropIfEmpty && Character) {
				Drop();
			}
		}
	}
}

void ATool::StartUse()
{
	IsUsing = true;
}

void ATool::StopUse()
{
	IsUsing = false;
}

void ATool::StartApply(AActor* Actor)
{
	ApplyActor = Actor;
	if (ApplyActor)
	{
		IsApplying = true;
	}
	else 
	{
		IsApplying = false;
	}
}

void ATool::StopApply()
{
	ApplyActor = nullptr;
	IsApplying = false;
}

void ATool::Drop()
{
	Super::Drop();
	StopUse();
	StopApply();
	if (Character && Character->Tools.Contains(this))
	{
		Character->Tools.Remove(this);
	}
	this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Character = nullptr;
}
