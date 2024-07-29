// Fill out your copyright notice in the Description page of Project Settings.


#include "RollABallItemBase.h"
#include "../Game/RollABallPlayer.h"
#include "devenabled_rollaball/Game/RollABallGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARollABallItemBase::ARollABallItemBase() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

void ARollABallItemBase::BeginPlay() {
	Super::BeginPlay();

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ARollABallItemBase::OverlapBegin);
}

void ARollABallItemBase::OverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
) {
	if (Cast<ARollABallPlayer>(OtherActor) != nullptr) {
		Collected();
	}
}

void ARollABallItemBase::Collected_Implementation() {
	ARollABallGameModeBase* GameMode = Cast<ARollABallGameModeBase>(GetWorld()->GetAuthGameMode());

	if (GameMode) {
		GameMode->ItemCollected();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, RootComponent->GetComponentLocation());
	}
}
