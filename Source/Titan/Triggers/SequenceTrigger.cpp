// Fill out your copyright notice in the Description page of Project Settings.


#include "SequenceTrigger.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "Components/BoxComponent.h"
#include "Titan/Characters/TitanCharacter.h"

// Sets default values
ASequenceTrigger::ASequenceTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(TriggerBox);
}

// Called when the game starts or when spawned
void ASequenceTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASequenceTrigger::OnOverlap);
}

void ASequenceTrigger::PlaySequence()
{
	TriggerBox->DestroyComponent();

	FMovieSceneSequencePlaybackSettings Settings = FMovieSceneSequencePlaybackSettings();
	Settings.bDisableLookAtInput = true;
	Settings.bDisableMovementInput = true;

	// Create a level sequence player
	ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), 
		LevelSequence, FMovieSceneSequencePlaybackSettings(), LevelSequenceActor);

	// Check if the player was created successfully
	if (LevelSequencePlayer)
	{
		// Play the level sequence
		LevelSequencePlayer->Play();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to create level sequence player"));
	}
}

void ASequenceTrigger::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ATitanCharacter>(OtherActor))
		PlaySequence();
}

// Called every frame
void ASequenceTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

