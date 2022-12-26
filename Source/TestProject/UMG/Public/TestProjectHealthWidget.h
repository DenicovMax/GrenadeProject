
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestProjectHealthWidget.generated.h"

class UProgressBar;

UCLASS()
class TESTPROJECT_API UTestProjectHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	virtual void NativeConstruct() override;

	void SetHealth(float NewHealth) const;

protected:
	
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UProgressBar* HealthBar;
};
