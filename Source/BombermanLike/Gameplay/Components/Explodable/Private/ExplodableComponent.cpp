// - Mario Palmero [2017], zlib/libpng licensed.

#include "Gameplay/Components/Explodable/Public/ExplodableComponent.h"
#include "ConstructorHelpers.h"
#include "Map/Public/MapManager.h"
#include "Gameplay/Components/Damageable/Public/DamageableComponent.h"

UExplodableComponent::UExplodableComponent() : Super(),
	BaseTimer(2.0f),
	BaseDamage(1.0f),
	BaseFlameLength(3),
	m_currentTimer(-1.0f),
	m_currentFlameLength(BaseFlameLength)
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> flameObject(TEXT("Blueprint'/Game/Gameplay/Items/Blueprints/BP_Flame.BP_Flame'"));
	if (flameObject.Object != nullptr)
		FlameClass = flameObject.Object->GeneratedClass;

	PrimaryComponentTick.bCanEverTick = true;
}

float UExplodableComponent::GetCurrenFlameLength()
{
	return m_currentFlameLength;
}

void UExplodableComponent::IncreaseFlameAmount(int lengthIncrement)
{
	m_currentFlameLength += lengthIncrement;
}

void UExplodableComponent::InitiateCountdown()
{
	m_currentTimer = BaseTimer;
	
}

void UExplodableComponent::Detonate()
{
	UDamageableComponent* damageable = Cast<UDamageableComponent>(GetOwner()->GetComponentByClass(UDamageableComponent::StaticClass()));
	if (damageable != nullptr)
		damageable->DestroyComponent();

	TArray<FVector> fireLocations = AMapManager::GetInstance()->GetExplosionLocations(GetOwner()->GetActorLocation(), m_currentFlameLength);

	for (auto location : fireLocations)
	{
		// Spawn flame
		AActor* flame = GetWorld()->SpawnActor<AActor>(FlameClass);
		flame->SetActorLocation(location);
	}
	
	OnExplosion.Broadcast(this);
}


void UExplodableComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,	FActorComponentTickFunction * ThisTickFunction)
{
	if (m_currentTimer > 0.0f)
	{
		m_currentTimer -= DeltaTime;
		if (m_currentTimer <= 0.0f)
			Detonate();
	}
}
