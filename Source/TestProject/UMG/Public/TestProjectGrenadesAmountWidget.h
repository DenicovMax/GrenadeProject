
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestProjectGrenadesAmountWidget.generated.h"

class UTextBlock;

UCLASS()
class TESTPROJECT_API UTestProjectGrenadesAmountWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	virtual void NativeConstruct() override;

protected:
	
	UFUNCTION()
	void OnChangeCurrentAmount(int32 NewCurrentAmount) const;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* CurrentGrenadesText;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* MaxGrenadesText;
};
