// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceTaxiGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPACETAXI_API ASpaceTaxiGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	int score;

protected:
	virtual void StartPlay() override;
};
