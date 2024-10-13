#pragma once
#include "Vector2D.h"
#include "Animation.h"
#include "Collision_box.h"
//·ÉïÚ
class Sword
{
public:
	Sword(const Vector2D& pos,bool move_left);
	~Sword();

	void on_update(float delta);
	void on_render();

	bool check_valid()const {
		return is_valid;
	}
private:
	const float SPEED_MOVE = 1250.f;
private:
	Vector2D position;
	Vector2D Velovity;
	Animation animation;
	bool is_valid = true;
	CollisionBox* collsition_box = nullptr;
};

