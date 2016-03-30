#include "crowmire.h"
#include "DoorBase.h"


ADoorBase::ADoorBase()
{
	//MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("StaticMesh'/Game/Assets/Interactive/SM_ovet/SM_roomdoor.SM_roomdoor'"));
	MeshComponent->SetStaticMesh(DefaultMesh.Object);

	PrimaryActorTick.bCanEverTick = true;
}


void ADoorBase::BeginPlay()
{
	bIsOpen = false;
	bIsOpening = false;
	bIsClosing = false;
}


void ADoorBase::Tick(float DeltaSeconds)
{
	float Epsilon = 0.5f;
	if (bIsOpening || bIsClosing)
	{	
		float MeshAbsoluteYaw = fabs(MeshComponent->RelativeRotation.Yaw);
		MeshComponent->AddRelativeRotation(Rotator * DeltaSeconds);
		
		if (bIsOpening && MeshAbsoluteYaw >= fabs(Rotator.Yaw))
		{
			bIsOpen = true;
			bIsOpening = false;
		}
		if (bIsClosing && MeshAbsoluteYaw <= Epsilon)
		{
			bIsOpen = false;
			bIsClosing = false;
			MeshComponent->SetRelativeRotation(FRotator::ZeroRotator);
		}
	}
}


void ADoorBase::Open()
{
	Rotator = FRotator(0, GetYaw(), 0);
	bIsOpening = true;
}


void ADoorBase::Close()
{
	Rotator = FRotator(0, GetYaw() * -1, 0);
	bIsClosing = true;
}

float ADoorBase::GetYaw()
{
	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	FVector m_location = MeshComponent->GetComponentLocation();
	FVector c_location = myCharacter->GetActorLocation();

	FRotator m_rotator = MeshComponent->GetComponentRotation();

	FVector unrotated = m_rotator.UnrotateVector(c_location - m_location);
	return (unrotated.Y < 0) ? -90 : 90;
}