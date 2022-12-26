
#include "TestProject/Base/Public/TestProjectBaseCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "TestProject/Base/Public/TestProjectPlayerController.h"
#include "TestProject/Components/Public/TestProjectHealthComponent.h"
#include "TestProject/Item/Public/TestProjectItemBase.h"
#include "TestProject/UMG/Public/TestProjectManagerWidget.h"
#include "TestProject/Weapon/Public/GrenadesBase.h"

ATestProjectBaseCharacter::ATestProjectBaseCharacter()
{

	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UTestProjectHealthComponent>("HealthComponent");
	if(HealthComponent)
	{
		HealthComponent->SetIsReplicated(true);
		OnDamageSignature.AddUObject(HealthComponent, &UTestProjectHealthComponent::ChangeHealth);
		HealthComponent->OnDeathSignature.AddUObject(this, &ATestProjectBaseCharacter::DeathCharacter);
	}
	if(GetCapsuleComponent())
	{
		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,
																  &ATestProjectBaseCharacter::OnBeginOverlapCapsule);
	}
	OnTakeRadialDamage.AddDynamic(this, &ATestProjectBaseCharacter::TakeRadialDamage);
}

void ATestProjectBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	CreateHUD();
}

void ATestProjectBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("StartFire", IE_Pressed, this, &ThisClass::StarFire);
}

void ATestProjectBaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATestProjectBaseCharacter, GrenadeInHand);
	DOREPLIFETIME(ATestProjectBaseCharacter, CurrentGrenades);
}

void ATestProjectBaseCharacter::StarFire()
{
	Server_StartFire();
}

void ATestProjectBaseCharacter::Server_StartFire_Implementation()
{
	if(CurrentGrenades > 0)
	{
		FActorSpawnParameters param;
		param.Owner							 = this;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AGrenadesBase* Grenade				 = GetWorld()->SpawnActor<AGrenadesBase>(
			  GrenadeInHand, GetMesh()->GetSocketLocation("hand_r"), GetControlRotation(), param);
		if(Grenade)
		{
			Grenade->StartFire();
			CurrentGrenades -= 1;
		}
	}
}

void ATestProjectBaseCharacter::DeathCharacter()
{
	if(ATestProjectPlayerController* PC = Cast<ATestProjectPlayerController>(GetController()))
	{
		PC->OnDeath();
	}

	Multi_Death();
}

void ATestProjectBaseCharacter::Multi_Death_Implementation()
{
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if(!HasAuthority())
	{
		GetMesh()->SetSimulatePhysics(true);
		if(GetController())
		{
			RemoveHUD();
		}
	}
	SetLifeSpan(5.f);
}

void ATestProjectBaseCharacter::RemoveHUD()
{
	if(MainHUD)
	{
		MainHUD->RemoveFromParent();
	}
}

void ATestProjectBaseCharacter::CreateHUD()
{
	if(HUDClassWidget)
	{
		if(APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			MainHUD = CreateWidget<UTestProjectManagerWidget>(PC, HUDClassWidget);
			if(!MainHUD)
			{
				return;
			}

			MainHUD->AddToViewport();
		}
	}
}

void ATestProjectBaseCharacter::OnBeginOverlapCapsule(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
													  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
													  bool bBFromSweep, const FHitResult& SweepResult)
{
	if(HasAuthority())
	{
		if(ATestProjectItemBase* Item = Cast<ATestProjectItemBase>(OtherActor))
		{
			GrenadeInHand	= Item->ItemStruct.ItemClass;
			int32 NewValue	= Item->ItemStruct.Amount + CurrentGrenades;
			CurrentGrenades = UKismetMathLibrary::Clamp(NewValue, 1, MaxGrenades);
		}
	}
}

void ATestProjectBaseCharacter::TakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
												 FVector Origin, FHitResult HitInfo, AController* InstigatedBy,
												 AActor* DamageCauser)
{
	if(HasAuthority() && !GetHealthComponent()->GetIsDead())
	{
		if(OnDamageSignature.IsBound())
		{
			OnDamageSignature.Broadcast(Damage);
		}
	}
}

void ATestProjectBaseCharacter::OnRep_CurrentAmountGrenades()
{
	if(!HasAuthority())
	{
		if(OnFireGrenadeSignature.IsBound())
		{
			OnFireGrenadeSignature.Broadcast(CurrentGrenades);
		}
	}
}