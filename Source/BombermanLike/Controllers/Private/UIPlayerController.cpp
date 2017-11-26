// - Mario Palmero [2017], zlib/libpng licensed.

#include "Controllers/Public/UIPlayerController.h"


void AUIPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Check if PlayerInputComponent is valid (not NULL)
	check(PlayerInput);

	FString sufix = FString::FromInt(GetLocalPlayer()->GetControllerId() + 1);
	// Bind buttons to actions
	InputComponent->BindAction(*FString("Continue" + sufix), IE_Pressed, this, &AUIPlayerController::Continue);
}

void AUIPlayerController::Continue()
{

}
