// - Mario Palmero [2017], zlib/libpng licensed.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UIPlayerController.generated.h"

/*! \brief Controller for the UI part of the game (Splash, Character Selection and EndMatch)
 * 
 * This controller has functionality for the UI sections of the game and has no AI counterpart.
 * It's intended for controlling the character selections and skipping the different UI screens.
 */
UCLASS()
class BOMBERMANLIKE_API AUIPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;	//<! Method for setting up the key bindings
private:
	UFUNCTION()
	void Continue();
};
