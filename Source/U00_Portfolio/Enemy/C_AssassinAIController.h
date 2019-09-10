
#pragma once

#include "CoreMinimal.h"
#include "Enemy/C_BaseAIController.h"
#include "C_AssassinAIController.generated.h"


UCLASS()
class U00_PORTFOLIO_API AC_AssassinAIController : public AC_BaseAIController
{
	GENERATED_BODY()
public:
	virtual void OnPossess(APawn* InPawn) override;

private:
	class AC_Assassin_Enemy* Enemy;
};
