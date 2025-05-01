#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnemyTypes/MeleeEnemy.h"
#include "GameFramework/Character.h"
#include "BasicEnemy.h"
#include "MeleeWeapon.generated.h"

class ACharacter;
class AThirdPersonCharacter;
class AMeleeEnemy;

UENUM(BLueprintType)
enum class EAttackType : uint8 {

	Light		UMETA(DisplayName = "Light"),
	Medium		UMETA(DisplayName = "Medium"),
	Heavy		UMETA(DisplayName = "Heavy"),
	Special		UMETA(DisplayName = "Special")

};

USTRUCT(BlueprintType)
struct FAttackData {

	GENERATED_BODY()

	/* Animation montage for attack */
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	UAnimMontage* AttackMontages;

	/* Damage per each attack */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> DamagePerAttack;

	/* Stamina Used per each attack */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> StaminaPerAttack;

	/* Attack Type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttackType Type;

};

UCLASS()
class LEARNINGUNREALPROJ_API AMeleeWeapon : public AActor {

	GENERATED_BODY()

public:

	/* Light Attack Data */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	FAttackData LightAttack = { nullptr, {}, {}, EAttackType::Light };

	/* Medium Attack Data */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	FAttackData MediumAttack = { nullptr, {}, {}, EAttackType::Medium };

	/* Heavy Attack Data */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	FAttackData HeavyAttack = { nullptr, {}, {}, EAttackType::Heavy };

	/* Special Attack Data */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	FAttackData SpecialAttack = { nullptr, {}, {}, EAttackType::Special };

	/* Owner of this component for faster referencing */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parent")
	ACharacter* OwnerCharacter;

	/* Mesh of weapon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* Mesh;

	/* Hurt Box of the weapon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HurtBox")
	UBoxComponent* HurtBox;

	/* Bool to control if this is a enemy weapon or not */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bIsEnemyWeapon = false;

protected:

	AMeleeWeapon();
	// Called when the game starts
	virtual void BeginPlay() override;

	


public:

	AThirdPersonCharacter* PlayerOwner = nullptr;
	AMeleeEnemy* EnemyOwner = nullptr;

	FORCEINLINE void SetPlayerOwner(AThirdPersonCharacter* Player) { PlayerOwner = Player; }
	FORCEINLINE void SetEnemyOwner(AMeleeEnemy* Enemy) { EnemyOwner = Enemy; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* For anim notifies to be called from OwnerCharacter */
	void EnableHurtBox();
	
	/* For anim notifies to be called from OwnerCharacter */
	void DisableHurtBox();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	FORCEINLINE FAttackData GetLightAttackData() const { return LightAttack; }
	FORCEINLINE FAttackData GetMediumAttackData() const { return MediumAttack; }
	FORCEINLINE FAttackData GetHeavyAttackData() const { return HeavyAttack; }
	FORCEINLINE FAttackData GetSpecialAttackData() const { return SpecialAttack; }
};
