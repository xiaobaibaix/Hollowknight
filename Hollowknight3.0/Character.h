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
	//ʹ�޵�
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
	const float FLOOR_Y = 620;//�ذ�ĸ߶�
	const float GRAVITY = 980*2;//����
protected:
	int hp = 10;//Ѫ��

	Vector2D position;//λ��
	Vector2D velocity;//�ٶ�

	float logic_height = 0;//��ɫ���߼��߶�

	bool is_facing_left = true;//��ɫ�Ƿ��泯��

	StateMachine state_machine;//��ɫ״̬��

	bool enable_gravity = true;//�Ƿ���������
	bool is_invulnerable = false;//��ɫ�Ƿ��޵�

	Timer timer_invulnerable_blink;//�޵���˸״̬��ʱ��
	Timer timer_invulnerable_status;//�޵�״̬��ʱ��
	bool is_blink_invisible = false;//��ǰ�Ƿ�����˸�Ĳ��ɼ�֡

	CollisionBox* hit_box = nullptr;//������ײ��
	CollisionBox* hurt_box = nullptr;//�ܻ���ײ��

	AnimationGroup* current_animation = nullptr;//��ǰ�Ķ���
	std::unordered_map<std::string, AnimationGroup> animation_pool;//��ɫ����״̬��

};
