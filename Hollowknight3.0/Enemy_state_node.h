#pragma once
#include "State_node.h"
#include "Timer.h"
//��׼
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
//�ڿ��г��
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
//�ڵذ���
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
//����
class EnemyDeadState :public StateNode
{
public:
	EnemyDeadState()=default;
	~EnemyDeadState()= default;

	void on_enter()override;

};
//����
class EnemyFallState :public StateNode
{
public:
	EnemyFallState();
	~EnemyFallState();

	void on_enter()override;
	void on_update(float delta)override;

};
//����
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
//��Ծ
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
//����
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

//�¶�
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
//����
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

//��Ȧ
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

//����
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
