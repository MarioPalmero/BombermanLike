// - Mario Palmero [2017], zlib/libpng licensed.

#include "Controllers/Public/MatchPlayerController.h"

void AMatchPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Check if PlayerInputComponent is valid (not NULL)
	check(PlayerInput);

	//FString sufix = FString::FromInt(GetLocalPlayer()->GetControllerId());
	// Bind buttons to actions
}
