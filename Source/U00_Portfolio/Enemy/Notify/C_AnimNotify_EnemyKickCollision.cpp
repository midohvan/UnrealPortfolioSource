#include "C_AnimNotify_EnemyKickCollision.h"
#include "Global.h"
#include "Enemy/C_EnemyBase.h"
#include "Enemy/Equipments/C_BaseKickDumy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

void UC_AnimNotify_EnemyKickCollision::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	if (EnemyBase == NULL) return;

	EnemyBase->GetKick()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UC_AnimNotify_EnemyKickCollision::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	if (EnemyBase == NULL) return;

	EnemyBase->GetKick()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);


}

