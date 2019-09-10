#include "C_Assassin_Enemy.h"
#include "Global.h"
#include "Equipments/C_AssassinHelmet.h"
#include "Equipments/C_Assassin_Weapon.h"
#include "Equipments/C_AssassinLeftWeapon.h"
#include "Equipments/C_AssassinKickDumy.h"
#include "C_AssassinAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Animation/AnimInstance.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "DamageType/C_DamageType_KnockBack.h"
#include "DamageType/C_DamageType_KnockDown.h"
#include "DamageType/C_DamageType_Default.h"
#include "DamageType/C_DamageType_BlowAway.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "TimerManager.h"

AC_Assassin_Enemy::AC_Assassin_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Montages();

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	HealthPoint = 100.0f;

	Assassin_PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Assassin_PawnSensingComp"));
	Assassin_PawnSensingComp->SetPeripheralVisionAngle(60.0f);

	Assassin_SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(FName("Assassin_SpringArmComp"));
	Assassin_SpringArmComp->SetupAttachment(RootComponent);
	Assassin_SpringArmComp->bUsePawnControlRotation = false;
	Assassin_SpringArmComp->bInheritPitch = true;
	Assassin_SpringArmComp->bInheritYaw = true;
	Assassin_SpringArmComp->bInheritRoll = true;
	Assassin_SpringArmComp->bDoCollisionTest = false;
	Assassin_SpringArmComp->bEnableCameraLag = true;
	Assassin_SpringArmComp->bEnableCameraRotationLag = true;
	Assassin_SpringArmComp->SetRelativeRotation(FRotator(0.f, -180, 0.f));
	Assassin_SpringArmComp->TargetArmLength = 400.0f;
	Assassin_SpringArmComp->SocketOffset = FVector(0.f, 40.f, -80.f);

	Assassin_CameraComp = CreateDefaultSubobject<UCameraComponent>(FName("Assassin_CameraComp"));
	Assassin_CameraComp->SetupAttachment(Assassin_SpringArmComp);
	Assassin_CameraComp->SetRelativeLocation(FVector(-108, 0.f, 130.f));
	Assassin_CameraComp->SetRelativeRotation(FRotator(180.f, 12.f, 0.f));

	Assassin_BloodComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Assassin_Blood"));
	Assassin_BloodComp->SetupAttachment(RootComponent);
	Assassin_BloodComp->bAutoActivate = false;


	ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset
	(
		TEXT("/Game/FXVillesBloodVFXPack/Particles/PS_StyleBlood_Slash_Omni_LRG")
	);
	if (ParticleAsset.Succeeded() == true) Assassin_Blood = ParticleAsset.Object;

	//무기
	ConstructorHelpers::FClassFinder<AC_Assassin_Weapon> AssassinWeapon
	(
		TEXT("Blueprint'/Game/Enemy/BpC_Assassin_Weapon.BpC_Assassin_Weapon_C'")
	);
	if (AssassinWeapon.Succeeded() == true) WeaponClass = AssassinWeapon.Class;
	//왼손무기
	ConstructorHelpers::FClassFinder<AC_AssassinLeftWeapon> AssassinLeftWeapon
	(
		TEXT("Blueprint'/Game/Enemy/BpC_AssassinLeftWeapon.BpC_AssassinLeftWeapon_C'")
	);
	if (AssassinLeftWeapon.Succeeded() == true) LeftWeaponClass = AssassinLeftWeapon.Class;
	//발
	ConstructorHelpers::FClassFinder<AC_AssassinKickDumy> AssassinKick
	(
		TEXT("Blueprint'/Game/Enemy/BpC_AssassinKickDumy.BpC_AssassinKickDumy_C'")
	);
	if (AssassinKick.Succeeded() == true) KickClass = AssassinKick.Class;
	//헬멧
	ConstructorHelpers::FClassFinder<AC_AssassinHelmet> AssassinHelmet
	(
		TEXT("Blueprint'/Game/Enemy/BpC_AssassinHelmet.BpC_AssassinHelmet_C'")
	);
	if (AssassinHelmet.Succeeded() == true) HelmetClass = AssassinHelmet.Class;

}

