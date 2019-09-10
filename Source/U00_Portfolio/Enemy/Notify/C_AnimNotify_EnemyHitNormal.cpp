#include "C_AnimNotify_EnemyHitNormal.h"
#include "Global.h"
#include "Enemy/C_2H_Enemy.h"
#include "Enemy/C_EnemyBase.h"
#include "Enemy/C_EnemyAIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enemy/Equipments/C_2H_Weapon.h"
#include "DamageType/C_DamageType_Default.h"

void UC_AnimNotify_EnemyHitNormal::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	if (EnemyBase == NULL) return;

	EnemyBase->GetWeapon()->SetDamageType(UC_DamageType_Default::StaticClass());
}

void UC_AnimNotify_EnemyHitNormal::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	if (EnemyBase == NULL) return;

	EnemyBase->GetWeapon()->SetDamageType(UC_DamageType_Default::StaticClass());
}

