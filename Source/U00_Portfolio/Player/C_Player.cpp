#include "C_Player.h"
#include "Global.h"
#include "Equipment/C_PlayerWeapon.h"
#include "Equipment/C_PlayerShield.h"
#include "Equipment/C_PlayerHelmet.h"
#include "Equipment/C_PlayerFootDumy.h"
#include "C_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/Engine.h"
#include "DamageType/C_DamageType_KnockBack.h"
#include "DamageType/C_DamageType_KnockDown.h"
#include "DamageType/C_DamageType_Default.h"
#include "DamageType/C_DamageType_BlowAway.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Components/PostProcessComponent.h"
#include "Blueprint/UserWidget.h"
#include "Animation/WidgetAnimation.h"
#include "TimerManager.h"

AC_Player::AC_Player()
{

	Montages();

	ArmLengthSpeed = 3.0f;
	ArmRotationSpeed = 10.0f;
	ArmLengthTo = 450.0f;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	PlayerSpringArm = CreateDefaultSubobject<USpringArmComponent>("PlayerSpringArm");
	PlayerSpringArm->SetupAttachment(RootComponent);
	PlayerSpringArm->bUsePawnControlRotation = true;
	PlayerSpringArm->bInheritPitch = true;
	PlayerSpringArm->bInheritYaw = true;
	PlayerSpringArm->bInheritRoll = true;
	PlayerSpringArm->bDoCollisionTest = false;
	PlayerSpringArm->TargetArmLength = 650.0f;
	PlayerSpringArm->SocketOffset = FVector(0, 20.f, 50.0f);
	PlayerSpringArm->SetRelativeRotation(FRotator(0, 0, 90.0f));
	PlayerSpringArm->SetRelativeLocation(FVector(0, 0, 70.0f));
	PlayerSpringArm->CameraLagSpeed = 5.0f;
	PlayerSpringArm->CameraRotationLagSpeed = 5.0f;
	PlayerSpringArm->ProbeSize = 24.f;

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	PlayerCamera->SetupAttachment(PlayerSpringArm, USpringArmComponent::SocketName);
	//PlayerCamera->SetRelativeRotation(FRotator(0, -20.f, 0.f));

	SkillCamera = CreateDefaultSubobject<UCameraComponent>("SkillCamera");
	SkillCamera->SetupAttachment(RootComponent);
	SkillCamera->Deactivate();

	RadialBlur = CreateDefaultSubobject<UPostProcessComponent>("RadialBlur");
	RadialBlur->bEnabled = false;

	//GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	//무기
	ConstructorHelpers::FClassFinder<AC_PlayerWeapon> playerWeapon
	(
		TEXT("Blueprint'/Game/Player/BpC_PlayerWeapon.BpC_PlayerWeapon_C'")
	);
	if (playerWeapon.Succeeded() == true) PlayerWeaponClass = playerWeapon.Class;
	
	//방패
	ConstructorHelpers::FClassFinder<AC_PlayerShield> playerShield
	(
		TEXT("Blueprint'/Game/Player/BpC_PlayerShield.BpC_PlayerShield_C'")
	);
	if (playerShield.Succeeded() == true) PlayerShieldClass = playerShield.Class;


	//헬멧
	ConstructorHelpers::FClassFinder<AC_PlayerHelmet> playerHelmet
	(
		TEXT("Blueprint'/Game/Player/BpC_PlayerHelmet.BpC_PlayerHelmet_C'")
	);
	if (playerHelmet.Succeeded() == true) PlayerHelmetClass = playerHelmet.Class;

	//발
	ConstructorHelpers::FClassFinder<AC_PlayerFootDumy> playerFootDumy
	(
		TEXT("Blueprint'/Game/Player/BpC_PlayerFootDumy.BpC_PlayerFootDumy_C'")
	);
	if (playerFootDumy.Succeeded() == true) PlayerFootDumyClass = playerFootDumy.Class;

	//MontagePlayer = NewObject<UCMontagePlayer>();

}

