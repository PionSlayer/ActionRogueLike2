// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGamePlayInterface.h"
#include "GameFramework/Actor.h"
#include "SItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE2_API ASItemChest : public AActor, public ISGamePlayInterface
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	float pitch;
	void Interact_Implementation(APawn* InstigationPawn) override;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	ASItemChest();
	virtual void Tick(float DeltaTime) override;

};
