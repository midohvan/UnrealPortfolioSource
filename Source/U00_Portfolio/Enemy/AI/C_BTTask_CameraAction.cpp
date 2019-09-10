#include "C_BTTask_CameraAction.h"
#include "Enemy/C_BaseAIController.h"


EBTNodeResult::Type UC_BTTask_CameraAction::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AIController = Cast<AC_BaseAIController>(OwnerComp.GetAIOwner());
	if (AIController == NULL) return EBTNodeResult::Failed;

	if (IsValid(AIController) == true)
		AIController->CameraAction();

	return EBTNodeResult::Succeeded;
}

//void UC_BTTask_CameraAction::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
//{
//	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
//
//	AIController = Cast<AC_BaseAIController>(OwnerComp.GetAIOwner());
//	if (AIController == NULL) return;
//
//	if (AIController->GetCheckMontageFinish() == true)
//		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
//}
