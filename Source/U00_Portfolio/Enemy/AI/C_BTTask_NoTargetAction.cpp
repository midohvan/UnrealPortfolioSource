#include "C_BTTask_NoTargetAction.h"
#include "Enemy/C_BaseAIController.h"


EBTNodeResult::Type UC_BTTask_NoTargetAction::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AIController = Cast<AC_BaseAIController>(OwnerComp.GetAIOwner());
	if (AIController == NULL) return EBTNodeResult::Failed;

	AIController->NoTargetAction();

	return EBTNodeResult::InProgress;
}

void UC_BTTask_NoTargetAction::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AIController = Cast<AC_BaseAIController>(OwnerComp.GetAIOwner());
	if (AIController == NULL) return;

	if (AIController->GetCheckMontageFinish() == true)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
