
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTTask_TurnToTarget.generated.h"


UCLASS()
class U00_PORTFOLIO_API UC_BTTask_TurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	class AC_EnemyBase* enemy;
	
	class AC_BaseAIController* AIController;
	
};
