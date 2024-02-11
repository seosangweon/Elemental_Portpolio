
#include "EGameMode.h"

AEGameMode::AEGameMode()
{
	ConstructorHelpers::FClassFinder<APawn>playerPawn(TEXT("Blueprint'/Game/Player/BP_Player.BP_Player_C'"));
	if (playerPawn.Succeeded())
		DefaultPawnClass = playerPawn.Class;
}