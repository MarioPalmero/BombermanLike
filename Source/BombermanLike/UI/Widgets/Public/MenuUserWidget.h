// - Mario Palmero [2017], zlib/libpng licensed.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Controllers/Public/UIPlayerController.h"
#include "MenuUserWidget.generated.h"

/////////////////////////////////////////////////
/// DELEGATES
/////////////////////////////////////////////////

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndSplashScreenFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndCharacterSelectionFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndEndMatchFinished);

/*! \brief Widget of the menu interface
 * 
 * This widget will have some methods to connect the UI controller with Game FSM
 */
UCLASS()
class BOMBERMANLIKE_API UMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	/*! \brief Creates the transition to show the splash screen
	*
	* Function called to play the transition show the splash screen
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = MenuState)
	void StartSplashScreen();

	/*! \brief Creates the transition that ends splash screen
	*
	* Function called to play the transition that ends splash screen
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = MenuState)
	void EndSplashScreen();

	/*! \brief Creates the transition from previous screen to character selection
	 *
	 * Function called to play the transition from previous screen to character selection
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = MenuState)
	void StartCharacterSelection();

	/*! \brief Creates the transition from character selection to match
	 *
	 * Function called to play the transition from character selection screen to match
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = MenuState)
	void EndCharacterSelection();

	/*! \brief Creates the transition from match to end match
	 *
	 * Function called to play the transition from match to end match screen
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = MenuState)
	void StartEndMatch();

	/*! \brief Creates the transition from end match back to character selection
	 *
	 * Function called to play the transition from end match screen back to character selection screen
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = MenuState)
	void EndEndMatch();

	/*! \brief Function to get the UI Controller
	*
	* Function that returns the UI Controller associated to this widget
	*/
	UFUNCTION(BlueprintCallable, Category = Controller)
	AUIPlayerController* GetUIPlayerController();

	/*! \brief Function to set the UI Controller
	*
	* Function that sets the UI Controller associated to this widget
	*/
	UFUNCTION(BlueprintCallable, Category = Controller)
	void SetUIPlayerController(AUIPlayerController* controller);

	/////////////////////////////////////////////////
	/// DELEGATES
	/////////////////////////////////////////////////

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = MenuState)
	FOnEndSplashScreenFinished	OnEndSplashScreenFinished;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = MenuState)
	FOnEndCharacterSelectionFinished OnEndCharacterSelectionFinished;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = MenuState)
	FOnEndEndMatchFinished OnEndEndMatchFinished;


private:
	AUIPlayerController* m_UIController; //<! UI Controller associated to this widget
};
