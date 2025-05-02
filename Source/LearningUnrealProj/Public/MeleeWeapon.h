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
class UMeleePlayerAnimInstance;
class AMeleeEnemy;

UENUM(BLueprintType)
enum class EAttackType : uint8 {

	Light		UMETA(DisplayName = "Light"),
	Heavy		UMETA(DisplayName = "Heavy"),

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


	/* Heavy Attack Data */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	FAttackData HeavyAttack = { nullptr, {}, {}, EAttackType::Heavy };

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

	/* Anim Instance of the owner if player owner */
	UMeleePlayerAnimInstance* AnimInstance; 

protected:

	AMeleeWeapon();
	// Called when the game starts
	virtual void BeginPlay() override;

	


public:

	AThirdPersonCharacter* PlayerOwner = nullptr;
	AMeleeEnemy* EnemyOwner = nullptr;

	FORCEINLINE void SetPlayerOwner(AThirdPersonCharacter* Player, UMeleePlayerAnimInstance* AnimInst) { PlayerOwner = Player; AnimInstance = AnimInst; }
	FORCEINLINE void SetEnemyOwner(AMeleeEnemy* Enemy) { EnemyOwner = Enemy; }

	/* --------------------- Attack Logic -------------------------------- */
	bool bWantsToCombo = false;
	bool bAttacking = false;
	bool bEnemyHitDuringAttack = false;

	FORCEINLINE void EnableEnemyHitDuringAttack() { bEnemyHitDuringAttack = true; }

	int CurrentAttackIndex = 0;

	int GetCurrentAttackIndex();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Handler for Anim Notify in blueprints */
	UFUNCTION(BlueprintCallable)
	void EnableHurtBox();
	
	/* Handler for Anim Notify in blueprints */
	UFUNCTION(BlueprintCallable)
	void DisableHurtBox();

	void AttackCombo(FAttackData Data);
	FAttackData CurrentAttackData;

	/* Handler for Anim Notify in blueprints */
	UFUNCTION(BlueprintCallable)
	void DisableComboWindow();

	/* Handler for Anim Notify in blueprints */
	UFUNCTION(BlueprintCallable)
	void EnableComboWindow();

	/* Handler for Anim Noitfy in blueprints*/
	UFUNCTION(BlueprintCallable)
	void ResetAttackState();

	/* Handler for Anim Notify in blueprints*/
	UFUNCTION(BlueprintCallable)
	void LastHit();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	FORCEINLINE FAttackData GetLightAttackData() const { return LightAttack; }
	FORCEINLINE FAttackData GetHeavyAttackData() const { return HeavyAttack; }
};
