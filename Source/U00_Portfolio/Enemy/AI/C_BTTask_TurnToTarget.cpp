#include "C_BTTask_TurnToTarget.h"
#include "Enemy/C_EnemyAIController.h"
#include "Enemy/C_BaseAIController.h"
#include "Enemy/C_2H_Enemy.h"
#include "Enemy/C_EnemyBase.h"
#include "Player/C_Player.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UC_BTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{

	enemy = Cast<AC_EnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (enemy == NULL) return EBTNodeResult::Failed;

	AIController = Cast<AC_BaseAIController>(OwnerComp.GetAIOwner());
	if (AIController == NULL) return EBTNodeResult::Failed;

	AC_Player* Target = Cast<AC_Player>(AIController->GetBlackboardComp()->GetValueAsObject("Target"));

	FVector LookVector = Target->GetActorLocation() - enemy->GetActorLocation();
	LookVector.Z = 0.0f;

	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

	enemy->SetActorRotation(
		FMath::RInterpTo(enemy->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f
		));

	return EBTNodeResult::Succeeded;
}

