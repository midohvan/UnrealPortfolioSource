#include "C_2H_Enemy.h"
#include "Global.h"
#include "Equipments/C_2H_Helmet.h"
#include "Equipments/C_2H_Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enemy/C_EnemyAIController.h"
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

AC_2H_Enemy::AC_2H_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Montages();

	//MontagePlayer = NewObject<UCMontagePlayer>();

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	HealthPoint = 100.0f;

	Enemy_PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("2H_PawnSensingComp"));

	Enemy_PawnSensingComp->SetPeripheralVisionAngle(45.0f);
	
	Enemy_SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(FName("2H_SpringArmComp"));
	Enemy_SpringArmComp->SetupAttachment(RootComponent);
	Enemy_SpringArmComp->bUsePawnControlRotation = false;
	Enemy_SpringArmComp->bInheritPitch = true;
	Enemy_SpringArmComp->bInheritYaw = true;
	Enemy_SpringArmComp->bInheritRoll = true;
	Enemy_SpringArmComp->bDoCollisionTest = false;
	Enemy_SpringArmComp->bEnableCameraLag = true;
	Enemy_SpringArmComp->bEnableCameraRotationLag = true;
	Enemy_SpringArmComp->SetRelativeRotation(FRotator(0.f, -180, 0.f));
	Enemy_SpringArmComp->TargetArmLength = 400.f;
	Enemy_SpringArmComp->SocketOffset = FVector(0.f, 40.f, -80.f);

	Enemy_CameraComp = CreateDefaultSubobject<UCameraComponent>(FName("2H_CameraComp"));
	Enemy_CameraComp->SetupAttachment(Enemy_SpringArmComp);
	Enemy_CameraComp->SetRelativeLocation(FVector(-108, 0.f, 130.f));
	Enemy_CameraComp->SetRelativeRotation(FRotator(0, 12.f, 0.f));


	Enemy_BloodComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("2H_Blood"));
	Enemy_BloodComp->SetupAttachment(RootComponent);
	Enemy_BloodComp->bAutoActivate = false;

	ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset
	(
		TEXT("/Game/FXVillesBloodVFXPack/Particles/PS_StyleBlood_Slice")
	);
	if (ParticleAsset.Succeeded() == true) Enemy_Blood = ParticleAsset.Object;

	//무기
	ConstructorHelpers::FClassFinder<AC_2H_Weapon> twoHandWeapon
	(
		TEXT("Blueprint'/Game/Enemy/BpC_2H_Weapon.BpC_2H_Weapon_C'")
	);
	if (twoHandWeapon.Succeeded() == true) WeaponClass = twoHandWeapon.Class;
	//헬멧
	ConstructorHelpers::FClassFinder<AC_2H_Helmet> enemyHelmet
	(
		TEXT("Blueprint'/Game/Enemy/BpC_2H_Helmet.BpC_2H_Helmet_C'")
	);
	if (enemyHelmet.Succeeded() == true) HelmetClass = enemyHelmet.Class;

}

void AC_2H_Enemy::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AC_2H_Enemy::OnHitOverlap);

	if (Enemy_PawnSensingComp != NULL)
	{
		Enemy_PawnSensingComp->OnSeePawn.AddDynamic(this, &AC_2H_Enemy::OnSeePlayer);
	}

	FActorSpawnParameters params;
	params.Owner = this;

	FTransform transform = FTransform::Identity;

	//무기
	Weapon = GetWorld()->SpawnActor<AC_2H_Weapon>(WeaponClass, transform, params);
	if (Weapon != NULL)
	{
		Weapon->AttachToComponent
		(
			(USceneComponent *)GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			FName("WeaponSocket")
		);
	}

	//뚝배기
	Helmet = GetWorld()->SpawnActor<AC_2H_Helmet>(HelmetClass, transform, params);
	if (Helmet != NULL)
	{
		Helmet->AttachToComponent
		(
			(USceneComponent *)GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			FName("HelmetSocket")
		);
	}

	
}

void AC_2H_Enemy::OnSeePlayer(APawn* InPawn)
{
	if (InPawn->ActorHasTag("Enemy") == true) return;

	AC_EnemyAIController* AIController = Cast<AC_EnemyAIController>(GetController());
	if (AIController != NULL)
	{
		AIController->SetSeenTarget(InPawn);
	}
}

void AC_2H_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_2H_Enemy::OnHitOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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

float AC_2H_Enemy::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
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
					PlayAnimMontage(enemyStateMontage.BackHit);
				else if (FrontBackResult < 0.5f)
					PlayAnimMontage(enemyStateMontage.Hit);
			}

		}

		HealthPoint -= FinalDamage;
	}
	
	if (Enemy_BloodComp != NULL)
	{
		Enemy_BloodComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Enemy_Blood, GetMesh()->GetSocketLocation("spine_01"), FRotator::ZeroRotator);
		Enemy_BloodComp->ActivateSystem();
	}

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Magenta, FString::Printf(L"%f", FinalDamage));

	return FinalDamage;
}

void AC_2H_Enemy::DestroyEnemy()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
	Weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	Helmet->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);

	Weapon->GetCapsuleComponent()->SetSimulatePhysics(true);
	Weapon->GetCapsuleComponent()->SetSimulatePhysics(true);
	
	Weapon->Destroy();
	Helmet->Destroy();
	this->Destroy();

}


