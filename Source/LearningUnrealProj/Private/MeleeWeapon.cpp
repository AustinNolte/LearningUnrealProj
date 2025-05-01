#include "MeleeWeapon.h"
#include "ThirdPersonCharacter.h"


// Sets default values
AMeleeWeapon::AMeleeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	HurtBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HurtBox"));
	HurtBox->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void AMeleeWeapon::BeginPlay(){

	Super::BeginPlay();

	// Collision for weapon should only be set when swinging
	HurtBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HurtBox->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::OnOverlapBegin);

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	}

// Called every frame
void AMeleeWeapon::Tick(float DeltaTime){

	Super::Tick(DeltaTime);

}

void AMeleeWeapon::EnableHurtBox() {
	UE_LOG(LogTemp, Warning, TEXT("Here in EnableHurtBox"));
	HurtBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMeleeWeapon::DisableHurtBox() {
	UE_LOG(LogTemp, Warning, TEXT("Here in DisableHurtBox"));
	HurtBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMeleeWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (PlayerOwner) {
		if (ABasicEnemy* EnemyHit = Cast<ABasicEnemy>(OtherActor)) {

			//get damage value only if an enemy has not been hit during this attack

			if (!(PlayerOwner->bEnemyHitDuringAttack)) {
				PlayerOwner->EnableEnemyHitDuringAttack();
				//UE_LOG(LogTemp, Warning, TEXT("CurrentAttackIndex: %d"), PlayerOwner->GetCurrentAttackIndex());
				float Damage = LightAttack.DamagePerAttack[PlayerOwner->GetCurrentAttackIndex()];
				//UE_LOG(LogTemp, Error, TEXT("Damage: %f"), Damage);
				UGameplayStatics::ApplyDamage(EnemyHit, Damage, GetInstigatorController(), this, UDamageType::StaticClass());
			}

		}
	}
}