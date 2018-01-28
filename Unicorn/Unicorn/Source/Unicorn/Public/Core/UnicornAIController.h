// Copyright 2018 Team Unicorn All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnicornAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNICORN_API  AUnicornAIController : public AAIController
{
	GENERATED_BODY()
	
	virtual FVector GetFocalPointOnActor(const AActor *Actor) const override;

	/**
	* Checks line to center and top of other actor
	* @param Other is the actor whose visibility is being checked.
	* @param ViewPoint is eye position visibility is being checked from.  If vect(0,0,0) passed in, uses current viewtarget's eye position.
	* @param bAlternateChecks used only in AIController implementation
	* @return true if controller's pawn can see Other actor.
	*/
	//virtual bool LineOfSightTo(const AActor* Other, FVector ViewPoint = FVector(ForceInit), bool bAlternateChecks = false) const override;
	//~ End AController Interface
};