void AC_2H_Enemy::NormalAttack()
{
	if (GetAttacking() == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;


	PlayAnimMontage(enemyAttackMontages.NormalAttack);
}

void AC_2H_Enemy::StrongAttack()
{
	if (GetAttacking() == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyAttackMontages.StrongAttack);

}

void AC_2H_Enemy::DownAttack()
{
	if (GetAttacking() == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyAttackMontages.NormalAttack);

}

void AC_2H_Enemy::SpecialAttack1()
{
	if (bIsAttacking == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyAttackMontages.SpecialAttack1);


}

void AC_2H_Enemy::SpecialAttack2()
{
	if (bIsAttacking == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyAttackMontages.SpecialAttack2);


}

void AC_2H_Enemy::SpecialAttack3()
{
	if (bIsAttacking == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyAttackMontages.SpecialAttack3);


}

void AC_2H_Enemy::SpecialAttack4()
{
	if (bIsAttacking == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyAttackMontages.SpecialAttack4);


}

void AC_2H_Enemy::Guard()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;
	
	PlayAnimMontage(enemyStateMontage.Guard);

}

void AC_2H_Enemy::StepBack()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;
	
	PlayAnimMontage(enemyStateMontage.StepBack);

}

void AC_2H_Enemy::StepLeft()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyStateMontage.StepLeft);
}

void AC_2H_Enemy::StepRight()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyStateMontage.StepRight);
}

void AC_2H_Enemy::Dead()
{
	if (bDying == true) return;
	
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.3f);
	
	PlayAnimMontage(enemyStateMontage.Die1);

	FTimerHandle RepeatTimerHandle;

	GetWorld()->GetTimerManager().SetTimer
	(
		RepeatTimerHandle, this, &AC_2H_Enemy::DestroyEnemy, 2.1f, false
	);

}

void AC_2H_Enemy::CameraAction()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;
	PlayAnimMontage(enemyStateMontage.CameraAction);
}

void AC_2H_Enemy::NoTargetACtion()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;
	PlayAnimMontage(enemyStateMontage.NoTargetAction);
}
void AC_2H_Enemy::Montages()
{
	//Attack
	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> NormalAttack
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_NormalAttack_Montage"
		);
		if (NormalAttack.Succeeded() == true)  enemyAttackMontages.NormalAttack = NormalAttack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> StrongAttack
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_Heavy_Montage"
		);
		if (StrongAttack.Succeeded() == true)  enemyAttackMontages.StrongAttack = StrongAttack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> DownAttack
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_StrongAttack_Montage"
		);
		if (DownAttack.Succeeded() == true)  enemyAttackMontages.DownAttack = DownAttack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialAttack1
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_WhirlWind_Montage"
		);
		if (SpecialAttack1.Succeeded() == true)  enemyAttackMontages.SpecialAttack1 = DownAttack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialAttack3
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_Combo_Montage"
		);
		if (SpecialAttack3.Succeeded() == true)  enemyAttackMontages.SpecialAttack3 = SpecialAttack3.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialAttack2
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_Combo5_All_Montage"
		);
		if (SpecialAttack2.Succeeded() == true)  enemyAttackMontages.SpecialAttack2 = SpecialAttack2.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialAttack4
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_RollingAttack_Montage"
		);
		if (SpecialAttack4.Succeeded() == true)  enemyAttackMontages.SpecialAttack4 = SpecialAttack4.Object;

	}
	//State
	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> Guard
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_Guard_Montage"
		);
		if (Guard.Succeeded() == true)  enemyStateMontage.Guard = Guard.Object;
		
		ConstructorHelpers::FObjectFinder<UAnimMontage> Block
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_Block_Montage"
		);
		if (Block.Succeeded() == true)  enemyStateMontage.Block = Block.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> Die1
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_Death_Montage"
		);
		if (Die1.Succeeded() == true)  enemyStateMontage.Die1 = Die1.Object;
		
		ConstructorHelpers::FObjectFinder<UAnimMontage> Getup
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_Getup_Montage"
		);
		if (Getup.Succeeded() == true)  enemyStateMontage.Getup = Getup.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> StepBack
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_StepBack_Montage"
		);
		if (StepBack.Succeeded() == true)  enemyStateMontage.StepBack = StepBack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> StepLeft
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_StepLeft_Montage"
		);
		if (StepLeft.Succeeded() == true)  enemyStateMontage.StepLeft = StepLeft.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> StepRight
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_StepRight_Montage"
		);
		if (StepRight.Succeeded() == true)  enemyStateMontage.StepRight = StepRight.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> CameraAction
		(
			L"/Game/Enemy/Animation/2Hand/Montages/CameraAction_Montage"
		);
		if (CameraAction.Succeeded() == true)  enemyStateMontage.CameraAction = CameraAction.Object;
		
		ConstructorHelpers::FObjectFinder<UAnimMontage> NoTargetAction
		(
			L"/Game/Enemy/Animation/2Hand/Montages/NoTargetAction_Montage"
		);
		if (NoTargetAction.Succeeded() == true)  enemyStateMontage.NoTargetAction = NoTargetAction.Object;


	}

	//Hit
	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> Hit
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_Hit_Montage"
		);
		if (Hit.Succeeded() == true)  enemyStateMontage.Hit = Hit.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> BackHit
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_BackHit_Montage"
		);
		if (BackHit.Succeeded() == true)  enemyStateMontage.BackHit = BackHit.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> KnockBack
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_KnockBack_Montage"
		);
		if (KnockBack.Succeeded() == true)  enemyStateMontage.KnockBack = KnockBack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> KnockDown
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_KnockDown_Montage"
		);
		if (KnockDown.Succeeded() == true)  enemyStateMontage.KnockDown = KnockDown.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> BlowAway
		(
			L"/Game/Enemy/Animation/2Hand/Montages/2H_BlowAway_IP_Montage"
		);
		if (BlowAway.Succeeded() == true)  enemyStateMontage.BlowAway = BlowAway.Object;
	}

}




