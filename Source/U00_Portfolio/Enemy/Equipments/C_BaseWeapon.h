#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_BaseWeapon.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
UCLASS()
class U00_PORTFOLIO_API AC_BaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_BaseWeapon();

public:
	UFUNCTION()
		virtual	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {};

	virtual void SetDamageType(TSubclassOf<UDamageType> val) { DamageEvent.DamageTypeClass = val; }

	virtual UCapsuleComponent* GetCapsuleComponent() { return CapsuleCollision; }
	virtual USkeletalMeshComponent* GetMesh() { return WeaponMeshComp; }


protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		UCapsuleComponent* CapsuleCollision;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		USkeletalMeshComponent* WeaponMeshComp;

protected:
	UPROPERTY(EditDefaultsOnly)
		float WeaponDamage = 20.0f;

	FDamageEvent DamageEvent;
};
