#include "C_AnimNotify_KickCollision.h"
#include "Player/C_Player.h"
#include "Player/C_PlayerController.h"
#include "Player/Equipment/C_PlayerFootDumy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
void UC_AnimNotify_KickCollision::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	player->GetPlayerFootDumy()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UC_AnimNotify_KickCollision::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	player->GetPlayerFootDumy()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);


}
