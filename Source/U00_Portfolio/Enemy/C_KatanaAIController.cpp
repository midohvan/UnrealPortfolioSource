#include "C_KatanaAIController.h"
#include "Global.h"
#include "Enemy/C_Katana_Enemy.h"

void AC_KatanaAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	Enemy = Cast<AC_Katana_Enemy>(InPawn);

}
