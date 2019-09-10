#include "C_AnimNotify_SkillCameraOn.h"
#include "Global.h"
#include "Player/C_Player.h"
#include "Player/C_PlayerController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"


void UC_AnimNotify_SkillCameraOn::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	AIController = Cast<AC_PlayerController>(player->GetController());
	if (AIController == NULL) return;

	player->GetFollowCamera()->Deactivate();
	player->GetSkillCamera()->Activate();

	UGameplayStatics::SetGlobalTimeDilation(player->GetWorld(), 0.7f);

}

void UC_AnimNotify_SkillCameraOn::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	player->GetSkillCamera()->Deactivate();
	player->GetFollowCamera()->Activate();
	
	UGameplayStatics::SetGlobalTimeDilation(player->GetWorld(), 1.f);

}
