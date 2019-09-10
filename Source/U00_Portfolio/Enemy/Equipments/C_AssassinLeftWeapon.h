// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Equipments/C_BaseWeapon.h"
#include "C_AssassinLeftWeapon.generated.h"

UCLASS()
class U00_PORTFOLIO_API AC_AssassinLeftWeapon : public AC_BaseWeapon
{
	GENERATED_BODY()
public:
	AC_AssassinLeftWeapon();
protected:
	virtual void BeginPlay() override;

public:
	//virtual void Tick(float DeltaTime) override;
	virtual	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void SetDamageType(TSubclassOf<UDamageType> val) { DamageEvent.DamageTypeClass = val; }

};
