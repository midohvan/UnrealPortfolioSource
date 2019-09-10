#include "C_BTTask_FindPatrolPos.h"
#include "Global.h"
#include "Enemy/C_EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "U00_PortfolioGameModeBase.h"
#include "NavigationSystem.h"



UC_BTTask_FindPatrolPos::UC_BTTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UC_BTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AC_EnemyAIController* AIController = Cast<AC_EnemyAIController>(OwnerComp.GetAIOwner());
	if (AIController == NULL) return EBTNodeResult::Failed;

	/*auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == NULL) return EBTNodeResult::Failed;*/
		
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(AIController->GetWorld());
	if (NavSystem == NULL) return EBTNodeResult::Failed;

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AC_EnemyAIController::HomePosKey);
	FNavLocation NextPatrol;

	if (NavSystem->GetRandomPointInNavigableRadius(Origin, 1000.0f, NextPatrol))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AC_EnemyAIController::PatrolPosKey, NextPatrol.Location);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
