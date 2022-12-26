
#include "TestProject/Components/Public/TestProjectHealthComponent.h"
#include "Net/UnrealNetwork.h"

UTestProjectHealthComponent::UTestProjectHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTestProjectHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void UTestProjectHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UTestProjectHealthComponent, CurrentHealth);
}

void UTestProjectHealthComponent::ChangeHealth(float DamageValue)
{
	CurrentHealth -= DamageValue;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Current HP %f"), CurrentHealth));
	if(CurrentHealth <= 0.0f)
	{
		Death();
	}
}

void UTestProjectHealthComponent::OnRep_CurrentHealth()
{
	OnHealthChangeSignature.Broadcast(CurrentHealth);
}

void UTestProjectHealthComponent::Death()
{
	IsDead = true;
	if(OnDeathSignature.IsBound())
	{
		OnDeathSignature.Broadcast();
	}
}
