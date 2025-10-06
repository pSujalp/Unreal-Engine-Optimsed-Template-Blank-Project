// Fill out your copyright notice in the Description page of Project Settings.


#include "Multi_Threading.h"
#include "Async/Async.h"







// Sets default values
AMulti_Threading::AMulti_Threading()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMulti_Threading::BeginPlay()
{
	Super::BeginPlay();
    
    DoBackgroundWork();

    

}

// Called every frame
void AMulti_Threading::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMulti_Threading::DoBackgroundWork(){
    Async(EAsyncExecution::Thread, []()
    {
        int32 ij = 0;
        for(size_t i=0 ; i< 100000000000000;++i)
        {
            for(size_t j=0 ; j< 100000000000000;++j)
            {
                ij++;

                if(ij > INT32_MAX)
                {
                    ij = 0;
                }
            }
            
            
        }
        // Runs on a background thread// Simulate work
        UE_LOG(LogTemp, Warning, TEXT("Background work finished! %d"),ij);
    });
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("100000000000000 iterations completed"));

    UE_LOG(LogTemp, Warning, TEXT("Main thread continues..."));
}
