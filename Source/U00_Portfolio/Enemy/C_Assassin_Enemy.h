#pragma once

#include "CoreMinimal.h"
#include "Enemy/C_EnemyBase.h"
#include "C_Assassin_Enemy.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UParticleSystemComponent;
class UParticleSystem;
class UPawnSensingComponent;



UCLASS()
class U00_PORTFOLIO_API AC_Assassin_Enemy : public AC_EnemyBase
{
	GENERATED_BODY()
public:
	AC_Assassin_Enemy();

protected:
	virtual void BeginPlay() override;
	virtual	void OnSeePlayer(APawn* InPawn);
public:
	virtual void Tick(float DeltaTime) override;
	void OnHitOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	void DestroyEnemy();
	void Montages();

public:
	virtual void NormalAttack();
	virtual void StrongAttack();
	virtual void DownAttack();
	virtual void SpecialAttack1();
	virtual void SpecialAttack2();
	virtual void SpecialAttack3();
	virtual void SpecialAttack4();
	virtual void SkillAttack() {};
	virtual void Guard();
	virtual void StepBack();
	virtual void StepLeft();
	virtual void StepRight();
	virtual void Dead();
	virtual void CameraAction();

public:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		UCameraComponent* Assassin_CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		USpringArmComponent* Assassin_SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Blood")
		UParticleSystemComponent* Assassin_BloodComp;

	UPROPERTY(VisibleAnywhere, Category = "AI")
		UPawnSensingComponent* Assassin_PawnSensingComp;

	UParticleSystem* Assassin_Blood;
};
