#include "C_BTTask_SpecialAttack3.h"
#include "Enemy/C_EnemyAIController.h"
#include "Enemy/C_BaseAIController.h"
#include "Enemy/C_2H_Enemy.h"


EBTNodeResult::Type UC_BTTask_SpecialAttack3::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AIController = Cast<AC_BaseAIController>(OwnerComp.GetAIOwner());
	if (AIController == NULL) return EBTNodeResult::Failed;

	if (IsValid(AIController) == true)
		AIController->SpecialAttack3();

	return EBTNodeResult::InProgress;
}

void UC_BTTask_SpecialAttack3::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AIController = Cast<AC_BaseAIController>(OwnerComp.GetAIOwner());
	if (AIController == NULL) return;

	if (AIController->GetCheckMontageFinish() == true)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
