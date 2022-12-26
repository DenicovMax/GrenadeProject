
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestProjectPlayerController.generated.h"

class UTestProjectDeathMenuWidget;

UCLASS()
class TESTPROJECT_API ATestProjectPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	ATestProjectPlayerController();

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void Restart();

	UFUNCTION(Server, Reliable)
	void Server_RestartPlayer();

public:
	
	void OnDeath();

	UFUNCTION(Client, Reliable)
	void Client_OnDeath();

protected:
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> DeathMenuWidgetClass;

	UPROPERTY()
	UTestProjectDeathMenuWidget* DeathWidget;
};
