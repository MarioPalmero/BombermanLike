// - Mario Palmero [2017], zlib/libpng licensed.

#include "Controllers/Public/UIPlayerController.h"
#include "BombermanLike.h"
#include "BombermanLikeGameModeBase.h"
#include "ConstructorHelpers.h"
#include "UI/Widgets/Public/MenuUserWidget.h"
#include "Kismet/GameplayStatics.h"

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

void AUIPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AUIPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Check if PlayerInputComponent is valid (not NULL)
	check(PlayerInput);

	// Bind buttons to actions
	InputComponent->BindAction(*FString("Continue1"), IE_Released, this, &AUIPlayerController::Continue);
	InputComponent->BindAction(*FString("Continue2"), IE_Released, this, &AUIPlayerController::CreatePlayer2);
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
		m_splashWidget = nullptr;
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
		m_characterSelectionWidget = nullptr;
	}
}

void AUIPlayerController::StartEndMatchScreen()
{
	if (m_endMatchWidgetClass != nullptr && m_endMatchWidget == nullptr)
		m_endMatchWidget  = CreateWidget<UMenuUserWidget>(GetWorld(), m_endMatchWidgetClass);

	if (m_endMatchWidget != nullptr)
	{
		m_endMatchWidget->AddToViewport();
		m_endMatchWidget->StartEndMatch();
	}
}

void AUIPlayerController::EndEndMatchScreen()
{
	if (m_endMatchWidget != nullptr)
	{
		if (m_endMatchWidget->OnEndEndMatchFinished.IsBound())
		{
			ABombermanLikeGameModeBase* gm = Cast<ABombermanLikeGameModeBase>(GetWorld()->GetAuthGameMode());
			if (gm != nullptr)
				m_endMatchWidget->OnEndEndMatchFinished.RemoveDynamic(gm, &ABombermanLikeGameModeBase::NotifyEndEndMatch);
		}
		m_endMatchWidget->RemoveFromViewport();
		m_endMatchWidget = nullptr;
	}
}

void AUIPlayerController::Continue()
{
	ABombermanLikeGameModeBase* gm = Cast<ABombermanLikeGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gm != nullptr)
	{
		EGameModeStates state = gm->GetCurrentState();
		if (state == EGameModeStates::CharacterSelection && m_characterSelectionWidget != nullptr)
		{
			if (!m_characterSelectionWidget->OnEndCharacterSelectionFinished.IsBound())
				m_characterSelectionWidget->OnEndCharacterSelectionFinished.AddDynamic(gm, &ABombermanLikeGameModeBase::NotifyEndCharacterSelection);
			m_characterSelectionWidget->EndCharacterSelection();
		}
		else if (state == EGameModeStates::Splash && m_splashWidget != nullptr)
		{
			if (!m_splashWidget->OnEndSplashScreenFinished.IsBound())
				m_splashWidget->OnEndSplashScreenFinished.AddDynamic(gm, &ABombermanLikeGameModeBase::NotifyEndSplash);
			m_splashWidget->EndSplashScreen();
		}
		else if (state == EGameModeStates::EndMatch && m_endMatchWidget != nullptr)
		{
			if (!m_endMatchWidget->OnEndEndMatchFinished.IsBound())
				m_endMatchWidget->OnEndEndMatchFinished.AddDynamic(gm, &ABombermanLikeGameModeBase::NotifyEndEndMatch);
			m_endMatchWidget->EndEndMatch();
		}
	}
}

void AUIPlayerController::CreatePlayer2()
{
	ABombermanLikeGameModeBase* gm = Cast<ABombermanLikeGameModeBase>(GetWorld()->GetAuthGameMode());

	if (gm != nullptr)
	{
		if(gm->NumPlayers == 1)
			UGameplayStatics::CreatePlayer(GetWorld(), 1);
		gm->NumPlayers = 2;
	}
}