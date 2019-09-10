#include "C_AnimNotify_EnemyKnockBack.h"
#include "Global.h"
#include "Enemy/C_2H_Enemy.h"
#include "Enemy/C_EnemyBase.h"
#include "Enemy/C_EnemyAIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enemy/Equipments/C_2H_Weapon.h"
#include "DamageType/C_DamageType_KnockBack.h"
#include "DamageType/C_DamageType_Default.h"

void UC_AnimNotify_EnemyKnockBack::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	if (EnemyBase == NULL) return;

	EnemyBase->GetWeapon()->SetDamageType(UC_DamageType_KnockBack::StaticClass());

	/*Enemy2H = Cast<AC_2H_Enemy>(MeshComp->GetOwner());
	if (Enemy2H == NULL) return;

	Enemy2H->Get2HWeapon()->SetDamageType(UC_DamageType_KnockBack::StaticClass());*/
}

void UC_AnimNotify_EnemyKnockBack::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	if (EnemyBase == NULL) return;

	EnemyBase->GetWeapon()->SetDamageType(UC_DamageType_Default::StaticClass());

	/*Enemy2H = Cast<AC_2H_Enemy>(MeshComp->GetOwner());
	if (Enemy2H == NULL) return;

	Enemy2H->Get2HWeapon()->SetDamageType(UC_DamageType_Default::StaticClass());*/
}

