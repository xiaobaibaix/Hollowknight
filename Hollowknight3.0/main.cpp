#pragma once
#include "ResourcesManager.h"
#include "CollisionManager.h"
#include "Character_manager.h"
#include "Bullet_time_manager.h"

#include <chrono>
#include <thread>
#include <graphics.h>

static void draw_background() {
	static IMAGE* img = ResourcesManager::instence()->find_image("background");
	static Rect rect_dst = {
		(getwidth() - img->getwidth()) / 2,
		(getheight() - img->getheight()) / 2,
		img->getwidth(),
		img->getheight()
	};
	putimage_ex(img, &rect_dst);
}

static void draw_remain_player_hp() {
	static IMAGE* img_ui_heart = ResourcesManager::instence()->find_image("ui_heart");
	Rect rect_dst = { 0,10,img_ui_heart->getwidth(),img_ui_heart->getheight() };
	for (int i = 0; i < CharacterManager::instence()->get_player()->get_hp();i++) {
		rect_dst.x = 10 + i * 40;
		putimage_ex(img_ui_heart, &rect_dst);
	}
}

static void draw_remain_enemy_hp() {

	setcolor(RGB(0, 255, 0));
	rectangle(40, 700, 1240, 710);
	setfillcolor(RGB(255, 0, 0));
	float d=CharacterManager::instence()->get_enemy()->get_hp()/10.f;
	fillrectangle(40, 700, 1240*d, 710);
}

int main(int argc,char** argv) {

	using namespace std::chrono;

	HWND hwnd = initgraph(1280, 720, EW_SHOWCONSOLE);
	SetWindowText(hwnd, _T("hollow katana"));
	
	bool is_quit = false;

	try
	{
		ResourcesManager::instence()->load();
	}
	catch (const LPCTSTR id)
	{
		TCHAR err_msg[512];
		_stprintf_s(err_msg, _T("无法加载： %s"), id);
		MessageBox(hwnd, err_msg, _T("资源加载失败!"), MB_OK | MB_ICONERROR);
		return -1;
	}
	play_audio(_T("bgm"), true);

	const nanoseconds frame_duration(1000000000 / 144);
	steady_clock::time_point last_tick = steady_clock::now();

	ExMessage msg;

	BeginBatchDraw();

	while (!is_quit) {
		while (peekmessage(&msg)) {
			CharacterManager::instence()->on_input(msg);
		}

		steady_clock::time_point frame_start = steady_clock::now();
		duration<float> delta = duration<float>(frame_start - last_tick);

		float scaled_delta = Bullet_time_manager::instence()->on_update(delta.count());
		CharacterManager::instence()->on_update(scaled_delta);
		CollisionManager::instence()->process_collide();

		setbkcolor(RGB(0, 0, 0));
		cleardevice();

		draw_background(); 
		CharacterManager::instence()->on_render();
		CollisionManager::instence()->on_debug_render();
		draw_remain_player_hp();
		draw_remain_enemy_hp();

		FlushBatchDraw();

		last_tick = frame_start;
		nanoseconds sleep_duration = frame_duration - (steady_clock::now() - frame_start);
		if (sleep_duration > nanoseconds(0))
			std::this_thread::sleep_for(sleep_duration);
	}

	EndBatchDraw();
	closegraph();
	return 0;
}