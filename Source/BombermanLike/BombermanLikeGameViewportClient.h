// - Mario Palmero [2017], zlib/libpng licensed.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "BombermanLikeGameViewportClient.generated.h"

/*! \brief Class the manages the input for different controllers
* Class the manages the input for different controllers overriden
* to manage multiple controllers on keyboard
*/
UCLASS()
class BOMBERMANLIKE_API UBombermanLikeGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
		virtual bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed = 1.f, bool bGamepad = false) override;	//<! Overriding the general input of keys for controllers
};
