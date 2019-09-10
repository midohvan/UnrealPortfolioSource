#include "C_AnimNotify_WeaponCollision.h"
#include "Player/C_Player.h"
#include "Player/Equipment/C_PlayerWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

void UC_AnimNotify_WeaponCollision::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	player->GetPlayerWeapon()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UC_AnimNotify_WeaponCollision::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	player->GetPlayerWeapon()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
