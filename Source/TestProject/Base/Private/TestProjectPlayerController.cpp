
#include "TestProject/Base/Public/TestProjectPlayerController.h"
#include "EngineUtils.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TestProject/UMG/Public/TestProjectDeathMenuWidget.h"

ATestProjectPlayerController::ATestProjectPlayerController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATestProjectPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATestProjectPlayerController::OnDeath()
{
	Client_OnDeath();
}

void ATestProjectPlayerController::Client_OnDeath_Implementation()
{
	if(DeathMenuWidgetClass)
	{
		DeathWidget = CreateWidget<UTestProjectDeathMenuWidget>(this, DeathMenuWidgetClass);
		DeathWidget->AddToViewport(99);
		DeathWidget->GetRestartButton()->OnPressed.AddDynamic(this, &ATestProjectPlayerController::Restart);
		SetShowMouseCursor(true);
		SetInputMode(FInputModeUIOnly());
	}
}

void ATestProjectPlayerController::Restart()
{
	if(DeathWidget)
	{
		DeathWidget->SetVisibility(ESlateVisibility::Hidden);
		DeathWidget->RemoveFromParent();
	}
	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());
	Server_RestartPlayer();
}

void ATestProjectPlayerController::Server_RestartPlayer_Implementation()
{
	if(HasAuthority())
	{
		FVector NewLocationToSpawn;
		FRotator NewRotationToSpawn;
		TArray<APlayerStart*> PlayersStart;
		for(TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
		{
			APlayerStart* Start = *It;
			PlayersStart.Add(Start);
		}

		// Selecting a random spawn point
		int32 RandPosition = UKismetMathLibrary::RandomInteger(PlayersStart.Num() - 1);
		if(RandPosition <= PlayersStart.Num())
		{
			if(PlayersStart[RandPosition])
			{
				NewLocationToSpawn = PlayersStart[RandPosition]->GetActorLocation();
				NewRotationToSpawn = PlayersStart[RandPosition]->GetActorRotation();
			}
		}

		if(GetWorld() && UGameplayStatics::GetGameMode(this))
		{
			FActorSpawnParameters param;
			param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			APawn* mCharacter = GetWorld()->SpawnActor<APawn>(UGameplayStatics::GetGameMode(this)->DefaultPawnClass,
															  NewLocationToSpawn, NewRotationToSpawn, param);
			Possess(mCharacter);
		}
	}
}
