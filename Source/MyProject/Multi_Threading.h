// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Multi_Threading.generated.h"






UCLASS()
class MYPROJECT_API AMulti_Threading : public AActor
{
	GENERATED_BODY()
    
private:
    

public:	
	// Sets default values for this actor's properties
	AMulti_Threading();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    


    void DoBackgroundWork();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
