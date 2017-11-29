// - Mario Palmero [2017], zlib/libpng licensed.

#pragma once

#include "BombermanLike.h"
#include "DamageableComponent.generated.h"


/////////////////////////////////////////////////
///DELEGATES
/////////////////////////////////////////////////
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);			//<! Delegate type creation for death event
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResurrection);	//<! Delegate type creation for resurrection event

/*! \brief Component for those that can be damaged and destroyed
 *
 * Component that handles actors being damaged and destroyed
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UDamageableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/*! \brief Indicates the MaxHealth for the owner
	 *
	 * Sets up a health cap. If -1 there will be no cap
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	float MaxHealth;

	/*! \brief Returns the current health of the owner
	 *
	 * Returns current health amount of this owner
	 */
	UFUNCTION(BlueprintCallable, Category = Damage)
	float GetCurrentHealth();

	/*! \brief Damages the owner
	*
	* Damages the owner a certain amount.
	* If this amount is higher than the current health
	* the death delegate will be broadcasted.
	*/
	UFUNCTION(BlueprintCallable, Category = Damage)
	void Damage(float damageAmount);

	/*! \brief Heals the owner
	*
	* Heals the owner a certain amount.
	* If this amount is higher than the max health
	* the healing will be capped
	*/
	UFUNCTION(BlueprintCallable, Category = Damage)
	void Heal(float damageAmount);

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Damage)
	FOnDeath OnDeath;					//<! Delegate to notify death
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Damage)
	FOnResurrection OnResurrection;		//<! Delegate to notify resurrection

	UDamageableComponent();				//<! Constructor
	
private:
	float m_currentHealth;				//<! Current life of the owner
};