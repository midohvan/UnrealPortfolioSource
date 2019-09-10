#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_BaseKickDumy.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class U00_PORTFOLIO_API AC_BaseKickDumy : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_BaseKickDumy();
public:
	UFUNCTION()
		virtual	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {};

	virtual void SetDamageType(TSubclassOf<UDamageType> val) { DamageEvent.DamageTypeClass = val; }

	virtual UCapsuleComponent* GetCapsuleComponent() { return CapsuleCollision; }
	virtual UStaticMeshComponent* GetMesh() { return KickMeshComp; }


protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		UCapsuleComponent* CapsuleCollision;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		UStaticMeshComponent* KickMeshComp;

protected:
	UPROPERTY(EditDefaultsOnly)
		float KickDamage = 20.0f;

	FDamageEvent DamageEvent;
};
