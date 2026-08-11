#include "Character/FlyingOne.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Controller/FlyingController.h"

AFlyingOne::AFlyingOne()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = GetRootComponent();
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetSimulatePhysics(false);
	BoxComponent->SetupAttachment(SceneComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	//SkeletalMeshComponent->SetSimulatePhysics(false);
	SkeletalMeshComponent->SetupAttachment(BoxComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(BoxComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	SpeedMoveMax = 600.f;
	//AccelMove = 60.f;
	SpeedRotateMax = 30.f;
	//AccelRotate = 60.f;
	SpeedFlyMax = 600.f;
	//AccelFly = 60.f;

}

void AFlyingOne::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFlyingOne::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentDeltaTime = DeltaTime;
}

void AFlyingOne::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhacedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EnhacedInput) {
		return;
	}
	
	AFlyingController* FlyingController = Cast<AFlyingController>(GetController());
	if (!FlyingController) {
		return;
	}

	if (FlyingController->MoveAction) {
		EnhacedInput->BindAction(
			FlyingController->MoveAction,
			ETriggerEvent::Triggered,
			this,
			AFlyingOne::Move
		);
	}
	if (FlyingController->LookAction) {
		EnhacedInput->BindAction(
			FlyingController->LookAction,
			ETriggerEvent::Triggered,
			this,
			AFlyingOne::Look
		);
	}
	if (FlyingController->FloatAction) {
		EnhacedInput->BindAction(
			FlyingController->FloatAction,
			ETriggerEvent::Triggered,
			this,
			AFlyingOne::Float
		);
	}
	if (FlyingController->SinkAction) {
		EnhacedInput->BindAction(
			FlyingController->SinkAction,
			ETriggerEvent::Triggered,
			this,
			AFlyingOne::Sink
		);
	}
	if (FlyingController->RollLeftAction) {
		EnhacedInput->BindAction(
			FlyingController->RollLeftAction,
			ETriggerEvent::Triggered,
			this,
			AFlyingOne::RollLeft
		);
	}
	if (FlyingController->RollRightAction) {
		EnhacedInput->BindAction(
			FlyingController->RollRightAction,
			ETriggerEvent::Triggered,
			this,
			AFlyingOne::RollRight
		);
	}
}

void AFlyingOne::Move(const FInputActionValue& Value)
{
	FVector2D MoveInput = Value.Get<FVector2D>();
	if (!FMath::IsNearlyZero(MoveInput.X)) {
		FVector FowardVector = GetActorForwardVector();
		
	}
}

void AFlyingOne::Look(const FInputActionValue& Value)
{
}

void AFlyingOne::Float(const FInputActionValue& Value)
{
}

void AFlyingOne::Sink(const FInputActionValue& Value)
{
}

void AFlyingOne::RollLeft(const FInputActionValue& Value)
{
}

void AFlyingOne::RollRight(const FInputActionValue& Value)
{
}

