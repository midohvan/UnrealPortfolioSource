#include "C_PlayerController.h"
#include "C_Player.h"
#include "Global.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Equipment/C_PlayerWeapon.h"
#include "Equipment/C_PlayerShield.h"
#include "Equipment/C_PlayerHelmet.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"
#include "Animation/AnimInstance.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"
#include "Enemy/C_EnemyBase.h"
#include "C_CameraShake.h"
#include "Camera/CameraShake.h"
#include "Camera/PlayerCameraManager.h"

AC_PlayerController::AC_PlayerController()
{
	//MontagePlayer = NewObject<UCMontagePlayer>();
}

void AC_PlayerController::OnPossess(APawn * aPawn)
{
	Super::OnPossess(aPawn);

	ControlledPlayer = Cast<ACharacter>(aPawn);

	ControlledPlayer->GetCharacterMovement()->MaxAcceleration = 650.0f;
	ControlledPlayer->GetCharacterMovement()->MaxWalkSpeed = MaxRunSpeed;
	ControlledPlayer->bUseControllerRotationYaw = true;
	ControlledPlayer->GetCharacterMovement()->bOrientRotationToMovement = false;
	ControlledPlayer->GetCharacterMovement()->bUseSeparateBrakingFriction = false;
	ControlledPlayer->GetCharacterMovement()->AirControl = 1.0f;
	ControlledPlayer->GetCharacterMovement()->bApplyGravityWhileJumping = true;
	ControlledPlayer->GetCharacterMovement()->BrakingDecelerationFalling = false;
	ControlledPlayer->GetCharacterMovement()->GravityScale = 2.0f;
	ControlledPlayer->GetCharacterMovement()->JumpZVelocity = 1000.0f;

	Player = Cast<AC_Player>(aPawn);
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_EnemyBase::StaticClass(), Enemies);

	

}

void AC_PlayerController::BeginPlay()
{
	Super::BeginPlay();

}


void AC_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsValid(CameraEnemy)&& CameraEnemy != NULL)
	{
		if (CameraEnemy->GetDying() == true)
		{
			SetDeadCamera(CameraEnemy);
		}
	}
}

void AC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AC_PlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AC_PlayerController::MoveRight);

	InputComponent->BindAxis("Turn", this, &AC_PlayerController::Turn);
	InputComponent->BindAxis("LookUp", this, &AC_PlayerController::LookUp);

	InputComponent->BindAction("Equip/Unequip", EInputEvent::IE_Pressed, this, &AC_PlayerController::Equip);

	InputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &AC_PlayerController::Attack);
	InputComponent->BindAction("Kick", EInputEvent::IE_Pressed, this, &AC_PlayerController::Kick);
	InputComponent->BindAction("ShieldAttack", EInputEvent::IE_Pressed, this, &AC_PlayerController::ShieldAttack);
	InputComponent->BindAction("SpecialAttack", EInputEvent::IE_Pressed, this, &AC_PlayerController::SpecialAttack);

	InputComponent->BindAction("Block", EInputEvent::IE_Pressed, this, &AC_PlayerController::BeginGuard);

	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AC_PlayerController::Jumping);
	InputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AC_PlayerController::Falling);
	
	InputComponent->BindAction("Walk/Run", EInputEvent::IE_Pressed, this, &AC_PlayerController::Walking);
	
	InputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &AC_PlayerController::Sprinting);
	InputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &AC_PlayerController::StopSprinting);

	InputComponent->BindAction("Evade", EInputEvent::IE_Pressed, this, &AC_PlayerController::Evade);
	

}

void AC_PlayerController::ASetTargetWithBlend(AActor* OtherActor)
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.7f);
	SetViewTargetWithBlend(OtherActor);

	FTimerHandle RepeatTimerHandle;

	GetWorld()->GetTimerManager().SetTimer
	(
		RepeatTimerHandle, this, &AC_PlayerController::ResetCamera, 0.25f, false
	);

	
}

void AC_PlayerController::SetActionCamera(AActor * OtherActor)
{
	bCameraAction = true;

	CameraEnemy = Cast<AC_EnemyBase>(OtherActor);

	CameraEnemy->SetCameraAction(true);

	SetViewTargetWithBlend(CameraEnemy, 2.0f);

	FTimerHandle RepeatTimerHandle;

	GetWorld()->GetTimerManager().SetTimer
	(
		RepeatTimerHandle, this, &AC_PlayerController::ResetCamera, 15.0f, false
	);
}

void AC_PlayerController::ResetCamera()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);

	this->SetViewTarget(ControlledPlayer);
	
	CameraEnemy->SetCameraAction(false);

	bCameraAction = false;
}

