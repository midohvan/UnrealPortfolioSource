#include "CMontagePlayer.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Player/C_PlayerController.h"
#include "Enemy/C_EnemyBase.h"
#include "Player/C_Player.h"


//UAnimMontage *UCMontagePlayer::MontagesFinder(const TCHAR * text)
//{
//	ConstructorHelpers::FObjectFinder<UAnimMontage> temp(text);
//
//	return temp.Succeeded() ? temp.Object : NULL;
//}

UCMontagePlayer::UCMontagePlayer()
{

	//////////////////////////////////////////////////////////////////////////////
	////////////////////////////////Player(Warrior)///////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	////Attack
	//{
	//	DirectionalMontages.MovingNormalAttack = MontagesFinder(L"/Game/Player/Montages/MovingNormalAttack_Montage");
	//	DirectionalMontages.StopNormalAttack = MontagesFinder(L"/Game/Player/Montages/StopNormalAttack_Montage");
	//	DirectionalMontages.LeftAttack = MontagesFinder(L"/Game/Player/Montages/LeftAttack_Montage");
	//	DirectionalMontages.RightAttack = MontagesFinder(L"/Game/Player/Montages/RightAttack_Montage");

	//	DirectionalMontages.NormalAttackCombo1 = MontagesFinder(L"/Game/Player/Montages/NormalAttackCombo1_Montage");
	//	DirectionalMontages.NormalAttackCombo2 = MontagesFinder(L"/Game/Player/Montages/NormalAttackCombo2_Montage");


	//	DirectionalMontages.Kick = MontagesFinder(L"/Game/Player/Montages/Kick_Montage");
	//	DirectionalMontages.KickCombo2 = MontagesFinder(L"/Game/Player/Montages/Kick_Combo2_Montage");
	//	DirectionalMontages.KickCombo3 = MontagesFinder(L"/Game/Player/Montages/Kick_Combo3_Montage");

	//	DirectionalMontages.JumpKnockDownAttack = MontagesFinder(L"/Game/Player/Montages/Jump_KnockDownAttack_Montage");
	//	DirectionalMontages.DashBlowAwayAttack = MontagesFinder(L"/Game/Player/Montages/Dash_BlowAway_Attack_Montage");
	//	
	//	DirectionalMontages.StepBackCombo1 = MontagesFinder(L"/Game/Player/Montages/StepBackCombo_Montage");
	//	DirectionalMontages.StepBackCombo2 = MontagesFinder(L"/Game/Player/Montages/StepBackCombo2_Montage");

	//	DirectionalMontages.ShieldAttack = MontagesFinder(L"/Game/Player/Montages/ShieldAttack_Montage");
	//	DirectionalMontages.ShieldAttackCombo = MontagesFinder(L"/Game/Player/Montages/ShieldAttackCombo_Montage");
	//	DirectionalMontages.ShieldAttackCombo2 = MontagesFinder(L"/Game/Player/Montages/ShieldAttackCombo2_Montage");
	//	DirectionalMontages.ShieldAttackCombo3 = MontagesFinder(L"/Game/Player/Montages/ShieldAttackCombo3_Montage");
	//	DirectionalMontages.DashShieldAttack = MontagesFinder(L"/Game/Player/Montages/Dash_ShieldAttack_Montage");
	//	DirectionalMontages.SpecialAttack = MontagesFinder(L"/Game/Player/Montages/SpecialAttack_Montage");


	//}
	//
	////Step
	//{
	//	DirectionalMontages.EvadeForward = MontagesFinder(L"/Game/Player/Montages/Evade_Forward_Montage");
	//	DirectionalMontages.EvadeBack = MontagesFinder(L"/Game/Player/Montages/Evade_Back_Montage");
	//	DirectionalMontages.EvadeLeft = MontagesFinder(L"/Game/Player/Montages/Evade_Left_Montage");
	//	DirectionalMontages.EvadeRight = MontagesFinder(L"/Game/Player/Montages/Evade_Right_Montage");

	//	DirectionalMontages.StepLeft = MontagesFinder(L"/Game/Player/Montages/Step_Left_Montage");
	//	DirectionalMontages.StepRight = MontagesFinder(L"/Game/Player/Montages/Step_Right_Montage");
	//	DirectionalMontages.StepForward = MontagesFinder(L"/Game/Player/Montages/Step_Forward_Montage");
	//	DirectionalMontages.StepBack = MontagesFinder(L"/Game/Player/Montages/Step_Back_Montage");
	//}
	//
	////State
	//{
	//	StateMontages.StopEquip = MontagesFinder(L"/Game/Player/Montages/StopEquip_Montage");
	//	StateMontages.StopUnequip = MontagesFinder(L"/Game/Player/Montages/StopUnequip_Montage");

	//	StateMontages.MovingEquip = MontagesFinder(L"/Game/Player/Montages/MovingEquip_Montage");
	//	StateMontages.MovingUnequip = MontagesFinder(L"/Game/Player/Montages/MovingUnequip_Montage");

	//	StateMontages.Guard = MontagesFinder(L"/Game/Player/Montages/Guard_Montage");
	//	StateMontages.Block = MontagesFinder(L"/Game/Player/Montages/Block1_Montage");
	//	StateMontages.Teleport = MontagesFinder(L"/Game/Player/Montages/Teleport_Montage");
	//}

	////Hit
	//{
	//	StateMontages.BackHit = MontagesFinder(L"/Game/Player/Montages/BackHit_Montage");
	//	StateMontages.LeftHit = MontagesFinder(L"/Game/Player/Montages/LeftHit_Montage");
	//	StateMontages.RightHit = MontagesFinder(L"/Game/Player/Montages/RightHit_Montage");
	//	StateMontages.KnockBack = MontagesFinder(L"/Game/Player/Montages/Hit_KnockBack_Montage");
	//	StateMontages.KnockDown = MontagesFinder(L"/Game/Player/Montages/Hit_KnockDown_Montage");
	//	StateMontages.BlowAway = MontagesFinder(L"/Game/Player/Montages/BlowAway_IP_Montage");
	//	StateMontages.Getup = MontagesFinder(L"/Game/Player/Montages/Getup_Montage");
	//}

	////////////////////////////////////////////////////////////////////////////
	//////////////////////////////Enemy(2H_Enemy)///////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	////Attack
	//{
	//	enemyAttackMontages.NormalAttack = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_NormalAttack_Montage");
	//	enemyAttackMontages.StrongAttack = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_Heavy_Montage");
	//	enemyAttackMontages.DownAttack = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_StrongAttack_Montage");
	//	enemyAttackMontages.SpecialAttack1 = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_WhirlWind_Montage");
	//	enemyAttackMontages.SpecialAttack3 = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_Combo_Montage");
	//	enemyAttackMontages.SpecialAttack2 = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_Combo5_All_Montage");
	//	enemyAttackMontages.SpecialAttack4 = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_RollingAttack_Montage");

	//}
	////State
	//{
	//	enemyStateMontage.Guard = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_Guard_Montage");
	//	enemyStateMontage.Block = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_Block_Montage");
	//	enemyStateMontage.Die1 = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_Death_Montage");
	//	enemyStateMontage.Getup = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_Getup_Montage");
	//	enemyStateMontage.StepBack = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_StepBack_Montage");
	//	enemyStateMontage.StepLeft = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_StepLeft_Montage");
	//	enemyStateMontage.StepRight = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_StepRight_Montage");
	//	enemyStateMontage.CameraAction = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/CameraAction_Montage");
	//	enemyStateMontage.NoTargetAction = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/CameraAction_Montage");

	//}
	//
	////Hit
	//{
	//	enemyStateMontage.Hit = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_Hit_Montage");
	//	enemyStateMontage.BackHit = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_BackHit_Montage");
	//	enemyStateMontage.KnockBack = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_KnockBack_Montage");
	//	enemyStateMontage.KnockDown = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_KnockDown_Montage");
	//	enemyStateMontage.BlowAway = MontagesFinder(L"/Game/Enemy/Animation/2Hand/Montages/2H_BlowAway_IP_Montage");
	//}

	////////////////////////////////////////////////////////////////////////////
	//////////////////////////////Enemy(Katana_Enemy)///////////////////////////
	////////////////////////////////////////////////////////////////////////////

	////Attack
	//{
	//	katanaAttackMontages.NormalAttack = MontagesFinder(L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_S1_Attack02_Montage");
	//	katanaAttackMontages.StrongAttack = MontagesFinder(L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_S2_Attack03_Montage");
	//	katanaAttackMontages.DownAttack = MontagesFinder(L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_S3_Attack03_Montage");
	//	katanaAttackMontages.SpecialAttack1 = MontagesFinder(L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_S2_Skill01_Montage");
	//	katanaAttackMontages.SpecialAttack2 = MontagesFinder(L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_S3_Skill02_Montage");
	//	katanaAttackMontages.SpecialAttack3 = MontagesFinder(L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_S2_Combo02_All_Montage");
	//	katanaAttackMontages.SpecialAttack4 = MontagesFinder(L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_S1_Skill01_Montage");
	//}

	////State
	//{
	//	katanaStateMontage.Hit = MontagesFinder(L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_Hit01_Montage");
	//	katanaStateMontage.BackHit = MontagesFinder(L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_Hit03_Montage");
	//	katanaStateMontage.KnockBack = MontagesFinder(L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_Hit_Knockback_Montage");
	//	katanaStateMontage.KnockDown = MontagesFinder(L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_Hit_Knockdown_Loop_Montage");
	//	katanaStateMontage.BlowAway = MontagesFinder(L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_Hit_Knockdown_Montage");
	//	katanaStateMontage.StepBack = MontagesFinder(L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_Tumbling_B_Montage");
	//	katanaStateMontage.Die1 = MontagesFinder(L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_Die01_Montage");
	//	katanaStateMontage.CameraAction = MontagesFinder(L"/Game/Enemy/Animation/Katana/Montages/CameraAction_Montage");
	//	//katanaStateMontage.NoTargetAction = MontagesFinder(L"/Game/Enemy/Animation/Katana/Montages/Frank_RPG_Katana_Die01_Montage");
	//}

}

