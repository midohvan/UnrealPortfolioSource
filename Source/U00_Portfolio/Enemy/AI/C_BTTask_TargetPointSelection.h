#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTTask_TargetPointSelection.generated.h"

UCLASS()
class U00_PORTFOLIO_API UC_BTTask_TargetPointSelection : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UC_BTTask_TargetPointSelection();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	
};
