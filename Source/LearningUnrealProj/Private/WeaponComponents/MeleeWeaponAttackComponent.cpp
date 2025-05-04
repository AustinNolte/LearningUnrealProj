//#include "WeaponComponents/MeleeWeaponAttackComponent.h"
//
//// Sets default values for this component's properties
//UMeleeWeaponAttackComponent::UMeleeWeaponAttackComponent(){
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = true;
//
//}
//
//
//// Called when the game starts
//void UMeleeWeaponAttackComponent::BeginPlay(){
//	Super::BeginPlay();
//
//	OwnerCharacter = Cast<ACharacter>(GetOwner());
//	if (OwnerCharacter){
//		USkeletalMeshComponent* OwnerMesh = OwnerCharacter->GetMesh();
//		if (OwnerMesh) {
//			UAnimInstance* AnimInstance = OwnerMesh->GetAnimInstance();
//			if (AnimInstance) {
//				AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UMeleeWeaponAttackComponent::OnNotifyBegin);
//			}
//		}
//	}
//}
//
//
//// Called every frame
//void UMeleeWeaponAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//
//}
//
//void UMeleeWeaponAttackComponent::OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload){
//
//	if (NotifyName == "Notify_HurtBox_Enabled") {
//		if (AThirdPersonCharacter* Player = Cast<AThirdPersonCharacter>(OwnerCharacter)) {
//			Player->EnableHurtBoxCollision();
//		}
//		else if (AMeleeEnemy* Enemy = Cast<AMeleeEnemy>(OwnerCharacter)) {
//			Enemy->EnableHurtBoxCollision();
//		}
//	}
//	else if (NotifyName == "Notify_HurtBox_Disabled") {
//		if (AThirdPersonCharacter* Player = Cast<AThirdPersonCharacter>(OwnerCharacter)) {
//			Player->DisableHurtBoxCollision();
//		}
//		else if(AMeleeEnemy* Enemy = Cast<AMeleeEnemy>(OwnerCharacter)){
//			Enemy->DisableHurtBoxCollision();
//		}
//	}
//}
//
//
