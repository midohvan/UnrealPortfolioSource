#include "C_AnimNotify_BloodEffect.h"
#include "Player/C_Player.h"
#include "Components/SkeletalMeshComponent.h"
#include "Blueprint/UserWidget.h"

void UC_AnimNotify_BloodEffect::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	player->GetBloodEffect()->AddToViewport();

	
	player->GetBloodEffect()->SetColorAndOpacity(FLinearColor(1, 1, 1, player->GetWorld()->GetTimeSeconds() * 0.15f));

}

void UC_AnimNotify_BloodEffect::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	player = Cast<AC_Player>(MeshComp->GetOwner());
	if (player == NULL) return;

	
	player->GetBloodEffect()->RemoveFromViewport();

}

