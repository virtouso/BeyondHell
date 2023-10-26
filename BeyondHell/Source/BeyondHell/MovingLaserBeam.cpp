#include "MovingLaserBeam.h"

#include "Animation/ActiveStateMachineScope.h"

// Sets default values
AMovingLaserBeam::AMovingLaserBeam()
{
	ActiveState = &AMovingLaserBeam::MovingState;
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
}

void AMovingLaserBeam::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("hit something"));
	APlayerController* PlayerController = Cast<APlayerController>(OtherActor);

	if (PlayerController)
	{
		// OtherActor is a player.
		// Your code for handling player character overlap here.
		UE_LOG(LogTemp, Warning, TEXT("hit player"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("hit suckers"));
		// OtherActor is not a player.
		// Your code for handling other objects here.
	}
}


void AMovingLaserBeam::BeginPlay()
{
	FColor DebugTextColor = FColor::Green; // Set the text color
	float TimeToDisplay = 5.0f; // Display time in seconds
	FVector2D ScreenLocation = FVector2D(50, 50); // Screen location

	FString DebugMessage = TEXT("This is an on-screen debug message!");
	GEngine->AddOnScreenDebugMessage(-1, 1, DebugTextColor, DebugMessage, false, ScreenLocation);
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AMovingLaserBeam::OnOverlap);
}


// Called every frame
void AMovingLaserBeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("tick suckers"));
	if (ActiveState != nullptr)
		(this->*ActiveState)(DeltaTime);
}

static float timer;

//static void(AMovingLaserBeam::* activeState)(float DeltaTime);

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
			timer = 0;
			ActiveState = &AMovingLaserBeam::StaticState;
		}
	}
}

void AMovingLaserBeam::StaticState(float DeltaTime)
{
	timer += DeltaTime;
	if (timer >= 3)
	{
		ActiveState = &AMovingLaserBeam::MovingState;
		timer = 0;
	}
}
