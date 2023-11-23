#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter() {


    UPlayerCharacterProperties* PlayerProps = CreateDefaultSubobject<UPlayerCharacterProperties>(TEXT("PlayerProperties"));
    Properties = Cast<UAdventureCharacterProperties>(PlayerProps);

    PuckUpItems = true;
    IsPlayer = true;
    CurrentPlayerInteraction = nullptr;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
    AttractNPC = false;
    if (GameMode)
    {
        GameMode->Players.Add(this);
        int PlayerNumber = GameMode->Players.Num();
        PlayerName = TEXT("Player ") + FString::FromInt(PlayerNumber);
    }
}

void APlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateNearPlayerInteractions(DeltaTime);
}

bool APlayerCharacter::CharacterCanMove()
{
    if (CurrentPlayerInteraction || SelectedPlayerInteraction) 
    {
       return false;
    }
   return Super::CharacterCanMove();
}

void APlayerCharacter::Die()
{
    if (GameMode) 
    {
        GameMode->GameOver(this, GameOverIfLost);
    }
    Super::Die();
}

void APlayerCharacter::OnAreaOverlapBegin(AAreaActor* AreaActor)
{
    Super::OnAreaOverlapBegin(AreaActor);
}

void APlayerCharacter::OnAreaOverlapEnd(AAreaActor* AreaActor)
{
    Super::OnAreaOverlapEnd(AreaActor);

}

void APlayerCharacter::ShowPlayerInteractionSelection()
{
    PlayerInteractionSelectionVisible = true;
}

void APlayerCharacter::HidePlayerInteractionSelection()
{
    PlayerInteractionSelectionVisible = false;
    SelectedPlayerInteraction = nullptr;
}


void APlayerCharacter::NewPlayerInteraction()
{
    if (!CurrentPlayerInteraction)
    {
        UPlayerInteraction* NewPlayerInteraction = NewObject<UPlayerInteraction>(this);
        NewPlayerInteraction->GameMode = GameMode;
        JoinPlayerInteraction(NewPlayerInteraction);
        ShowInteraction();
    }

}

void APlayerCharacter::SelectPlayerInteraction(UPlayerInteraction* PlayerInteraction)
{
    if (!PlayerInteraction->InitialPlayer) 
    {
        SelectedPlayerInteraction = PlayerInteraction;
    }
    else
    {
        JoinPlayerInteraction(PlayerInteraction);
    }
}

void APlayerCharacter::SelectPrevPlayerInteraction()
{
    if (NearPlayerInteractions.Num() == 0)
    {
        return;
    }

    if (SelectedPlayerInteraction)
    {
        int32 SelectedIndex = NearPlayerInteractions.IndexOfByKey(SelectedPlayerInteraction);
        int32 PrevIndex = (SelectedIndex - 1 + NearPlayerInteractions.Num()) % NearPlayerInteractions.Num();
        SelectPlayerInteraction(NearPlayerInteractions[PrevIndex]);
    }
    else
    {
        SelectPlayerInteraction(NearPlayerInteractions.Last());
    }
}

void APlayerCharacter::SelcetNextPlayerInteraction()
{
    if (NearPlayerInteractions.Num() == 0)
    {
        return;
    }

    if (SelectedPlayerInteraction)
    {
        int32 SelectedIndex = NearPlayerInteractions.IndexOfByKey(SelectedPlayerInteraction);
        int32 NextIndex = (SelectedIndex + 1) % NearPlayerInteractions.Num();
        SelectPlayerInteraction(NearPlayerInteractions[NextIndex]);
    }
    else
    {
        SelectPlayerInteraction(NearPlayerInteractions[0]);
    }
}

void APlayerCharacter::JoinPlayerInteraction(UPlayerInteraction* PlayerInteraction)
{
    if (CurrentPlayerInteraction || SelectedPlayerInteraction)
    {
        CancelPlayerInteraction();
    }
    if (PlayerInteraction)
    {
        PlayerInteraction->JoinInteraction(this);
        CurrentPlayerInteraction = PlayerInteraction;
        SelectedPlayerInteraction = nullptr;
        ShowInteraction();
    }

}

void APlayerCharacter::UpdateNearPlayerInteractions(float DeltaTime)
{
    NearPlayerInteractions.Empty();
    FVector PlayerLocation = GetActorLocation();
    if (GameMode)
    {
        for (APlayerCharacter* PlayersCharacter : GameMode->Players)
        {
            if (PlayersCharacter != this) 
            {
                float Distance = FVector::Distance(PlayerLocation, PlayersCharacter->GetActorLocation());
                if (Distance <= MaxPlayerInteractionDistance && PlayersCharacter->CurrentPlayerInteraction && PlayersCharacter->CurrentPlayerInteraction != CurrentPlayerInteraction)
                {
                    NearPlayerInteractions.Add(PlayersCharacter->CurrentPlayerInteraction);
                }
            }
        }
    }
}



void APlayerCharacter::CancelPlayerInteraction()
{
    if (CurrentPlayerInteraction)
    {
        CurrentPlayerInteraction->CancelInteraction(this);
    }
    if (SelectedPlayerInteraction) {
        SelectedPlayerInteraction->CancelInteraction(this);
    }
    CloseInteraction();
}



void APlayerCharacter::MenuAccept()
{
    if (!CurrentPlayerInteraction && !SelectedPlayerInteraction && NearPlayerInteractions.Num())
    {
        SelectPlayerInteraction(NearPlayerInteractions[0]);
        return;
    }
    else if (SelectedPlayerInteraction && !CurrentPlayerInteraction) 
    {
        JoinPlayerInteraction(SelectedPlayerInteraction);
        return;
    }
    Super::MenuAccept();
}

void APlayerCharacter::MenuDeny()
{
 
    if (CurrentPlayerInteraction || SelectedPlayerInteraction)
    {
        CancelPlayerInteraction();
        return;
    }
    Super::MenuDeny();
}

void APlayerCharacter::MenuPrevTab()
{

    Super::MenuPrevTab();
}


void APlayerCharacter::MenuNextTab()
{
    Super::MenuNextTab();
}


void APlayerCharacter::MenuPrevOption()
{
    if (!CurrentPlayerInteraction && SelectedPlayerInteraction && NearPlayerInteractions.Num())
    {
        SelectPrevPlayerInteraction();
        return;
    }
    Super::MenuPrevOption();
}


void APlayerCharacter::MenuNextOption()
{
    if (!CurrentPlayerInteraction && SelectedPlayerInteraction && NearPlayerInteractions.Num())
    {
        SelcetNextPlayerInteraction();
        return;
    }
    Super::MenuNextOption();
}

bool APlayerCharacter::CanAttackCharacter(AAdventureCharacter* Character)
{
    if (Character)
    {
        return true;
    }
    return false;
}
