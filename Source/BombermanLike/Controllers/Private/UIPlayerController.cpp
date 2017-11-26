// - Mario Palmero [2017], zlib/libpng licensed.

#include "Controllers/Public/UIPlayerController.h"
#include "BombermanLike.h"
#include "BombermanLikeGameModeBase.h"
#include "ConstructorHelpers.h"
#include "UI/Widgets/Public/MenuUserWidget.h"

AUIPlayerController::AUIPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> splashWidgetLoader(TEXT("UserWidget'/Game/UI/Widgets/BP_SplashScreenWidget.BP_SplashScreenWidget_C'"));
	if (splashWidgetLoader.Class != nullptr)
		m_splashWidgetClass = splashWidgetLoader.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> characterSelectionWidgetLoader(TEXT("UserWidget'/Game/UI/Widgets/BP_CharacterSelectionWidget.BP_CharacterSelectionWidget_C'"));
	if (characterSelectionWidgetLoader.Class != nullptr)
		m_characterSelectionWidgetClass = characterSelectionWidgetLoader.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> endMatchWidgetLoader(TEXT("UserWidget'/Game/UI/Widgets/BP_EndMatchWidget.BP_EndMatchWidget_C'"));
	if (endMatchWidgetLoader.Class != nullptr)
		m_endMatchWidgetClass = endMatchWidgetLoader.Class;

}

void AUIPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AUIPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Check if PlayerInputComponent is valid (not NULL)
	check(PlayerInput);

	// Binding the any key action
	InputComponent->BindAction("AnyKey", IE_Released, this, &AUIPlayerController::AnyKeyReleased);

	FString sufix = FString::FromInt(GetLocalPlayer()->GetControllerId() + 1);
	// Bind buttons to actions
	InputComponent->BindAction(*FString("Continue" + sufix), IE_Released, this, &AUIPlayerController::Continue);
}

void AUIPlayerController::StartSplashScreen()
{
	if (m_splashWidgetClass != nullptr)
	{
		m_splashWidget = CreateWidget<UMenuUserWidget>(GetWorld(), m_splashWidgetClass);
		if (m_splashWidget != nullptr)
		{
			m_splashWidget->AddToViewport();
			m_splashWidget->SetKeyboardFocus();
		}
	}
}

void AUIPlayerController::StartCharacterSelectionScreen()
{

}

void AUIPlayerController::StartEndMatchScreen()
{

}

void AUIPlayerController::AnyKeyReleased()
{

}

void AUIPlayerController::Continue()
{

}
