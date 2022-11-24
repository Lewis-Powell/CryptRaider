// Fill out your copyright notice in the Description page of Project Settings.

//#include "Mover.h"
#include "TriggerComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AActor* AcceptedActor = GetAcceptableActor();
	//UMover* Result = GetOwner()->FindComponentByClass<UMover>();

	//UE_LOG(LogTemp, Display, TEXT("AcceptedActor%s"), *AcceptedActor);
	if (AcceptedActor != nullptr)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(AcceptedActor->GetRootComponent());
		if (Component != nullptr)
		{
			Component->SetSimulatePhysics(false);	
		}
		Component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetMoving(true);

	}
	else
	{
		Mover->SetMoving(false);
	}

}


AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	//UE_LOG(LogTemp, Display, TEXT("%s"), AcceptedTagName.ToString());
	for (AActor* Actor : Actors)
	{
		
		if (Actor->ActorHasTag(AcceptedTagName) && !Actor->ActorHasTag("Grabbed"))
		{
			//UE_LOG(LogTemp, Display, TEXT("Returning Actor with tag:"));
			return Actor;
		}
	}
	return nullptr;
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}