#include "C_Katana_Enemy.h"
#include "Global.h"
#include "Equipments/C_KatanaHelmet.h"
#include "Equipments/C_Katana.h"
#include "C_KatanaAIController.h"
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

AC_Katana_Enemy::AC_Katana_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Montages();

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	HealthPoint = 100.0f;

	Katana_PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Katana_PawnSensingComp"));

	Katana_PawnSensingComp->SetPeripheralVisionAngle(60.0f);

	Katana_SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(FName("Katana_SpringArmComp"));
	Katana_SpringArmComp->SetupAttachment(RootComponent);
	Katana_SpringArmComp->bUsePawnControlRotation = false;
	Katana_SpringArmComp->bInheritPitch = true;
	Katana_SpringArmComp->bInheritYaw = true;
	Katana_SpringArmComp->bInheritRoll = true;
	Katana_SpringArmComp->bDoCollisionTest = false;
	Katana_SpringArmComp->bEnableCameraLag = true;
	Katana_SpringArmComp->bEnableCameraRotationLag = true;
	Katana_SpringArmComp->SetRelativeRotation(FRotator(0.f, -180, 0.f));
	Katana_SpringArmComp->TargetArmLength = 400.0f;
	Katana_SpringArmComp->SocketOffset = FVector(0.f, 40.f, -80.f);

	Katana_CameraComp = CreateDefaultSubobject<UCameraComponent>(FName("Katana_CameraComp"));
	Katana_CameraComp->SetupAttachment(Katana_SpringArmComp);
	Katana_CameraComp->SetRelativeLocation(FVector(-108, 0.f, 130.f));
	Katana_CameraComp->SetRelativeRotation(FRotator(180.f, 12.f, 0.f));

	Katana_BloodComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Katana_Blood"));
	Katana_BloodComp->SetupAttachment(RootComponent);
	Katana_BloodComp->bAutoActivate = false;


	ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset
	(
		TEXT("/Game/FXVillesBloodVFXPack/Particles/PS_StyleBlood_Slash_Omni_LRG")
	);
	if (ParticleAsset.Succeeded() == true) Katana_Blood = ParticleAsset.Object;

	//무기
	ConstructorHelpers::FClassFinder<AC_Katana> Katana
	(
		TEXT("Blueprint'/Game/Enemy/BpC_Katana.BpC_Katana_C'")
	);
	if (Katana.Succeeded() == true) WeaponClass = Katana.Class;
	//헬멧
	ConstructorHelpers::FClassFinder<AC_KatanaHelmet> KatanaHelmet
	(
		TEXT("Blueprint'/Game/Enemy/BpC_KatanaHelmet.BpC_KatanaHelmet_C'")
	);
	if (KatanaHelmet.Succeeded() == true) HelmetClass = KatanaHelmet.Class;

}

void AC_Katana_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AC_Katana_Enemy::OnHitOverlap);

	if (Katana_PawnSensingComp != NULL)
	{
		Katana_PawnSensingComp->OnSeePawn.AddDynamic(this, &AC_Katana_Enemy::OnSeePlayer);
	}

	FActorSpawnParameters params;
	params.Owner = this;

	FTransform transform = FTransform::Identity;

	//무기
	Weapon = GetWorld()->SpawnActor<AC_Katana>(WeaponClass, transform, params);
	if (Weapon != NULL)
	{
		Weapon->AttachToComponent
		(
			(USceneComponent *)GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
			FName("WeaponSocket")
		);
	}

	//뚝배기
	Helmet = GetWorld()->SpawnActor<AC_KatanaHelmet>(HelmetClass, transform, params);
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

void AC_Katana_Enemy::OnSeePlayer(APawn * InPawn)
{
	if (InPawn->ActorHasTag("Enemy") == true) return;

	AC_KatanaAIController* AIController = Cast<AC_KatanaAIController>(GetController());
	if (AIController != NULL)
	{
		AIController->SetSeenTarget(InPawn);
	}
}

void AC_Katana_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_Katana_Enemy::OnHitOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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

float AC_Katana_Enemy::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
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

	if (Katana_BloodComp != NULL)
	{
		Katana_BloodComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Katana_Blood, GetMesh()->GetSocketLocation("spine_01"), FRotator::ZeroRotator);
		Katana_BloodComp->ActivateSystem();
	}

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Magenta, FString::Printf(L"%f", FinalDamage));

	return FinalDamage;
}

void AC_Katana_Enemy::DestroyEnemy()
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

void AC_Katana_Enemy::NormalAttack()
{
	if (GetAttacking() == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyAttackMontages.NormalAttack);
}

void AC_Katana_Enemy::StrongAttack()
{
	if (GetAttacking() == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyAttackMontages.StrongAttack);

}

