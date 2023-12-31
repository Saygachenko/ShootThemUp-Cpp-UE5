// Shoo Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUHealthComponent.generated.h"

class UCameraShakeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUHealthComponent();

	FOnDeathSignature OnDeath;
    FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const // ������� ���������� ���� ��� �������� ��� ���
    {
        return FMath::IsNearlyZero(Health); // ������� �������� �� 0 IsNearlyZero()
    }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const // ���������� ����� ���������� ������� ���������� ������
	{
        return Health / MaxHealth;
	}

	float GetHealth() const // ������ ����������� ������ ��
	{
        return Health;
	}

	bool TryToAddHealth(float HealthAmount); // ������� ������ �������� ������� �� ����� ��� ������ ������ ����������
    bool IsHealthFull() const; // ��������������� ������� ���� ��

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (clampMin = "0.0", clampMax = "1000.0"))
    float MaxHealth = 100.0f; // ������������ �������� ��

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    bool AutoHeal = true; // ��������� ��������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal")) // meta = (EditCondition = "AutoHeal") - ���� ���� ��������� ������� ����������, �� � ����� �������� �������������� �����������
    float HealUpdateTime = 1.0f; // ������� � ������� ����� ����������� ��

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealDelay = 3.0f; // �������� ����� ������� ������� ����������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealModifier = 5.0f; // ���-�� ����������� ��

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShake; // ��� ����� ��������� ���� ������ ������

	virtual void BeginPlay() override;
	
private:
    float Health = 0.0f; // ���� �������� �� ��������� �� ���������
    FTimerHandle HealTimerHandle; // ��� ������ ��� ������
	
	UFUNCTION() // OnTakeAnyDamage(����� �������� ��� ������ �����, ����, ��� damage, ���������� ������� ������������ �� �����, ����� ������� ����� �����)
	void OnTakeAnyDamage(AActor *DamagedActor, float Damage, const class UDamageType *DamageType, class AController *InstigatedBy, AActor *DamageCauser);

	void HealUpdate(); // ������� ���������� ��
    void SetHealth(float NewHealth); // ������� ��

	void PlayCameraShake(); // ���� ������� ������������ ������ ������

	void Killed(AController* KillerController); // ��������������� ������� �������
};
