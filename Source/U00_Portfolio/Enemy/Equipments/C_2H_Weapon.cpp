#include "C_2H_Weapon.h"
#include "Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/DamageType.h"

AC_2H_Weapon::AC_2H_Weapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(FName("2H_Weapon"));
	WeaponMeshComp->SetWorldScale3D(FVector(3.0, 3.0, 5.0f));

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(FName("WeaponCapsule"));

	CapsuleCollision->SetupAttachment(WeaponMeshComp);
	CapsuleCollision->SetCapsuleHalfHeight(220);
	CapsuleCollision->SetCapsuleRadius(22);
	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleCollision->SetGenerateOverlapEvents(true);

	WeaponDamage = 5.f;
}

void AC_2H_Weapon::BeginPlay()
{
	Super::BeginPlay();

	CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &AC_2H_Weapon::OnBeginOverlap);

}

void AC_2H_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_2H_Weapon::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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

