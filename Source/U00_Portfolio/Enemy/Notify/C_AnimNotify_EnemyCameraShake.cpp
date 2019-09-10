#include "C_AnimNotify_EnemyCameraShake.h"
#include "Global.h"
#include "Enemy/C_EnemyBase.h"
#include "Enemy/C_BaseAIController.h"
#include "Components/SkeletalMeshComponent.h"


void UC_AnimNotify_EnemyCameraShake::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	//EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	//if (EnemyBase == NULL) return;
	//AIController = Cast<AC_BaseAIController>(EnemyBase->GetController());
	//if (AIController == NULL) return;

}

void UC_AnimNotify_EnemyCameraShake::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	//EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	//if (EnemyBase == NULL) return;

	//AIController = Cast<AC_BaseAIController>(EnemyBase->GetController());
	//if (AIController == NULL) return;

	//EnemyBase->SetCameraAction(false);

}
