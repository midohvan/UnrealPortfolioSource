#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_Player.generated.h"

class AC_PlayerWeapon;
class AC_PlayerShield;
class AC_PlayerHelmet;
class AC_PlayerFootDumy;
class APlayerController;
class UUserWidget;

UENUM(BlueprintType)
enum class EInputDirection : uint8
{
	Left, Right, Forward, Back,
	Kick, KickCombo2, KickCombo3,
	ShieldAttack, ShieldAttackCombo, ShieldAttackCombo2, ShieldAttackCombo3,
	JumpKnockDownAttack, DashBlowAwayAttack, DashShieldAttack,
	StepBackCombo1, StepBackCombo2,
	NormalCombo1, NormalCombo2, Special
};
UENUM(BlueprintType)
enum class EState : uint8
{
	Equip, Unequip, Guard, Block,
	JumpStart, JumpLoop, JumpEnd,
	BackHit, LeftHit, RightHit,
	KnockBack, KnockDown, BlowAway,
	Die1, Die2, Getup, Teleport
};

//PlayerMontage
USTRUCT(Atomic, BlueprintType)
struct FDirectionalMontage
{
	GENERATED_BODY()

public:
	UAnimMontage* MovingNormalAttack;
	UAnimMontage* StopNormalAttack;
	UAnimMontage* NormalAttackCombo1;
	UAnimMontage* NormalAttackCombo2;
	UAnimMontage* Kick;
	UAnimMontage* KickCombo2;
	UAnimMontage* KickCombo3;
	UAnimMontage* ShieldAttack;
	UAnimMontage* ShieldAttackCombo;
	UAnimMontage* ShieldAttackCombo2;
	UAnimMontage* ShieldAttackCombo3;
	UAnimMontage* DashShieldAttack;
	UAnimMontage* LeftAttack;
	UAnimMontage* RightAttack;
	UAnimMontage* EvadeLeft;
	UAnimMontage* EvadeRight;
	UAnimMontage* EvadeForward;
	UAnimMontage* EvadeBack;
	UAnimMontage* StepLeft;
	UAnimMontage* StepRight;
	UAnimMontage* StepForward;
	UAnimMontage* StepBack;
	UAnimMontage* StepBackCombo1;
	UAnimMontage* StepBackCombo2;
	UAnimMontage* JumpKnockDownAttack;
	UAnimMontage* DashBlowAwayAttack;
	UAnimMontage* DashFloatAttack;
	UAnimMontage* SpecialAttack;


};

//PlayerMontage
USTRUCT(Atomic, BlueprintType)
struct FStateMontage
{
	GENERATED_BODY()

public:
	UAnimMontage* StopEquip;
	UAnimMontage* MovingEquip;
	UAnimMontage* StopUnequip;
	UAnimMontage* MovingUnequip;
	UAnimMontage* Guard;
	UAnimMontage* Block;
	UAnimMontage* JumpStart;
	UAnimMontage* JumpLoop;
	UAnimMontage* JumpEnd;
	UAnimMontage* BackHit;
	UAnimMontage* RightHit;
	UAnimMontage* LeftHit;
	UAnimMontage* KnockBack;
	UAnimMontage* KnockDown;
	UAnimMontage* BlowAway;
	UAnimMontage* Die1;
	UAnimMontage* Die2;
	UAnimMontage* Getup;
	UAnimMontage* Teleport;

};



UCLASS()
class U00_PORTFOLIO_API AC_Player : public ACharacter
{
	GENERATED_BODY()

public:
	AC_Player();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
		void OnHitOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	void TeleportingToTwoHand();
	void TeleportToTwoHand();

	void TeleportingToKatana();
	void TeleportToKatana();

	void TeleportingToAssassin();
	void TeleportToAssassin();


	//class UCMontagePlayer* MontagePlayer;

	class UCameraComponent* GetFollowCamera() const { return PlayerCamera; }
	class UCameraComponent* GetSkillCamera() const { return SkillCamera; }
	class USpringArmComponent* GetCameraBoom() const { return PlayerSpringArm; }
	class UPostProcessComponent* GetRadialBlur() const { return RadialBlur; }
	class UUserWidget* GetBloodEffect() const { return BloodEffect; }
public:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class UCameraComponent* SkillCamera;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class USpringArmComponent* PlayerSpringArm;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PostProcess")
		class UPostProcessComponent* RadialBlur;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> BloodEffectClass;

	UPROPERTY()
		UUserWidget* BloodEffect;

	TSubclassOf<class UCameraShake> GetCameraShake() { return CameraShake; }

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShake> CameraShake;

private:
	FVector DirectionToMove = FVector::ZeroVector;

public:
	AC_PlayerWeapon* GetPlayerWeapon() { return PlayerWeapon; }
	AC_PlayerShield* GetPlayerShield() { return PlayerShield; }
	AC_PlayerHelmet* GetPlayerHelmet() { return PlayerHelmet; }
	AC_PlayerFootDumy* GetPlayerFootDumy() { return PlayerFootDumy; }

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<AC_PlayerWeapon> PlayerWeaponClass;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<AC_PlayerShield> PlayerShieldClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AC_PlayerHelmet> PlayerHelmetClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AC_PlayerFootDumy> PlayerFootDumyClass;

	UFUNCTION(BlueprintPure, BlueprintCallable)
		bool GetHit() const { return bGetHit; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
		bool GetCanBlock() const { return bCanBlock; }

	bool GetKnockDown() const { return bKnockDown; }
	bool GetTeleporting() const { return bTeleporting; }

	void SetHit(bool val) { bGetHit = val; }
	void SetCanBlock(bool val) { bCanBlock = val; }
	void SetCanGetup(bool val) { bCanGetup = val; }
	void SetKnockDown(bool val) { bKnockDown = val; }
	void SetTeleporting(bool val) { bTeleporting = val; }
	
	void Montages();

	FDirectionalMontage GetDierctionalMontages() { return DirectionalMontages; }
	FStateMontage GetStateMontages() { return StateMontages; }

private:
	AC_PlayerWeapon* PlayerWeapon;
	AC_PlayerShield* PlayerShield;
	AC_PlayerHelmet* PlayerHelmet;
	AC_PlayerFootDumy* PlayerFootDumy;

private:
	bool bGetHit;
	bool bCanBlock;
	bool bCanGetup;
	bool bKnockDown;
	bool bTeleporting;

	float FrontBackResult;
	float LeftRightResult;

	float ArmLengthTo = 0.0f;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;


private:
	FDirectionalMontage DirectionalMontages;
	FStateMontage StateMontages;
	UAnimMontage* PlayerCurrentMontage;
	float PlayMontageRate = 1.0f;

};