void AC_PlayerController::SetDeadCamera(AC_EnemyBase* enemy)
{
	CameraEnemy->SetDying(false);

	SetViewTargetWithBlend(enemy,0.5f);

	FTimerHandle RepeatTimerHandle;

	GetWorld()->GetTimerManager().SetTimer
	(
		RepeatTimerHandle, this, &AC_PlayerController::ResetCamera, 2.0f, false
	);
}



void AC_PlayerController::MoveForward(float Axis)
{
	if (bCanMove == false) return;

	if (Axis > 0.1f) bMovingForward = true;
	
	else if(Axis < -0.1f) bMovingForward = false;
	
	if (bMovingForward == false && bWalking == false)
		ControlledPlayer->GetCharacterMovement()->MaxWalkSpeed = 500.0f;

	FRotator rotator = GetControlRotation();
	FRotator forward = FRotator(0, rotator.Yaw, 0);
	FQuat quat = FQuat(forward);

	FVector vec = quat.GetForwardVector();
	ControlledPlayer->AddMovementInput(vec, Axis);
}

void AC_PlayerController::MoveRight(float Axis)
{
	if (bCanMove == false) return;

	FRotator rotator = GetControlRotation();
	FRotator forward = FRotator(0, rotator.Yaw, 0);
	FQuat quat = FQuat(forward);

	FVector vec = quat.GetRightVector();
	ControlledPlayer->AddMovementInput(vec, Axis);
}

void AC_PlayerController::Turn(float Axis)
{
	ControlledPlayer->AddControllerYawInput(Axis);
}

void AC_PlayerController::LookUp(float Axis)
{
	ControlledPlayer->AddControllerPitchInput(Axis);
}

void AC_PlayerController::Walking()
{
	bWalking = !bWalking;

	if (bWalking)
	{
		ControlledPlayer->GetCharacterMovement()->MaxAcceleration = 300.0f;
		ControlledPlayer->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	}
	else
	{
		ControlledPlayer->GetCharacterMovement()->MaxAcceleration = 650.0f;
		ControlledPlayer->GetCharacterMovement()->MaxWalkSpeed = MaxRunSpeed;
	}
}

void AC_PlayerController::Sprinting()
{
	if (bWalking == true) return;
	
	bSprinting = true;

	ControlledPlayer->GetCharacterMovement()->MaxAcceleration = 1000.0f;
	ControlledPlayer->GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
}

void AC_PlayerController::StopSprinting()
{
	if (bWalking == true) return;

	bSprinting = false;

	ControlledPlayer->GetCharacterMovement()->MaxAcceleration = 650.0f;
	ControlledPlayer->GetCharacterMovement()->MaxWalkSpeed = MaxRunSpeed;
}

void AC_PlayerController::Equip()
{
	if (ControlledPlayer->GetCharacterMovement()->IsFalling() == true) return;
	if (bAttacking == true) return;

	if (bWeaponDrawn == true)
	{
		if (ControlledPlayer->GetCharacterMovement()->Velocity.Size() > 0.1f)
			ControlledPlayer->PlayAnimMontage(Player->GetStateMontages().MovingUnequip);
		else
			ControlledPlayer->PlayAnimMontage(Player->GetStateMontages().StopUnequip);

	}
	else
	{
		if (ControlledPlayer->GetCharacterMovement()->Velocity.Size() > 0.1f)
			ControlledPlayer->PlayAnimMontage(Player->GetStateMontages().MovingEquip);
		else
			ControlledPlayer->PlayAnimMontage(Player->GetStateMontages().StopEquip);
	}
	
}

void AC_PlayerController::BeginGuard()
{
	if (ControlledPlayer->GetCharacterMovement()->IsFalling() == true) return;
	if (bAttacking == true) return;

	ControlledPlayer->PlayAnimMontage(Player->GetStateMontages().Guard);
}

void AC_PlayerController::Hit()
{

}

void AC_PlayerController::Jumping()
{
	if (ControlledPlayer->GetCharacterMovement()->IsFalling() == true) return;

	ControlledPlayer->Jump();
}

void AC_PlayerController::Falling()
{
	ControlledPlayer->StopJumping();
}

