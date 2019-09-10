#include "C_EnemyAIController.h"
#include "Global.h"
#include "Enemy/C_2H_Enemy.h"

void AC_EnemyAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	Enemy = Cast<AC_2H_Enemy>(InPawn);

}


