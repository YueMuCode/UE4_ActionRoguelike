// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharactermovementComponent.h"
#include  "MyInteractionActorComponent.h"
#include "DrawDebugHelpers.h"
// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	springArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmofPlayer");//创建一个弹簧板实例，名字为springarmofplayer
	springArmComp->SetupAttachment(RootComponent);//将创建的弹簧板附加到根组件上
	springArmComp->bUsePawnControlRotation = true;//勾选由人物控制相机的上下旋转
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraofPlayer");
	CameraComp->SetupAttachment(springArmComp);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;//玩家的面向跟随移动的方向
	bUseControllerRotationYaw = false;//？

	InteractionComp = CreateDefaultSubobject<UMyInteractionActorComponent>("InteractionComp");

	attackanim = CreateDefaultSubobject<UAnimMontage>("attack1");
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



// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);//绑定轴输入

	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);//偏航轴输入
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//绑定交互输入
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AMyCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Attack1", IE_Pressed, this, &AMyCharacter::Attack1);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
}

void AMyCharacter::MoveForward(float value)
{
	FRotator controlRot = GetControlRotation();//获取控制器（相机）的旋转方向
	controlRot.Pitch = 0.0f;
	controlRot.Roll = 0.0f;//防止其他方向的转动，我们只需要yaw

	AddMovementInput(controlRot.Vector(), value);//将四元数转换为矢量
}
void AMyCharacter::MoveRight(float value)
{
	FRotator controlRot = GetControlRotation();
	controlRot.Pitch = 0.0f;
	controlRot.Roll = 0.0f;
	//与前后的轴值不同的是，获取左右的轴值用的是y轴的旋转值
	FVector rightVector = FRotationMatrix(controlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(rightVector, value);
}

void AMyCharacter::PrimaryInteract()
{
	if (InteractionComp != NULL)
	{
		InteractionComp->PrimaryInteration();
	}
	
}

void AMyCharacter::Attack1()
{
	
	PlayAnimMontage(attackanim);
	GetWorldTimerManager().SetTimer(TimerHandle_Attack, this, &AMyCharacter::Attack_TimeElapsed, 0.2f);//计时器
}



void AMyCharacter::Attack_TimeElapsed()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
} 