//void UCMontagePlayer::PlayAttackMontage(ACharacter * character, EInputDirection direction)
//{
//	if (IsValid(character) == false) return;
//
//	switch (direction)
//	{
//		case EInputDirection::Left:
//		{
//			PlayerCurrentMontage = DirectionalMontages.LeftAttack;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage, 0.9f);
//		}
//		break;
//		case EInputDirection::Right:
//		{
//			PlayerCurrentMontage = DirectionalMontages.RightAttack;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage, 0.9f);
//		}
//		break;
//		case EInputDirection::Back:break;
//		case EInputDirection::Forward:
//		{
//			if (character->GetCharacterMovement()->Velocity.Size() > 0.1f)
//			{
//				PlayerCurrentMontage = DirectionalMontages.MovingNormalAttack;
//				if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//			}
//			else
//			{
//				PlayerCurrentMontage = DirectionalMontages.StopNormalAttack;
//				if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//			}
//		}
//		break;
//		case EInputDirection::NormalCombo1:
//		{
//			PlayerCurrentMontage = DirectionalMontages.NormalAttackCombo1;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage,0.9f);
//		}
//		break;
//		case EInputDirection::NormalCombo2:
//		{
//			PlayerCurrentMontage = DirectionalMontages.NormalAttackCombo2;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage,0.9f);
//		}
//		break;
//
//		case EInputDirection::JumpKnockDownAttack:
//		{
//			PlayerCurrentMontage = DirectionalMontages.JumpKnockDownAttack;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//		}
//		break;
//		case EInputDirection::DashBlowAwayAttack:
//		{
//			PlayerCurrentMontage = DirectionalMontages.DashBlowAwayAttack;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//		}
//		break;
//		case EInputDirection::DashShieldAttack:
//		{
//			PlayerCurrentMontage = DirectionalMontages.DashShieldAttack;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//		}
//		break;
//
//		case EInputDirection::StepBackCombo1:
//		{
//			PlayerCurrentMontage = DirectionalMontages.StepBackCombo1;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage,0.9f);
//		}
//		break;
//		case EInputDirection::StepBackCombo2:
//		{
//			PlayerCurrentMontage = DirectionalMontages.StepBackCombo2;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//		}
//		break;
//
//		case EInputDirection::Kick:
//		{
//			PlayerCurrentMontage = DirectionalMontages.Kick;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//		}
//		break;
//		case EInputDirection::KickCombo2:
//		{
//			PlayerCurrentMontage = DirectionalMontages.KickCombo2;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage, 0.9f);
//		}
//		break;
//		case EInputDirection::KickCombo3:
//		{
//			PlayerCurrentMontage = DirectionalMontages.KickCombo3;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage,0.9f);
//		}
//		break;
//		case EInputDirection::ShieldAttack:
//		{
//			PlayerCurrentMontage = DirectionalMontages.ShieldAttack;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//		}
//		break;
//		case EInputDirection::ShieldAttackCombo:
//		{
//			PlayerCurrentMontage = DirectionalMontages.ShieldAttackCombo;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//		}
//		break;
//		case EInputDirection::ShieldAttackCombo2:
//		{
//			PlayerCurrentMontage = DirectionalMontages.ShieldAttackCombo2;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage,0.9f);
//		}
//		break;
//		case EInputDirection::ShieldAttackCombo3:
//		{
//			PlayerCurrentMontage = DirectionalMontages.ShieldAttackCombo3;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage,0.9f);
//		}
//		break;
//		case EInputDirection::Special:
//		{
//			PlayerCurrentMontage = DirectionalMontages.SpecialAttack;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage, 1.2f);
//		}
//		break;
//	}
//
//	return;
//
//}
//
//void UCMontagePlayer::PlayMovingMontage(ACharacter * character, EInputDirection direction, bool bWeaponDrawn)
//{
//	if (IsValid(character) == false) return;
//	
//	switch (direction)
//	{
//		case EInputDirection::Left:
//		{
//			if (bWeaponDrawn == true)
//			{
//				PlayerCurrentMontage = DirectionalMontages.StepLeft;
//				if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//			}
//			else
//			{
//				PlayerCurrentMontage = DirectionalMontages.EvadeLeft;
//				if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//			}
//		}
//		break;
//		case EInputDirection::Right:
//		{
//			if (bWeaponDrawn == true)
//			{
//				PlayerCurrentMontage = DirectionalMontages.StepRight;
//				if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//			}
//			else
//			{
//				PlayerCurrentMontage = DirectionalMontages.EvadeRight;
//				if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//			}
//		}
//		break;
//		case EInputDirection::Forward:
//		{
//			if (bWeaponDrawn == true)
//			{
//				PlayerCurrentMontage = DirectionalMontages.StepForward;
//				if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//			}
//			else
//			{
//				PlayerCurrentMontage = DirectionalMontages.EvadeForward;
//				if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//			}
//		}
//		break;
//		case EInputDirection::Back:
//		{
//			if (bWeaponDrawn == true)
//			{
//				PlayerCurrentMontage = DirectionalMontages.StepBack;
//				if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//			}
//			else
//			{
//				PlayerCurrentMontage = DirectionalMontages.EvadeBack;
//				if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//			}
//		}
//		break;
//	}
//
//	return;
//
//}
//
//void UCMontagePlayer::PlayStateMontage(ACharacter * character, EState state)
//{
//
//	if (IsValid(character) == false) return;
//	
//	
//	switch (state)
//	{
//		case EState::Equip:
//		{
//			if (character->GetCharacterMovement()->Velocity.Size() > 0.1f)
//			{
//				PlayerCurrentMontage = StateMontages.MovingEquip;
//				if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//			}
//			else
//			{
//				PlayerCurrentMontage = StateMontages.StopEquip;
//				if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//			}
//		}
//		break;
//		case EState::Unequip:
//		{
//			if (character->GetCharacterMovement()->Velocity.Size() > 0.1f)
//			{
//				PlayerCurrentMontage = StateMontages.MovingUnequip;
//				if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//			}
//			else
//			{
//				PlayerCurrentMontage = StateMontages.StopUnequip;
//				if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//			}
//		}
//		break;
//		case EState::Guard:
//		{
//			PlayerCurrentMontage = StateMontages.Guard;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage, 0.5f);
//		}
//		break;
//		case EState::BackHit:
//		{
//			PlayerCurrentMontage = StateMontages.BackHit;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//		}
//		break;
//		case EState::LeftHit:
//		{
//			PlayerCurrentMontage = StateMontages.LeftHit;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//		}
//		break;
//		case EState::RightHit:
//		{
//			PlayerCurrentMontage = StateMontages.RightHit;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//		}
//		break;
//		case EState::KnockBack:
//		{
//			PlayerCurrentMontage = StateMontages.KnockBack;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//		}
//		break;
//		case EState::KnockDown:
//		{
//			PlayerCurrentMontage = StateMontages.KnockDown;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//		}
//		break;
//		case EState::BlowAway:
//		{
//			if (IsValid(character) == true) character->LaunchCharacter(-(character->GetActorForwardVector()* 500.0f) + FVector(0, 0, 700.0f), true, true);
//			PlayerCurrentMontage = StateMontages.BlowAway;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage, 0.7f);
//
//		}
//		break;
//		case EState::Getup:
//		{
//			PlayerCurrentMontage = StateMontages.Getup;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage);
//		}
//		break;
//		case EState::Block:
//		{
//			PlayerCurrentMontage = StateMontages.Block;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage, 0.8f);
//		}
//		break;
//		case EState::Teleport:
//		{
//			PlayerCurrentMontage = StateMontages.Teleport;
//			if (IsValid(character) == true) character->PlayAnimMontage(PlayerCurrentMontage, 0.8f);
//		}
//		break;
//	}//switch
//
//	return;
//
//}

