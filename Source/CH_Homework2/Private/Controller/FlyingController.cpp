#include "Controller/FlyingController.h"
#include "EnhancedInputSubsystems.h"

void AFlyingController::BeginPlay()
{
	Super::BeginPlay();

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (!LocalPlayer) {
		return;
	}
	UEnhancedInputLocalPlayerSubsystem* PlayerSubSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!PlayerSubSystem) {
		return;
	}

	if (!InputMappingContext) {
		return;
	}

	PlayerSubSystem->AddMappingContext(InputMappingContext, 0);
}

AFlyingController::AFlyingController()
	:InputMappingContext(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr),
	FloatAction(nullptr),
	SinkAction(nullptr),
	RollLeftAction(nullptr),
	RollRightAction(nullptr),
	RollResetAction(nullptr)
{
}
