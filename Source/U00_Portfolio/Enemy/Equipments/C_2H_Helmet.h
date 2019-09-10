#pragma once

#include "CoreMinimal.h"
#include "Enemy/Equipments/C_BaseHelmet.h"
#include "C_2H_Helmet.generated.h"

UCLASS()
class U00_PORTFOLIO_API AC_2H_Helmet : public AC_BaseHelmet
{
	GENERATED_BODY()
	
public:	
	AC_2H_Helmet();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
