// Shoo Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
	
public:
    ASTURifleWeapon();

    virtual void StartFire() override; // ������� ����
    virtual void StopFire() override;  // ������� ����


protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TimeBetweenShots = 0.1f; // ������� ������������ ������� ��������

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float BulletSpread = 1.5f; // ������� ��������

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmout = 10.0f; // ���� �� ���������

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    USTUWeaponFXComponent *WeaponFXComponent; // ��� ��������� �������

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem *TraceFX; // ������ ��������� �� ����� ������

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget"; // �������� �������� ����������, ��� ������� ����� ������ �������

    virtual void BeginPlay() override;

    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const override; // ������� ������ ����� � ����� (�������)

private:

    FTimerHandle ShotTimerHandle; // ������ ��� �������� �� ��������

    UPROPERTY()
    UNiagaraComponent *MuzzleFXComponent; // ������ ��������� �� ������ ���������

    void MakeDamage(const FHitResult &HitResult); // ������� ��������� ����� �� �����

    void InitMuzzleFX(); // ����� ����� ������� ���� ��������� 0 (������� ����)
    void SetMuzzleFXVisibility(bool Visible); // ������� ��������� ����� ������ �������

    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd); // ������� �������� �� ����� ������� ������

    AController* GetController() const; // ������� ��������� �����������
};
