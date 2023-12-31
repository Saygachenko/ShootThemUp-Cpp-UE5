// Shoo Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUCoreTypes.h"
#include "STUGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FString TestString = "Hello Game!"; // ���� ��� �����

	FLevelData GetStartupLevel() const // �������� ��� ��������� ������
	{
		return StartupLevel;
	}

	void SetStartupLevel(const FLevelData& Data) // ������ ��������� ������
	{
		StartupLevel = Data;
	}

	TArray<FLevelData> GetLevelsData() const // ������ ������ �� �������
	{
		return LevelsData;
	}

	FName GetMenuLevelName() const // �������� ��� ������ ����
	{
		return MenuLevelName;
	}

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MenuLevelName = NAME_None; // ���� ������ �������� ������ (���� ��� none, ������� ���� �� ������)

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ToolTip = "Level names must be unique!")) // ToolTip - ������ ��������� � ������
	TArray<FLevelData> LevelsData; // ������ �������

private:
	FLevelData StartupLevel; // ��������� �������
	
};
