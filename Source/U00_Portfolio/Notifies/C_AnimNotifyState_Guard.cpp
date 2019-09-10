#include "C_AnimNotifyState_Guard.h"
#include "Global.h"
#include "Player/C_Player.h"
#include "Player/C_PlayerController.h"
#include "Components/SkeletalMeshComponent.h"

void UC_AnimNotifyState_Guard::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	CController = Cast<AC_PlayerController>(player->GetController());
	if (CController == NULL) return;
	player->SetCanBlock(true);
}

void UC_AnimNotifyState_Guard::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	CController = Cast<AC_PlayerController>(player->GetController());
	if (CController == NULL) return;
	player->SetCanBlock(false);
}
