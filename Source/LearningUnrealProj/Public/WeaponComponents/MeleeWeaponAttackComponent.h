#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterComponents/MeleePlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "ThirdPersonCharacter.h"
#include "EnemyTypes/MeleeEnemy.h"
#include "MeleeWeaponAttackComponent.generated.h"


class ACharacter;
class USkeletalMeshComponent;

//UENUM(BLueprintType)
//enum class EAttackType : uint8 {
//	
//	Light		UMETA(DisplayName = "Light"),
//	Medium		UMETA(DisplayName = "Medium"),
//	Heavy		UMETA(DisplayName = "Heavy"),
//	Special		UMETA(DisplayName = "Special")
//
//};
//
//USTRUCT(BlueprintType)
//struct FAttackData {
//
//	GENERATED_BODY()
//
//	/* Animation montage for attack */
//	UPROPERTY(EditAnywhere, BluePrintReadWrite)
//	UAnimMontage* AttackMontages;
//
//	/* Damage per each attack */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<float> DamagePerAttack;
//
//	/* Stamina Used per each attack */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<float> StaminaPerAttack;
//
//	/* Attack Type */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	EAttackType Type;
//
//};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARNINGUNREALPROJ_API UMeleeWeaponAttackComponent : public UActorComponent{
	GENERATED_BODY()

//public:	
//	// Sets default values for this component's properties
//	UMeleeWeaponAttackComponent();
//
//	/* Light Attack Data */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
//	FAttackData LightAttack = { nullptr, {}, {}, EAttackType::Light };
//
//	/* Medium Attack Data */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
//	FAttackData MediumAttack = { nullptr, {}, {}, EAttackType::Medium};
//
//	/* Heavy Attack Data */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
//	FAttackData HeavyAttack = { nullptr, {}, {}, EAttackType::Heavy };
//	
//	/* Special Attack Data */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
//	FAttackData SpecialAttack = { nullptr, {}, {}, EAttackType::Special };
//
//	/* Owner of this component for faster referencing */
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parent")
//	ACharacter* OwnerCharacter;
//
//	
//protected:
//	// Called when the game starts
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
//
//	/* Handle Animation notifiers */
//	UFUNCTION()
//	void OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
};
