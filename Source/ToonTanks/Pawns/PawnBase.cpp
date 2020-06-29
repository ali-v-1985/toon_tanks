// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"

// Sets default values
APawnBase::APawnBase()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
    RootComponent = CapsuleComponent;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
    BaseMesh->SetupAttachment(RootComponent);

    TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
    TurretMesh->SetupAttachment(BaseMesh);

    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
    ProjectileSpawnPoint->SetupAttachment(TurretMesh);

    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void APawnBase::BeginPlay()
{
    Super::BeginPlay();
}

void APawnBase::RotateTurret(const FVector TargetLocation)
{
    FVector StartLocation = TurretMesh->GetComponentLocation();
    FVector TargetSightLocation = FVector(TargetLocation.X, TargetLocation.Y, TurretMesh->GetComponentLocation().Z);
    FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation,
                                                                     TargetSightLocation);
    TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire()
{
    if (ProjectileClass)
    {
        FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
        FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
        AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass,
                                                                                  SpawnLocation,
                                                                                  SpawnRotation);
        TempProjectile->SetOwner(this);
    }
}

void APawnBase::HandleDestruction()
{
    if (DeathParticle)
    {
        UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle,
                                                 GetActorLocation(),
                                                 FRotator::ZeroRotator);
    }
    if (DeathSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, DeathSound,
                                              GetActorLocation());
    }
}

// Called every frame
void APawnBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APawnBase::PawnDestroyed()
{
    HandleDestruction();
}
