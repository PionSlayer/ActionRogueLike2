// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	UseOnHit();
	Damage = -20;
}

void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp -> IgnoreActorWhenMoving(GetInstigator(),true);
}

void ASMagicProjectile::OnDissipate()
{
	Super::OnDissipate();
	if(ParticleSystem)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(), // World context
			ParticleSystem, // Your particle system template
			GetActorLocation(), // World location where the emitter should spawn
			FRotator::ZeroRotator, // Initial rotation
			true // Whether to auto-destroy the emitter when it's done
			);
	}
	Destroy();
}

void ASMagicProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor)
	{
		if(OtherActor != GetInstigator())
		{
			USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
			if(AttributeComponent)
			{
				AttributeComponent->ApplyHealthChange(Damage);
			}
			OnDissipate();
		}
		return;
	}
	OnDissipate();
}




