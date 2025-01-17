// Copyright Padapew 2019

#include "OpenDoor.h"
#include"Runtime/Engine/Classes/Engine/World.h"
#include"GameFramework/PlayerController.h"
#include"GameFramework/Actor.h"
#include"Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Pressure Plate"), *GetOwner()->GetName())
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the total mass on the plate is higher than TriggerMass
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) { OnOpen.Broadcast(); } 
	else { OnClose.Broadcast(); }
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	//Find all the overlapping actors
	TArray<AActor*> OVerlappingActors ;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OVerlappingActors);
	//Interate through them adding their masses
	for (const auto* Actor : OVerlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName())
	}
	return TotalMass;
}


