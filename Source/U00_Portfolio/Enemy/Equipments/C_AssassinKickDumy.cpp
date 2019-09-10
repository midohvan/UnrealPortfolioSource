#include "C_AssassinKickDumy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/DamageType.h"

AC_AssassinKickDumy::AC_AssassinKickDumy()
{
	KickMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("Assassin_Kick"));
	RootComponent = KickMeshComp;

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(FName("KickCapsule"));

	CapsuleCollision->SetupAttachment(KickMeshComp);
	CapsuleCollision->SetCapsuleHalfHeight(25);
	CapsuleCollision->SetCapsuleRadius(5);
	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleCollision->SetGenerateOverlapEvents(true);

	KickDamage = 5.f;
}

void AC_AssassinKickDumy::BeginPlay()
{
	Super::BeginPlay();

	CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &AC_AssassinKickDumy::OnBeginOverlap);

}

void AC_AssassinKickDumy::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this) return;
	if (OtherActor == GetOwner()) return;
	if (OtherActor->Tags == GetOwner()->Tags) return;
	if (SweepResult.Actor->Tags == GetOwner()->Tags) return;
	if (SweepResult.Actor == this) return;
	if (SweepResult.Actor == GetOwner()) return;
	if (OtherActor->ActorHasTag("Trigger") == true) return;
	if (OtherActor->ActorHasTag("Equipments") == true) return;
	if (SweepResult.Actor->ActorHasTag("Trigger") == true) return;
	if (SweepResult.Actor->ActorHasTag("Equipments") == true) return;


	SweepResult.Actor->TakeDamage(KickDamage, DamageEvent, GetOwner()->GetInstigatorController(), this);

}
