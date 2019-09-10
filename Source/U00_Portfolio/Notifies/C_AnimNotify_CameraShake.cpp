
#include "C_AnimNotify_CameraShake.h"
#include "Player/C_PlayerController.h"
#include "Player/C_Player.h"
#include "C_CameraShake.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraShake.h"
#include "Camera/PlayerCameraManager.h"

void UC_AnimNotify_CameraShake::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AC_Player* player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	AC_PlayerController* CController = Cast<AC_PlayerController>(player->GetController());
	if (CController == NULL) return;

	if (player->GetCameraShake() != NULL)
		CController->PlayerCameraManager->PlayCameraShake(player->GetCameraShake(), 1.0f);
	
}