// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SBaseProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE2_API ASBaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASBaseProjectile();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USphereComponent* SphereComp;
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* Projectile;
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* Particles;

	UPROPERTY(EditAnywhere)
	float Speed = 1000;

	UPROPERTY(EditAnywhere)
	float Range = 1000;
	UPROPERTY(EditAnywhere)
	bool UseRange = false;
	FVector StartLocation;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ParticleSystem;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnDissipate();
	
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void UseOnHit();

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 otherBodyIndex, bool fromSweep, const FHitResult& Overlap);
	void UseOnOverlap();

};
