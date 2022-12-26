#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GrenadesBase.generated.h"

USTRUCT(BlueprintType)
struct FGrenadesInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Damage = 30.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MinDamage = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float InnerRadius = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float OuterRadius = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageFalloff = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeToExplosion = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USoundBase* ExplosionSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UParticleSystem* ExplosionParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;
};

UCLASS()
class TESTPROJECT_API AGrenadesBase : public AActor
{
	GENERATED_BODY()

public:
	
	AGrenadesBase();

protected:
	
	virtual void BeginPlay() override;

public:
	
	void StartFire();

protected:
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult);

	void Detonation();

	UFUNCTION(NetMulticast, Reliable)
	void Multi_PlayEffect();

protected:
	
	FTimerHandle TimerToExplosion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* GrenadeMesh;

	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGrenadesInfo Info;
};
