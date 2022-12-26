
#include "TestProject/Weapon/Public/GrenadesBase.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AGrenadesBase::AGrenadesBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GrenadeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	if(GrenadeMesh)
	{
		SetRootComponent(GrenadeMesh);
		GrenadeMesh->OnComponentBeginOverlap.AddDynamic(this, &AGrenadesBase::OnBeginOverlap);
	}

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	bReplicates		  = true;
}

void AGrenadesBase::BeginPlay()
{
	Super::BeginPlay();
}

void AGrenadesBase::StartFire()
{
	if(MovementComponent)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerToExplosion, this, &AGrenadesBase::Detonation,
											   Info.TimeToExplosion);
	}
}

void AGrenadesBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep,
								   const FHitResult& SweepResult)
{
	if(HasAuthority() && OtherActor != GetOwner())
	{
		Detonation();
	}
}

void AGrenadesBase::Detonation()
{
	if(HasAuthority() && GetOwner())
	{
		FVector loc = GrenadeMesh->GetComponentLocation();
		UGameplayStatics::ApplyRadialDamage(this, Info.Damage, loc, Info.InnerRadius, Info.DamageType, {}, nullptr,
											GetOwner()->GetInstigatorController());
		Multi_PlayEffect();
	}
}

void AGrenadesBase::Multi_PlayEffect_Implementation()
{
	if(!HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this, Info.ExplosionSound, GrenadeMesh->GetComponentLocation());
		UParticleSystemComponent* ParticleSystemComponent =
			UGameplayStatics::SpawnEmitterAtLocation(this, Info.ExplosionParticle, GrenadeMesh->GetComponentLocation());
		ParticleSystemComponent->Deactivate();
	}
	Destroy();
}
