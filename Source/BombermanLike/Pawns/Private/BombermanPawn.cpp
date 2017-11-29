// - Mario Palmero [2017], zlib/libpng licensed.

#include "Pawns/Public/BombermanPawn.h"
#include "ConstructorHelpers.h"
#include "Engine/CollisionProfile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Gameplay/Components/Damageable/Public/DamageableComponent.h"
#include "Gameplay/Components/Explodable/Public/ExplodableComponent.h"
#include "Map/Public/MapManager.h"

ABombermanPawn::ABombermanPawn() : Super(),
	BaseBombAmount(1),
	Speed(10.0f)
{
 	// Set this pawn to call Tick() every frame. 
	PrimaryActorTick.bCanEverTick = true;

	// Collision
	m_collisionComponent = CreateDefaultSubobject<USphereComponent>("Collision");
	m_collisionComponent->InitSphereRadius(35.0f);
	m_collisionComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	m_collisionComponent->CanCharacterStepUpOn = ECB_No;
	m_collisionComponent->bShouldUpdatePhysicsVolume = true;
	m_collisionComponent->SetCanEverAffectNavigation(false);
	m_collisionComponent->bDynamicObstacle = true;

	RootComponent = m_collisionComponent;

	// Movement
	m_movementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>("Movement");
	m_movementComponent->UpdatedComponent = m_collisionComponent;

	// Damage
	DamageableComponent = CreateDefaultSubobject<UDamageableComponent>("Damageable");

	//Bomb
	static ConstructorHelpers::FObjectFinder<UBlueprint> bombObject(TEXT("Blueprint'/Game/Gameplay/Items/Blueprints/BP_Bomb.BP_Bomb'"));
	if (bombObject.Object != nullptr)
		BombClass = bombObject.Object->GeneratedClass;
}

void ABombermanPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABombermanPawn::BeginPlay()
{
	Super::BeginPlay();

	m_currentBombsMax = BaseBombAmount;
	m_currentBombsLeft = m_currentBombsMax;
		
}

void ABombermanPawn::Move(FVector movementAmount)
{
	AddMovementInput(movementAmount.GetSafeNormal(), movementAmount.Size());
}

void ABombermanPawn::PlaceBomb()
{
	// Checking if we can place a bomb
	if (m_currentBombsLeft > 0)
	{
		FVector2D bombCoordinates = AMapManager::GetInstance()->GetCoordinatesByLocation(GetActorLocation());
		if (AMapManager::GetInstance()->GetCellTypeByCoordinates(bombCoordinates.X, bombCoordinates.Y) == EMapCellType::Empty)
		{
			// Spawn bomb
			AActor* bomb = GetWorld()->SpawnActor<AActor>(BombClass);
			bomb->SetActorLocation(AMapManager::GetInstance()->GetTilePosition(bombCoordinates.X, bombCoordinates.Y));

			UExplodableComponent* explodable = Cast<UExplodableComponent>(bomb->GetComponentByClass(UExplodableComponent::StaticClass()));
			if (explodable != nullptr)
			{
				explodable->InitiateCountdown();
				explodable->OnExplosion.AddDynamic(this, &ABombermanPawn::RecoverBomb);
			}
			// Reduce number of bombs
			--m_currentBombsLeft;
		}
	}
}

void ABombermanPawn::IncreaseMaxNumberOFBombs(int amount)
{
	++m_currentBombsMax;
	++m_currentBombsLeft;
}

void ABombermanPawn::RecoverBomb(UExplodableComponent* explodable)
{
	if (explodable->OnExplosion.IsBound())
	{
		explodable->OnExplosion.RemoveDynamic(this, &ABombermanPawn::RecoverBomb);
		explodable->GetOwner()->Destroy();
	}

	m_currentBombsLeft = FMath::Min(m_currentBombsMax, m_currentBombsLeft + 1);
}

void ABombermanPawn::ResetMaxBombs()
{
	m_currentBombsLeft = BaseBombAmount;
	m_currentBombsMax = BaseBombAmount;
}