void AC_PlayerController::Evade()
{
	if (ControlledPlayer->GetCharacterMovement()->IsFalling() == true) return;

	if (bAttacking == true) return;
	if (bEvading == true) return;
	if (bStepping == true) return;
	if (bCanMove == false) return;
	
	float forwardAxisValue = InputComponent->GetAxisValue("MoveForward");
	float rightAxisValue = InputComponent->GetAxisValue("MoveRight");

	if (rightAxisValue >= 0.5f)
	{
		if(bWeaponDrawn == true)
			ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().StepRight);
		else
			ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().EvadeRight);
		//MontagePlayer->PlayMovingMontage(ControlledPlayer, EInputDirection::Right, bWeaponDrawn);
	}
	else if (rightAxisValue <= -0.5f)
	{
		if (bWeaponDrawn == true)
			ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().StepLeft);
		else
			ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().EvadeLeft);
		//MontagePlayer->PlayMovingMontage(ControlledPlayer, EInputDirection::Left, bWeaponDrawn);
	}
	else if (forwardAxisValue >= 0.5f)
	{
		if (bWeaponDrawn == true)
			ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().StepForward);
		else
			ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().EvadeForward);
		//MontagePlayer->PlayMovingMontage(ControlledPlayer, EInputDirection::Forward, bWeaponDrawn);
	}
	else if (forwardAxisValue <= -0.5f)
	{
		if (bWeaponDrawn == true)
			ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().StepBack);
		else
			ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().EvadeBack);
		//MontagePlayer->PlayMovingMontage(ControlledPlayer, EInputDirection::Back, bWeaponDrawn);
	}
	else
		return;
}

AActor * AC_PlayerController::GetClosestEnemy(FVector sourceLocation)
{
	if (Enemies.Num() <= 0)
	{
		return nullptr;
	}

	AActor* closestActor = nullptr;
	float currentClosestDistance = TNumericLimits<float>::Max();

	for (int i = 0; i < Enemies.Num(); i++)
	{
		float distance = FVector::DistSquared(sourceLocation, Enemies[i]->GetActorLocation());
		if (distance < currentClosestDistance)
		{
			currentClosestDistance = distance;
			closestActor = Enemies[i];
		}
	}

	return closestActor;
}

void AC_PlayerController::Attack()
{
	if (bWeaponDrawn == false) return;

	if (ControlledPlayer->GetCharacterMovement()->IsFalling() == true && bAttacking == false)
		ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().JumpKnockDownAttack);

	float rightAxisValue = InputComponent->GetAxisValue("MoveRight");

	if (rightAxisValue >= 0.5f && bAttacking == false)
		ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().RightAttack,0.8f);
	else if (rightAxisValue <= -0.5f && bAttacking == false)
		ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().LeftAttack,0.8f);
	else if (bAttacking == false && ControlledPlayer->GetCharacterMovement()->IsFalling() == false)
	{
		if (bSprinting == true)
			ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().DashBlowAwayAttack);
		else if (bStepping == true)
			ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().StepBackCombo1,0.9f);
		else
		{
			if (ControlledPlayer->GetCharacterMovement()->Velocity.Size() > 0.1f)
				ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().MovingNormalAttack);
			else
				ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().StopNormalAttack);
		}
	}
	else if (bAttacking == true && bStepping == true && bCanSecondInput == true && ControlledPlayer->GetCharacterMovement()->IsFalling() == false)
		ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().StepBackCombo2,0.9f);
	
	//NormalAttackCombo
	else if (bAttacking == true && bCanSecondInput == true && ControlledPlayer->GetCharacterMovement()->IsFalling() == false)
		ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().NormalAttackCombo1,0.9f);
	else if (bAttacking == true && bCanThirdInput == true && ControlledPlayer->GetCharacterMovement()->IsFalling() == false)
		ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().NormalAttackCombo2,0.9f);
}

void AC_PlayerController::ShieldAttack()
{
	if (ControlledPlayer->GetCharacterMovement()->IsFalling() == true) return;


	if (bWeaponDrawn == false && bSprinting == false)
		ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().ShieldAttack);
	else if (bSprinting == true)
	{
		ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().DashShieldAttack);
	}
	else if (bAttacking == true && bCanSecondInput == true)
		ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().ShieldAttackCombo2,0.9f);
	else if (bAttacking == true && bCanThirdInput == true)
		ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().ShieldAttackCombo3,0.9f);
	else if (bAttacking == false && bWeaponDrawn)
		ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().ShieldAttackCombo,0.9f);

}

void AC_PlayerController::SpecialAttack()
{
	if (ControlledPlayer->GetCharacterMovement()->IsFalling() == true) return;
	if (bWeaponDrawn == false) return;
	if (bSprinting == true) return;

	ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().SpecialAttack);
}

void AC_PlayerController::Kick()
{
	if (bWeaponDrawn == false) return;

	if (bAttacking == true && bCanSecondInput == true)
		ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().KickCombo2,0.9f);
	else if (bAttacking == true && bCanThirdInput == true)
		ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().KickCombo3,0.9f);
	else if (bAttacking == false)
		ControlledPlayer->PlayAnimMontage(Player->GetDierctionalMontages().Kick,0.9f);

}
