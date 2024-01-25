#pragma once
// Ű���带 �������ִ� �� OS�ϰ��̱� ������
// �Է¿� ���� �Լ��� �翬�� OS�� �츮���� �����ؾ� �մϴ�.
#include <Windows.h>
#include <map>

// AllStateClass
// ���� :
class EngineInput
{
	friend class InputInitCreator;

private:
	class EngineKey
	{
		friend EngineInput;

	public:
		bool Down = false; // ���� ����
		bool Press = false; // ��� ������
		bool Up = false; // ������ ����
		bool Free = true; // ������ ������

		float PressTime = 0.0f;

		int Key = -1; // VK_LBUTTON

		EngineKey()
		{

		}

		EngineKey(int _Key)
			: Key(_Key)
		{

		}
	};

public:
	// constrcuter destructer
	EngineInput();
	~EngineInput();

	// delete Function
	EngineInput(const EngineInput& _Other) = delete;
	EngineInput(EngineInput&& _Other) noexcept = delete;
	EngineInput& operator=(const EngineInput& _Other) = delete;
	EngineInput& operator=(EngineInput&& _Other) noexcept = delete;

	static bool IsPress(int _Key)
	{
		return AllKeys[VK_LBUTTON].Down;
	}

protected:
	//              'A'  ���°� �?
	static std::map<int, EngineKey> AllKeys;

private:
	static void InputInit();
};

