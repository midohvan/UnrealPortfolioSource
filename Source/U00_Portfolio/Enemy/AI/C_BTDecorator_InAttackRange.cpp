#include "C_BTDecorator_InAttackRange.h"
#include "Global.h"
#include "Player/C_Player.h"
#include "Enemy/C_2H_Enemy.h"
#include "Enemy/C_EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UC_BTDecorator_InAttackRange::UC_BTDecorator_InAttackRange()
{
	NodeName = TEXT("Can Attack");
}

bool UC_BTDecorator_InAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	bool bResult = false;

	C_Log::Print(bResult);

	AC_EnemyAIController* AIController = Cast<AC_EnemyAIController>(OwnerComp.GetAIOwner());
	if (AIController == NULL) return false;

	AC_Player* Target = Cast<AC_Player>(AIController->GetBlackboardComp()->GetValueAsObject("Target"));
	if (Target == NULL) return false;
	
	bResult = (Target->GetDistanceTo(AIController->GetPawn()) <= 250.f);

	C_Log::Print("InCombat");

	C_Log::Print(Target->GetDistanceTo(AIController->GetPawn()), 10.0f, FColor::Green);

	return bResult;
}
