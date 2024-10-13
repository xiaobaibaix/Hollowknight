#pragma once

#include "State_machine.h"
#include "Animation.h"
#include "Collision_box.h"

class Character
{
public:
	Character();

	~Character();

	void decrease_hp();

	int get_hp();

	void set_position(const Vector2D& vec);

	const Vector2D& get_position() const;

	void set_velocity(const Vector2D& vec);

	const Vector2D& get_velocity() const;

	Vector2D get_logic_center()const;

	void set_gravity_enable(bool flag);

	CollisionBox* get_hit_box();

	CollisionBox* get_hurt_box();

	bool is_on_floor()const;

	float get_floor_y()const;
	//使无敌
	void make_invulnerable();

	virtual void on_input(const ExMessage& msg);
	virtual void on_update(float delta);
	virtual void on_render();

	virtual void on_hurt();

	void switch_state(const std::string& id);
	void set_animation(const std::string& id);
protected:
	struct AnimationGroup
	{
		Animation left;
		Animation right;
	};
protected:
	const float FLOOR_Y = 620;//地板的高度
	const float GRAVITY = 980*2;//重力
protected:
	int hp = 10;//血量

	Vector2D position;//位置
	Vector2D velocity;//速度

	float logic_height = 0;//角色的逻辑高度

	bool is_facing_left = true;//角色是否面朝左

	StateMachine state_machine;//角色状态机

	bool enable_gravity = true;//是否启用重力
	bool is_invulnerable = false;//角色是否无敌

	Timer timer_invulnerable_blink;//无敌闪烁状态定时器
	Timer timer_invulnerable_status;//无敌状态定时器
	bool is_blink_invisible = false;//当前是否处于闪烁的不可见帧

	CollisionBox* hit_box = nullptr;//攻击碰撞箱
	CollisionBox* hurt_box = nullptr;//受击碰撞箱

	AnimationGroup* current_animation = nullptr;//当前的动画
	std::unordered_map<std::string, AnimationGroup> animation_pool;//角色动画状态池

};
