#include "C_Assassin_Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/DamageType.h"

AC_Assassin_Weapon::AC_Assassin_Weapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Assassin_Weapon"));
	RootComponent = WeaponMeshComp;

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(FName("WeaponCapsule"));

	CapsuleCollision->SetupAttachment(WeaponMeshComp);
	CapsuleCollision->SetCapsuleHalfHeight(50);
	CapsuleCollision->SetCapsuleRadius(10);
	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleCollision->SetGenerateOverlapEvents(true);

	WeaponDamage = 5.f;
}

void AC_Assassin_Weapon::BeginPlay()
{
	Super::BeginPlay();

	CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &AC_Assassin_Weapon::OnBeginOverlap);

}

void AC_Assassin_Weapon::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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

	SweepResult.Actor->TakeDamage(WeaponDamage, DamageEvent, GetOwner()->GetInstigatorController(), this);

}
