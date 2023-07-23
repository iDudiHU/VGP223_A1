// Copyright Epic Games, Inc. All Rights Reserved.


#include "SpaceTaxiGameModeBase.h"

void ASpaceTaxiGameModeBase::StartPlay()
{
	Super::StartPlay();
	score = 10;
	// C asset() <- stop code here
	check(GEngine != nullptr)
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Yellow, TEXT("Hi"));
	UE_LOG(LogTemp, Warning, TEXT("Consol log message."))
}
