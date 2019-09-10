#include "C_AnimNotify_EnemyWeaponCol.h"
#include "Global.h"
#include "Enemy/C_EnemyBase.h"
#include "Enemy/Equipments/C_BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

void UC_AnimNotify_EnemyWeaponCol::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	if (EnemyBase == NULL) return;

	EnemyBase->SetCheckHit(true);
	EnemyBase->GetWeapon()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UC_AnimNotify_EnemyWeaponCol::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	
	EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	if (EnemyBase == NULL) return;

	EnemyBase->SetCheckHit(false);
	EnemyBase->GetWeapon()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
}
