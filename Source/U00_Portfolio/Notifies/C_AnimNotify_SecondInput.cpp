#include "C_AnimNotify_SecondInput.h"
#include "Global.h"
#include "Player/C_Player.h"
#include "Player/C_PlayerController.h"
#include "Player/Equipment/C_PlayerWeapon.h"
#include "Components/SkeletalMeshComponent.h"

void UC_AnimNotify_SecondInput::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	CController = Cast<AC_PlayerController>(player->GetController());
	if (CController == NULL) return;
	CController->SetSecondInput(true);
}

void UC_AnimNotify_SecondInput::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	CController = Cast<AC_PlayerController>(player->GetController());
	if (CController == NULL) return;
	CController->SetSecondInput(false);
}
