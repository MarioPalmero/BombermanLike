// - Mario Palmero [2017], zlib/libpng licensed.

#include "Pawns/Public/BombermanPawn.h"
#include "Engine/CollisionProfile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Gameplay/Components/Damageable/Public/DamageableComponent.h"


ABombermanPawn::ABombermanPawn() : Super(),
	Speed(10.0f)
{
 	// Set this pawn to call Tick() every frame. 
	PrimaryActorTick.bCanEverTick = true;

	m_collisionComponent = CreateDefaultSubobject<USphereComponent>("Collision");
	m_collisionComponent->InitSphereRadius(35.0f);
	m_collisionComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	m_collisionComponent->CanCharacterStepUpOn = ECB_No;
	m_collisionComponent->bShouldUpdatePhysicsVolume = true;
	m_collisionComponent->SetCanEverAffectNavigation(false);
	m_collisionComponent->bDynamicObstacle = true;

	RootComponent = m_collisionComponent;

	m_movementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>("Movement");
	m_movementComponent->UpdatedComponent = m_collisionComponent;

	DamageableComponent = CreateDefaultSubobject<UDamageableComponent>("Damageable");
}

void ABombermanPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABombermanPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABombermanPawn::Move(FVector movementAmount)
{
	AddMovementInput(movementAmount.GetSafeNormal(), movementAmount.Size());
}


