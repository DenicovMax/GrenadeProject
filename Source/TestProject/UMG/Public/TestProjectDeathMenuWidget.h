
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestProjectDeathMenuWidget.generated.h"

class UButton;

UCLASS()
class TESTPROJECT_API UTestProjectDeathMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	virtual void NativeConstruct() override;

	UButton* GetRestartButton() const { return RestartButton; }

protected:
	
	UFUNCTION()
	void OnExitButtonDown();

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;
};
