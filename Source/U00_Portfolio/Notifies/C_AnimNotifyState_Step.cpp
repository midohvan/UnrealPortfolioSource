#include "C_AnimNotifyState_Step.h"
#include "Global.h"
#include "Player/C_Player.h"
#include "Player/C_PlayerController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


void UC_AnimNotifyState_Step::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	CController = Cast<AC_PlayerController>(player->GetController());

	FVector vec = CController->GetControlledPlayer()->GetLastMovementInputVector();

	CController->GetControlledPlayer()->LaunchCharacter(vec * 1000.0f + FVector(0,0,230.f) , true, true);
	if (CController == NULL) return;

	CController->SetStepping(true);
}

void UC_AnimNotifyState_Step::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	CController = Cast<AC_PlayerController>(player->GetController());
	if (CController == NULL) return;

	CController->SetStepping(false);

}
