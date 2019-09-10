#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_2H_EnemyAnim.generated.h"


UCLASS()
class U00_PORTFOLIO_API UC_2H_EnemyAnim : public UAnimInstance
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
	class AC_2H_Enemy* Enemy;
	class AC_EnemyAIController* AIController;
};
