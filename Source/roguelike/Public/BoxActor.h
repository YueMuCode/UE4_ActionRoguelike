// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyInterface.h"
#include "BoxActor.generated.h"

class UStaticMeshComponent;//mesh

UCLASS()
class ROGUELIKE_API ABoxActor : public AActor,public IMyInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxActor();
public:

	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* lidMesh;//Ïä×Ó¸Ç×Ó
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* baseMesh;//Ïä×Óµ××ù
	UPROPERTY(EditAnywhere)
	float boxRotation;

	virtual void BeginPlay() override;


public:
	void Interact_Implementation(APawn* Interacter);

};
