// Shoo Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	void SetTeaimID(int32 ID)
	{
		TeamID = ID;
	}
	int32 GetTeaimID() const
	{
		return TeamID;
	}

	void SetTeamColor(const FLinearColor& Color)
	{
		TeamColor = Color;
	}
	FLinearColor GetTeamColor() const
	{
		return TeamColor;
	}


private:
	int32 TeamID; // �� �������
	FLinearColor TeamColor; // ���� �������
};
