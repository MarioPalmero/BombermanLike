// - Mario Palmero [2017], zlib/libpng licensed.

#include "Controllers/Public/MatchPlayerController.h"
#include "Pawns/Public/BombermanPawn.h"

AMatchPlayerController::AMatchPlayerController() : Super(),
	m_movementInput(FVector::ZeroVector)
{
	// Set the controller to tick every frame
	PrimaryActorTick.bCanEverTick = true;
}

void AMatchPlayerController::Tick(float DeltaTime)
{
	if (m_bWalkUpPressed)
		m_movementInput.Y -= 1.0f;
	if (m_bWalkDownPressed)
		m_movementInput.Y += 1.0f;
	if (m_bWalkLeftPressed)
		m_movementInput.X -= 1.0f;
	if (m_bWalkRightPressed)
		m_movementInput.X += 1.0f;


	ABombermanPawn* pawn = Cast<ABombermanPawn>(GetPawn());
	if (pawn != nullptr)
	{
		pawn->Move(m_movementInput * DeltaTime * pawn->Speed);
	}
	m_movementInput = FVector::ZeroVector;
}

void AMatchPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Check if PlayerInputComponent is valid (not NULL)
	check(PlayerInput);

	FString sufix = FString::FromInt(GetLocalPlayer()->GetControllerId() + 1);
	// Bind buttons to actions
	InputComponent->BindAction(*("WalkUp" + sufix), IE_Pressed, this, &AMatchPlayerController::WalkUpPressed);
	InputComponent->BindAction(*("WalkUp" + sufix), IE_Released, this, &AMatchPlayerController::WalkUpReleased);
	InputComponent->BindAction(*("WalkDown" + sufix), IE_Pressed, this, &AMatchPlayerController::WalkDownPressed);
	InputComponent->BindAction(*("WalkDown" + sufix), IE_Released, this, &AMatchPlayerController::WalkDownReleased);
	InputComponent->BindAction(*("WalkLeft" + sufix), IE_Pressed, this, &AMatchPlayerController::WalkLeftPressed);
	InputComponent->BindAction(*("WalkLeft" + sufix), IE_Released, this, &AMatchPlayerController::WalkLeftReleased);
	InputComponent->BindAction(*("WalkRight" + sufix), IE_Pressed, this, &AMatchPlayerController::WalkRightPressed);
	InputComponent->BindAction(*("WalkRight" + sufix), IE_Released, this, &AMatchPlayerController::WalkRightReleased);
	InputComponent->BindAction(*("PlaceBomb" + sufix), IE_Released, this, &AMatchPlayerController::PlaceBombReleased);
}

void AMatchPlayerController::WalkUpPressed()
{
	m_bWalkUpPressed = true;
}

void AMatchPlayerController::WalkUpReleased()
{
	m_bWalkUpPressed = false;
}

void AMatchPlayerController::WalkDownPressed()
{
	m_bWalkDownPressed = true;
}

void AMatchPlayerController::WalkDownReleased()
{
	m_bWalkDownPressed = false;
}

void AMatchPlayerController::WalkLeftPressed()
{
	m_bWalkLeftPressed = true;
}

void AMatchPlayerController::WalkLeftReleased()
{
	m_bWalkLeftPressed = false;
}

void AMatchPlayerController::WalkRightPressed()
{
	m_bWalkRightPressed = true;
}

void AMatchPlayerController::WalkRightReleased()
{
	m_bWalkRightPressed = false;
}

void AMatchPlayerController::PlaceBombReleased()
{
	ABombermanPawn* pawn = Cast<ABombermanPawn>(GetPawn());
	if (pawn != nullptr)
	{
		pawn->PlaceBomb();
	}
}
