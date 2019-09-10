#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "C_BTService_CheckDistance.generated.h"

UCLASS()
class U00_PORTFOLIO_API UC_BTService_CheckDistance : public UBTService
{
	GENERATED_BODY()
public:
	UC_BTService_CheckDistance();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	
};
