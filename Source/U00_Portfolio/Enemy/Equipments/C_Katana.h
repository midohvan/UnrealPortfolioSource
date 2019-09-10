
#pragma once

#include "CoreMinimal.h"
#include "Enemy/Equipments/C_BaseWeapon.h"
#include "C_Katana.generated.h"


UCLASS()
class U00_PORTFOLIO_API AC_Katana : public AC_BaseWeapon
{
	GENERATED_BODY()
public:
	AC_Katana();

protected:
	virtual void BeginPlay() override;

public:
	//virtual void Tick(float DeltaTime) override;
	virtual	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void SetDamageType(TSubclassOf<UDamageType> val) { DamageEvent.DamageTypeClass = val; }

};
