// Shoo Them Up Game


#include "UI/STUPlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USTUPlayerStatRowWidget::SetPlayerName(const FText& Text)
{
	if (!PlayerNameTextBlock) // ���� ��������� �� ��� �� ����������
	{
		return; // ����� �� �������
	}
	PlayerNameTextBlock->SetText(Text); // ������������� ���
}

void USTUPlayerStatRowWidget::SetKills(const FText& Text)
{
	if (!KillsTextBlock) // ���� ��������� �� ���-�� ������� �� ����������
	{
		return; // ����� �� �������
	}
	KillsTextBlock->SetText(Text); // ������������� ����
}

void USTUPlayerStatRowWidget::SetDeaths(const FText& Text)
{
	if (!DeathsTextBlock) // ���� ��������� �� ���-�� ������� �� ����������
	{
		return; // ����� �� �������
	}
	DeathsTextBlock->SetText(Text); // ������������� ����
}

void USTUPlayerStatRowWidget::SetTeam(const FText& Text)
{
	if (!TeamTextBlock) // ���� ��������� �� ����� ������� �� ����������
	{
		return; // ����� �� �������
	}
	TeamTextBlock->SetText(Text); // ������������� ����� �������
}

void USTUPlayerStatRowWidget::SetPlayerIndicatorVisibillity(bool Visible)
{
	if (!PlayerIndicatorImage) // ���� ��������� �� ��������� ��������� ��������� �� ����������
	{
		return; // ����� �� �������
	}
	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden); // ������������� ��������� ���������� �� �������� Visible ���� �� true
}

void USTUPlayerStatRowWidget::SetTeamColor(const FLinearColor& TeamColor)
{
	if (!TeamImage) // ���� ��������� �� �������� ����� ������� �� ����������
	{
		return; // ����� �� �������
	}

	TeamImage->SetColorAndOpacity(TeamColor); // ����� �������� ������� �����
}
