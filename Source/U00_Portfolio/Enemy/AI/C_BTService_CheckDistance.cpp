#include "C_BTService_CheckDistance.h"
#include "Global.h"
#include "BotTargetPoint.h"
#include "Player/C_Player.h"
#include "Enemy/C_2H_Enemy.h"
#include "Enemy/C_EnemyBase.h"
#include "Enemy/C_EnemyAIController.h"
#include "Enemy/C_BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"

UC_BTService_CheckDistance::UC_BTService_CheckDistance()
{
	NodeName = TEXT("Check Distance");

}

void UC_BTService_CheckDistance::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AC_BaseAIController* controller = Cast<AC_BaseAIController>(OwnerComp.GetAIOwner());
	if (controller == NULL) return;

	AC_EnemyBase* enemy = Cast<AC_EnemyBase>(controller->GetPawn());
	if (enemy == NULL) return;

	AC_Player* player = Cast<AC_Player>(controller->GetBlackboardComp()->GetValueAsObject("Target"));

	/*ABotTargetPoint* PatrolPoint = Cast<ABotTargetPoint>(controller->GetBlackboardComp()->GetValueAsObject("PatrolPoint"));
	if (PatrolPoint == NULL) return;*/

	//float DistanceToPatrol = (controller->GetPawn()->GetActorLocation() - PatrolPoint->GetActorLocation()).Size();
	
	if (player == NULL)
	{
		enemy->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		enemy->GetCharacterMovement()->MaxAcceleration = 350.0f;

		/*if (DistanceToPatrol >= 150.0f)
			controller->GetBlackboardComp()->SetValueAsBool("IsPatrol", true);
		else
			controller->GetBlackboardComp()->SetValueAsBool("IsPatrol", false);*/
	}
	else
	{
		float DistanceToPlayer = (controller->GetPawn()->GetActorLocation() - player->GetActorLocation()).Size();
		controller->GetBlackboardComp()->SetValueAsFloat("DistanceToPlayer", DistanceToPlayer);

		//if (player->GetKnockDown() == true) 
		//	controller->GetBlackboardComp()->SetValueAsBool("IsPlayerDown", true);
		//else
		//	controller->GetBlackboardComp()->SetValueAsBool("IsPlayerDown", false);


		enemy->GetCharacterMovement()->MaxWalkSpeed = 500.0f;
		enemy->GetCharacterMovement()->MaxAcceleration = 550.0f;
		controller->GetBlackboardComp()->SetValueAsBool("IsPatrol", false);


		
		if (DistanceToPlayer > 600.f)
		{
			controller->GetBlackboardComp()->SetValueAsBool("IsAttach", true);
			controller->GetBlackboardComp()->SetValueAsBool("CanAttack", false);
		}
		else
		{
			controller->GetBlackboardComp()->SetValueAsBool("IsAttach", false);
			controller->GetBlackboardComp()->SetValueAsBool("CanAttack", true);

			if (player->GetKnockDown() == true)
			{
				controller->GetBlackboardComp()->SetValueAsBool("IsPlayerDown", true);
			}	
			else
				controller->GetBlackboardComp()->SetValueAsBool("IsPlayerDown", false);
			
		
		}
			
		

	}

}
