#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "C_Trigger_TeleportToKatana.generated.h"

UCLASS()
class U00_PORTFOLIO_API AC_Trigger_TeleportToKatana : public ATriggerBox
{
	GENERATED_BODY()
public:
	AC_Trigger_TeleportToKatana();

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

};
