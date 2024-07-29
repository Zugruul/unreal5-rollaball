// Fill out your copyright notice in the Description page of Project Settings.


#include "RollABallPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARollABallPlayer::ARollABallPlayer() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	RootComponent = Mesh;
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);

	Mesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ARollABallPlayer::BeginPlay() {
	Super::BeginPlay();

	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();

	Mesh->OnComponentHit.AddDynamic(this, &ARollABallPlayer::OnHit);
}

void ARollABallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("HorizontalAxis", this, &ARollABallPlayer::MoveHorizontal);
	InputComponent->BindAxis("VerticalAxis", this, &ARollABallPlayer::MoveVertical);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ARollABallPlayer::Jump);
}

void ARollABallPlayer::MoveHorizontal(float Value) {
	const FVector Right = Camera->GetRightVector() * MoveForce * Value;
	Mesh->AddForce(Right);
}

void ARollABallPlayer::MoveVertical(float Value) {
	const FVector Right = Camera->GetForwardVector() * MoveForce * Value;
	Mesh->AddForce(Right);
}

void ARollABallPlayer::Jump() {
	if (JumpCount >= MaxJumpCount) {
		return;
	}

	Mesh->AddImpulse(FVector(0, 0, JumpImpulse));
	JumpCount += 1;
}

void ARollABallPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	const float ZNormal = Hit.Normal.Z;
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, FString::Printf(TEXT("Z Normal %f"), ZNormal));

	if (ZNormal) {
		JumpCount = 0;
	}
}
