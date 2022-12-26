
#include "TestProject/UMG/Public/TestProjectGrenadesAmountWidget.h"
#include "Components/TextBlock.h"
#include "TestProject/Base/Public/TestProjectBaseCharacter.h"

void UTestProjectGrenadesAmountWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(ATestProjectBaseCharacter* Char = Cast<ATestProjectBaseCharacter>(GetOwningPlayerPawn()))
	{
		Char->OnFireGrenadeSignature.AddUObject(this, &UTestProjectGrenadesAmountWidget::OnChangeCurrentAmount);
		CurrentGrenadesText->SetText(FText::FromString(FString::FromInt(Char->GetCurrentGrenades())));
		MaxGrenadesText->SetText(FText::FromString(FString::FromInt(Char->GetMaxGrenades())));
	}
}

void UTestProjectGrenadesAmountWidget::OnChangeCurrentAmount(int32 NewCurrentAmount) const
{
	CurrentGrenadesText->SetText(FText::FromString(FString::FromInt(NewCurrentAmount)));
}
