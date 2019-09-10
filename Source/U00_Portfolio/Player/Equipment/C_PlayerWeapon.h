#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_PlayerWeapon.generated.h"

UCLASS()
class U00_PORTFOLIO_API AC_PlayerWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_PlayerWeapon();

protected:
	virtual void BeginPlay() override;



public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	class UCapsuleComponent* GetCapsuleComponent() { return CapsuleCollision; }
	class USkeletalMeshComponent* GetMesh() { return PlayerWeaponMeshComp; }

public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
		class UCapsuleComponent* CapsuleCollision;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		class USkeletalMeshComponent* PlayerWeaponMeshComp;

	void SetDamageType(TSubclassOf<UDamageType> val) { DamageEvent.DamageTypeClass = val; }

private:
	UPROPERTY(EditDefaultsOnly)
		float WeaponDamage = 5.f;

	FDamageEvent DamageEvent;

};
