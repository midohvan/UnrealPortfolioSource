#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_EnemyBase.generated.h"

class AC_BaseWeapon;
class AC_BaseHelmet;
class AC_BaseKickDumy;
class UCameraComponent;
class USpringArmComponent;
class UBehaviorTree;
class UPawnSensingComponent;

//Enemy
USTRUCT(Atomic, BlueprintType)
struct FEnemyAttackMontage
{
	GENERATED_BODY()
public:
	UAnimMontage* NormalAttack;
	UAnimMontage* StrongAttack;
	UAnimMontage* DownAttack;
	UAnimMontage* SpecialAttack1;
	UAnimMontage* SpecialAttack2;
	UAnimMontage* SpecialAttack3;
	UAnimMontage* SpecialAttack4;

};
USTRUCT(Atomic, BlueprintType)
struct FEnemyStateMontage
{
	GENERATED_BODY()
public:
	UAnimMontage* Guard;
	UAnimMontage* Block;
	UAnimMontage* Hit;
	UAnimMontage* BackHit;
	UAnimMontage* KnockBack;
	UAnimMontage* KnockDown;
	UAnimMontage* BlowAway;
	UAnimMontage* Die1;
	UAnimMontage* Getup;
	UAnimMontage* StepBack;
	UAnimMontage* StepRight;
	UAnimMontage* StepLeft;
	UAnimMontage* CameraAction;
	UAnimMontage* NoTargetAction;

};

UCLASS()
class U00_PORTFOLIO_API AC_EnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AC_EnemyBase();

public:
	UFUNCTION()
		virtual void OnHitOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {};
	UFUNCTION()
		virtual void OnSeePlayer(APawn* InPawn) {};


public:
	virtual void DestroyEnemy() {};
	virtual void NormalAttack() {};
	virtual void StrongAttack() {};
	virtual void DownAttack() {};
	virtual void SpecialAttack1() {};
	virtual void SpecialAttack2() {};
	virtual void SpecialAttack3() {};
	virtual void SpecialAttack4() {};
	virtual void SkillAttack() {};
	virtual void Hit() {};
	virtual void KnockBack() {};
	virtual void KnockDown() {};
	virtual void BlowAway() {};
	virtual void Guard() {};
	virtual void StepBack() {};
	virtual void StepLeft() {};
	virtual void StepRight() {};
	virtual void Dead() {};
	virtual void CameraAction() {};
	virtual void NoTargetAction() {};

public:
	UFUNCTION(BlueprintPure)
		virtual bool GetBeingHit() { return bBeingHit; }

	UFUNCTION(BlueprintPure)
		virtual bool GetDead() { return bDead; }

	UFUNCTION(BlueprintPure)
		virtual bool GetEquip() { return bEquipped; }

	UFUNCTION(BlueprintPure)
		virtual bool GetAttacking() { return bIsAttacking; }

	UFUNCTION(BlueprintPure)
		virtual bool GetGuarding() { return bGuarding; }

	UFUNCTION(BlueprintPure)
		virtual	bool GetCanCheckHit() { return bCanCheckHit; }

	UFUNCTION(BlueprintPure)
		virtual	float GetHealthPoint() { return HealthPoint; }

	virtual bool GetCameraAction() { return bCameraAction; }
	virtual bool GetDying() { return bDying; }

	virtual void SetAttacking(bool val) { bIsAttacking = val; }
	virtual void SetCheckHit(bool val) { bCanCheckHit = val; }
	virtual void SetBeingHit(bool val) { bBeingHit = val; }
	virtual void SetCanBlock(bool val) { bCanBlock = val; }
	virtual void SetCanMove(bool val) { bCanMove = val; }
	virtual void SetDying(bool val) { bDying = val; }
	virtual void SetDead(bool val) { bDead = val; }
	virtual void SetCameraAction(bool val) { bCameraAction = val; }

public:
	virtual AC_BaseWeapon* GetWeapon() { return Weapon; }
	virtual AC_BaseWeapon* GetLeftWeapon() { return LeftWeapon; }
	virtual AC_BaseHelmet* GetHelmet() { return Helmet; }
	virtual AC_BaseKickDumy* GetKick() { return Kick; }
	virtual float GetHP() { return HealthPoint; }
	virtual TSubclassOf<class UCameraShake> GetCameraShake() { return CameraShake; }
public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<AC_BaseWeapon> WeaponClass;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<AC_BaseWeapon> LeftWeaponClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AC_BaseKickDumy> KickClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AC_BaseHelmet> HelmetClass;

	UPROPERTY(EditAnywhere, Category = "AI")
		UBehaviorTree* BotBehaviorTree;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShake> CameraShake;


protected:
	FEnemyAttackMontage enemyAttackMontages;
	FEnemyStateMontage enemyStateMontage;

	AC_BaseHelmet* Helmet;
	AC_BaseWeapon* Weapon;
	AC_BaseWeapon* LeftWeapon;
	AC_BaseKickDumy* Kick;

	bool bBeingHit;
	bool bEquipped;
	bool bDead;
	bool bIsAttacking;
	bool bCanCheckHit;
	bool bCanBlock;
	bool bCanMove;
	bool bDying;
	bool bCameraAction;

	bool bGuarding;
	bool bKnockDown;
	bool bKnockBack;
	bool bBlowAway;

	float HealthPoint = 300.0f;
	
	float FrontBackResult;
	float LeftRightResult;

};