//void UCMontagePlayer::PlayEnemyAttackMontage(ACharacter * character, EEnemyAttack attack)
//{
//	if (IsValid(character) == false) return;
//
//	
//	switch (attack)
//	{
//		case EEnemyAttack::Normal:
//		{
//			EnemyCurrentMontage = enemyAttackMontages.NormalAttack;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage);
//		}
//		break;
//		case EEnemyAttack::Strong:
//		{
//			EnemyCurrentMontage = enemyAttackMontages.StrongAttack;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage);
//		}
//		break;
//		case EEnemyAttack::Down:
//		{
//			EnemyCurrentMontage = enemyAttackMontages.DownAttack;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage);
//		}
//		break;
//		case EEnemyAttack::Special1:
//		{
//			EnemyCurrentMontage = enemyAttackMontages.SpecialAttack1;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage);
//		}
//		break;
//		case EEnemyAttack::Special2:
//		{
//			EnemyCurrentMontage = enemyAttackMontages.SpecialAttack2;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage);
//		}
//		break;
//		case EEnemyAttack::Special3:
//		{
//			EnemyCurrentMontage = enemyAttackMontages.SpecialAttack3;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage,0.75f);
//		}
//		break;
//		case EEnemyAttack::Special4:
//		{
//			EnemyCurrentMontage = enemyAttackMontages.SpecialAttack4;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage, 0.75f);
//		}
//		break;
//	}
//
//	return;
//
//}
//
//void UCMontagePlayer::PlayEnemyStateMontage(ACharacter * character, EEnemyState state)
//{
//	if (IsValid(character) == false) return;
//
//
//	switch (state)
//	{
//		case EEnemyState::Guard:
//		{
//
//			EnemyCurrentMontage = enemyStateMontage.Guard;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage, 0.5f);
//		}
//		break;
//		case EEnemyState::Block:
//		{
//			EnemyCurrentMontage = enemyStateMontage.Block;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage, 0.8f);
//		}
//		break;
//		case EEnemyState::Hit:
//		{
//			EnemyCurrentMontage = enemyStateMontage.Hit;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage);
//		}
//		break;
//		case EEnemyState::BackHit:
//		{
//			EnemyCurrentMontage = enemyStateMontage.BackHit;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage);
//		}
//		break;
//		case EEnemyState::StepBack:
//		{
//			EnemyCurrentMontage = enemyStateMontage.StepBack;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage);
//		}
//		break;
//		case EEnemyState::StepLeft:
//		{
//			EnemyCurrentMontage = enemyStateMontage.StepLeft;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage);
//		}
//		break;
//		case EEnemyState::StepRight:
//		{
//			EnemyCurrentMontage = enemyStateMontage.StepRight;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage);
//		}
//		break;
//		case EEnemyState::KnockBack:
//		{
//			EnemyCurrentMontage = enemyStateMontage.KnockBack;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage);
//		}
//		break;
//		case EEnemyState::KnockDown:
//		{
//			EnemyCurrentMontage = enemyStateMontage.KnockDown;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage);
//		}
//		break;
//		case EEnemyState::BlowAway:
//		{
//			if (IsValid(character) == true)character->LaunchCharacter(-(character->GetActorForwardVector()* 700.f) + FVector(0, 0, 400.f), true, true);
//			EnemyCurrentMontage = enemyStateMontage.BlowAway;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage);
//		}
//		break;
//		case EEnemyState::Die1:
//		{
//			EnemyCurrentMontage = enemyStateMontage.Die1;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage);
//		}
//		break;
//		case EEnemyState::CameraAction:
//		{
//			EnemyCurrentMontage = enemyStateMontage.CameraAction;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage);
//		}
//		break;
//		case EEnemyState::NoTargetAction:
//		{
//			EnemyCurrentMontage = enemyStateMontage.NoTargetAction;
//			if (IsValid(character) == true)character->PlayAnimMontage(EnemyCurrentMontage);
//		}
//		break;
//	}
//
//	return;
//
//}

