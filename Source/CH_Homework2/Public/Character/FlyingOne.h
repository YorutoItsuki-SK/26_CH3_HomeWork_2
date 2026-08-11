#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FlyingOne.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class USkeletalMeshComponent;
struct FInputActionValue;

UCLASS()
class CH_HOMEWORK2_API AFlyingOne : public APawn
{
	GENERATED_BODY()

public:
	AFlyingOne();

protected:
	float CurrentDeltaTime = 0;

	/*float AccelMove;
	float AccelRotate;
	float AccelFly;*/
	float Gravity = 980.f;

	float SpeedMoveMax;
	float SpeedRotateMax;
	float SpeedFlyMax;

	/*float SpeedMove = 0;
	float SpeedRotate = 0;
	float SpeedFly = 0;*/

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	TObjectPtr<UBoxComponent> BoxComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;

	const bool IsGrounded() const;

	UFUNCTION(BlueprintCallable, Category = "Rotate")
	void RollResetFunc();

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	UFUNCTION()
	void Float(const FInputActionValue& Value);
	UFUNCTION()
	void Sink(const FInputActionValue& Value);
	UFUNCTION()
	void RollLeft(const FInputActionValue& Value);
	UFUNCTION()
	void RollRight(const FInputActionValue& Value);
	UFUNCTION()
	void RollReset(const FInputActionValue& Value);

};
