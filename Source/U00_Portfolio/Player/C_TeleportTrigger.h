#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "C_TeleportTrigger.generated.h"


UCLASS()
class U00_PORTFOLIO_API AC_TeleportTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:
	AC_TeleportTrigger();

	virtual void BeginPlay() override;
	
	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

};
