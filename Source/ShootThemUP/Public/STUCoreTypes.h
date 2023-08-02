#pragma once

#include "STUCoreTypes.generated.h"

class ASTUBaseWeapon;
class UNiagaraSystem;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, ASTUBaseWeapon*); // ������� ��������� � ��� ��� � ��� ����������� ������� + ��������� �� ������� ������
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature); // ������� ������� ��������� ������ ��������� � ������
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, float); // ������� ��� �������� ��������� �� � ���������

USTRUCT(BLueprintType)
struct FAmmoData // ��������� ����������
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets = 0; // ���-�� �������� � ��������

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
    int32 Clips = 0; // ���-�� ���������

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool Infinite = true; // ���������� ������� ������� ������� ������ ��� ���
};

USTRUCT(BlueprintType)
struct FWeaponData // � ��������� ������ ������ � �������� ����������� ������
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASTUBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    UAnimMontage *ReloadAnimMontage;
};

USTRUCT(BlueprintType) 
struct FWeaponUIData // ��������� ����������� ������� ������
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D *MainIcon; // �������� ������

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D *CrossHairIcon; // �������� �������
    
};

USTRUCT(BlueprintType)
struct FDecalData // ��������� ��� ��������� Decal
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UMaterialInterface *Material; // �������� Decal

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FVector Size = FVector(10.0f); // ������ (� ����� ����������, ������������� ��� ��������� ������� �� 10 ����)

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    float LifeTime = 5.0f; // ����� ����� (������� �� ����� ��������� �� �����)

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    float FadeOutTime = 0.7f; // ����� �������� (�� ������ ���������� ������� ����� ������������)
};

USTRUCT(BlueprintType)
struct FImpactData // ��������� ���������� ������� � ������
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem *NiagaraEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FDecalData DecalData;
};

USTRUCT(BlueprintType)
struct FGameData // ��������� ������ ������ � ������� ��������� ��� ��������� ����
{
    GENERATED_USTRUCT_BODY()
    // ���-�� �������
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"))
    int32 PlayersNum = 2;
    // ���-�� �������
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
    int32 RoundsNum = 4;
    // ����������������� ������
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "300"))
    int32 RoundTime = 10;
    // ��������� ���� �������
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FLinearColor DefaultTeamColor = FLinearColor::Red;
    // ������ ������ �� �������� �� ����� �������� ���� ��� ������� ������������ �� �� �������
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TArray<FLinearColor> TeamColors;
    // ����� ��������
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "20"))
    int32 RespawnTime = 5;
};