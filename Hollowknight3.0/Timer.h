#pragma once

#include <functional>

class Timer {

public:
	Timer()=default;
	~Timer() = default;

	void restart();

	void set_wait_time(float val);

	void set_one_shot(bool flag);

	void set_on_timeout(std::function<void()> on_timeout);

	void pause();

	void resume();

	void on_update(float deta);

private:
	float pass_time = 0;
	float wait_time = 0;
	bool paused = false;
	bool shotted = false;
	bool one_shot = false;
	std::function<void()> on_timeout;
};