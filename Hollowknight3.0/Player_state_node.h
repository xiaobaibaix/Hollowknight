#pragma once
#include "State_node.h"
#include "Timer.h"

class PlayerAttackState :public StateNode {
public:
	PlayerAttackState();;
	~PlayerAttackState();;

	void on_enter() override;
	void on_update(float delta)override;
	void on_exit()override;

private:
	Timer timer;

private:
	void update_hit_box_position();
};

class PlayerDeadState :public StateNode {
public:
	PlayerDeadState();;
	~PlayerDeadState();;

	void on_enter() override;
	void on_update(float delta)override;
	void on_exit()override;

private:
	Timer timer;
};

class PlayerFallState :public StateNode {
public:
	PlayerFallState() {};
	~PlayerFallState() {};

	void on_enter() override;
	void on_update(float deta)override;
	void on_exit()override;


private:
	Timer timer;

private:
};

class PlayerIdleState :public StateNode {
public:
	PlayerIdleState() {};
	~PlayerIdleState() {};

	void on_enter() override;
	void on_update(float deta)override;
	void on_exit()override;
};

class PlayerJumpState :public StateNode {
public:
	PlayerJumpState() {};
	~PlayerJumpState() {};

	void on_enter() override;
	void on_update(float deta)override;
	void on_exit()override;
};

class PlayerRollState :public StateNode {
public:
	PlayerRollState();;
	~PlayerRollState();;

	void on_enter() override;
	void on_update(float delta)override;
	void on_exit()override;

private:
	Timer timer;
};

class PlayerRunState :public StateNode {
public:
	PlayerRunState() {};
	~PlayerRunState() {};

	void on_enter() override;
	void on_update(float deta)override;
	void on_exit()override;

};


