#include "C_PlayerWeapon.h"
#include "Global.h"
#include "Player/C_Player.h"
#include "Player/C_PlayerController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/DamageType.h"
#include "DamageType/C_DamageType_KnockBack.h"
#include "DamageType/C_DamageType_KnockDown.h"
#include "DamageType/C_DamageType_Default.h"
#include "DamageType/C_DamageType_BlowAway.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"

AC_PlayerWeapon::AC_PlayerWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerWeaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(FName("PlayerWeapon"));
	RootComponent = PlayerWeaponMeshComp;

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(FName("WeaponCapsule"));

	CapsuleCollision->SetupAttachment(PlayerWeaponMeshComp);
	CapsuleCollision->SetCapsuleHalfHeight(220);
	CapsuleCollision->SetCapsuleRadius(22);
	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponDamage = 10.f;
}

void AC_PlayerWeapon::BeginPlay()
{
	Super::BeginPlay();

	CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &AC_PlayerWeapon::OnBeginOverlap);
	
}

void AC_PlayerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_PlayerWeapon::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this) return;
	if (OtherActor == GetOwner()) return;
	if (OtherActor->ActorHasTag("Map") == true) return;
	if (OtherActor->ActorHasTag("Trigger") == true) return;
	//if (OtherActor->ActorHasTag("DM") == true) return;

	AC_Player* Player = Cast<AC_Player>(GetOwner());
	if (Player == NULL) return;
	AC_PlayerController* AIController = Cast<AC_PlayerController>(Player->GetController());

	if (DamageEvent.DamageTypeClass == UC_DamageType_BlowAway::StaticClass())
	{
		if(AIController != NULL && OtherActor->ActorHasTag("DM") == false)
			AIController->ASetTargetWithBlend(OtherActor);
	}
	
	if (SweepResult.Actor != NULL)
	{
		SweepResult.Actor->TakeDamage(WeaponDamage, DamageEvent, GetOwner()->GetInstigatorController(), this);
	}
	
}




