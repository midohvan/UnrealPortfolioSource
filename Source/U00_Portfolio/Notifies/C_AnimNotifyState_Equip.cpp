#include "C_AnimNotifyState_Equip.h"
#include "Player/C_Player.h"
#include "Player/C_PlayerController.h"
#include "Player/Equipment/C_PlayerWeapon.h"
#include "Components/SkeletalMeshComponent.h"


void UC_AnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	CController = Cast<AC_PlayerController>(player->GetController());
	if (CController == NULL) return;
	USceneComponent* mesh = player->GetMesh();
	AC_PlayerWeapon* playerWeapon = player->GetPlayerWeapon();

	CController->SetEquipping(true);

	playerWeapon->AttachToComponent
	(
		mesh,
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
		FName("WeaponSocket")
	);
}

void UC_AnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	CController = Cast<AC_PlayerController>(player->GetController());
	if (CController == NULL) return;
	CController->SetEquipping(false);
	CController->SetEquipped(true);
}
