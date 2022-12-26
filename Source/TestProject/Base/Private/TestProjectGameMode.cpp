#include "TestProject/Base/Public/TestProjectGameMode.h"
#include "UObject/ConstructorHelpers.h"

ATestProjectGameMode::ATestProjectGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if(PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
