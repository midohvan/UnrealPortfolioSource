#include "C_AnimNotifyState_Evade.h"
#include "Player/C_Player.h"
#include "Player/C_PlayerController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


void UC_AnimNotifyState_Evade::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	CController = Cast<AC_PlayerController>(player->GetController());
	if (CController == NULL) return;
	CController->SetEvading(true);
	
	FVector vec = CController->GetControlledPlayer()->GetLastMovementInputVector();

	CController->GetControlledPlayer()->LaunchCharacter(vec * 1000.0f + FVector(0, 0, 230.f), true, true);


	//CController->GetControlledPlayer()->GetCapsuleComponent()->IgnoreActorWhenMoving()
}

void UC_AnimNotifyState_Evade::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	CController = Cast<AC_PlayerController>(player->GetController());
	if (CController == NULL) return;
	CController->SetEvading(false);
	
}
