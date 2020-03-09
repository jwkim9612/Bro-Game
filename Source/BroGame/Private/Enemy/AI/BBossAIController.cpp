// Fill out your copyright notice in the Description page of Project Settings.


#include "BBossAIController.h"
#include "BGameStateBase.h"
#include "BLevelScriptActor.h"

ABBossAIController::ABBossAIController()
{

}

void ABBossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BGameStateBase->IsBossWave())
	{
		ABLevelScriptActor* BLevelScriptActor = Cast<ABLevelScriptActor>(GetWorld()->GetLevelScriptActor());
		if (BLevelScriptActor != nullptr)
		{
			BLevelScriptActor->OnEndCinematic.AddUObject(this, &ABBossAIController::RunAI);
		}
		else
		{
			BLOG(Warning, TEXT("No Controller"));
		}
	}
}
