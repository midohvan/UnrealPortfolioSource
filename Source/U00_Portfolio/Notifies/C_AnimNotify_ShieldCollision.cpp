#include "C_AnimNotify_ShieldCollision.h"
#include "Player/C_Player.h"
#include "Player/Equipment/C_PlayerShield.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

void UC_AnimNotify_ShieldCollision::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	player->GetPlayerShield()->GetBoxComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

void UC_AnimNotify_ShieldCollision::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;


	player->GetPlayerShield()->GetBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}
