#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_PlayerController.generated.h"

class ACharacter;
class AActor;

UCLASS()
class U00_PORTFOLIO_API AC_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AC_PlayerController();

public:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void ASetTargetWithBlend(AActor* OtherActor);
	void SetActionCamera(AActor* OtherActor);
	void ResetCamera();

	void SetDeadCamera(class AC_EnemyBase* enemy);
public:
	class ACharacter* GetControlledPlayer() { return ControlledPlayer; }
	//class UCMontagePlayer* GetMontagePlayer() { return MontagePlayer; }
private:
	//빙의할 케릭터
	class ACharacter* ControlledPlayer;
	class AC_Player* Player;
	//class UCMontagePlayer* MontagePlayer;

private:
	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void Turn(float Axis);
	void LookUp(float Axis);

	void Walking();

	void Sprinting();
	void StopSprinting();

	void Equip();
	void Attack();
	void ShieldAttack();
	void SpecialAttack();
	void Kick();

	void BeginGuard();

	void Hit();

	void Jumping();
	void Falling();
	void Evade();

public:
	//GetSet
	UFUNCTION(BlueprintPure, BlueprintCallable)
		bool GetWeaponDrawn() const { return bWeaponDrawn; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
		bool GetDrawingWeapon() const { return bDrawingWeapon; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
		bool GetSheathingWeapon() const { return bSheathingWeapon; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
		bool GetAttacking() const { return bAttacking; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
		bool GetShieldAttacking() const { return bShieldAttacking; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
		bool GetDead() const { return bDead; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
		bool GetCanAttack() const { return bCanAttack; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
		bool GetCanBlock() const { return bCanBlock; }

	
	bool GetSecondInput() { return bCanSecondInput; }
	bool GetThirdInput()  { return bCanThirdInput; }
	bool GetFinishCombo() { return bFinishCombo; }
	bool GetCameraAction() { return bCameraAction; }

	void SetAttacking(bool val) { bAttacking = val; }
	void SetShieldAttacking(bool val) { bShieldAttacking = val; }
	void SetCanAttack(bool val) { bCanAttack = val; }
	void SetCanMove(bool val) { bCanMove = val; }
	void SetEvading(bool val) { bEvading = val; }
	void SetStepping(bool val) { bStepping = val; }
	void SetEquipped(bool val) { bWeaponDrawn = val; }
	void SetSheathing(bool val) { bSheathingWeapon = val; }
	void SetEquipping(bool val) { bDrawingWeapon = val; }
	void SetCanBlock(bool val) { bCanBlock = val; }
	void SetSecondInput(bool val) { bCanSecondInput = val; }
	void SetThirdInput(bool val) { bCanThirdInput = val; }
	void SetFinishCombo(bool val) { bFinishCombo = val; }
	void SetCameraAction(bool val) { bCameraAction = val; }
	
	AActor* GetClosestEnemy(FVector sourceLocation);

	TArray<AActor*> GetAvailableEnemy() { return Enemies; }

public:
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float MaxWalkSpeed = 300;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float MaxRunSpeed = 650;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float MaxSprintSpeed = 1000;

	TArray<AActor*> Enemies;
	class AC_EnemyBase* CameraEnemy;


private:
	bool bAnimPlaying;

	bool bEvading;
	bool bStepping;

	bool bWalking = false;	//Toggle
	bool bSprinting;

	bool bWeaponDrawn;
	bool bDrawingWeapon;
	bool bSheathingWeapon;

	bool bDead;
	bool bAttacking;
	bool bShieldAttacking;

	bool bCameraAction;

	bool bCanRageAttack;
	bool bCanAttack;
	bool bCanBlock;
	bool bCanMove = true;
	bool bMovingForward;

	bool bCanSecondInput;
	bool bCanThirdInput;
	bool bFinishCombo;
	

};