void AC_Assassin_Enemy::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AC_Assassin_Enemy::OnHitOverlap);

	if (Assassin_PawnSensingComp != NULL)
	{
		Assassin_PawnSensingComp->OnSeePawn.AddDynamic(this, &AC_Assassin_Enemy::OnSeePlayer);
	}

	FActorSpawnParameters params;
	params.Owner = this;

	FTransform transform = FTransform::Identity;

	//무기
	Weapon = GetWorld()->SpawnActor<AC_Assassin_Weapon>(WeaponClass, transform, params);
	if (Weapon != NULL)
	{
		Weapon->AttachToComponent
		(
			(USceneComponent *)GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
			FName("WeaponSocket")
		);
	}

	//왼손무기
	LeftWeapon = GetWorld()->SpawnActor<AC_AssassinLeftWeapon>(LeftWeaponClass, transform, params);
	if (LeftWeapon != NULL)
	{
		LeftWeapon->AttachToComponent
		(
			(USceneComponent *)GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
			FName("LeftWeaponSocket")
		);
	}

	//왼손무기
	Kick = GetWorld()->SpawnActor<AC_AssassinKickDumy>(KickClass, transform, params);
	if (Kick != NULL)
	{
		Kick->AttachToComponent
		(
			(USceneComponent *)GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
			FName("KickSocket")
		);
	}
	//뚝배기
	Helmet = GetWorld()->SpawnActor<AC_AssassinHelmet>(HelmetClass, transform, params);
	if (Helmet != NULL)
	{
		Helmet->AttachToComponent
		(
			(USceneComponent *)GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
			FName("HelmetSocket")
		);
	}
}

void AC_Assassin_Enemy::OnSeePlayer(APawn * InPawn)
{
	if (InPawn->ActorHasTag("Enemy") == true) return;

	AC_AssassinAIController* AIController = Cast<AC_AssassinAIController>(GetController());
	if (AIController != NULL)
	{
		AIController->SetSeenTarget(InPawn);
	}
}

void AC_Assassin_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_Assassin_Enemy::OnHitOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this) return;
	if (OtherActor == GetOwner()) return;
	if (OtherActor->ActorHasTag("Map") == true) return;
	if (OtherActor->ActorHasTag("Enemy") == true) return;
	if (OtherActor->ActorHasTag("Trigger") == true) return;
	if (OtherActor->ActorHasTag("Player") == true) return;
	if (bDying == true) return;

	FVector ForwardVector = GetActorForwardVector();
	FVector RightVector = GetActorRightVector();
	FVector VectorA = GetActorLocation() - OtherActor->GetOwner()->GetActorLocation();

	if (VectorA.Normalize())
	{
		//앞뒤판단 음수면 앞 // 양수 뒤
		FrontBackResult = UKismetMathLibrary::Dot_VectorVector(ForwardVector, VectorA);
		//좌우판단 음수면 오른 // 양수 왼
		LeftRightResult = UKismetMathLibrary::Dot_VectorVector(RightVector, VectorA);
	}

}

