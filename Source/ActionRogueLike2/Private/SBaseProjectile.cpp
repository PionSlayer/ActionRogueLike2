// Fill out your copyright notice in the Description page of Project Settings.


#include "SBaseProjectile.h"

#include "Particles/ParticleSystemComponent.h"

ASBaseProjectile::ASBaseProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp -> SetCollisionProfileName("Projectile");
	SphereComp -> SetSimulatePhysics(false);
	SphereComp -> SetEnableGravity(false);
	RootComponent=SphereComp;

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");
	Projectile -> bRotationFollowsVelocity = true;
	Projectile -> bInitialVelocityInLocalSpace = true;
	Projectile -> ProjectileGravityScale = 0.0f;
	Projectile -> InitialSpeed = Speed;
	
	Particles = CreateDefaultSubobject<UParticleSystemComponent>("Particles");
	Particles -> SetupAttachment(SphereComp);


}

void ASBaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = SphereComp->GetComponentLocation();
}

void ASBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(UseRange){
		if(FVector::Distance(SphereComp->GetComponentLocation(),StartLocation) >= Range)
		{
			OnDissipate();
		}
	}
}

void ASBaseProjectile::OnDissipate()
{
	
}

void ASBaseProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
}
void ASBaseProjectile::UseOnHit()
{
	SphereComp->OnComponentHit.AddDynamic(this,&ASBaseProjectile::OnHit);
}
void ASBaseProjectile::OnOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                 int32 otherBodyIndex, bool fromSweep, const FHitResult& Overlap)
{
}
void ASBaseProjectile::UseOnOverlap()
{
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&ASBaseProjectile::OnOverlap);
}

