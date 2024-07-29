// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RollABallPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class DEVENABLED_ROLLABALL_API ARollABallPlayer : public APawn {
	GENERATED_BODY()

public:
	ARollABallPlayer();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveForce = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpImpulse = 500.0f;

	UPROPERTY(EditAnywhere)
	int32 MaxJumpCount = 2;

private:
	int32 JumpCount = 0;

	void MoveHorizontal(float Value);
	void MoveVertical(float Value);
	void Jump();

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
