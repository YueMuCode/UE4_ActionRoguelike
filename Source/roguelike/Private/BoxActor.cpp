// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABoxActor::ABoxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("baseMesh"));
	RootComponent = baseMesh;
	lidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("lidMesh"));
	lidMesh->SetupAttachment(baseMesh);
	
	boxRotation = 110;
}


// Called when the game starts or when spawned
void ABoxActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABoxActor::Interact_Implementation(APawn* Interacter)
{
	lidMesh->SetRelativeRotation(FRotator(boxRotation, 0, 0));
}

