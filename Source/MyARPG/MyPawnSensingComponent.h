// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"
#include "MyPawnSensingComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))//需要有meta才能在蓝图中找到该类
class MYARPG_API UMyPawnSensingComponent : public UPawnSensingComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMyPawnSensingComponent();

	//可以在蓝图中直接调用
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="AI|Components|PawnSensing")
	bool HasLineOfSightTo_BP(const AActor* Other);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
