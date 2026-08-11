#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FlyingController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class CH_HOMEWORK2_API AFlyingController : public APlayerController
{
	GENERATED_BODY()

	protected:
		virtual void BeginPlay() override;

	public:
		AFlyingController();

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		UInputMappingContext* InputMappingContext;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		UInputAction* MoveAction;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		UInputAction* LookAction;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		UInputAction* FloatAction;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		UInputAction* SinkAction;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		UInputAction* RollLeftAction;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		UInputAction* RollRightAction;
};
