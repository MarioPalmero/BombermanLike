// - Mario Palmero [2017], zlib/libpng licensed.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UIPlayerController.generated.h"

/////////////////////////////////////////////////
///FORWARD DECLARATIONS
/////////////////////////////////////////////////
class UMenuUserWidget;

/*! \brief Controller for the UI part of the game (Splash, Character Selection and EndMatch)
 * 
 * This controller has functionality for the UI sections of the game and has no AI counterpart.
 * It's intended for controlling the character selections and skipping the different UI screens.
 */
UCLASS()
class BOMBERMANLIKE_API AUIPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AUIPlayerController();		//<! Constructor

	/*! \brief Starts the widget and control over the splash Screen
	 *
	 *	Creates the widget for the splash Screen, and starts the transition on it 
	 */
	UFUNCTION(BlueprintCallable, Category = MenuState)
	void StartSplashScreen();

	/*! \brief Ends the widget and control over the splash
	*
	*	Removes and frees the widget for the splash screen
	*/
	UFUNCTION(BlueprintCallable, Category = MenuState)
		void EndSplashScreen();

	/*! \brief Starts the widget and control over the character selection
	*
	*	Creates the widget for the character selection, and starts the transition on it
	*/
	UFUNCTION(BlueprintCallable, Category = MenuState)
	void StartCharacterSelectionScreen();

	/*! \brief Ends the widget and control over the character selection
	*
	*	Removes and frees the widget for the character selection
	*/
	UFUNCTION(BlueprintCallable, Category = MenuState)
	void EndCharacterSelectionScreen();

	/*! \brief Starts the widget and control over the end match screen
	*
	*	Creates the widget for the end match Screen, and starts the transition on it
	*/
	UFUNCTION(BlueprintCallable, Category = MenuState)
	void StartEndMatchScreen();

	/*! \brief Ends the widget and control over the end match
	*
	*	Removes and frees the widget for the end match
	*/
	UFUNCTION(BlueprintCallable, Category = MenuState)
		void EndEndMatchScreen();

protected:
	virtual void BeginPlay() override;				//<! Called when the game starts or when spawned
	virtual void SetupInputComponent() override;	//<! Method for setting up the key bindings

private:
	UFUNCTION()
	void AnyKeyReleased();		//<! Method that handles any key being pressed
	UFUNCTION()
	void Continue();			//<! Method to accept or continue
	UFUNCTION()
	void CreatePlayer2();		//<! Creates the second player

	TSubclassOf<UUserWidget> m_splashWidgetClass;				//<! Class for the widget that handles the splash screen
	TSubclassOf<UUserWidget> m_characterSelectionWidgetClass;	//<! Class for the widget that handles the character selection
	TSubclassOf<UUserWidget> m_endMatchWidgetClass;				//<! Class for the widget that handles the end match screen

	UMenuUserWidget* m_splashWidget;					//<! Widget that handles the splash screen
	UMenuUserWidget* m_characterSelectionWidget;		//<! Widget that manages the character selection
	UMenuUserWidget* m_endMatchWidget;					//<! Widget that handles the end match screen

};
