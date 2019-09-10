// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AnimNotify_CameraAction.h"
#include "Global.h"
#include "Enemy/C_EnemyBase.h"
#include "Components/SkeletalMeshComponent.h"

void UC_AnimNotify_CameraAction::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	if (EnemyBase == NULL) return;

	EnemyBase->SetCameraAction(true);

}

void UC_AnimNotify_CameraAction::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	EnemyBase = Cast<AC_EnemyBase>(MeshComp->GetOwner());
	if (EnemyBase == NULL) return;

	EnemyBase->SetCameraAction(false);



}