void AC_Player::BeginPlay()
{
	Super::BeginPlay();
	
	if (BloodEffectClass != NULL)
	{
		BloodEffect = CreateWidget<UUserWidget>(GetWorld(), BloodEffectClass);
	}

	

	FActorSpawnParameters params;
	params.Owner = this;

	FTransform transform = FTransform::Identity;
	
	//무기
	PlayerWeapon = GetWorld()->SpawnActor<AC_PlayerWeapon>(PlayerWeaponClass, transform, params);
	if (PlayerWeapon != NULL)
	{
		PlayerWeapon->AttachToComponent
		(
			(USceneComponent *)GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			FName("SheathWeaponSocket")
		);
	}
	//방패
	PlayerShield = GetWorld()->SpawnActor<AC_PlayerShield>(PlayerShieldClass, transform, params);
	if (PlayerShield != NULL)
	{
		PlayerShield->AttachToComponent
		(
			(USceneComponent *)GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			FName("ShieldSocket")
		);
	}

	//뚝배기
	PlayerHelmet = GetWorld()->SpawnActor<AC_PlayerHelmet>(PlayerHelmetClass, transform, params);
	if (PlayerHelmet != NULL)
	{
		PlayerHelmet->AttachToComponent
		(
			(USceneComponent *)GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			FName("HelmetSocket")
		);
	}

	//발
	PlayerFootDumy = GetWorld()->SpawnActor<AC_PlayerFootDumy>(PlayerFootDumyClass, transform, params);
	if (PlayerFootDumy != NULL)
	{
		PlayerFootDumy->AttachToComponent
		(
			(USceneComponent *)GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			FName("FootDumySocket")
		);
	}

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AC_Player::OnHitOverlap);
	
	GetController()->bFindCameraComponentWhenViewTarget = true;
}

void AC_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AC_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AC_Player::OnHitOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this) return;
	if (OtherActor == GetOwner()) return;
	if (OtherActor->ActorHasTag("Map") == true) return;
	if (OtherActor->ActorHasTag("Trigger") == true) return;
	if (OtherActor->ActorHasTag("Enemy") == true) return;
	
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

float AC_Player::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	
	if (bGetHit == false)
	{
		if (bCanBlock == true)
		{
			if (DamageEvent.DamageTypeClass == UC_DamageType_KnockDown::StaticClass() ||
				DamageEvent.DamageTypeClass == UC_DamageType_BlowAway::StaticClass() ||
				DamageEvent.DamageTypeClass == UC_DamageType_KnockBack::StaticClass())
			{
				PlayAnimMontage(StateMontages.KnockBack);
			}
			else
				PlayAnimMontage(StateMontages.Block, 0.8f);
		}
		else
		{
			if (DamageEvent.DamageTypeClass == UC_DamageType_KnockDown::StaticClass())
				PlayAnimMontage(StateMontages.KnockDown);
			else if (DamageEvent.DamageTypeClass == UC_DamageType_KnockBack::StaticClass())
				PlayAnimMontage(StateMontages.KnockBack);
			else if (DamageEvent.DamageTypeClass == UC_DamageType_BlowAway::StaticClass())
			{
				LaunchCharacter(-(GetActorForwardVector()* 500.0f) + FVector(0, 0, 700.0f), true, true);
				PlayAnimMontage(StateMontages.BlowAway, 0.8f);
			}
				
			else if (DamageEvent.DamageTypeClass == UC_DamageType_Default::StaticClass())
			{
				//음수면 정면에서 처맞은거
				if (FrontBackResult < 0.1f)
				{
					if (LeftRightResult > 0.1f)
						PlayAnimMontage(StateMontages.LeftHit);
					else if (LeftRightResult < 0.1f)
						PlayAnimMontage(StateMontages.RightHit);
				}
				else if(FrontBackResult > 0.1f)
					PlayAnimMontage(StateMontages.BackHit);
			}
			
		}
		
	}

	return FinalDamage;
}

