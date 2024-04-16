// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAttributeComponent.h"
#include "SInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "SCharacter.generated.h"

UCLASS()
class ACTIONROGUELIKE2_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	
public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComp;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere)
	USInteractionComponent* InteractionComp;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	USAttributeComponent* AttributeComponent;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackAnim;
	FTimerHandle TimerHandle_PrimaryAttack;


	
	virtual void BeginPlay() override;

public:
	void MoveForward(float Value);
	void MoveSideways(float Value);

	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed();
	void PrimaryInteract();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
