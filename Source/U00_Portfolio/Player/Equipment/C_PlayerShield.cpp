#include "C_PlayerShield.h"
#include "Global.h"
#include "Player/C_Player.h"
#include "Player/C_PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/DamageType.h"



AC_PlayerShield::AC_PlayerShield()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerShieldMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("PlayerShield"));
	RootComponent = PlayerShieldMeshComp;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("ShieldBox"));
	BoxCollision->SetupAttachment(PlayerShieldMeshComp);
	BoxCollision->SetBoundsScale(50);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ShieldDamage = 5.f;

}

void AC_PlayerShield::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AC_PlayerShield::OnBeginOverlap);
}

void AC_PlayerShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AC_PlayerShield::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this) return;
	if (OtherActor == GetOwner()) return;
	if (OtherActor->ActorHasTag("Trigger") == true) return;

	SweepResult.Actor->TakeDamage(ShieldDamage, DamageEvent, GetOwner()->GetInstigatorController(), this);

}