void AC_Katana_Enemy::DownAttack()
{
	if (GetAttacking() == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;
	
	PlayAnimMontage(enemyAttackMontages.DownAttack);

}

void AC_Katana_Enemy::SpecialAttack1()
{
	if (bIsAttacking == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyAttackMontages.SpecialAttack1);

}

void AC_Katana_Enemy::SpecialAttack2()
{
	if (bIsAttacking == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;
	PlayAnimMontage(enemyAttackMontages.SpecialAttack2);

}

void AC_Katana_Enemy::SpecialAttack3()
{
	if (bIsAttacking == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyAttackMontages.SpecialAttack3);

}

void AC_Katana_Enemy::SpecialAttack4()
{
	if (bIsAttacking == true) return;
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyAttackMontages.SpecialAttack4);

}

void AC_Katana_Enemy::Guard()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;
	PlayAnimMontage(enemyStateMontage.Guard);

}

void AC_Katana_Enemy::StepBack()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyStateMontage.StepBack);

}

void AC_Katana_Enemy::StepLeft()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;

	PlayAnimMontage(enemyStateMontage.StepLeft);
}

void AC_Katana_Enemy::StepRight()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;
	PlayAnimMontage(enemyStateMontage.StepRight);
}

void AC_Katana_Enemy::Dead()
{
	if (bDying == true) return;

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.3f);
	PlayAnimMontage(enemyStateMontage.Die1,0.5f);

	FTimerHandle RepeatTimerHandle;

	GetWorld()->GetTimerManager().SetTimer
	(
		RepeatTimerHandle, this, &AC_Katana_Enemy::DestroyEnemy, 2.1f, false
	);
}

void AC_Katana_Enemy::CameraAction()
{
	if (GetMesh()->GetAnimInstance()->IsAnyMontagePlaying() == true) return;
	PlayAnimMontage(enemyStateMontage.CameraAction);
}
void AC_Katana_Enemy::Montages()
{
	//Attack
	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> NormalAttack
		(
			L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_S1_Attack02_Montage"
		);
		if (NormalAttack.Succeeded() == true)  enemyAttackMontages.NormalAttack = NormalAttack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> StrongAttack
		(
			L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_S2_Attack03_Montage"
		);
		if (StrongAttack.Succeeded() == true)  enemyAttackMontages.StrongAttack = StrongAttack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> DownAttack
		(
			L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_S3_Attack03_Montage"
		);
		if (DownAttack.Succeeded() == true)  enemyAttackMontages.DownAttack = DownAttack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialAttack1
		(
			L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_S2_Skill01_Montage"
		);
		if (SpecialAttack1.Succeeded() == true)  enemyAttackMontages.SpecialAttack1 = DownAttack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialAttack3
		(
			L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_S2_Combo02_All_Montage"
		);
		if (SpecialAttack3.Succeeded() == true)  enemyAttackMontages.SpecialAttack3 = SpecialAttack3.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialAttack2
		(
			L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_S3_Skill02_Montage"
		);
		if (SpecialAttack2.Succeeded() == true)  enemyAttackMontages.SpecialAttack2 = SpecialAttack2.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialAttack4
		(
			L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_S1_Skill01_Montage"
		);
		if (SpecialAttack4.Succeeded() == true)  enemyAttackMontages.SpecialAttack4 = SpecialAttack4.Object;

	}
	//State
	{

		ConstructorHelpers::FObjectFinder<UAnimMontage> Die1
		(
			L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_Die01_Montage"
		);
		if (Die1.Succeeded() == true)  enemyStateMontage.Die1 = Die1.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> StepBack
		(
			L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_Tumbling_B_Montage"
		);
		if (StepBack.Succeeded() == true)  enemyStateMontage.StepBack = StepBack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> CameraAction
		(
			L"/Game/Enemy/Animation/Katana/Montages/CameraAction_Montage"
		);
		if (CameraAction.Succeeded() == true)  enemyStateMontage.CameraAction = CameraAction.Object;

	}

	//Hit
	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> Hit
		(
			L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_Hit01_Montage"
		);
		if (Hit.Succeeded() == true)  enemyStateMontage.Hit = Hit.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> BackHit
		(
			L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_Hit03_Montage"
		);
		if (BackHit.Succeeded() == true)  enemyStateMontage.BackHit = BackHit.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> KnockBack
		(
			L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_Hit_Knockback_Montage"
		);
		if (KnockBack.Succeeded() == true)  enemyStateMontage.KnockBack = KnockBack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> KnockDown
		(
			L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_Hit_Knockdown_Loop_Montage"
		);
		if (KnockDown.Succeeded() == true)  enemyStateMontage.KnockDown = KnockDown.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> BlowAway
		(
			L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_Hit_Knockdown_Montage"
		);
		if (BlowAway.Succeeded() == true)  enemyStateMontage.BlowAway = BlowAway.Object;
	}

}