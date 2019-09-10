#include "C_PlayerFootDumy.h"
#include "Global.h"
#include "Player/C_Player.h"
#include "Player/C_PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/DamageType.h"
#include "DamageType/C_DamageType_KnockBack.h"



AC_PlayerFootDumy::AC_PlayerFootDumy()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerFootDumyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("PlayerShield"));
	RootComponent = PlayerFootDumyMeshComp;

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(FName("ShieldBox"));
	CapsuleCollision->SetupAttachment(PlayerFootDumyMeshComp);
	CapsuleCollision->SetBoundsScale(50);
	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
}


void AC_PlayerFootDumy::BeginPlay()
{
	Super::BeginPlay();
	CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &AC_PlayerFootDumy::OnBeginOverlap);

}

void AC_PlayerFootDumy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_PlayerFootDumy::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this) return;
	if (OtherActor == GetOwner()) return;
	if (OtherActor->ActorHasTag("Trigger") == true) return;


	FDamageEvent DamageEvent(UC_DamageType_KnockBack::StaticClass());

	SweepResult.Actor->TakeDamage(KickDamage, DamageEvent, GetOwner()->GetInstigatorController(), this);

}

