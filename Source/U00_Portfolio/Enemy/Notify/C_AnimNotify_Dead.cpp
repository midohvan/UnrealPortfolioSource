#include "C_AnimNotify_Dead.h"
#include "Global.h"
#include "Enemy/C_2H_Enemy.h"
#include "Enemy/C_EnemyBase.h"
#include "Enemy/C_EnemyAIController.h"
#include "Components/SkeletalMeshComponent.h"

void UC_AnimNotify_Dead::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	if (EnemyBase == NULL) return;
	
	EnemyBase->SetDying(true);
}

void UC_AnimNotify_Dead::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	if (EnemyBase == NULL) return;

	EnemyBase->SetDying(false);

	//EnemyBase->DestroyEnemy();

}
