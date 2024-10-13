#pragma once
#include "ManagerSingle.h"
class Bullet_time_manager :public ManagerSingle<Bullet_time_manager>
{
	friend class ManagerSingle<Bullet_time_manager>;
public:
	enum class Status
	{
		Entering,
		Exiting
	};
public:
	void post_process();
	void set_status(Status status);

	float on_update(float delta);

private:
	Bullet_time_manager();
	~Bullet_time_manager();
private:
	float process = 0;
	Status status = Status::Exiting;
	const float SPEED_PROCESS = 2.f;
	const float DST_DELTA_FACTOR = 0.35f;
	const float DST_COLOR_FACTOR = 0.35f;

private:

};

