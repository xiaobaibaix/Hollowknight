#pragma once
#include "Vector2D.h"
#include "Animation.h"
#include "Collision_box.h"
#include "Timer.h"

//´ÌÇò×Óµ¯
class Barb
{
public:

	Barb();
	~Barb();

	void on_update(float delta);
	void on_render();

	void set_position(const Vector2D& pos) {
		base_position = pos;
		cur_position = pos;
	}

	bool check_valid()const {
		return is_valid;
	}

	void reset();
private:
	enum class Stage
	{
		Idle,//µÈ´ý×´Ì¬
		Aim,//¶¶¶¯×´Ì¬
		Dash,//³å´Ì×´Ì¬
		Break//ÆÆËé×´Ì¬
	};

private:
	const float SPEED_DASH = 1500.f;

private:

	Timer timer_idle;
	Timer timer_aim;
	int diff_period = 0;//ÉÏÏÂ¸¡¶¯Ëæ»úÖµ
	bool is_valid = true;
	float total_delta_time = 0;

	Vector2D base_position;
	Vector2D cur_position;
	Vector2D Velovity;

	Animation animation_loose;
	Animation animation_break;
	Animation *animation_cur = nullptr;;

	Stage stage = Stage::Idle;
	CollisionBox* collsition_box = nullptr;
private:
	void on_break();
};

