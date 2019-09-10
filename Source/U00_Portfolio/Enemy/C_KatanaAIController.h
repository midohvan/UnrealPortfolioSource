#pragma once

#include "CoreMinimal.h"
#include "Enemy/C_BaseAIController.h"
#include "C_KatanaAIController.generated.h"

UCLASS()
class U00_PORTFOLIO_API AC_KatanaAIController : public AC_BaseAIController
{
	GENERATED_BODY()
public:
	virtual void OnPossess(APawn* InPawn) override;

private:
	class AC_Katana_Enemy* Enemy;
};
