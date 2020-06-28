// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;
/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
    GENERATED_BODY()
public:
    APawnTurret();
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    virtual void HandleDestruction() override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    float FireRate = 2.f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    float FireRange = 500.f;
    
    float InitialRotateAngel = 0.f;
    
    FTimerHandle FireRateTimerHandle;

    APawnTank* PlayerPawn;

    void CheckFireCondition();

    float DistanceToPlayer() const;
};
