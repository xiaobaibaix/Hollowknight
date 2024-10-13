#pragma once
#include "ManagerSingle.h"

class Hurt_show_manager :public ManagerSingle<Hurt_show_manager>
{
	friend class ManagerSingle<Hurt_show_manager>;
public:
	enum class Status
	{
		Entering,
		Exiting
	};

public:

	void post_process();

	float on_update(float delta);

private:
	Hurt_show_manager();
	~Hurt_show_manager();
private:
	float process = 0;
	const float SPEED_PROCESS = 2.f;
	Status status = Status::Exiting;
	const float DST_DELTA_FACTOR = 0.35f;
	const float DST_COLOR_FACTOR = 0.35f;
};

