#pragma once

#include "CoreMinimal.h"
#include "Enemy/C_EnemyBase.h"
#include "C_2H_Enemy.generated.h"

class AC_2H_Helmet;
class AC_2H_Weapon;

UCLASS()
class U00_PORTFOLIO_API AC_2H_Enemy : public AC_EnemyBase
{
	GENERATED_BODY()
	
public:
	virtual	void OnSeePlayer(APawn* InPawn);

public:
	AC_2H_Enemy();

protected:
	virtual void BeginPlay() override;

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
	virtual void Hit() {};
	virtual void KnockBack() {};
	virtual void KnockDown() {};
	virtual void BlowAway() {};
	virtual void CameraAction();
	virtual void NoTargetACtion();

public:
	UPROPERTY(VisibleAnywhere, Category = "Blood")
		class UParticleSystemComponent* Enemy_BloodComp;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class UCameraComponent* Enemy_CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class USpringArmComponent* Enemy_SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "AI")
		class UPawnSensingComponent* Enemy_PawnSensingComp;

	class UParticleSystem* Enemy_Blood;

};
