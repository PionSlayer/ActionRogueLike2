// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE2_API ASMagicProjectile : public ASBaseProjectile
{
	GENERATED_BODY()
	
public:	
	ASMagicProjectile();

protected:

	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly);
	float Damage;

public:
	void OnDissipate() override;
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
