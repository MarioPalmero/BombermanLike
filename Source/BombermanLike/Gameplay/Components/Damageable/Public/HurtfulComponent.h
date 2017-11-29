// - Mario Palmero [2017], zlib/libpng licensed.

#pragma once

#include "BombermanLike.h"
#include "HurtfulComponent.generated.h"


/*! \brief Component for those that can hurt or do damage
 *
 * Component for those that can hurt or do damage
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UHurtfulComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = Damage)
	float GetDamage() const;					//<! Returns the amount of damage that applies
	UFUNCTION(BlueprintCallable, Category = Damage)
	void SetDamage(float baseAmount);		//<! Sets the amount of damage this component can do

	UHurtfulComponent();	//<! Constructor
private:
	float m_damage;
};
