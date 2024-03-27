// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChest.h"

// Sets default values
ASItemChest::ASItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh -> SetupAttachment(BaseMesh);
	pitch = 80;
}



void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}
void ASItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASItemChest::Interact_Implementation(APawn* InstigationPawn)
{
	LidMesh->SetRelativeRotation(FRotator(pitch,0,0));
}