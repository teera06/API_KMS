#pragma once

// 커비와 몬스터 개념 공유
enum class AMode
{
	Base,
	Fire,
	Mike,
	Sword,
	Hammer,
};

enum class ActorState
{
	None,
	Idle,
	Walk,
	Run,
	Jump,
	Absorption,
	CameraFreeMove,
	FreeMove,

};

enum class EActorDir
{
	Left,
	Right,
};

enum RenderOrder
{
	TitleMap,
	Stage1_Map,
	Monster,
	Base,
	Fire,
	kirby,
};