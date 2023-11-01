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
	springArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmofPlayer");//����һ�����ɰ�ʵ��������Ϊspringarmofplayer
	springArmComp->SetupAttachment(RootComponent);//�������ĵ��ɰ帽�ӵ��������
	springArmComp->bUsePawnControlRotation = true;//��ѡ��������������������ת
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraofPlayer");
	CameraComp->SetupAttachment(springArmComp);
	
	GetCharacterMovement()->bOrientRotationToMovement = true;//��ҵ���������ƶ��ķ���
	bUseControllerRotationYaw = false;//��

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

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);//��������

	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);//ƫ��������
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//�󶨽�������
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AMyCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Attack1", IE_Pressed, this, &AMyCharacter::Attack1);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
}

void AMyCharacter::MoveForward(float value)
{
	FRotator controlRot = GetControlRotation();//��ȡ�����������������ת����
	controlRot.Pitch = 0.0f;
	controlRot.Roll = 0.0f;//��ֹ���������ת��������ֻ��Ҫyaw

	AddMovementInput(controlRot.Vector(), value);//����Ԫ��ת��Ϊʸ��
}
void AMyCharacter::MoveRight(float value)
{
	FRotator controlRot = GetControlRotation();
	controlRot.Pitch = 0.0f;
	controlRot.Roll = 0.0f;
	//��ǰ�����ֵ��ͬ���ǣ���ȡ���ҵ���ֵ�õ���y�����תֵ
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
	GetWorldTimerManager().SetTimer(TimerHandle_Attack, this, &AMyCharacter::Attack_TimeElapsed, 0.2f);//��ʱ��
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