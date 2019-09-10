#include "C_BTTask_MoveToTargetPoint.h"
#include "Global.h"
#include "Enemy/C_EnemyAIController.h"
#include "Enemy/C_BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Engine/Engine.h"
#include "Enemy/C_2H_Enemy.h"


EBTNodeResult::Type UC_BTTask_MoveToTargetPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AC_BaseAIController* AIController = Cast<AC_BaseAIController>(OwnerComp.GetAIOwner());
	if (AIController == NULL) return EBTNodeResult::Failed;

	UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComp();

	AActor* TargetPoint = Cast<AActor>(BlackboardComp->GetValueAsObject("PatrolPoint"));
	
	if (AIController->GetBlackboardComp()->GetValueAsBool("IsPatrol") == true)
	{
		AIController->MoveToActor(TargetPoint, 5.f, true, true, true, 0, true);
	
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
