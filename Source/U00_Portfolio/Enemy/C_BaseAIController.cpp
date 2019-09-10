#include "C_BaseAIController.h"
#include "Global.h"
#include "TimerManager.h"
#include "Enemy/C_EnemyBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AI/BotTargetPoint.h"

const FName AC_BaseAIController::HomePosKey(TEXT("HomePos"));
const FName AC_BaseAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AC_BaseAIController::TargetKey(TEXT("Target"));

AC_BaseAIController::AC_BaseAIController()
{
	RepeatInterval = 3.0f;

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}
void AC_BaseAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	Enemy = Cast<AC_EnemyBase>(InPawn);

	if (Enemy != NULL && Enemy->BotBehaviorTree != NULL)
		BlackboardComp->InitializeBlackboard(*Enemy->BotBehaviorTree->BlackboardAsset);

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABotTargetPoint::StaticClass(), BotTargetpoints);

	if (BlackboardComp != NULL)
		BehaviorComp->StartTree(*Enemy->BotBehaviorTree);
}

void AC_BaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BlackboardComp != NULL)
	{
		BlackboardComp->SetValueAsFloat("HP", Enemy->GetHP());
		BlackboardComp->SetValueAsBool("bCameraAction", Enemy->GetCameraAction());
	}
		


}

void AC_BaseAIController::SetSeenTarget(APawn * InPawn)
{
	if (BlackboardComp != NULL)
		BlackboardComp->SetValueAsObject(TargetKey, InPawn);

	//GetWorld()->GetTimerManager().SetTimer
	//(
	//	RepeatTimerHandle, this, &AC_EnemyAIController::OnRepeatTimer, RepeatInterval, false
	//);
}

void AC_BaseAIController::NormalAttack()
{
	if(Enemy != NULL)
		Enemy->NormalAttack();
}

void AC_BaseAIController::StrongAttack()
{
	if (Enemy != NULL)
		Enemy->StrongAttack();
}

void AC_BaseAIController::DownAttack()
{
	if (Enemy != NULL)
		Enemy->DownAttack();
}

void AC_BaseAIController::SpecialAttack1()
{
	if (Enemy != NULL)
		Enemy->SpecialAttack1();
}

void AC_BaseAIController::SpecialAttack2()
{
	if (Enemy != NULL)
		Enemy->SpecialAttack2();
}

void AC_BaseAIController::SpecialAttack3()
{
	if (Enemy != NULL)
		Enemy->SpecialAttack3();
}
void AC_BaseAIController::SpecialAttack4()
{
	if (Enemy != NULL)
		Enemy->SpecialAttack4();
}

void AC_BaseAIController::CameraAction()
{
	if (Enemy != NULL)
		Enemy->CameraAction();
}

void AC_BaseAIController::NoTargetAction()
{
	if (Enemy != NULL)
		Enemy->NoTargetAction();
}

void AC_BaseAIController::Guard()
{
	if (Enemy != NULL)
		Enemy->Guard();
}

void AC_BaseAIController::StepBack()
{
	if (Enemy != NULL)
		Enemy->StepBack();
}

void AC_BaseAIController::StepLeft()
{
	if (Enemy != NULL)
		Enemy->StepLeft();
}

void AC_BaseAIController::StepRight()
{
	if (Enemy != NULL)
		Enemy->StepRight();
}

void AC_BaseAIController::Dead()
{
	if (Enemy != NULL)
		Enemy->Dead();
}
