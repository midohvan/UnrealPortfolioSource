#include "C_BTTask_TargetPointSelection.h"
#include "BotTargetPoint.h"
#include "Enemy/C_EnemyAIController.h"
#include "Enemy/C_BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/Engine.h"

UC_BTTask_TargetPointSelection::UC_BTTask_TargetPointSelection()
{
	NodeName = TEXT("Next Target Selection");

}

EBTNodeResult::Type UC_BTTask_TargetPointSelection::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AC_BaseAIController* AIController = Cast<AC_BaseAIController>(OwnerComp.GetAIOwner());

	if (AIController != NULL)
	{
		UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComp();
		ABotTargetPoint* CurrentPoint = Cast<ABotTargetPoint>(BlackboardComp->GetValueAsObject("PatrolPoint"));

		TArray<AActor*> AvailableTargetPoints = AIController->GetAvailableTargetPoints();

		int32 RandomIndex;

		ABotTargetPoint* NextTargetPoint = nullptr;

		do 
		{
			RandomIndex = FMath::RandRange(0, AvailableTargetPoints.Num() - 1);
			NextTargetPoint = Cast<ABotTargetPoint>(AvailableTargetPoints[RandomIndex]);

		} while (CurrentPoint == NextTargetPoint);

		BlackboardComp->SetValueAsObject("PatrolPoint", NextTargetPoint);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;

	

}
