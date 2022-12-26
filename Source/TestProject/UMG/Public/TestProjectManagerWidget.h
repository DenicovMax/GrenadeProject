
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestProjectManagerWidget.generated.h"

class UTestProjectGrenadesAmountWidget;
class UTestProjectHealthWidget;

UCLASS()
class TESTPROJECT_API UTestProjectManagerWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTestProjectHealthWidget* HealthWidget;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTestProjectGrenadesAmountWidget* GrenadeWidget;
};
