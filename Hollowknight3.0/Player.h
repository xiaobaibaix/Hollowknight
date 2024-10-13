#pragma once
#include "Character.h"

class Player :public Character
{
public:
	enum class AttackDir
	{
		Up,Down,Left,Right
	};
public:

	Player();

	~Player();

	void on_input(const ExMessage& msg)override;

	void on_update(float delta)override;

	void on_render()override;

	void on_hurt()override;

	void set_rolling(bool flag);

	bool get_rolling()const;

	bool can_roll()const;

	void set_attacking(bool flag);

	bool get_attacking()const;

	bool can_attck()const;

	bool can_jump()const;

	int get_move_axis()const;

	AttackDir get_attack_dir()const;

	void on_jump();

	void on_land();

	void on_roll();

	void on_attack();
private:
	Timer timer_roll_cd;//翻滚cd定时器
	bool is_rolling = false;
	bool is_roll_cd_comp = true;

	Timer timer_attack_cd;//攻击cd
	bool is_attacking = false;
	bool is_attack_cd_comp=true;
	//动作
	bool is_left_key_down = false;
	bool is_right_key_down = false;
	bool is_jump_key_down = false;
	bool is_roll_key_down = false;
	bool is_attack_key_down = false;
	//攻击
	Animation animation_slash_up;
	Animation animation_slash_down;
	Animation animation_slash_left;
	Animation animation_slash_right;
	AttackDir attack_dir = AttackDir::Right;
	Animation* current_slash_animation = nullptr;
	//起跳
	bool is_jump_vfx_visible = false;//特效可见
	Animation animation_jump_vfx;
	//落地
	bool is_land_vfx_visible = false;//特效可见
	Animation animation_land_vfx;

private:
	const float CD_ROLL = 0.75f;
	const float CD_ATTACK = 0.5f;
	const float SPEED_RUN = 300.0f;
	const float SPEED_JUMP = 780.0f;
	const float SPEED_ROLL = 800.0f;

private:
	void update_attack_dir(int x, int y);
};
