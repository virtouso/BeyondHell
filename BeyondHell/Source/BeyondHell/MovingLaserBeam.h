// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MovingLaserBeam.generated.h"

UCLASS()
class BEYONDHELL_API AMovingLaserBeam : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Moving")
	float moveThreshold;
	UPROPERTY(EditAnywhere, Category = "Moving")
	int moveIndexPoint;
	UPROPERTY(EditAnywhere, Category = "Moving")
	float moveSpeed;
	UPROPERTY(EditAnywhere, Category = "Moving")
	TArray<AActor*> movingPoints;
	UPROPERTY(EditAnywhere, Category = "Moving")
	UBoxComponent* CollisionComponent;

	void (*ActiveState)(int);
	
public:
	// Sets default values for this actor's properties
	AMovingLaserBeam();

protected:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void MovingState(float DeltaTime);
	void DeltaTimeStaticState(float DeltaTime);
};
