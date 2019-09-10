#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_PlayerShield.generated.h"

UCLASS()
class U00_PORTFOLIO_API AC_PlayerShield : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_PlayerShield();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	class UBoxComponent* GetBoxComponent() { return BoxCollision; }
	class UStaticMeshComponent* GetMesh() { return PlayerShieldMeshComp; }
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
		class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		class UStaticMeshComponent* PlayerShieldMeshComp;

	void SetDamageType(TSubclassOf<UDamageType> val) { DamageEvent.DamageTypeClass = val; }


private:
	UPROPERTY(EditDefaultsOnly)
		float ShieldDamage = 5.f;

	UPROPERTY(EditDefaultsOnly)
		float ShieldDuration = 100.0f;

	FDamageEvent DamageEvent;
};
