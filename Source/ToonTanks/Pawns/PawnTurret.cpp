// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

APawnTurret::APawnTurret()
{
}

void APawnTurret::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle,
                                           this,
                                           &APawnTurret::CheckFireCondition,
                                           FireRate, true, false);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

    InitialRotateAngel = GetActorRotation().Yaw;
    UE_LOG(LogTemp, Log, TEXT("%s InitialRotateAngel : %f"), *GetName(), InitialRotateAngel);
}

void APawnTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(!PlayerPawn || DistanceToPlayer() > FireRange) return;

    RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
    if(!PlayerPawn || !PlayerPawn->GetPlayerAlive()) return;
    if(DistanceToPlayer() <= FireRange)
    {
        Fire();
    }
}

float APawnTurret::DistanceToPlayer() const
{
    if(!PlayerPawn) return 0.f;

    return  (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();
}

void APawnTurret::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}