void AC_Player::TeleportingToTwoHand()
{
	if (bTeleporting == true) return;


	PlayAnimMontage(StateMontages.Teleport,0.8f);

	FTimerHandle RepeatTimerHandle;

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.7f);

	GetWorld()->GetTimerManager().SetTimer
	(
		RepeatTimerHandle, this, &AC_Player::TeleportToTwoHand, 1.5f, false
	);
}
void AC_Player::TeleportToTwoHand()
{
	//TwoHandEnemyRoomLocation
	SetActorLocation(FVector(-7245.f, 9171.f, 1000.0f));
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);

}

void AC_Player::TeleportingToKatana()
{
	if (bTeleporting == true) return;


	PlayAnimMontage(StateMontages.Teleport,0.8f);

	FTimerHandle RepeatTimerHandle;

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.7f);

	GetWorld()->GetTimerManager().SetTimer
	(
		RepeatTimerHandle, this, &AC_Player::TeleportToKatana, 1.5f, false
	);
}

void AC_Player::TeleportToKatana()
{
	//KatanaRoomLocation
	SetActorLocation(FVector(5360.f, 9517.f, 2500.f));
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}

void AC_Player::TeleportingToAssassin()
{
	if (bTeleporting == true) return;


	PlayAnimMontage(StateMontages.Teleport, 0.8f);

	FTimerHandle RepeatTimerHandle;

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.7f);

	GetWorld()->GetTimerManager().SetTimer
	(
		RepeatTimerHandle, this, &AC_Player::TeleportToAssassin, 1.5f, false
	);
}

void AC_Player::TeleportToAssassin()
{
	SetActorLocation(FVector(5403.f, 1635.f, 4000.f));
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}

