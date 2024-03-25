// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh -> SetSimulatePhysics(true);
	Mesh->OnComponentHit.AddDynamic(this,&ASExplosiveBarrel::OnHit);
	RootComponent = Mesh;
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->bIgnoreOwningActor=true;
	RadialForceComponent -> SetupAttachment(Mesh);
	RadialForceComponent -> bImpulseVelChange = true;
	RadialForceComponent ->Radius=2000;
	Mesh -> SetCollisionProfileName("PhysicsActor");


}

void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASExplosiveBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherComp->GetCollisionObjectType()==ECC_GameTraceChannel1)
	{
		Mesh->AddImpulse(OtherActor->GetVelocity()*1000);
		RadialForceComponent -> FireImpulse();

	}
}

