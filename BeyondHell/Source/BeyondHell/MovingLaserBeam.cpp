
#include "MovingLaserBeam.h"

// Sets default values
AMovingLaserBeam::AMovingLaserBeam()
{
 
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
}

void AMovingLaserBeam::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	APlayerController* PlayerController = Cast<APlayerController>(OtherActor);

	if (PlayerController)
	{
		// OtherActor is a player.
		// Your code for handling player character overlap here.
	}
	else
	{
		// OtherActor is not a player.
		// Your code for handling other objects here.
	}
}


void AMovingLaserBeam::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AMovingLaserBeam::OnOverlap);
}


// Called every frame
void AMovingLaserBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

static float timer;

void AMovingLaserBeam::MovingState(float DeltaTime)
{
	if (movingPoints.Num() > 1)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector Destination = movingPoints[moveIndexPoint]->GetActorLocation();
		
		FVector Direction = (Destination - CurrentLocation).GetSafeNormal();
		
		SetActorLocation(CurrentLocation + Direction * moveSpeed * DeltaTime);
		
		if (FVector::DistSquared(CurrentLocation, Destination) < FMath::Square(moveThreshold))
		{
			moveIndexPoint = (moveIndexPoint + 1) % movingPoints.Num();
			timer=0;
		}
	}
}

void AMovingLaserBeam::DeltaTimeStaticState(float DeltaTime)
{
	auto x= MovingState;
}