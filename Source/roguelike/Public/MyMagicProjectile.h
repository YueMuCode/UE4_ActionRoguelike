// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ROGUELIKE_API AMyMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyMagicProjectile();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USphereComponent* SphereComp;
	
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;

public:
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
