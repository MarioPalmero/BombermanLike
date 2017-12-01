// - Mario Palmero [2017], zlib/libpng licensed.

#include "Controllers/Public/MatchPlayerController.h"
#include "ConstructorHelpers.h"
#include "Pawns/Public/BombermanPawn.h"
#include "UI/Widgets/Public/MenuUserWidget.h"

AMatchPlayerController::AMatchPlayerController() : Super(),
	m_movementInput(FVector::ZeroVector),
	m_bWalkUpPressed(false),
	m_bWalkDownPressed(false),
	m_bWalkLeftPressed(false),
	m_bWalkRightPressed(false),
	m_PlaceBombPressed(false)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> matchWidgetLoader(TEXT("WidgetBlueprint'/Game/UI/Widgets/BP_MatchTimer.BP_MatchTimer_C'"));
	if (matchWidgetLoader.Class != nullptr)
		m_matchWidgetClass = matchWidgetLoader.Class;

	// Set the controller to tick every frame
	PrimaryActorTick.bCanEverTick = true;	
}


void AMatchPlayerController::ShowCountdown(int second)
{

	if (m_matchWidgetClass != nullptr && m_matchWidget == nullptr)
		m_matchWidget = CreateWidget<UMenuUserWidget>(GetWorld(), m_matchWidgetClass);

	if (m_matchWidget != nullptr)
	{
		m_matchWidget->AddToViewport();
		m_matchWidget->StartCountdown(second);
	}
}

void AMatchPlayerController::RemoveCountdown()
{
	if (m_matchWidget != nullptr)
	{
		m_matchWidget->RemoveFromViewport();
		m_matchWidget = nullptr;
	}
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
		pawn->Move(m_movementInput * DeltaTime * pawn->GetCurrentSpeed());
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
	InputComponent->BindAction(*("PlaceBomb" + sufix), IE_Pressed, this, &AMatchPlayerController::PlaceBombPressed);
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

void AMatchPlayerController::PlaceBombPressed()
{
	m_PlaceBombPressed = true;
}

void AMatchPlayerController::PlaceBombReleased()
{
	if (m_PlaceBombPressed)
	{
		ABombermanPawn* pawn = Cast<ABombermanPawn>(GetPawn());
		if (pawn != nullptr)
		{
			pawn->PlaceBomb();
		}
	}
	m_PlaceBombPressed = false;
}
