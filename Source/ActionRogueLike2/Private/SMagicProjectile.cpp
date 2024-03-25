// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	//SphereComp -> SetCollisionObjectType(ECC_WorldStatic);
	//SphereComp -> SetCollisionResponseToAllChannels(ECR_Ignore);
	//SphereComp -> SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp -> SetCollisionProfileName("Projectile");
	SphereComp -> SetEnableGravity(false);
	RootComponent = SphereComp;

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	ParticleComp ->SetupAttachment(SphereComp);

	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileComp");
	ProjectileComp -> InitialSpeed = 1000.0f;
	ProjectileComp -> bRotationFollowsVelocity = true;
	ProjectileComp -> bInitialVelocityInLocalSpace = true;
	ProjectileComp -> ProjectileGravityScale = 0.0f;
	


}

void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