float AC_Assassin_Enemy::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (bDying == true) return 0;

	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (bBeingHit == false && bDying == false)
	{
		if (bCanBlock == true)
		{
			if (DamageEvent.DamageTypeClass == UC_DamageType_KnockDown::StaticClass() ||
				DamageEvent.DamageTypeClass == UC_DamageType_BlowAway::StaticClass() ||
				DamageEvent.DamageTypeClass == UC_DamageType_KnockBack::StaticClass())
			{
				PlayAnimMontage(enemyStateMontage.KnockBack);
			}
			else
				PlayAnimMontage(enemyStateMontage.Block);
		}
		else
		{
			if (DamageEvent.DamageTypeClass == UC_DamageType_KnockDown::StaticClass())
				PlayAnimMontage(enemyStateMontage.KnockDown);
			else if (DamageEvent.DamageTypeClass == UC_DamageType_KnockBack::StaticClass())
				PlayAnimMontage(enemyStateMontage.KnockBack);
			else if (DamageEvent.DamageTypeClass == UC_DamageType_BlowAway::StaticClass())
				PlayAnimMontage(enemyStateMontage.BlowAway);
			else if (DamageEvent.DamageTypeClass == UC_DamageType_Default::StaticClass())
			{
				// 음수면 정면에서 처맞은거
				if (FrontBackResult > 0.5f)
					PlayAnimMontage(enemyStateMontage.BackHit,0.9f);
				else if (FrontBackResult < 0.5f)
					PlayAnimMontage(enemyStateMontage.Hit,0.9f);
			}

		}

		HealthPoint -= FinalDamage;
	}

	if (Assassin_BloodComp != NULL)
	{
		Assassin_BloodComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Assassin_Blood, GetMesh()->GetSocketLocation("spine_01"), FRotator::ZeroRotator);
		Assassin_BloodComp->ActivateSystem();
	}

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Magenta, FString::Printf(L"%f", FinalDamage));

	return FinalDamage;
}

void AC_Assassin_Enemy::DestroyEnemy()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	Weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	Helmet->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	LeftWeapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	Kick->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);

	Weapon->GetCapsuleComponent()->SetSimulatePhysics(true);
	LeftWeapon->GetCapsuleComponent()->SetSimulatePhysics(true);
	Kick->GetCapsuleComponent()->SetSimulatePhysics(true);
	Helmet->GetBoxComponent()->SetSimulatePhysics(true);

	Weapon->Destroy();
	LeftWeapon->Destroy();
	Kick->Destroy();
	Helmet->Destroy();
	this->Destroy();
}



void AC_Assassin_Enemy::NormalAttack()
{
	if (GetAttacking() == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyAttackMontages.NormalAttack);
}

void AC_Assassin_Enemy::StrongAttack()
{

	if (GetAttacking() == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyAttackMontages.StrongAttack);

}

void AC_Assassin_Enemy::DownAttack()
{
	if (GetAttacking() == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyAttackMontages.DownAttack);
}

void AC_Assassin_Enemy::SpecialAttack1()
{
	if (bIsAttacking == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyAttackMontages.SpecialAttack1);
}

void AC_Assassin_Enemy::SpecialAttack2()
{
	if (bIsAttacking == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;
	PlayAnimMontage(enemyAttackMontages.SpecialAttack2);
}

void AC_Assassin_Enemy::SpecialAttack3()
{
	if (bIsAttacking == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyAttackMontages.SpecialAttack3);
}

void AC_Assassin_Enemy::SpecialAttack4()
{
	if (bIsAttacking == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyAttackMontages.SpecialAttack4);
}

void AC_Assassin_Enemy::Guard()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;
	PlayAnimMontage(enemyStateMontage.Guard);
}

void AC_Assassin_Enemy::StepBack()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyStateMontage.StepBack);
}

void AC_Assassin_Enemy::StepLeft()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyStateMontage.StepLeft);
}

void AC_Assassin_Enemy::StepRight()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;
	PlayAnimMontage(enemyStateMontage.StepRight);
}

void AC_Assassin_Enemy::Dead()
{
	if (bDying == true) return;

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.3f);
	PlayAnimMontage(enemyStateMontage.Die1, 0.6f);

	FTimerHandle RepeatTimerHandle;

	GetWorld()->GetTimerManager().SetTimer
	(
		RepeatTimerHandle, this, &AC_Assassin_Enemy::DestroyEnemy, 2.1f, false
	);
}

void AC_Assassin_Enemy::CameraAction()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;
	PlayAnimMontage(enemyStateMontage.CameraAction);
}

