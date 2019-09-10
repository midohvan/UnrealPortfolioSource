#include "C_AnimNotifyState_EnemyAttack.h"
#include "Enemy/C_2H_Enemy.h"
#include "Enemy/C_EnemyBase.h"
#include "Enemy/C_EnemyAIController.h"
#include "Global.h"
#include "Components/SkeletalMeshComponent.h"

void UC_AnimNotifyState_EnemyAttack::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	if (EnemyBase == NULL) return;

	EnemyBase->SetAttacking(true);
}

void UC_AnimNotifyState_EnemyAttack::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	if (EnemyBase == NULL) return;

	EnemyBase->SetAttacking(false);

}
