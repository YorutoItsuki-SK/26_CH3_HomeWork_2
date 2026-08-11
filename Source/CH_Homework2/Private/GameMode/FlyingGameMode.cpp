#include "GameMode/FlyingGameMode.h"
#include "Character/FlyingOne.h"
#include "Controller/FlyingController.h"

AFlyingGameMode::AFlyingGameMode()
{
	DefaultPawnClass = AFlyingOne::StaticClass();
	PlayerControllerClass = AFlyingController::StaticClass();
}
