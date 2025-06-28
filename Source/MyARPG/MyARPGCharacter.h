// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "MyARPGCharacter.generated.h"

	//此处class与struct为前向声明，相当于告诉下文此处有该变量。不需要在头文件中包含该变量的完整定义
	class USpringArmComponent;//U表明该类继承自Uobject
	class UCameraComponent;
	class UInputMappingContext;
	class UInputAction;
	struct FInputActionValue;//F表明是一个结构体

	DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

	UCLASS(config=Game)
	class AMyARPGCharacter : public ACharacter
	{
		GENERATED_BODY()

		//UPROPERTY是反射系统的宏，将C++类成员暴露给UE系统
		//1. 编辑器的属性面板中 VisibleAnywhere或EditAnywhere
		//2. 该变量在蓝图中 BlueprintReadOnly或BlueprintReadWrite
		//3. 该变量在"Details"面板中属于哪个条目下
		//4. 该变量不论是private还是protected，都可以在蓝图中访问
		
		/** Camera boom positioning the camera behind the character */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* CameraBoom;

		/** Follow camera */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FollowCamera;
	
		/** MappingContext */
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputMappingContext* DefaultMappingContext;

		/** Jump Input Action */
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* JumpAction;

		/** Move Input Action */
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* MoveAction;

		/** Look Input Action */
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
		UInputAction* LookAction;

	public:
		AMyARPGCharacter();
	

	protected:

		/**BlueprintImplementableEvent表示C++只负责声明，具体实现存在于蓝图中，类似于ReceiveBeginPlay，在蓝图中显示为BeginPlay*/
		UFUNCTION(BlueprintImplementableEvent, Category = "Character")
		void OnDamaged(float DamageAmount, struct FHitResult const& HitResult, AMyARPGCharacter* InstigatorCharacter, AActor* DamageCauser);

		UFUNCTION(BlueprintCallable,Category = "Character")
		virtual void HandleDamage(float DamageAmount, struct FHitResult const& HitResult, AMyARPGCharacter* InstigatorCharacter, AActor* DamageCauser)
		{
			OnDamaged(DamageAmount, HitResult, InstigatorCharacter, DamageCauser);
		}
		
		/** Called for movement input */
		void Move(const FInputActionValue& Value);

		/** Called for looking input */
		void Look(const FInputActionValue& Value);
			

	protected:

		virtual void NotifyControllerChanged() override;

		//UInputComponent将键盘鼠标手柄的输入映射为游戏中的动作或事件
		//此处的class可写可不写，写是因为既保证代码的可读性，也可能避免类名与变量名潜在的二义性问题
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	public:
		//FORCEINLINE是UE的宏，作用类似于inline内联函数
		/** Returns CameraBoom subobject **/
		FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
		/** Returns FollowCamera subobject **/
		FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	};
	

