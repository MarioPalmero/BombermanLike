// - Mario Palmero [2017], zlib/libpng licensed.

#include "Controllers/Public/UIPlayerController.h"
#include "BombermanLike.h"
#include "BombermanLikeGameModeBase.h"
#include "ConstructorHelpers.h"
#include "UI/Widgets/Public/MenuUserWidget.h"

AUIPlayerController::AUIPlayerController() : Super(),
	m_splashWidget(nullptr),
	m_characterSelectionWidget(nullptr),
	m_endMatchWidget(nullptr)
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

void AUIPlayerController::EndEndMatchScreen()
{
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
	if (m_splashWidgetClass != nullptr && m_splashWidget == nullptr)
		m_splashWidget = CreateWidget<UMenuUserWidget>(GetWorld(), m_splashWidgetClass);

	if (m_splashWidget != nullptr)
	{
		m_splashWidget->AddToViewport();
		m_splashWidget->StartSplashScreen();
	}
}

void AUIPlayerController::EndSplashScreen()
{
	if (m_splashWidget != nullptr)
	{
		if (m_splashWidget->OnEndSplashScreenFinished.IsBound())
		{
			ABombermanLikeGameModeBase* gm = Cast<ABombermanLikeGameModeBase>(GetWorld()->GetAuthGameMode());
			if (gm != nullptr)
				m_splashWidget->OnEndSplashScreenFinished.RemoveDynamic(gm, &ABombermanLikeGameModeBase::NotifyEndSplash);
		}
		m_splashWidget->RemoveFromViewport();
	}
}

void AUIPlayerController::StartCharacterSelectionScreen()
{

	if (m_characterSelectionWidgetClass != nullptr && m_characterSelectionWidget == nullptr)
		m_characterSelectionWidget = CreateWidget<UMenuUserWidget>(GetWorld(), m_characterSelectionWidgetClass);

	if (m_characterSelectionWidget != nullptr)
	{
		m_characterSelectionWidget->AddToViewport();
		m_characterSelectionWidget->StartCharacterSelection();
	}
}

void AUIPlayerController::EndCharacterSelectionScreen()
{
	if (m_characterSelectionWidget != nullptr)
	{
		if (m_characterSelectionWidget->OnEndCharacterSelectionFinished.IsBound())
		{
			ABombermanLikeGameModeBase* gm = Cast<ABombermanLikeGameModeBase>(GetWorld()->GetAuthGameMode());
			if (gm != nullptr)
				m_characterSelectionWidget->OnEndCharacterSelectionFinished.RemoveDynamic(gm, &ABombermanLikeGameModeBase::NotifyEndCharacterSelection);
		}
		m_characterSelectionWidget->RemoveFromViewport();
	}
}

void AUIPlayerController::StartEndMatchScreen()
{

}

void AUIPlayerController::AnyKeyReleased()
{
	ABombermanLikeGameModeBase* gm = Cast<ABombermanLikeGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gm != nullptr)
	{
		EGameModeStates state = gm->GetCurrentState();
		if (state == EGameModeStates::Splash)
		{
			if(!m_splashWidget->OnEndSplashScreenFinished.IsBound())
				m_splashWidget->OnEndSplashScreenFinished.AddDynamic(gm, &ABombermanLikeGameModeBase::NotifyEndSplash);
			m_splashWidget->EndSplashScreen();
		}
	}
}

void AUIPlayerController::Continue()
{
	ABombermanLikeGameModeBase* gm = Cast<ABombermanLikeGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gm != nullptr)
	{
		EGameModeStates state = gm->GetCurrentState();
		if (state == EGameModeStates::CharacterSelection)
		{
			if (!m_characterSelectionWidget->OnEndCharacterSelectionFinished.IsBound())
				m_characterSelectionWidget->OnEndCharacterSelectionFinished.AddDynamic(gm, &ABombermanLikeGameModeBase::NotifyEndCharacterSelection);
			m_characterSelectionWidget->EndCharacterSelection();
		}
	}
}
