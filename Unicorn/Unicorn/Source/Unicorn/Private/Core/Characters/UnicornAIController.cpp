// Copyright 2018 Team Unicorn All Rights Reserved

#include "UnicornAIController.h"
#include "UnicornCharacter.h"

AUnicornAIController::AUnicornAIController(const FObjectInitializer& ObjectInitializer)
{
	VisionComponent = nullptr;
	VRAimLocationHeightMultiplier = 0.9f;
}

void AUnicornAIController::GetActorEyesViewPoint(FVector& out_Location, FRotator& out_Rotation) const
{
	// Vision component override
	if (VisionComponent)
	{
		FTransform VisionTransform = VisionComponent->GetComponentTransform();
		out_Location = VisionTransform.GetLocation();
		out_Rotation = VisionTransform.Rotator();
		return;
	}
	AUnicornCharacter* UnicornCharacter = Cast<AUnicornCharacter>(GetPawn());

	// Default vision component from Unicorn Character
	if (UnicornCharacter)
	{
		USceneComponent* CharVisionComp = UnicornCharacter->GetVisionComponent();
		if (CharVisionComp)
		{
			FTransform VisionTransform = CharVisionComp->GetComponentTransform();
			out_Location = VisionTransform.GetLocation();
			out_Rotation = VisionTransform.Rotator();
			return;
		}
	}

	return Super::GetActorEyesViewPoint(out_Location, out_Rotation);
}

FVector AUnicornAIController::GetAimLocationOnActor(AActor* Actor) const
{
	// If the target is a player pawn, then get the aim position based on the camera and ZOffset
	AVRBaseCharacter* VRCharacter = Cast<AVRBaseCharacter>(Actor);
	if (VRCharacter)
	{
		// Get the camera location
		const UCameraComponent* Camera = VRCharacter->VRReplicatedCamera;
		if (Camera != nullptr)
		{
			// Get the camera's initial location
			FVector AimLoc = Camera->GetRelativeTransform().GetLocation();

			// Multiply the Z by the multiplier
			AimLoc.Z = AimLoc.Z * VRAimLocationHeightMultiplier;
			AimLoc = Camera->GetOwner()->GetTransform().TransformPosition(AimLoc);
			return AimLoc;
		}
	}
	// Otherwise, if its an actor, aim at the center of their bounding box
	if (Actor)
	{
		FBox ActorBoundingBox = Actor->GetComponentsBoundingBox();

		// Consider Child Actor components
		// This is a workaround for GetActorBounds not considering child actor components
		for (const UActorComponent* ActorComponent : Actor->GetComponents())
		{
			UChildActorComponent const* const ChildActorComponent = Cast<const UChildActorComponent>(ActorComponent);
			AActor const* const CurrChildActor = ChildActorComponent ? ChildActorComponent->GetChildActor() : nullptr;
			if (CurrChildActor)
			{
				ActorBoundingBox += CurrChildActor->GetComponentsBoundingBox();
			}
		}

		if (ActorBoundingBox.IsValid)
		{
			FVector BoundsOrigin = ActorBoundingBox.GetCenter();
			return BoundsOrigin;
		}
	}

	if (Actor)
	{
		return Actor->GetActorLocation();
	}
	else
	{
		return FVector::ZeroVector;
	}
}