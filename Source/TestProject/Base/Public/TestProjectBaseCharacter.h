
#pragma once

#include "CoreMinimal.h"
#include "TestProjectCharacter.h"
#include "TestProjectBaseCharacter.generated.h"

class UTestProjectManagerWidget;
class AGrenadesBase;
class UTestProjectHealthComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDamage, float /*Damage*/)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnFireGrenade, int32 /*CurrentAmount*/)

UCLASS()
class TESTPROJECT_API ATestProjectBaseCharacter : public ATestProjectCharacter
{
	GENERATED_BODY()

public:
	
	ATestProjectBaseCharacter();

protected:
	
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void StarFire();

	UFUNCTION(Server, Reliable)
	void Server_StartFire();

	void DeathCharacter();

	UFUNCTION(NetMulticast, Reliable)
	void Multi_Death();

	void CreateHUD();

	void RemoveHUD();

	UFUNCTION()
	void OnBeginOverlapCapsule(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep,
							   const FHitResult& SweepResult);

	UFUNCTION()
	void TakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin,
						  FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnRep_CurrentAmountGrenades();

public:
	
	UTestProjectHealthComponent* GetHealthComponent() const { return HealthComponent; }

	int32 GetCurrentGrenades() const { return CurrentGrenades; }
	
	int32 GetMaxGrenades() const { return MaxGrenades; }

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTestProjectHealthComponent* HealthComponent;

	UPROPERTY()
	UTestProjectManagerWidget* MainHUD;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> HUDClassWidget;

	UPROPERTY(Replicated)
	TSubclassOf<AGrenadesBase> GrenadeInHand;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentAmountGrenades)
	int32 CurrentGrenades = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxGrenades = 4;

public:
	
	FOnDamage OnDamageSignature;

	FOnFireGrenade OnFireGrenadeSignature;
};