void AC_Player::Montages()
{
	//Attack
	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> MovingNormalAttack
		(
			L"/Game/Player/Montages/MovingNormalAttack_Montage"
		);
		if (MovingNormalAttack.Succeeded() == true)  DirectionalMontages.MovingNormalAttack = MovingNormalAttack.Object;
		
		ConstructorHelpers::FObjectFinder<UAnimMontage> StopNormalAttack
		(
			L"/Game/Player/Montages/StopNormalAttack_Montage"
		);
		if (StopNormalAttack.Succeeded() == true)  DirectionalMontages.StopNormalAttack = StopNormalAttack.Object;
		
		ConstructorHelpers::FObjectFinder<UAnimMontage> LeftAttack
		(
			L"/Game/Player/Montages/LeftAttack_Montage"
		);
		if (LeftAttack.Succeeded() == true)  DirectionalMontages.LeftAttack = LeftAttack.Object;
		
		ConstructorHelpers::FObjectFinder<UAnimMontage> RightAttack
		(
			L"/Game/Player/Montages/RightAttack_Montage"
		);
		if (RightAttack.Succeeded() == true)  DirectionalMontages.RightAttack = RightAttack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> NormalAttackCombo1
		(
			L"/Game/Player/Montages/NormalAttackCombo1_Montage"
		);
		if (NormalAttackCombo1.Succeeded() == true)  DirectionalMontages.NormalAttackCombo1 = NormalAttackCombo1.Object;
	
		ConstructorHelpers::FObjectFinder<UAnimMontage> NormalAttackCombo2
		(
			L"/Game/Player/Montages/NormalAttackCombo2_Montage"
		);
		if (NormalAttackCombo2.Succeeded() == true)  DirectionalMontages.NormalAttackCombo2 = NormalAttackCombo2.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> Kick
		(
			L"/Game/Player/Montages/Kick_Montage"
		);
		if (Kick.Succeeded() == true)  DirectionalMontages.Kick = Kick.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> KickCombo2
		(
			L"/Game/Player/Montages/Kick_Combo2_Montage"
		);
		if (KickCombo2.Succeeded() == true)  DirectionalMontages.KickCombo2 = KickCombo2.Object;
	
		ConstructorHelpers::FObjectFinder<UAnimMontage> KickCombo3
		(
			L"/Game/Player/Montages/Kick_Combo3_Montage"
		);
		if (KickCombo3.Succeeded() == true)  DirectionalMontages.KickCombo3 = KickCombo3.Object;
		
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpKnockDownAttack
		(
			L"/Game/Player/Montages/Jump_KnockDownAttack_Montage"
		);
		if (JumpKnockDownAttack.Succeeded() == true)  DirectionalMontages.JumpKnockDownAttack = JumpKnockDownAttack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> DashBlowAwayAttack
		(
			L"/Game/Player/Montages/Dash_BlowAway_Attack_Montage"
		);
		if (DashBlowAwayAttack.Succeeded() == true)  DirectionalMontages.DashBlowAwayAttack = DashBlowAwayAttack.Object;
		
		ConstructorHelpers::FObjectFinder<UAnimMontage> StepBackCombo1
		(
			L"/Game/Player/Montages/StepBackCombo_Montage"
		);
		if (StepBackCombo1.Succeeded() == true)  DirectionalMontages.StepBackCombo1 = StepBackCombo1.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> StepBackCombo2
		(
			L"/Game/Player/Montages/StepBackCombo2_Montage"
		);
		if (StepBackCombo2.Succeeded() == true)  DirectionalMontages.StepBackCombo2 = StepBackCombo2.Object;
		
		ConstructorHelpers::FObjectFinder<UAnimMontage> ShieldAttack
		(
			L"/Game/Player/Montages/ShieldAttack_Montage"
		);
		if (ShieldAttack.Succeeded() == true)  DirectionalMontages.ShieldAttack = ShieldAttack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> ShieldAttackCombo
		(
			L"/Game/Player/Montages/ShieldAttackCombo_Montage"
		);
		if (ShieldAttackCombo.Succeeded() == true)  DirectionalMontages.ShieldAttackCombo = ShieldAttackCombo.Object;
		
		ConstructorHelpers::FObjectFinder<UAnimMontage> ShieldAttackCombo2
		(
			L"/Game/Player/Montages/ShieldAttackCombo2_Montage"
		);
		if (ShieldAttackCombo2.Succeeded() == true)  DirectionalMontages.ShieldAttackCombo2 = ShieldAttackCombo2.Object;
		
		ConstructorHelpers::FObjectFinder<UAnimMontage> ShieldAttackCombo3
		(
			L"/Game/Player/Montages/ShieldAttackCombo3_Montage"
		);
		if (ShieldAttackCombo3.Succeeded() == true)  DirectionalMontages.ShieldAttackCombo3 = ShieldAttackCombo3.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> DashShieldAttack
		(
			L"/Game/Player/Montages/Dash_ShieldAttack_Montage"
		);
		if (ShieldAttackCombo3.Succeeded() == true)  DirectionalMontages.DashShieldAttack = DashShieldAttack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> SpecialAttack
		(
			L"/Game/Player/Montages/SpecialAttack_Montage"
		);
		if (SpecialAttack.Succeeded() == true)  DirectionalMontages.SpecialAttack = SpecialAttack.Object;
	
	}

	//Step
	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> EvadeForward
		(
			L"/Game/Player/Montages/Evade_Forward_Montage"
		);
		if (EvadeForward.Succeeded() == true)  DirectionalMontages.EvadeForward = EvadeForward.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> EvadeBack
		(
			L"/Game/Player/Montages/Evade_Back_Montage"
		);
		if (EvadeBack.Succeeded() == true)  DirectionalMontages.EvadeBack = EvadeBack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> EvadeLeft
		(
			L"/Game/Player/Montages/Evade_Left_Montage"
		);
		if (EvadeLeft.Succeeded() == true)  DirectionalMontages.EvadeLeft = EvadeLeft.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> EvadeRight
		(
			L"/Game/Player/Montages/Evade_Right_Montage"
		);
		if (EvadeRight.Succeeded() == true)  DirectionalMontages.EvadeRight = EvadeRight.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> StepLeft
		(
			L"/Game/Player/Montages/Step_Left_Montage"
		);
		if (StepLeft.Succeeded() == true)  DirectionalMontages.StepLeft = StepLeft.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> StepRight
		(
			L"/Game/Player/Montages/Step_Right_Montage"
		);
		if (StepRight.Succeeded() == true)  DirectionalMontages.StepRight = StepRight.Object;


		ConstructorHelpers::FObjectFinder<UAnimMontage> StepForward
		(
			L"/Game/Player/Montages/Step_Forward_Montage"
		);
		if (StepForward.Succeeded() == true)  DirectionalMontages.StepForward = StepForward.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> StepBack
		(
			L"/Game/Player/Montages/Step_Back_Montage"
		);
		if (StepBack.Succeeded() == true)  DirectionalMontages.StepBack = StepBack.Object;

	
	}

	//State
	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> StopEquip
		(
			L"/Game/Player/Montages/StopEquip_Montage"
		);
		if (StopEquip.Succeeded() == true)  StateMontages.StopEquip = StopEquip.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> StopUnequip
		(
			L"/Game/Player/Montages/StopUnequip_Montage"
		);
		if (StopUnequip.Succeeded() == true)  StateMontages.StopUnequip = StopUnequip.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> MovingEquip
		(
			L"/Game/Player/Montages/MovingEquip_Montage"
		);
		if (MovingEquip.Succeeded() == true)  StateMontages.MovingEquip = MovingEquip.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> MovingUnequip
		(
			L"/Game/Player/Montages/MovingUnequip_Montage"
		);
		if (MovingUnequip.Succeeded() == true)  StateMontages.MovingUnequip = MovingUnequip.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> Guard
		(
			L"/Game/Player/Montages/Guard_Montage"
		);
		if (Guard.Succeeded() == true)  StateMontages.Guard = Guard.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> Block
		(
			L"/Game/Player/Montages/Block1_Montage"
		);
		if (Block.Succeeded() == true)  StateMontages.Block = Block.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> Teleport
		(
			L"/Game/Player/Montages/Teleport_Montage"
		);
		if (Teleport.Succeeded() == true)  StateMontages.Teleport = Teleport.Object;
	}

	//Hit
	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> BackHit
		(
			L"/Game/Player/Montages/BackHit_Montage"
		);
		if (BackHit.Succeeded() == true)  StateMontages.BackHit = BackHit.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> LeftHit
		(
			L"/Game/Player/Montages/LeftHit_Montage"
		);
		if (LeftHit.Succeeded() == true)  StateMontages.LeftHit = LeftHit.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> RightHit
		(
			L"/Game/Player/Montages/RightHit_Montage"
		);
		if (RightHit.Succeeded() == true)  StateMontages.RightHit = RightHit.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> KnockBack
		(
			L"/Game/Player/Montages/Hit_KnockBack_Montage"
		);
		if (KnockBack.Succeeded() == true)  StateMontages.KnockBack = KnockBack.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> KnockDown
		(
			L"/Game/Player/Montages/Hit_KnockDown_Montage"
		);
		if (KnockDown.Succeeded() == true)  StateMontages.KnockDown = KnockDown.Object;

		ConstructorHelpers::FObjectFinder<UAnimMontage> BlowAway
		(
			L"/Game/Player/Montages/BlowAway_IP_Montage"
		);
		if (BlowAway.Succeeded() == true)  StateMontages.BlowAway = BlowAway.Object;

		/*ConstructorHelpers::FObjectFinder<UAnimMontage> BlowAway
		(
			L"/Game/Player/Montages/BlowAway_IP_Montage"
		);
		if (BlowAway.Succeeded() == true)  StateMontages.BlowAway = BlowAway.Object;*/

	}

}



