#include "PlayerInteraction.h"
#include "PlayerCharacter.h"

UPlayerInteraction::UPlayerInteraction()
{
}

void UPlayerInteraction::CancelInteraction(APlayerCharacter* PlayerWhoCanceled)
{
	LeaveInteraction(PlayerWhoCanceled);
	OnCancelInteraction(PlayerWhoCanceled);
}


void UPlayerInteraction::JoinInteraction(APlayerCharacter* PlayerCharacter)
{
	if (!Players.Contains(PlayerCharacter))
	{
		Players.Add(PlayerCharacter);
	}
	if (!InitialPlayer)
	{
		InitialPlayer = PlayerCharacter;
	}
	OnJoinInteraction(PlayerCharacter);
}


void UPlayerInteraction::LeaveInteraction(APlayerCharacter* PlayerCharacter)
{

	if (PlayerCharacter->SelectedPlayerInteraction == this)
	{
		PlayerCharacter->SelectedPlayerInteraction = nullptr;
	}
	if (PlayerCharacter->CurrentPlayerInteraction == this)
	{
		PlayerCharacter->CurrentPlayerInteraction = nullptr;
	}
	if (Players.Contains(PlayerCharacter))
	{
		Players.Remove(PlayerCharacter);
	}
	if (InitialPlayer == PlayerCharacter)
	{
		for (APlayerCharacter* Player : Players)
		{
			if (Player != PlayerCharacter) {
				LeaveInteraction(Player);
			}
		}
		InitialPlayer = nullptr;
		ConditionalBeginDestroy();
	}
	OnLeaveInteraction(PlayerCharacter);
}



void UPlayerInteraction::OnCancelInteraction_Implementation(APlayerCharacter* PlayerCharacter)
{
	// can be overwitten by blueprint
}

void UPlayerInteraction::OnJoinInteraction_Implementation(APlayerCharacter* PlayerCharacter)
{
	// can be overwitten by blueprint
}

void UPlayerInteraction::OnLeaveInteraction_Implementation(APlayerCharacter* PlayerCharacter)
{
	// can be overwitten by blueprint
}