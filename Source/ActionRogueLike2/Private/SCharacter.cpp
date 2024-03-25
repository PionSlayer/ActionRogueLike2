

#include "SCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp=CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp=CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

}

void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent -> BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent -> BindAxis("MoveSideways", this, &ASCharacter::MoveSideways);

	
	PlayerInputComponent -> BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent -> BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent -> BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
}


void ASCharacter::MoveForward(float Value)
{
	FRotator Direction = GetControlRotation();
	Direction.Pitch=0.00f;
	Direction.Roll=0.00f;
	AddMovementInput(Direction.Vector(),Value);
	
}
void ASCharacter::MoveSideways(float Value)
{
	FRotator Direction = GetControlRotation();
	Direction.Pitch=0.00f;
	Direction.Roll=0.00f;
	FVector directionRight = FRotationMatrix(Direction).GetScaledAxis(EAxis::Y);
	AddMovementInput(directionRight,Value);
}

void ASCharacter::PrimaryAttack()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FTransform MyTransform = FTransform(GetControlRotation(),HandLocation);

	FActorSpawnParameters MySpawnParams;
	MySpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	GetWorld()->SpawnActor<AActor>(ProjectileClass,MyTransform,MySpawnParams);
	
}



