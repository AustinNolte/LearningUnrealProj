#include "CharacterComponents/InventoryManager.h"



// Sets default values for this component's properties
UInventoryManager::UInventoryManager(){

	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UInventoryManager::BeginPlay(){

	Super::BeginPlay();
	
}


// Called every frame
void UInventoryManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UInventoryManager::addWeapon(AWeapon* weapon) {
	weaponInventory.Add(weapon);
}

void UInventoryManager::removeWeapon(int index) {
	if (index >= weaponInventory.Num()) {
		return;
	}

	weaponInventory[index] = nullptr;
}

AWeapon* UInventoryManager::getWeaponAtIndex(int index){

	if (index > weaponInventory.Num()) {
		return nullptr; 
	}

	if (weaponInventory[index] == nullptr) {
		return nullptr;
	}

	return weaponInventory[index];
}
