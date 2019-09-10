#include "C_AnimNotify_EnemyBlowAway.h"
#include "Global.h"
#include "Enemy/C_EnemyBase.h"
#include "Enemy/C_2H_Enemy.h"
#include "Enemy/C_EnemyAIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enemy/Equipments/C_2H_Weapon.h"
#include "DamageType/C_DamageType_BlowAway.h"
#include "DamageType/C_DamageType_Default.h"

void UC_AnimNotify_EnemyBlowAway::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	if (EnemyBase == NULL) return;

	EnemyBase->GetWeapon()->SetDamageType(UC_DamageType_BlowAway::StaticClass());


	/*Enemy2H = Cast<AC_2H_Enemy>(MeshComp->GetOwner());
	if (Enemy2H == NULL) return;

	Enemy2H->Get2HWeapon()->SetDamageType(UC_DamageType_BlowAway::StaticClass());*/
}

void UC_AnimNotify_EnemyBlowAway::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	if (EnemyBase == NULL) return;

	EnemyBase->GetWeapon()->SetDamageType(UC_DamageType_Default::StaticClass());


	/*Enemy2H = Cast<AC_2H_Enemy>(MeshComp->GetOwner());
	if (Enemy2H == NULL) return;

	Enemy2H->Get2HWeapon()->SetDamageType(UC_DamageType_Default::StaticClass());*/
	
}

