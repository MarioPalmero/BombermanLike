// - Mario Palmero [2017], zlib/libpng licensed.

#include "Gameplay/Components/Damageable/Public/DamageableComponent.h"

UDamageableComponent::UDamageableComponent() : Super(),
	MaxHealth(1.0f),
	m_currentHealth(1.0f)
{

}

float UDamageableComponent::GetCurrentHealth()
{
	return m_currentHealth;
}

void UDamageableComponent::Damage(float damageAmount)
{
	bool bNotifyDeath = m_currentHealth > 0.0f && m_currentHealth - damageAmount <= 0.0f;

	if (MaxHealth >= 0.0f)
		m_currentHealth = FMath::Clamp(m_currentHealth - damageAmount, 0.0f, MaxHealth);
	else
		m_currentHealth = FMath::Max(m_currentHealth - damageAmount, 0.0f);

	if (bNotifyDeath)
		OnDeath.Broadcast();
}

void UDamageableComponent::Heal(float damageAmount)
{
	bool bNotifyResurrection = m_currentHealth <= 0.0f && damageAmount > 0.0f;

	if (MaxHealth >= 0.0f)
		m_currentHealth = FMath::Clamp(m_currentHealth + damageAmount, 0.0f, MaxHealth);
	else
		m_currentHealth = FMath::Max(m_currentHealth + damageAmount, 0.0f);

	if (bNotifyResurrection)
		OnResurrection.Broadcast();
}
