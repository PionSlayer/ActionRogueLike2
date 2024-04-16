// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "SBlackHoleProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE2_API ASBlackHoleProjectile : public ASBaseProjectile
{
	GENERATED_BODY()
public:
	ASBlackHoleProjectile();
	UPROPERTY(EditAnywhere);
	float Radius = 1000;
	UPROPERTY(EditAnywhere);
	float Power = 100;
	
protected:
	void BeginPlay() override;
	
public:
	void OnDissipate() override;
	void OnOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 otherBodyIndex, bool fromSweep, const FHitResult& Overlap) override;
	void Tick(float DeltaSeconds) override;
	void Pull();
};
