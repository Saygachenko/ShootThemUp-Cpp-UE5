// Shoo Them Up Game


#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h" // ����� �������� �������
#include "STUGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameHUD, All, All);

void ASTUGameHUD::DrawHUD()
{
    Super::DrawHUD();

    //DrawCrossHair();
}

void ASTUGameHUD::BeginPlay()
{
    Super::BeginPlay();

    GameWidgets.Add(ESTUMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHudWidgetClass)); // ��������� � ��� ��������� ��������� ���� "InProgress" � ��� ������
    GameWidgets.Add(ESTUMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass)); // ��������� � ��� ��������� ��������� ���� "Pause" � ��� ������
    GameWidgets.Add(ESTUMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass)); // ��������� � ��� ��������� ��������� ���� "GameOver" � ��� ������

    for (auto GameWidgetPair : GameWidgets) // ����������� �� ������ ����������
    {
        const auto GameWidget = GameWidgetPair.Value; // �������� ��� ���� �� ����������
        if (!GameWidget) // ���� ������� ����
        {
            continue; // ���������� �������
        }

        GameWidget->AddToViewport(); // ��������� ������ �� �����
        GameWidget->SetVisibility(ESlateVisibility::Hidden); // ������ ������ ���������
    }

    if (GetWorld()) // ���� ��������� �� ��� ����������
    {
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()); // �������� ��������� �� �������
        if (GameMode) // ���� ��������� ����������
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASTUGameHUD::OnMatchStateChanged); // ������������� �� ��� ������� ��������� ����
        }
    }
}

void ASTUGameHUD::DrawCrossHair()
{
    // TInterval(����� ������ ������) - ��� ���������� ������ ������
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f); // ��� ��������� ������� ������ ������������ �������������� ������ Canvas

    const float HalfLineSize = 10.0f; // ������ �������� �����
    const float LineThickness = 2.0f; // ������� �����
    const FLinearColor LineColor = FLinearColor::Green; // ���� ������� (�����)

    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness); // DrawLine(��������� ����� �� ������ X, Y, �������� ����� �� ������ X, Y, ���� �����, ������� �����) ������� ����, ��������� �������� ����� �� ������
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}

void ASTUGameHUD::OnMatchStateChanged(ESTUMatchState State)
{
    if (CurrentWidget) // ��������� ��� ������� ������ ����������
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden); // ������ ��� ���������
    }
    
    if (GameWidgets.Contains(State)) // ��������� ��� � ����� ���������� ���� ���� � ����� ����������
    {
        CurrentWidget = GameWidgets[State]; // ������������� ������� ��������� � ��� ������
    }

    if (CurrentWidget) // ���� ������ ����������
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible); // ������ ��� �������
    }

    UE_LOG(LogSTUGameHUD, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State)); // ������� � ���� ���������� �� ���������� ��������� ���� GetValueAsString - ����������� �������� enum � ������
}
