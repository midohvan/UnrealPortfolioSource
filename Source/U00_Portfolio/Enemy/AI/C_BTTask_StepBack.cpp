#include "C_BTTask_StepBack.h"
#include "Enemy/C_EnemyAIController.h"
#include "Enemy/C_BaseAIController.h"


EBTNodeResult::Type UC_BTTask_StepBack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);


	AIController = Cast<AC_BaseAIController>(OwnerComp.GetAIOwner());
	if (IsValid(AIController) == false)  return EBTNodeResult::Failed;

	if (IsValid(AIController) == true)
		AIController->StepBack();

	return EBTNodeResult::InProgress;
}

void UC_BTTask_StepBack::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AIController = Cast<AC_BaseAIController>(OwnerComp.GetAIOwner());
	if (IsValid(AIController) == false)  return;

	if (AIController->GetCheckMontageFinish() == true)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