void AC_Assassin_Enemy::Montages()
{
	//Attack
	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> NormalAttack
		(
			L"/Game/Enemy/Animation/Assassin/Montages/Frank_RPG_Assassin_Attack02_Montage"
		);
		if (NormalAttack.Succeeded() == true)  enemyAttackMontages.NormalAttack = NormalAttack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> StrongAttack
		(
			L"/Game/Enemy/Animation/Assassin/Montages/Frank_RPG_Assassin_Attack04_Montage"
		);
		if (StrongAttack.Succeeded() == true)  enemyAttackMontages.StrongAttack = StrongAttack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> DownAttack
		(
			L"/Game/Enemy/Animation/Assassin/Montages/Frank_RPG_Assassin_Attack05_Montage"
		);
		if (DownAttack.Succeeded() == true)  enemyAttackMontages.DownAttack = DownAttack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialAttack1
		(
			L"/Game/Enemy/Animation/Assassin/Montages/Frank_RPG_Assassin_Combo03_All_Montage"
		);
		if (SpecialAttack1.Succeeded() == true)  enemyAttackMontages.SpecialAttack1 = DownAttack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialAttack3
		(
			L"/Game/Enemy/Animation/Assassin/Montages/Frank_RPG_Assassin_Skill03_Montage"
		);
		if (SpecialAttack3.Succeeded() == true)  enemyAttackMontages.SpecialAttack3 = SpecialAttack3.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialAttack2
		(
			L"/Game/Enemy/Animation/Assassin/Montages/Frank_RPG_Assassin_Skill04_Montage"
		);
		if (SpecialAttack2.Succeeded() == true)  enemyAttackMontages.SpecialAttack2 = SpecialAttack2.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialAttack4
		(
			L"/Game/Enemy/Animation/Assassin/Montages/Frank_RPG_Assassin_Skill05_Montage"
		);
		if (SpecialAttack4.Succeeded() == true)  enemyAttackMontages.SpecialAttack4 = SpecialAttack4.Object;

	}
	//State
	{

		ConstructorHelpers::FObjectFinder<UAnimMontage> Die1
		(
			L"/Game/Enemy/Animation/Assassin/Montages/Frank_RPG_Assassin_Die02_Montage"
		);
		if (Die1.Succeeded() == true)  enemyStateMontage.Die1 = Die1.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> StepBack
		(
			L"/Game/Enemy/Animation/Assassin/Montages/Frank_RPG_Assassin_Tumbling_F_Montage"
		);
		if (StepBack.Succeeded() == true)  enemyStateMontage.StepBack = StepBack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> CameraAction
		(
			L"/Game/Enemy/Animation/Assassin/Montages/CameraAction_Montage"
		);
		if (CameraAction.Succeeded() == true)  enemyStateMontage.CameraAction = CameraAction.Object;

	}

	//Hit
	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> Hit
		(
			L"/Game/Enemy/Animation/Assassin/Montages/Frank_RPG_Assassin_Hit01_Montage"
		);
		if (Hit.Succeeded() == true)  enemyStateMontage.Hit = Hit.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> BackHit
		(
			L"/Game/Enemy/Animation/Assassin/Montages/Frank_RPG_Assassin_Hit03_Montage"
		);
		if (BackHit.Succeeded() == true)  enemyStateMontage.BackHit = BackHit.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> KnockBack
		(
			L"/Game/Enemy/Animation/Assassin/Montages/Frank_RPG_Assassin_Hit_Knockback_Montage"
		);
		if (KnockBack.Succeeded() == true)  enemyStateMontage.KnockBack = KnockBack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> KnockDown
		(
			L"/Game/Enemy/Animation/Assassin/Montages/Frank_RPG_Assassin_Hit_Knockdown_Loop_Montage"
		);
		if (KnockDown.Succeeded() == true)  enemyStateMontage.KnockDown = KnockDown.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> BlowAway
		(
			L"/Game/Enemy/Animation/Assassin/Montages/Frank_RPG_Assassin_Hit_Knockdown_Montage"
		);
		if (BlowAway.Succeeded() == true)  enemyStateMontage.BlowAway = BlowAway.Object;
	}

}