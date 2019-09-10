#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_PlayerAnimInstance.generated.h"

UCLASS()
class U00_PORTFOLIO_API UC_PlayerAnimInstance : public UAnimInstance
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
		bool bDrawing;

	UPROPERTY(BlueprintReadOnly)
		bool bSheathing;

	UPROPERTY(BlueprintReadOnly)
		bool bInAir;

	UPROPERTY(BlueprintReadOnly)
		bool bWeaponDrawn;

private:
	class AC_Player* player;
	class AC_PlayerController* CController;
};
