// - Mario Palmero [2017], zlib/libpng licensed.

#include "Gameplay/Components/Damageable/Public/HurtfulComponent.h"

UHurtfulComponent::UHurtfulComponent() : Super(),
	m_damage (1.0f)
{
}

float UHurtfulComponent::GetDamage() const
{
	return m_damage;
}

void UHurtfulComponent::SetDamage(float baseAmount)
{
	m_damage = baseAmount;
}
