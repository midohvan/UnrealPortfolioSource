#pragma once

#include "CoreMinimal.h"
#include "Enemy/C_BaseAIController.h"
#include "C_EnemyAIController.generated.h"

UCLASS()
class U00_PORTFOLIO_API AC_EnemyAIController : public AC_BaseAIController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* InPawn) override;

private:
	class AC_2H_Enemy* Enemy;


};
