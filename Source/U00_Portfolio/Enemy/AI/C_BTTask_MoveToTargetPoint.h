#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTTask_MoveToTargetPoint.generated.h"

UCLASS()
class U00_PORTFOLIO_API UC_BTTask_MoveToTargetPoint : public UBTTaskNode
{
	GENERATED_BODY()
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
