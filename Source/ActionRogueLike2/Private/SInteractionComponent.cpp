// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "SGamePlayInterface.h"


USInteractionComponent::USInteractionComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}


void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}



void USInteractionComponent::PrimaryInteraction()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interaction Called:2"));
	AActor* myOwner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	myOwner ->GetActorEyesViewPoint(EyeLocation,EyeRotation);
	FVector End = EyeLocation+(EyeRotation.Vector()*2000);
	FCollisionObjectQueryParams Params;
	Params.AddObjectTypesToQuery(ECC_WorldDynamic);

	float radios = 30;
	FCollisionShape Shape;
	Shape.SetSphere(radios);

	TArray<FHitResult>Hits;
	
	bool lineHit = GetWorld()->SweepMultiByObjectType(Hits,EyeLocation,End,FQuat::Identity,Params,Shape);
	FColor lineColor = lineHit? FColor::Green : FColor::Red;

	for(FHitResult Hit :Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if(HitActor)
		{

			if(HitActor->Implements<USGamePlayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(HitActor);
				ISGamePlayInterface::Execute_Interact(HitActor,MyPawn);
				break;
			}
			
		}
	}
	DrawDebugLine(GetWorld(),EyeLocation,End,lineColor,false,2.0f,0.0f,2.0f);

}