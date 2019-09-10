#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CMontagePlayer.generated.h"

//class UAnimMontage;
//class ACharacter;


//Player
//UENUM(BlueprintType)
//enum class EInputDirection : uint8
//{
//	Left, Right, Forward, Back,
//	Kick, KickCombo2, KickCombo3,
//	ShieldAttack, ShieldAttackCombo, ShieldAttackCombo2, ShieldAttackCombo3,
//	JumpKnockDownAttack, DashBlowAwayAttack, DashShieldAttack,
//	StepBackCombo1, StepBackCombo2,
//	NormalCombo1, NormalCombo2,Special
//};
//UENUM(BlueprintType)
//enum class EState : uint8
//{
//	Equip, Unequip, Guard, Block,
//	JumpStart, JumpLoop, JumpEnd,
//	BackHit, LeftHit, RightHit,
//	KnockBack, KnockDown, BlowAway,
//	Die1, Die2, Getup, Teleport
//};

////Enemy
//UENUM(BlueprintType)
//enum class EEnemyAttack : uint8
//{
//	Normal, Strong, 
//	Special1, Special2, Special3,
//	Special4,Down
//};
//
////Enemy
//UENUM(BlueprintType)
//enum class EEnemyState : uint8
//{
//	Guard, Hit, BackHit,Block, 
//	KnockBack, KnockDown, BlowAway,
//	Die1, Die2, StepBack, StepRight,StepLeft,
//	Getup,
//	CameraAction,NoTargetAction,
//};


////Enemy
//USTRUCT(Atomic, BlueprintType)
//struct FEnemyAttackMontage
//{
//	GENERATED_BODY()
//public:
//	UAnimMontage* NormalAttack;
//	UAnimMontage* StrongAttack;
//	UAnimMontage* DownAttack;
//	UAnimMontage* SpecialAttack1;
//	UAnimMontage* SpecialAttack2;
//	UAnimMontage* SpecialAttack3;
//	UAnimMontage* SpecialAttack4;
//
//};
//USTRUCT(Atomic, BlueprintType)
//struct FEnemyStateMontage
//{
//	GENERATED_BODY()
//public:
//	UAnimMontage* Guard;
//	UAnimMontage* Block;
//	UAnimMontage* Hit;
//	UAnimMontage* BackHit;
//	UAnimMontage* KnockBack;
//	UAnimMontage* KnockDown;
//	UAnimMontage* BlowAway;
//	UAnimMontage* Die1;
//	UAnimMontage* Getup;
//	UAnimMontage* StepBack;
//	UAnimMontage* StepRight;
//	UAnimMontage* StepLeft;
//	UAnimMontage* CameraAction;
//	UAnimMontage* NoTargetAction;
//
//};

//
////PlayerMontage
//USTRUCT(Atomic, BlueprintType)
//struct FDirectionalMontage 
//{
//	GENERATED_BODY()
//
//public:
//	UAnimMontage* MovingNormalAttack;
//	UAnimMontage* StopNormalAttack;
//	UAnimMontage* NormalAttackCombo1;
//	UAnimMontage* NormalAttackCombo2;
//	UAnimMontage* Kick;
//	UAnimMontage* KickCombo2;
//	UAnimMontage* KickCombo3;
//	UAnimMontage* ShieldAttack;
//	UAnimMontage* ShieldAttackCombo;
//	UAnimMontage* ShieldAttackCombo2;
//	UAnimMontage* ShieldAttackCombo3;
//	UAnimMontage* DashShieldAttack;
//	UAnimMontage* LeftAttack;
//	UAnimMontage* RightAttack;
//	UAnimMontage* EvadeLeft;
//	UAnimMontage* EvadeRight;
//	UAnimMontage* EvadeForward;
//	UAnimMontage* EvadeBack;
//	UAnimMontage* StepLeft;
//	UAnimMontage* StepRight;
//	UAnimMontage* StepForward;
//	UAnimMontage* StepBack;
//	UAnimMontage* StepBackCombo1;
//	UAnimMontage* StepBackCombo2;
//	UAnimMontage* JumpKnockDownAttack;
//	UAnimMontage* DashBlowAwayAttack;
//	UAnimMontage* DashFloatAttack;
//	UAnimMontage* SpecialAttack;
//
//
//};
//
////PlayerMontage
//USTRUCT(Atomic, BlueprintType)
//struct FStateMontage
//{
//	GENERATED_BODY()
//
//public:
//	UAnimMontage* StopEquip;
//	UAnimMontage* MovingEquip;
//	UAnimMontage* StopUnequip;
//	UAnimMontage* MovingUnequip;
//	UAnimMontage* Guard;
//	UAnimMontage* Block;
//	UAnimMontage* JumpStart;
//	UAnimMontage* JumpLoop;
//	UAnimMontage* JumpEnd;
//	UAnimMontage* BackHit;
//	UAnimMontage* RightHit;
//	UAnimMontage* LeftHit;
//	UAnimMontage* KnockBack;
//	UAnimMontage* KnockDown;
//	UAnimMontage* BlowAway;
//	UAnimMontage* Die1;
//	UAnimMontage* Die2;
//	UAnimMontage* Getup;
//	UAnimMontage* Teleport;
//	
//};
//

UCLASS()
class U00_PORTFOLIO_API UCMontagePlayer : public UObject
{
	GENERATED_BODY()
	
public:
	UCMontagePlayer();

	//EInputDirection GetInputDirection() { return InputDirection; }
	//FDirectionalMontage GetDierctionalMontages() { return DirectionalMontages; }
	//FStateMontage GetStateMontages() { return StateMontages; }

	UAnimMontage* MontagesFinder(const TCHAR* text);

	////PlayerMontage
	//void PlayAttackMontage(ACharacter* character, EInputDirection direction);
	//void PlayMovingMontage(ACharacter* character, EInputDirection direction , bool bWeaponDrawn);
	//void PlayStateMontage(ACharacter* character, EState state);

	/*float GetPlayMontageRate() { return PlayMontageRate; }
	void SetPlayMontageRate(float val) { PlayMontageRate = val; }*/

	////2H_EnemyMontage
	//void PlayEnemyAttackMontage(ACharacter* character, EEnemyAttack attack);
	//void PlayEnemyStateMontage(ACharacter* character, EEnemyState state);

	////Katana_EnemyMontage
	//void PlayKatanaAttackMontage(ACharacter* character, EEnemyAttack attack);
	//void PlayKatanaStateMontage(ACharacter* character, EEnemyState state);

private:

	//Player
	////EInputDirection InputDirection;
	//FDirectionalMontage DirectionalMontages;
	//FStateMontage StateMontages;
	//UAnimMontage* PlayerCurrentMontage;
	//float PlayMontageRate = 1.0f;

	////2HEnemy
	//FEnemyAttackMontage enemyAttackMontages;
	//FEnemyStateMontage enemyStateMontage;
	//UAnimMontage* EnemyCurrentMontage;
	//float EnemyMontagePlayRate = 1.0f;

	////Katana
	//FEnemyAttackMontage katanaAttackMontages;
	//FEnemyStateMontage katanaStateMontage;
	//UAnimMontage* KatanaCurrentMontage;
	

};
