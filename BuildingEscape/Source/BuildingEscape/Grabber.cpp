// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Core/Public/Math/Vector.h"
#include "DrawDebugHelpers.h"
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber Reporting for duty"));
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	/// Get player viewpoint this tick
	FVector PlayerViewLocation = FVector::ZeroVector;
	FRotator PlayerViewRotator = FRotator::ZeroRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewLocation,PlayerViewRotator);
	
	///Draw line view trace to visualize
	FVector LineTraceEnd = PlayerViewLocation + (Reach * PlayerViewRotator.Vector()); //FVector(0.f, 0.f, 50.f);
	DrawDebugLine(GetWorld(), PlayerViewLocation, LineTraceEnd, FColor::Green, false, 0.f, 0.f, 3.f);
	
	
	///set up query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Ray-cast (Line Trace) to reach distance
	FHitResult ResultofLineTrace;
	GetWorld()->LineTraceSingleByObjectType(ResultofLineTrace, PlayerViewLocation, 
		LineTraceEnd,FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),TraceParameters);


	///see what we hit
	if (ResultofLineTrace.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Object In Reach: %s"), *ResultofLineTrace.GetActor()->GetName());
	}
}

