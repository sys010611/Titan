// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "Hitbox.generated.h"

class UBoxComponent;

UCLASS()
class TITAN_API AHitbox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitbox();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);

	TArray<AActor*> IgnoreActors;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnSuccessfulHit(AActor* HitActor, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* BoxTraceStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* BoxTraceEnd;

private:
	void BoxTrace(FHitResult& BoxHit);

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	float Damage = 15.f;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	UParticleSystem* HitParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* WeaponCollisionBox;


public:
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }

	FORCEINLINE void SetHitParticle(UParticleSystem* Particle) { HitParticle = Particle; }
};
