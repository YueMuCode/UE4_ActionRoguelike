// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	springArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmofPlayer");//创建一个弹簧板实例，名字为springarmofplayer
	springArmComp->SetupAttachment(RootComponent);//将创建的弹簧板附加到根组件上
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraofPlayer");
	CameraComp->SetupAttachment(springArmComp);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}


// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);//绑定轴输入
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);//偏航轴输入
}

