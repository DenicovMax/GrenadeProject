
#include "TestProject/Item/Public/TestProjectItemBase.h"
#include "Particles/ParticleSystemComponent.h"

ATestProjectItemBase::ATestProjectItemBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshPreview");
	if(Mesh)
	{
		SetRootComponent(Mesh);
		Mesh->OnComponentBeginOverlap.AddDynamic(this, &ATestProjectItemBase::OnComponentBeginOverlap);
	}

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	if(ParticleSystem)
	{
		ParticleSystem->SetupAttachment(Mesh);
	}
}

void ATestProjectItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATestProjectItemBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
												   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
												   bool bBFromSweep, const FHitResult& SweepResult)
{
	Destroy();
}
