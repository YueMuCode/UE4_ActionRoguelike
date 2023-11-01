// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInteractionActorComponent.h"
#include "MyInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UMyInteractionActorComponent::UMyInteractionActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyInteractionActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyInteractionActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyInteractionActorComponent::PrimaryInteration()
{
	//看不懂这段关于碰撞检测的
	FCollisionObjectQueryParams objectQueryparams;
	objectQueryparams.AddObjectTypesToQuery(ECC_WorldDynamic);
	AActor* myOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	myOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	/*FHitResult Hit;
	bool isBlock=GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, objectQueryparams);*/
	//将射线检测换成球形
	TArray<FHitResult> Hits;
	FCollisionShape shape;
	shape.SetSphere(30.0f);//发射的圆的大小半径为30
	bool isBlock = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, objectQueryparams, shape);
	FColor lineColor = isBlock ? FColor::Green : FColor::Blue;
	for (FHitResult hit : Hits)
	{
		AActor* HitActor = hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UMyInterface>())//检测的时候用U
			{
				APawn* myPawn = Cast<APawn>(myOwner);
				IMyInterface::Execute_Interact(HitActor, myPawn);//调用的时候用I
				break;//保证一次只触发一个
			}
			DrawDebugSphere(GetWorld(), hit.ImpactPoint, 30.0f, 32, lineColor, false, 2.0f);
			
		}
		
	}
	
	DrawDebugLine(GetWorld(), EyeLocation, End, lineColor, false, 2.0f, 0, 2.0f);
}

