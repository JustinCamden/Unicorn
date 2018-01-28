// Copyright 2018 Team Unicorn All Rights Reserved

#include "UnicornAIController.h"
#include "VRBaseCharacter.h"

FVector AUnicornAIController::GetFocalPointOnActor(const AActor* Actor) const
{
	const AVRBaseCharacter* VRChar = Cast<const AVRBaseCharacter>(Actor);
	if (VRChar)
	{
		return VRChar->GetVRLocation();
	}
	else
	{
		return Super::GetFocalPointOnActor(Actor);
	}
}