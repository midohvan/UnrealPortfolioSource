#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "C_Trigger_TeleportToAssassin.generated.h"

UCLASS()
class U00_PORTFOLIO_API AC_Trigger_TeleportToAssassin : public ATriggerBox
{
	GENERATED_BODY()
public:
	AC_Trigger_TeleportToAssassin();

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

};
