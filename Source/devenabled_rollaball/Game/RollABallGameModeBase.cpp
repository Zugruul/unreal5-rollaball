// Fill out your copyright notice in the Description page of Project Settings.


#include "RollABallGameModeBase.h"

#include "RollABallWidget.h"
#include "devenabled_rollaball/Items/RollABallItemBase.h"
#include "Kismet/GameplayStatics.h"

void ARollABallGameModeBase::BeginPlay() {
	Super::BeginPlay();

	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollABallItemBase::StaticClass(), Items);


	ItemsInLevel = Items.Num();

	GEngine->AddOnScreenDebugMessage(
		-1,
		15.0f,
		FColor::White,
		FString::Printf(TEXT("Items in level %d"), ItemsInLevel)
	);

	if (GameWidgetClass) {
		GameWidget = Cast<URollABallWidget>(CreateWidget(GetWorld(), GameWidgetClass));

		if (GameWidget) {
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}
}

void ARollABallGameModeBase::UpdateItemText() {
	// GEngine->AddOnScreenDebugMessage(
	// 	-1,
	// 	15.0f,
	// 	FColor::White,
	// 	FString::Printf(TEXT("Items %d/%d"), ItemsCollected, ItemsInLevel)
	// );
	GameWidget->SetItemText(ItemsCollected, ItemsInLevel);
}

void ARollABallGameModeBase::ItemCollected() {
	ItemsCollected += 1;
	// GEngine->AddOnScreenDebugMessage(
	// 	-1,
	// 	15.0f,
	// 	FColor::White,
	// 	FString::Printf(TEXT("Collected item"))
	// );
	UpdateItemText();
}
