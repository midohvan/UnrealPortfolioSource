#include "C_AssassinAIController.h"
#include "Global.h"
#include "Enemy/C_Assassin_Enemy.h"

void AC_AssassinAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	Enemy = Cast<AC_Assassin_Enemy>(InPawn);

}
