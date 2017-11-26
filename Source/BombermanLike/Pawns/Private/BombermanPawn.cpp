// - Mario Palmero [2017], zlib/libpng licensed.

#include "Pawns/Public/BombermanPawn.h"


// Sets default values
ABombermanPawn::ABombermanPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABombermanPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABombermanPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABombermanPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

