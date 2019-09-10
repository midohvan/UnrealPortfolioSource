#include "C_AnimNotify_RadialBlur.h"
#include "Player/C_Player.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PostProcessComponent.h"


void UC_AnimNotify_RadialBlur::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	player->GetRadialBlur()->bEnabled = true;
	

}

void UC_AnimNotify_RadialBlur::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	player->GetRadialBlur()->bEnabled = false;


}

