#include "ImageRenderer.h"
#include "EngineCore.h"
#include "Actor.h"

UImageRenderer::UImageRenderer()
{
}

UImageRenderer::~UImageRenderer()
{
}

void UImageRenderer::Render()
{
	HDC WindowDC = GEngine->MainWindow.GetWindowDC();
	FTransform ThisTrans = GetTransform();
	FTransform OwnerTrans = GetOwner()->GetTransform();

	// ������Ʈ�� ��ġ�� �θ𿡰Լ� ������̱� ������.
	// �θ��� ��ġ�� ������� �Ѵ�.
	ThisTrans.AddPosition(OwnerTrans.GetPosition());

	Rectangle(WindowDC, ThisTrans.iLeft(), ThisTrans.iTop(), ThisTrans.iRight(), ThisTrans.iBottom());
}