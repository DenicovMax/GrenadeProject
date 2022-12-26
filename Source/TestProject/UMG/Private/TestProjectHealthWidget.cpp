
#include "TestProject/UMG/Public/TestProjectHealthWidget.h"
#include "Components/ProgressBar.h"
#include "TestProject/Base/Public/TestProjectBaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "TestProject/Components/Public/TestProjectHealthComponent.h"

void UTestProjectHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HealthBar->SetPercent(1.f);

	if(ATestProjectBaseCharacter* Char = Cast<ATestProjectBaseCharacter>(GetOwningPlayerPawn()))
	{
		if(Char->GetHealthComponent())
		{
			MaxHealth = Char->GetHealthComponent()->GetMaxHealth();
			Char->GetHealthComponent()->OnHealthChangeSignature.AddUObject(this, &UTestProjectHealthWidget::SetHealth);
		}
	}
}

void UTestProjectHealthWidget::SetHealth(float NewHealth) const
{
	HealthBar->SetPercent(UKismetMathLibrary::Clamp(NewHealth, 0.f, MaxHealth) / MaxHealth);
}
