
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "C_AnimNotify_ThirdInput.generated.h"


UCLASS()
class U00_PORTFOLIO_API UC_AnimNotify_ThirdInput : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration);
	void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation);

private:
	class AC_PlayerController* CController;
	class AC_Player* player;
};
