#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTTask_StrongAttack.generated.h"

UCLASS()
class U00_PORTFOLIO_API UC_BTTask_StrongAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	class AC_2H_Enemy* enemy;
	//class AC_EnemyAIController* AIController;
	class AC_BaseAIController* AIController;
};
