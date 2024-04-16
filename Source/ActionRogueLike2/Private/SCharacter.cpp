

#include "SCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"


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

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("AttributeComponent");

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
	PlayerInputComponent -> BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	
	PlayerInputComponent -> BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent -> BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent -> BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent -> BindAction("PrimaryInteraction", IE_Pressed, this, &ASCharacter::PrimaryInteract);
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
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack,this,&ASCharacter::PrimaryAttack_TimeElapsed,0.2f);
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	FVector Start = CameraComp->GetComponentLocation();
	FVector End = Start +(GetControlRotation().Vector()*10000);
	TArray<FHitResult> Hits;
	FCollisionObjectQueryParams Params;
	Params.AddObjectTypesToQuery(ECC_WorldDynamic);
	Params.AddObjectTypesToQuery(ECC_WorldStatic);
	Params.AddObjectTypesToQuery(ECC_Pawn);
	Params.AddObjectTypesToQuery(ECC_PhysicsBody);
	GetWorld()->LineTraceMultiByObjectType(Hits,Start,End,Params);
	AActor* hitActor;
	bool foundHit = false;
	FVector hitLocation;
	for(FHitResult hit: Hits)
	{
		hitActor = hit.GetActor();
		if(hitActor){if(hitActor != GetInstigator()){foundHit=true;}else{hitActor=nullptr;}}else{foundHit=true;}
		if(foundHit){hitLocation = hit.Location;break;}
	}
	if(!foundHit){hitLocation = End;}

	
	DrawDebugSphere(GetWorld(),hitLocation,5,32,FColor::Red,false,2,0,2);
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");


	FTransform MyTransform = FTransform(UKismetMathLibrary::FindLookAtRotation(HandLocation,hitLocation),HandLocation);
	FActorSpawnParameters MySpawnParams;
	MySpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	MySpawnParams.Instigator = this;
	GetWorld()->SpawnActor<AActor>(ProjectileClass,MyTransform,MySpawnParams);
}

void ASCharacter::PrimaryInteract()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Interaction Called:3"));
	InteractionComp->PrimaryInteraction();
}



