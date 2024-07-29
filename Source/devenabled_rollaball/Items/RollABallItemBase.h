// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RollABallItemBase.generated.h"

UCLASS()
class DEVENABLED_ROLLABALL_API ARollABallItemBase : public AActor {
	GENERATED_BODY()

public:
	ARollABallItemBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category="Components")
	USoundBase* PickupSound;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION(BlueprintNativeEvent)
	void Collected();
};
