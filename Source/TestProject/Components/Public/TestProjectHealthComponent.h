
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TestProjectHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChange, float /*NewHealth*/) DECLARE_MULTICAST_DELEGATE(FOnDeath)

UCLASS(ClassGroup = (Custom),
meta=(BlueprintSpawnableComponent))
class TESTPROJECT_API UTestProjectHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UTestProjectHealthComponent();

	UFUNCTION()
	void ChangeHealth(float DamageValue);

	float GetMaxHealth() const { return MaxHealth; }

	bool GetIsDead() const { return IsDead; }

public:
	
	FOnHealthChange OnHealthChangeSignature;

	FOnDeath OnDeathSignature;

protected:
	
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_CurrentHealth();

	void Death();

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxHealth = 100.0f;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth)
	float CurrentHealth;

	bool IsDead = false;
};
