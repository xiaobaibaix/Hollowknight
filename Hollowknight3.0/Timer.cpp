#include "Timer.h"

void Timer::restart() {
	pass_time = 0;
	shotted = false;
}

void Timer::set_wait_time(float val) {
	wait_time = val;
}

void Timer::set_one_shot(bool flag) {
	one_shot = flag;
}

void Timer::set_on_timeout(std::function<void()> on_timeout) {
	this->on_timeout = on_timeout;
}

void Timer::pause() {
	paused = true;
}

void Timer::resume() {
	paused = false;
}

void Timer::on_update(float deta) {
	if (paused)return;

	pass_time += deta;
	if (pass_time >= wait_time) {
		bool can_shot = (!one_shot || (one_shot && !shotted));
		shotted = true;
		if (can_shot && on_timeout)
			on_timeout();
		pass_time -= wait_time;
	}
}
