
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestProjectItemBase.generated.h"

class AGrenadesBase;

USTRUCT(BlueprintType)
struct FItemStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText NameItem = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Description = FText();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTexture* Icon2D = nullptr;

	// In the future, it is possible to expand to use the inventory system
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AGrenadesBase> ItemClass;
};

UCLASS()
class TESTPROJECT_API ATestProjectItemBase : public AActor
{
	GENERATED_BODY()

public:
	
	ATestProjectItemBase();

	UPROPERTY(EditAnywhere)
	FItemStruct ItemStruct;

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep,
								 const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystemComponent* ParticleSystem;

public:
};
