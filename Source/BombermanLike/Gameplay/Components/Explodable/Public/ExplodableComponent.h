// - Mario Palmero [2017], zlib/libpng licensed.

#pragma once

#include "BombermanLike.h"
#include "ExplodableComponent.generated.h"

/////////////////////////////////////////////////
///DELEGATES
/////////////////////////////////////////////////
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExplosion, UExplodableComponent*, bomb);		//<! Delegate type creation for explosion event

/*! \brief Component for those that can explode
 *
 * Component that handles actors exploding
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UExplodableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/*! \brief Indicates the base timer
	*
	* Sets the basic time for exploding
	* If -1 it will wait till manual detonation
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Explosion)
	float BaseTimer;

	/*! \brief Indicates the base damage
	*
	* Sets the basic damage for explosions
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Explosion)
	float BaseDamage;

	/*! \brief Indicates the base flame length
	*
	* Sets the basic flame for explosions
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Explosion)
	int FlameLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Explosion)
	UClass* FlameClass;		//<! Class for the bomb
	
	/*! \brief Initiates the inminent explosion
	*
	* Prepares the component for the countdown and the explosion
	*/
	UFUNCTION(BlueprintCallable, Category = Explosion)
	void InitiateCountdown();

	/*! \brief Detonates the explosion
	*
	* Detonates explosion
	*/
	UFUNCTION(BlueprintCallable, Category = Explosion)
	void Detonate();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Explosion)
	FOnExplosion OnExplosion;			//<! Delegate to notify explosion

	UExplodableComponent();				//<! Constructor

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;	//<! Every frame method
private:
	float m_currentTimer;				//<! Current time before explosion
};
