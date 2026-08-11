// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FlyingOne.h"

// Sets default values
AFlyingOne::AFlyingOne()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlyingOne::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlyingOne::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFlyingOne::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

