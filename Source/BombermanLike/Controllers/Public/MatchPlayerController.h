// - Mario Palmero [2017], zlib/libpng licensed.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MatchPlayerController.generated.h"


/*! \brief Controller for the Match part of the game (suitable for 2P mode, two actors of this class will be spawned)
 *
 * This controller has functionality for the match: moving character, placing bombs and so.
 * It could have an AI counterpart.
 */
UCLASS()
class BOMBERMANLIKE_API AMatchPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;	//<! Method for setting up the key bindings
};
