// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTurret;
class APawnTank;

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    void ActorDied(AActor* DeadActor);

    UFUNCTION(BlueprintImplementableEvent)
    void GameStart();

    UFUNCTION(BlueprintImplementableEvent)
    void GameOver(bool PlayerWon);

protected:
    int32 GetTargetTurretCount();
    virtual void BeginPlay() override;

private:

    int32 TargetTurrets = 0;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
    APawnTank* PlayerTank;

    APawnTurret* PawnTurret;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Loop", meta = (AllowPrivateAccess = "true"))
    int StartDelay = 3;

    void HandleGameStart();

    void HandleGameOver(bool PlayerWon);
};