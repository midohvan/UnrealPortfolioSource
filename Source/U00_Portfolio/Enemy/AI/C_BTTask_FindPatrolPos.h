#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTTask_FindPatrolPos.generated.h"


UCLASS()
class U00_PORTFOLIO_API UC_BTTask_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UC_BTTask_FindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
