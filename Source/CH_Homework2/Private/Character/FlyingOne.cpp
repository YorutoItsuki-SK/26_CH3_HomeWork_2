#include "Character/FlyingOne.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputComponent.h"

#include "Controller/FlyingController.h"

AFlyingOne::AFlyingOne()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	BoxComponent->SetSimulatePhysics(false);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	//SkeletalMeshComponent->SetSimulatePhysics(false);
	SkeletalMeshComponent->SetupAttachment(BoxComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->SetupAttachment(BoxComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	SpeedMoveMax = 600.f;
	//AccelMove = 60.f;
	SpeedRotateMax = 30.f;
	//AccelRotate = 60.f;
	SpeedFlyMax = 2000.f;
	//AccelFly = 60.f;

}

void AFlyingOne::BeginPlay()
{
	Super::BeginPlay();
}

const bool AFlyingOne::IsGrounded() const
{
	FVector BoxExtent = BoxComponent->GetScaledBoxExtent();

	const FVector Start = GetActorLocation();
	const FVector End =
		Start - FVector(0.f, 0.f, BoxExtent.Z + 1.f);

	FHitResult HitResult;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	return GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		Params
	);
}

void AFlyingOne::RollResetFunc()
{
	FRotator Rotation = GetActorRotation();
	Rotation.Pitch = 0.f;
	Rotation.Roll = 0.f;
	SetActorRotation(Rotation);
}

void AFlyingOne::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentDeltaTime = DeltaTime;

	if (!IsGrounded()) {
		AddActorWorldOffset(FVector(0.f, 0.f, -Gravity * DeltaTime), true);
	}

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
			&AFlyingOne::Move
		);
	}


	if (FlyingController->LookAction) {
		EnhacedInput->BindAction(
			FlyingController->LookAction,
			ETriggerEvent::Triggered,
			this,
			&AFlyingOne::Look
		);
	}
	if (FlyingController->FloatAction) {
		EnhacedInput->BindAction(
			FlyingController->FloatAction,
			ETriggerEvent::Triggered,
			this,
			&AFlyingOne::Float
		);
	}
	if (FlyingController->SinkAction) {
		EnhacedInput->BindAction(
			FlyingController->SinkAction,
			ETriggerEvent::Triggered,
			this,
			&AFlyingOne::Sink
		);
	}
	if (FlyingController->RollLeftAction) {
		EnhacedInput->BindAction(
			FlyingController->RollLeftAction,
			ETriggerEvent::Triggered,
			this,
			&AFlyingOne::RollLeft
		);
	}
	if (FlyingController->RollRightAction) {
		EnhacedInput->BindAction(
			FlyingController->RollRightAction,
			ETriggerEvent::Triggered,
			this,
			&AFlyingOne::RollRight
		);
	}
	if (FlyingController->RollResetAction) {
		EnhacedInput->BindAction(
			FlyingController->RollResetAction,
			ETriggerEvent::Started,
			this,
			&AFlyingOne::RollReset
		);
	}
}

void AFlyingOne::Move(const FInputActionValue& Value)
{
	const FVector2D MoveInput = Value.Get<FVector2D>();

	const FVector LocalMovement(
		MoveInput.X,
		MoveInput.Y,
		0.f
	);

	AddActorLocalOffset(
		LocalMovement * SpeedMoveMax * CurrentDeltaTime,
		true
	);
}

void AFlyingOne::Look(const FInputActionValue& Value)
{
	const FVector2D LookInput = Value.Get<FVector2D>();

	if (IsGrounded()) {
		AddActorLocalRotation(
			FRotator(
				0.f,
				LookInput.X,
				0.f
			)
		);
	}
	else {
		AddActorLocalRotation(
			FRotator(
				LookInput.Y,
				LookInput.X,
				0.f
			)
		);
	}

	
}

void AFlyingOne::Float(const FInputActionValue& Value)
{
	AddActorWorldOffset(FVector(0.f, 0.f, SpeedFlyMax * CurrentDeltaTime), true);
}

void AFlyingOne::Sink(const FInputActionValue& Value)
{
	AddActorWorldOffset(FVector(0.f, 0.f, -SpeedFlyMax * CurrentDeltaTime), true);
}

void AFlyingOne::RollLeft(const FInputActionValue& Value)
{
	AddActorLocalRotation(
		FRotator(
			0.f,
			0.f,
			-SpeedRotateMax * CurrentDeltaTime
		),
		true
	);
}

void AFlyingOne::RollRight(const FInputActionValue& Value)
{
	AddActorLocalRotation(
		FRotator(
			0.f,
			0.f,
			SpeedRotateMax * CurrentDeltaTime
		),
		true
	);
}

void AFlyingOne::RollReset(const FInputActionValue& Value)
{
	RollResetFunc();
}

