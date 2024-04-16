// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackHoleProjectile.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ASBlackHoleProjectile::ASBlackHoleProjectile()
{
	UseRange=true;
	Range=1000;
	UseOnOverlap();
	SphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	Projectile->InitialSpeed = Speed;
}

void ASBlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();
}
void ASBlackHoleProjectile::OnDissipate()
{
	Super::OnDissipate();
	if(ParticleSystem)
	{
		UGameplayStatics::SpawnEmitterAtLocation
		(
			GetWorld(),
			ParticleSystem,
			SphereComp->GetComponentLocation(),
			FRotator::ZeroRotator,
			true);
	}
	Destroy();
}
void ASBlackHoleProjectile::OnOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                      int32 otherBodyIndex, bool fromSweep, const FHitResult& Overlap)
{
	Super::OnOverlap(HitComp, OtherActor, OtherComp, otherBodyIndex, fromSweep, Overlap);
	if(OtherActor!=GetInstigator())
	{
		if(OtherComp->GetCollisionObjectType()==ECC_PhysicsBody)
		{
			OtherActor->Destroy();
		}
	}
}

void ASBlackHoleProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Pull();
}

void ASBlackHoleProjectile::Pull()
{
	TArray<FHitResult> Hits;
	FCollisionObjectQueryParams Params;
	Params.AddObjectTypesToQuery(ECC_PhysicsBody);
	FCollisionShape Shape;
	Shape.SetSphere(Radius);
	GetWorld()->SweepMultiByObjectType(Hits,GetActorLocation(),GetActorLocation(),FQuat::Identity,Params,Shape);

	for(FHitResult hit: Hits)
	{

		AActor* hitActor = hit.GetActor();
		if(hitActor)
		{
			if(hitActor != GetInstigator())
			{
				DrawDebugString(GetWorld(),GetActorLocation(),"HELLO",nullptr,FColor::Green,2.0f,true);

				FVector forceDirection = UKismetMathLibrary::FindLookAtRotation(hitActor->GetActorLocation(),GetActorLocation()).Vector();
				hitActor->GetComponentByClass<UPrimitiveComponent>()->AddImpulse(forceDirection*Power);
			}
		}
	}
}


