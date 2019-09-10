#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "C_AnimNotify_EnemyKnockBack.generated.h"

UCLASS()
class U00_PORTFOLIO_API UC_AnimNotify_EnemyKnockBack : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration);
	void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation);

private:
	class AC_EnemyBase* EnemyBase;
	class AC_2H_Enemy* Enemy2H;
	class AC_EnemyAIController* AIController;
};
