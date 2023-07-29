#include "TTTMinimax.h"

ATTTMinimax::ATTTMinimax()
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

    // Initialize
    turns = 0;
    playerScore = 0;
    numOfGames = 0;
    computerScore = 0;
    board.Init(0, 9);
}

void ATTTMinimax::BeginPlay()
{
	Super::BeginPlay();
}

void ATTTMinimax::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATTTMinimax::PlacePiece(int32 index)
{
    // Broadcast the AI's move to Blueprint
    OnPiecePlaced.Broadcast(index);
}

void ATTTMinimax::StartGame()
{
    UE_LOG(LogTemp, Warning, TEXT("\n-----------Tic Tac Toe-----------\n"));
    board.Init(0, 9); //Initialize the board to 0s

    turns = 0;
    UE_LOG(LogTemp, Warning, TEXT("\n\nPlay your first place:\n"));
    //Player = -1, Computer = 1
}

int32 ATTTMinimax::Win() const
{
    TArray<TArray<int32>> wins{
        {0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}
    };

    for (const TArray<int32>& win : wins)
    {
        if (board[win[0]] != 0 && board[win[0]] == board[win[1]] && board[win[1]] == board[win[2]])
        {
            return board[win[2]]; // 1 if AI wins or -1 if the player wins
        }
    }

    return 0; // draw
}

int32 ATTTMinimax::Minimax(int32 player)
{
    int32 winner = Win();
    if (winner != 0)
    {
        return winner * player;
    }

    int32 move = -1;
    int32 score = -2;

    for (int32 i = 0; i < 9; i++)
    {
        if (board[i] == 0)
        {
            board[i] = player;
            int32 thisScore = -Minimax(player * -1);
            if (thisScore > score)
            {
                score = thisScore;
                move = i;
            }
            board[i] = 0;
        }
    }

    if (move == -1)
    {
        return 0;
    }

    return score;
}

int32 ATTTMinimax::ComputerMove()
{
    int32 move = -1;
    int32 score = -2;

    for (int32 i = 0; i < 9; ++i)
    {
        if (board[i] == 0)
        {
            board[i] = 1;
            int32 tempScore = -Minimax(-1);
            board[i] = 0;
            if (tempScore > score)
            {
                score = tempScore;
                move = i;
            }
        }
    }

    return move;
}

int32 ATTTMinimax::PlayerMove(int32 location)
{
    // Check if the location is valid and unoccupied
    if (location >= 0 && location < 9 && board[location] == 0)
    {
        board[location] = -1; // -1 for player's move
        turns++;

        // Check for win condition after player move
        //if (Win() != 0)
        //{
        //    playerScore++;
        //    UE_LOG(LogTemp, Warning, TEXT("You win")); // Player wins
        //    return -1;
        //}

        // If game is still going on and it's not a full board, AI should make a move
        if (turns < 9)
        {
            int32 aiMove = ComputerMove();
            board[aiMove] = 1; // 1 for AI's move
            turns++;

            // Broadcast the AI's move to Blueprint
            PlacePiece(aiMove);

            // Check for win condition after AI move
            if (Win() == 1)
            {
                computerScore++;
                UE_LOG(LogTemp, Warning, TEXT("You lose")); // AI wins
                return 1;
            }
        }

        // If no winner and the board is full, it's a draw
        if (turns == 9 && Win() == 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("It's a draw"));
            return 0;
        }
    }

    // If the game is still ongoing, return -1
    return -1;
}


void ATTTMinimax::ResetGame()
{
    // Resetting the board
    board.Init(0, 9);

    // Resetting the turns
    turns = 0;

    // You might also want to reset the game state like who's turn it is, etc.
    // Your logic might vary based on how you have structured your game

    UE_LOG(LogTemp, Warning, TEXT("Game has been reset."));

    // Call the delegate
    OnGameReset.Broadcast(computerScore, ++numOfGames);
    StartGame();
}



