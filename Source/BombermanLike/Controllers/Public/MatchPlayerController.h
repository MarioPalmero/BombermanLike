// - Mario Palmero [2017], zlib/libpng licensed.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MatchPlayerController.generated.h"

/////////////////////////////////////////////////
///FORWARD DECLARATIONS
/////////////////////////////////////////////////
class UMenuUserWidget;

/*! \brief Controller for the Match part of the game (suitable for 2P mode, two actors of this class will be spawned)
 *
 * This controller has functionality for the match: moving character, placing bombs and so.
 * It could have an AI counterpart.
 */
UCLASS()
class BOMBERMANLIKE_API AMatchPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = Match)
	void ShowCountdown(int second);				//<! Invokes the widget of the countdown

	UFUNCTION(BlueprintCallable, Category = Match)
	void RemoveCountdown();						//<! Removes the widget of the countdown

	AMatchPlayerController();	//<! Constructor

	virtual void Tick(float DeltaTime) override;	//<! Every frame method
protected:
	virtual void SetupInputComponent() override;	//<! Method for setting up the key bindings

private:
	UFUNCTION()
	void WalkUpPressed();				//<! Processess the input of the WalkUp action being pressed
	UFUNCTION()
	void WalkUpReleased();				//<! Processess the input of the WalkUp action being released
	UFUNCTION()
	void WalkDownPressed();			//<! Processess the input of the WalkDown action being pressed
	UFUNCTION()
	void WalkDownReleased();			//<! Processess the input of the WalkDown action being released
	UFUNCTION()
	void WalkLeftPressed();			//<! Processess the input of the WalkLeft action being pressed
	UFUNCTION()
	void WalkLeftReleased();			//<! Processess the input of the WalkLeft action being released
	UFUNCTION()
	void WalkRightPressed();			//<! Processess the input of the WalkRight action being pressed
	UFUNCTION()
	void WalkRightReleased();			//<! Processess the input of the WalkRight action being released
	UFUNCTION()
	void PlaceBombPressed();			//<! Processess the input of the PlaceBomb action being pressed
	UFUNCTION()
	void PlaceBombReleased();			//<! Processess the input of the PlaceBomb action being released

	FVector m_movementInput;	//<! Accumulates all the movement input
	bool m_bWalkUpPressed;		//<! Indicates if the key for WalkUp is pressed
	bool m_bWalkDownPressed;		//<! Indicates if the key for WalkDown is pressed
	bool m_bWalkLeftPressed;		//<! Indicates if the key for WalkLeft is pressed
	bool m_bWalkRightPressed;		//<! Indicates if the key for WalkRight is pressed
	bool m_PlaceBombPressed;		//<! Indicates if the key for Placing Bombs is pressed

	TSubclassOf<UUserWidget> m_matchWidgetClass;		//<! Class for the widget that handles the match countdown
	UMenuUserWidget* m_matchWidget;						//<! Widget that handles the countdown

};
