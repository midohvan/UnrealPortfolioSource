#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_KatanaAnimInstance.generated.h"

UCLASS()
class U00_PORTFOLIO_API UC_KatanaAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	virtual void NativeUpdateAnimation(float Delta) override;

protected:
	UPROPERTY(BlueprintReadOnly)
		bool bDead;

	UPROPERTY(BlueprintReadOnly)
		float Speed;

	UPROPERTY(BlueprintReadOnly)
		float Direction;

	UPROPERTY(BlueprintReadOnly)
		bool bInAir;

	UPROPERTY(BlueprintReadOnly)
		bool bHit;

private:
	class AC_Katana_Enemy* Enemy;
	class AC_KatanaAIController* AIController;
};
