#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_PlayerHelmet.generated.h"

UCLASS()
class U00_PORTFOLIO_API AC_PlayerHelmet : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_PlayerHelmet();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	class UBoxComponent* GetBoxComponent() { return BoxCollision; }
	class UStaticMeshComponent* GetMesh() { return PlayerHelmetMeshComp; }

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
		class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		class UStaticMeshComponent* PlayerHelmetMeshComp;
private:
	UPROPERTY(EditDefaultsOnly)
		float HelmetDuration = 100.0f;
};
