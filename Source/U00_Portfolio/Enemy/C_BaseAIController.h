#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_BaseAIController.generated.h"

UCLASS()
class U00_PORTFOLIO_API AC_BaseAIController : public AAIController
{
	GENERATED_BODY()
public:
	AC_BaseAIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

public:
	virtual void NormalAttack() ;
	virtual void StrongAttack();
	virtual void DownAttack() ;
	virtual void SpecialAttack1() ;
	virtual void SpecialAttack2() ;
	virtual void SpecialAttack3();
	virtual void SpecialAttack4() ;
	virtual void CameraAction();
	virtual void NoTargetAction();
	virtual void Guard() ;
	virtual void StepBack();
	virtual void StepLeft();
	virtual void StepRight() ;
	virtual void Dead();

public:
	virtual UBlackboardComponent* GetBlackboardComp() { return BlackboardComp; }
	virtual TArray<AActor*> GetAvailableTargetPoints() { return BotTargetpoints; }

	virtual void SetSeenTarget(APawn* InPawn) ;
	virtual void OnRepeatTimer() {};

	virtual bool GetNormalAttack() { return bNormalAttack; }
	virtual bool GetCheckMontageFinish() { return bCheckMontageFinish; }

	virtual void SetCheckMontageFinish(bool val) { bCheckMontageFinish = val; }

public:
	UPROPERTY(Transient) class UBlackboardComponent* BlackboardComp;
	UPROPERTY(Transient) class UBehaviorTreeComponent* BehaviorComp;

	TArray<AActor*> BotTargetpoints;

	class AC_EnemyBase* Enemy;

	bool bNormalAttack;
	bool bCheckMontageFinish;


	FTimerHandle RepeatTimerHandle;
	float RepeatInterval;
	
};
