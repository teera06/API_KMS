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

	// 컴포넌트의 위치는 부모에게서 상대적이기 때문에.
	// 부모의 위치를 더해줘야 한다.
	ThisTrans.AddPosition(OwnerTrans.GetPosition());

	Rectangle(WindowDC, ThisTrans.iLeft(), ThisTrans.iTop(), ThisTrans.iRight(), ThisTrans.iBottom());
}