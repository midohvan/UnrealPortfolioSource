
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "C_BTDecorator_InAttackRange.generated.h"

UCLASS()
class U00_PORTFOLIO_API UC_BTDecorator_InAttackRange : public UBTDecorator
{
	GENERATED_BODY()
public:
	UC_BTDecorator_InAttackRange();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;


};
