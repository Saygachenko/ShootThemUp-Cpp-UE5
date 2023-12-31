// Shoo Them Up Game


#include "Pickups/STUBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

// Sets default values
ASTUBasePickup::ASTUBasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f); // ������ �����
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // ���������� �������������� �� ����� � ���� ��������
    CollisionComponent->SetCollisionResponseToChannels(ECollisionResponse::ECR_Overlap); // ������� ������� � �������
    SetRootComponent(CollisionComponent); // ������� ��� ��������

}

// Called when the game starts or when spawned
void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();
    
    check(CollisionComponent); // �������� ������� ������

    GenerateRotationYaw(); // �������� ���������� ��� ������ ����
	
}

// Called every frame
void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f)); // ���� �������� ����������� ������ ����� � ������� ������� AddActorLocalRotation() - ��� � ���� ������� ����

    for (const auto OverlapPawn : OverlappingPawns) // ����������� �� ������� OverlappingPawns
    {
        if (GivePickupTo(OverlapPawn)) // ���������, �����-�� �� ������ ����-������ ����� �� ������ � ������� (�� ��� ���������� � ������ ������ �������� ������)
        {
            PickupWasTaken(); // ��������� �����
            break; // ����� �� �����
        }
    }
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor *OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor); // ��������� �� ����
    if (GivePickupTo(Pawn)) // ���� ����� ������� �������
    {
        PickupWasTaken(); // �������� ������� ������ ������
    }
    else if (Pawn) // ���� ����� ��������� �������
    {
        OverlappingPawns.Add(Pawn); // ��������� ��������� �� ����� � ������
    }
}

void ASTUBasePickup::NotifyActorEndOverlap(AActor *OtherActor)
{
    Super::NotifyActorEndOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor); // ��������� �� ����
    OverlappingPawns.Remove(Pawn); // ������� ��������� �� ����� �� �������
}

bool ASTUBasePickup::GivePickupTo(APawn *PlayerPawn)
{
    return false; // ����� �������� ������ ����� ����������
}

void ASTUBasePickup::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore); // ��������� ��� �������� (���������� ����������������� � ���������� �����)
    if (GetRootComponent()) // �������� �� 0
    {
        GetRootComponent()->SetVisibility(false, true); // ������ ����� ���������. ������� SetVisibility(������ ����������, ����� �������� Visibility ��������� �� ���� �������� �����������) ��� ����� �������� ����������
    }

    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickup::Respawn, RespawnTime);
}

void ASTUBasePickup::Respawn()
{
    GenerateRotationYaw(); // ��� ���� ����� �������� �� ����� �������� ������
    if (GetRootComponent()) // �������� �� 0
    {
        GetRootComponent()->SetVisibility(true, true); // ������ ����� �������
    }
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap); // ���������� ��������
}

void ASTUBasePickup::GenerateRotationYaw()
{
    const auto Direction = FMath::RandBool() ? 1.0f : -1.0f; // ��������� �������� �������� RandBool()
    RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction; // ������� ��������� ��������� ����� RandRange(������ �������, ����� �������)
}

bool ASTUBasePickup::CouldBeTaken() const  // ������� ������ ������ ��� EQS
{
    return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle); // ���� ������ RespawnTimerHandle �� �������� �� ����� ����� �����.
}

