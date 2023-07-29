// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTTMinimax.generated.h"

UCLASS()
class SPACETAXI_API ATTTMinimax : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATTTMinimax();

	// Declare delegate to communicate AI's move to Blueprint
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPiecePlaced, int32, AIMove);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameReset, int32, PlayerScore, int32, NumOfGames);


	UPROPERTY(BlueprintAssignable)
	FOnPiecePlaced OnPiecePlaced;
	UPROPERTY(BlueprintAssignable)
	FOnGameReset OnGameReset;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Public methods
	UFUNCTION(BlueprintCallable, Category = "Minimax")
	void PlacePiece(int32 index);

	UFUNCTION(BlueprintCallable, Category = "Minimax")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "Minimax")
	int32 Win() const;
	int32 Minimax(int32 player);
	int32 ComputerMove();

	UFUNCTION(BlueprintCallable, Category = "Minimax")
	int32 PlayerMove(int32 location);
	UFUNCTION(BlueprintCallable, Category = "Minimax")
	void ResetGame();

	// Public properties
	UPROPERTY(BlueprintReadOnly, Category = "Minimax")
	int32 turns;
	int32 playerScore;
	UPROPERTY(BlueprintReadOnly, Category = "Minimax")
	int32 numOfGames;
	UPROPERTY(BlueprintReadOnly, Category = "Minimax")
	int32 computerScore;

private:
	// Board state
	TArray<int32> board;
};
