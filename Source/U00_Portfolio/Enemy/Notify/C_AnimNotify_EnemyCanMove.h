#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "C_AnimNotify_EnemyCanMove.generated.h"

UCLASS()
class U00_PORTFOLIO_API UC_AnimNotify_EnemyCanMove : public UAnimNotifyState
{
	GENERATED_BODY()
public:
    void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration);
	void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation);

private:
	class AC_EnemyBase* EnemyBase;

};
