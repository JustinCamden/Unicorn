// Copyright 2018 Team Unicorn All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "VRAIController.h"
#include "UnicornAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNICORN_API AUnicornAIController : public AVRAIController
{
	GENERATED_BODY()
public:
	AUnicornAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Override for vision location and rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Vision")
	USceneComponent* VisionComponent;
	
	/** How high we expect a VR character's chest to be, based on the height of the VR camera component */
	UPROPERTY(EditAnywhere, Category = "Config|Vision")
	float VRAimLocationHeightMultiplier;
		
	/** Override for the character's eyesight */
	virtual void GetActorEyesViewPoint(FVector& out_Location, FRotator& out_Rotation) const override;

	/** Gets the aim location on target actor */
	UFUNCTION(BlueprintCallable, Category = "AI|Vision")
	FVector GetAimLocationOnActor(AActor* TargetActor) const;
};
