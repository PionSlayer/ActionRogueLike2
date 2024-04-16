// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportProjectile.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	UseRange = true;
	Range = 1000;
	Speed = 4000;
	hit = false;
	UseOnHit();
}

void ASTeleportProjectile::OnDissipate()
{
	StartCountDown();
}

void ASTeleportProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor != GetInstigator()){StartCountDown();}
	
}



void ASTeleportProjectile::StartCountDown()
{
	if(!hit)
	{
		hit = true;
		Projectile->SetVelocityInLocalSpace(FVector::Zero());
		Particles->Deactivate();
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
                   	GetWorld()->GetTimerManager().SetTimer(Timer,this,&ASTeleportProjectile::Teleport,Delay);
	}
	
}

void ASTeleportProjectile::Teleport()
{
	GetInstigator()->SetActorLocation(GetActorLocation());
	Destroy();
}
