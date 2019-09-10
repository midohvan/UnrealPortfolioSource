#include "C_AnimNotifyState_KnockBack.h"
#include "Player/C_Player.h"
#include "Player/Equipment/C_PlayerWeapon.h"
#include "Player/Equipment/C_PlayerShield.h"
#include "Components/SkeletalMeshComponent.h"
#include "DamageType/C_DamageType_KnockBack.h"
#include "DamageType/C_DamageType_Default.h"

void UC_AnimNotifyState_KnockBack::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	player->GetPlayerWeapon()->SetDamageType(UC_DamageType_KnockBack::StaticClass());
	player->GetPlayerShield()->SetDamageType(UC_DamageType_KnockBack::StaticClass());
}

void UC_AnimNotifyState_KnockBack::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	player->GetPlayerWeapon()->SetDamageType(UC_DamageType_Default::StaticClass());
	player->GetPlayerShield()->SetDamageType(UC_DamageType_KnockBack::StaticClass());


}

