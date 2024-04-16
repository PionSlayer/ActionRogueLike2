// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "STeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE2_API ASTeleportProjectile : public ASBaseProjectile
{
	GENERATED_BODY()
protected:
	FTimerHandle Timer;
	bool hit;
	void BeginPlay() override;
	

public:
	void OnDissipate() override;
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	UPROPERTY(EditAnywhere)
	float Delay=0.05;
	void StartCountDown();
	void Teleport();
};
