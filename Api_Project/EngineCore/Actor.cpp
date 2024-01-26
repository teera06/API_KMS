#include "Actor.h"
#include "ImageRenderer.h"

AActor::AActor()
{
}

AActor::~AActor()
{
	for (UImageRenderer* ImageRenderer : Renderers)
	{
		if (nullptr == ImageRenderer)
		{
			MsgBoxAssert("�̹��� �������� nullptr�� ��Ȳ�� �־����ϴ�");
		}

		delete ImageRenderer;
		ImageRenderer = nullptr;
	}

	Renderers.clear();
}

UImageRenderer* AActor::CreateImageRenderer()
{
	UImageRenderer* NewRenderer = new UImageRenderer();
	UActorComponent* ActorCom = NewRenderer;
	ActorCom->SetOwner(this);
	Renderers.push_back(NewRenderer);
	return NewRenderer;
}
