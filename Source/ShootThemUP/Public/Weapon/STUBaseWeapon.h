// Shoo Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"


class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUBaseWeapon();

    FOnClipEmptySignature OnClipEmpty;

	virtual void StartFire(); // ������� ����
    virtual void StopFire(); // ������� ����

    void ChangeClip(); // ������ ������� ������ �� �����
    bool CanReload() const; // ��������� , �����-�� ������ ������ ������ �����������

    bool FireInProgress = false; // ����������������� ��������
    bool IsFiring() const;       // ������� ������ ��������

    FWeaponUIData GetUIData() const // ������ ��� ���������
    {
        return UIData;
    }

    FAmmoData GetAmmoData() const // ������ ������� ������� (���-�� ��������, ��������� � ���������)
    {
        return CurrentAmmo;
    }

    bool TryToAddAmmo(int32 ClipsAmount); // ������ ���������� ��������� � ��������(������ ���-�� ���������)

protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent *WeaponMesh; // ��������� ���������� ����

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleSocket"; // ����� �����

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 1500.0f; // ������������ ��������� ��������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{15, 10, false}; // ����� �������� �� ��������� ������� ������

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData; // ��� ������� ������ ��� ����� ������������������� ������� ���������

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem *MuzzleFX; // �������� ������� ������� ����
	
	virtual void BeginPlay() override;

	virtual void MakeShot(); // ������� ������ ��������
    APlayerController* GetPlayerController() const; // ������� �� ��������� �������� ���������
    bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRoration) const; // ������� �� ��������� ������� � ������
    FVector GetMuzzleWorldLocation() const; // ������� ���������� ��������� ������ ������ �� �������
    virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const; // ������� ������ ����� � ����� (�������)
    void MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd) const; // ������� ����������� ����� � ���������� ���������

	void DecreaseAmmo(); // ����� ���������� ������ ��� ����� ��������
    bool IsAmmoEmpty() const; // ����� ���������� true ����� ��� ������� ��������� ������
    bool IsClipEmpty() const; // ����� ���������� true ����� ������� ������ � ��� ������
    void LogAmmo(); // ����� ���������� ��� ������� � �������

    bool IsAmmoFull() const; // ������� ��� ��������� ���������� ���� (���� ������� �����)

    UNiagaraComponent *SpawnMuzzleFX(); // ������� ������ �������

private:
    FAmmoData CurrentAmmo; // ����� �������� �� ������� ������� ������

};
