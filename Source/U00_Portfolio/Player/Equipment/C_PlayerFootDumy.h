#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_PlayerFootDumy.generated.h"

UCLASS()
class U00_PORTFOLIO_API AC_PlayerFootDumy : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_PlayerFootDumy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	class UCapsuleComponent* GetCapsuleComponent() { return CapsuleCollision; }
	class UStaticMeshComponent* GetMesh() { return PlayerFootDumyMeshComp; }

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
		class UCapsuleComponent* CapsuleCollision;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		class UStaticMeshComponent* PlayerFootDumyMeshComp;

private:
	UPROPERTY(EditDefaultsOnly)
		float KickDamage = 5.f;

	

};
