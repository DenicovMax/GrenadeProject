
#include "TestProject/UMG/Public/TestProjectDeathMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UTestProjectDeathMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ExitButton->OnPressed.AddDynamic(this, &UTestProjectDeathMenuWidget::OnExitButtonDown);
}

void UTestProjectDeathMenuWidget::OnExitButtonDown()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}