//void UCMontagePlayer::PlayKatanaAttackMontage(ACharacter * character, EEnemyAttack attack)
//{
//	if (IsValid(character) == false) return;
//
//
//	switch (attack)
//	{
//		case EEnemyAttack::Normal:
//		{
//			KatanaCurrentMontage = katanaAttackMontages.NormalAttack;
//			if(IsValid(character) == true)
//				character->PlayAnimMontage(KatanaCurrentMontage);
//		}
//		break;
//		case EEnemyAttack::Strong:
//		{
//			KatanaCurrentMontage = katanaAttackMontages.StrongAttack;
//			if (IsValid(character) == true)character->PlayAnimMontage(KatanaCurrentMontage);
//		}
//		break;
//		case EEnemyAttack::Special1:
//		{
//			KatanaCurrentMontage = katanaAttackMontages.SpecialAttack1;
//			if (IsValid(character) == true)character->PlayAnimMontage(KatanaCurrentMontage);
//		}
//		break;
//		case EEnemyAttack::Special2:
//		{
//			KatanaCurrentMontage = katanaAttackMontages.SpecialAttack2;
//			if (IsValid(character) == true)character->PlayAnimMontage(KatanaCurrentMontage);
//		}
//		break;
//		case EEnemyAttack::Special3:
//		{
//			KatanaCurrentMontage = katanaAttackMontages.SpecialAttack3;
//			if (IsValid(character) == true)character->PlayAnimMontage(KatanaCurrentMontage);
//		}
//		break;
//		case EEnemyAttack::Special4:
//		{
//			KatanaCurrentMontage = katanaAttackMontages.SpecialAttack4;
//			character->PlayAnimMontage(KatanaCurrentMontage);
//		}
//		break;
//		case EEnemyAttack::Down:
//		{
//			KatanaCurrentMontage = katanaAttackMontages.DownAttack;
//			if (IsValid(character) == true)character->PlayAnimMontage(KatanaCurrentMontage);
//		}
//		break;
//	
//	}
//	return;
//}
//
//void UCMontagePlayer::PlayKatanaStateMontage(ACharacter * character, EEnemyState state)
//{
//	if (IsValid(character) == false) return;
//
//
//	switch (state)
//	{
//		case EEnemyState::Guard:
//		{
//			KatanaCurrentMontage = katanaStateMontage.Guard;
//			if (IsValid(character) == true) character->PlayAnimMontage(KatanaCurrentMontage,0.5f);
//		}
//		break;
//		case EEnemyState::Hit:
//		{
//			KatanaCurrentMontage = katanaStateMontage.Hit;
//			if (IsValid(character) == true) character->PlayAnimMontage(KatanaCurrentMontage);
//		}
//		break;
//		case EEnemyState::BackHit:
//		{
//			KatanaCurrentMontage = katanaStateMontage.BackHit;
//			if (IsValid(character) == true) character->PlayAnimMontage(KatanaCurrentMontage);
//		}
//		break;
//		case EEnemyState::Block:
//		{
//			KatanaCurrentMontage = katanaStateMontage.Block;
//			if (IsValid(character) == true) character->PlayAnimMontage(KatanaCurrentMontage);
//		}
//		break;
//		case EEnemyState::KnockBack:
//		{
//			KatanaCurrentMontage = katanaStateMontage.KnockBack;
//			if (IsValid(character) == true) character->PlayAnimMontage(KatanaCurrentMontage);
//		}
//		break;
//		case EEnemyState::KnockDown:
//		{
//			KatanaCurrentMontage = katanaStateMontage.KnockDown;
//			if (IsValid(character) == true)character->PlayAnimMontage(KatanaCurrentMontage);
//		}
//		break;
//		case EEnemyState::BlowAway:
//		{
//			KatanaCurrentMontage = katanaStateMontage.BlowAway;
//			if (IsValid(character) == true) character->PlayAnimMontage(KatanaCurrentMontage);
//		}
//		break;
//		case EEnemyState::Die1:
//		{
//			KatanaCurrentMontage = katanaStateMontage.Die1;
//			if (IsValid(character) == true)character->PlayAnimMontage(KatanaCurrentMontage,0.8f);
//		}
//		break;
//		case EEnemyState::StepBack:
//		{
//			KatanaCurrentMontage = katanaStateMontage.StepBack;
//			if (IsValid(character) == true)character->PlayAnimMontage(KatanaCurrentMontage);
//		}
//		break;
//		case EEnemyState::CameraAction:
//		{
//			KatanaCurrentMontage = katanaStateMontage.CameraAction;
//			if (IsValid(character) == true)character->PlayAnimMontage(KatanaCurrentMontage);
//		}
//		break;
//
//	}
//
//	return;
//}
