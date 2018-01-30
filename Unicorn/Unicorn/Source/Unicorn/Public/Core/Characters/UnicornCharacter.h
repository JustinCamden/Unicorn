// Copyright 2018 Team Unicorn All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TeamComponent.h"
#include "HealthInterface.h"
#include "UnicornCharacter.generated.h"

UCLASS()
class UNICORN_API AUnicornCharacter : public ACharacter, public IHealthInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnicornCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Team of this character. Helps allies, harms enemies. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetTeam, Category = "Config")
	ETeam Team;

	/** Health of this character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	class UResourceComponent* HealthComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Getter for the character's eyesight component */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, BlueprintPure, Category = "AI|Vision")
	USceneComponent* GetVisionComponent() const;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	UTeamComponent* TeamComponent;

	/** Setter for Character's Team. Automatically updates Team Component */
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetTeam(ETeam NewTeam);
	
	/** Whether this character is currently dead */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool bDead;

	bool LoseHealth_Implementation(float HealthLost, bool& bDied) override;
	bool GainHealth_Implementation(float HealthGained) override;
};
