// - Mario Palmero [2017], zlib/libpng licensed.

#include "BombermanLikeGameViewportClient.h"

bool UBombermanLikeGameViewportClient::InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	// Sending Key strokes to both controllers
	Super::InputKey(Viewport, 0, Key, EventType, AmountDepressed, bGamepad);
	return Super::InputKey(Viewport, 1, Key, EventType, AmountDepressed, bGamepad);
}
