#pragma once
#include "State_node.h"
#include "Timer.h"
//Ãé×¼
class EnemyAimState :public StateNode
{
public:
	EnemyAimState();
	~EnemyAimState();

	void on_enter()override;
	void on_update(float delta)override;

private:
	Timer timer;
};
//ÔÚ¿ÕÖÐ³å´Ì
class EnemyDashInAirState :public StateNode
{
public:
	EnemyDashInAirState();
	~EnemyDashInAirState();

	void on_enter()override;
	void on_update(float delta)override;
	void on_exit()override;

private:
	const float SPEED_DASH = 1500.f;
};
//ÔÚµØ°å³å´Ì
class EnemyDashOnFloorState :public StateNode
{
public:
	EnemyDashOnFloorState();
	~EnemyDashOnFloorState();

	void on_enter()override;
	void on_update(float delta)override;
	void on_exit()override;

private:

	const float SPEED_DASH = 1000.f;
	
private:
	Timer timer;
};
//ËÀÍö
class EnemyDeadState :public StateNode
{
public:
	EnemyDeadState()=default;
	~EnemyDeadState()= default;

	void on_enter()override;

};
//ÂäÏÂ
class EnemyFallState :public StateNode
{
public:
	EnemyFallState();
	~EnemyFallState();

	void on_enter()override;
	void on_update(float delta)override;

};
//ÏÐÖÃ
class EnemyIdleState :public StateNode
{
public:
	EnemyIdleState();
	~EnemyIdleState();

	void on_enter()override;
	void on_update(float delta)override;
	void on_exit()override;

private:
	Timer timer;
};
//ÌøÔ¾
class EnemyJumpState :public StateNode
{
public:
	EnemyJumpState();
	~EnemyJumpState();

	void on_enter()override;
	void on_update(float delta)override;

private:
	const float SPEED_JUMP = 1000.f;

};
//±¼ÅÜ
class EnemyRunState :public StateNode
{
public:
	EnemyRunState();
	~EnemyRunState();

	void on_enter()override;
	void on_update(float delta)override;
	void on_exit()override;

private:
	const float MIN_DIS = 350.f;
	const float SPEED_RUN = 500.f;
};

//ÏÂ¶×
class EnemySquatState :public StateNode
{
public:
	EnemySquatState();
	~EnemySquatState();

	void on_enter()override;
	void on_update(float delta)override;

private:
	Timer timer;
};
//´ÌÇò
class EnemyThrowBarbState :public StateNode
{
public:
	EnemyThrowBarbState();
	~EnemyThrowBarbState();

	void on_enter()override;
	void on_update(float delta)override;

private:
	Timer timer;
};

//ÏßÈ¦
class EnemyThrowSilkState :public StateNode
{
public:
	EnemyThrowSilkState();
	~EnemyThrowSilkState();

	void on_enter()override;
	void on_update(float delta)override;

private:
	Timer timer;
};

//·ÉïÚ
class EnemyThrowSwordState :public StateNode
{
public:
	EnemyThrowSwordState();
	~EnemyThrowSwordState();

	void on_enter()override;
	void on_update(float delta)override;

private:
	Timer timer_throw;
	Timer timer_switch;
};
