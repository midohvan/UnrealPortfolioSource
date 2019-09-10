#pragma once

#include "U00_Portfolio.h"
#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "C_BTService_CheckForTarget.generated.h"

UCLASS()
class U00_PORTFOLIO_API UC_BTService_CheckForTarget : public UBTService
{
	GENERATED_BODY()
	
public:
	UC_BTService_CheckForTarget();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


};
