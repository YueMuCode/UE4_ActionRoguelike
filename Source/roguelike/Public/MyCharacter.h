// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"
//声明对应的类，不直接声明头文件是为了节省时间
class UCameraComponent;
class USpringArmComponent;
class UMyInteractionActorComponent;
class UAnimMontage;
UCLASS()
class ROGUELIKE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf <AActor>ProjectileClass;//?

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* springArmComp;


	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	UMyInteractionActorComponent *InteractionComp;

	UPROPERTY(EditAnywhere,Category="Attack")
	UAnimMontage* attackanim;

	FTimerHandle TimerHandle_Attack;//延迟
	void Attack_TimeElapsed();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void MoveForward(float value);
	void MoveRight(float value);
	
	void PrimaryInteract();
	void Attack1();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

};
