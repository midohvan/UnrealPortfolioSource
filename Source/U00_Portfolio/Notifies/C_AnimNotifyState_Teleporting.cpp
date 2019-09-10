#include "C_AnimNotifyState_Teleporting.h"
#include "Player/C_Player.h"
#include "Player/C_PlayerController.h"
#include "Components/SkeletalMeshComponent.h"

void UC_AnimNotifyState_Teleporting::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	CController = Cast<AC_PlayerController>(player->GetController());
	if (CController == NULL) return;

	player->SetTeleporting(true);
}

void UC_AnimNotifyState_Teleporting::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	CController = Cast<AC_PlayerController>(player->GetController());
	if (CController == NULL) return;

	player->SetTeleporting(false);
}
