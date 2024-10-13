#include "ResourcesManager.h"

#include "util.h"


const std::vector<ResourcesManager::ImageResInfo> ResourcesManager::image_info_list{
	{"background",_T(R"(resources/picture/background.png)")},
	{"logo",_T(R"(resources/picture/logo.jpg)")},
	{"ui_heart",_T(R"(resources/picture/ui_heart.png)")},
	{"ui_btn",_T(R"(resources/picture/ui_btn.png)")},

	{"player_attack_right",_T(R"(resources/player/attack.png)")},
	{"player_dead_right",_T(R"(resources/player/dead.png)")},
	{"player_fall_right",_T(R"(resources/player/fall.png)")},
	{"player_idle_right",_T(R"(resources/player/idle.png)")},
	{"player_jump_right",_T(R"(resources/player/jump.png)")},
	{"player_roll_right",_T(R"(resources/player/roll.png)")},
	{"player_run_right",_T(R"(resources/player/run.png)")},

	{"player_vfx_attack_down",_T(R"(resources/player/vfx_attack_down.png)")},
	{"player_vfx_attack_up",_T(R"(resources/player/vfx_attack_up.png)")},
	{"player_vfx_attack_left",_T(R"(resources/player/vfx_attack_left.png)")},
	{"player_vfx_attack_right",_T(R"(resources/player/vfx_attack_right.png)")},
	{"player_vfx_jump",_T(R"(resources/player/vfx_jump.png)")},
	{"player_vfx_land",_T(R"(resources/player/vfx_land.png)")}
};

const std::vector<ResourcesManager::AtlasResInfo> ResourcesManager::atlas_info_list{
	{"enemy_barb_break",_T(R"(resources/enemy/barb_break)"),3},
	{"enemy_barb_loose",_T(R"(resources/enemy/barb_loose)"),5},

	{"enemy_dash_in_air_left",_T(R"(resources/enemy/dash_in_air)"),2},
	{"enemy_dash_on_floor_left",_T(R"(resources/enemy/dash_on_floor)"),2},

	{"enemy_aim_left",_T(R"(resources/enemy/aim)"),9},
	{"enemy_fall_left",_T(R"(resources/enemy/fall)"),4},
	{"enemy_idle_left",_T(R"(resources/enemy/idle)"),6},
	{"enemy_jump_left",_T(R"(resources/enemy/jump)"),8},
	{"enemy_run_left",_T(R"(resources/enemy/run)"),8},
	{"silk",_T(R"(resources/enemy/silk)"),9},
	{"enemy_squat_left",_T(R"(resources/enemy/squat)"),10},
	{"enemy_sword_left",_T(R"(resources/enemy/sword)"),3},

	{"enemy_throw_barb_left",_T(R"(resources/enemy/throw_barb)"),8},
	{"enemy_throw_silk_left",_T(R"(resources/enemy/throw_silk)"),17},
	{"enemy_throw_sword_left",_T(R"(resources/enemy/throw_sword)"),16},

	{"enemy_vfx_dash_in_air_left",_T(R"(resources/enemy/vfx_dash_in_air)"),5},
	{"enemy_vfx_dash_on_floor_left",_T(R"(resources/enemy/vfx_dash_on_floor)"),6},
};


void ResourcesManager::load() {
	for (const auto& info : image_info_list) {
		IMAGE* img = new IMAGE();
		loadimage(img, info.path);
		if (!check_image_valid(img))
			throw info.path;
		image_pool[info.id] = img;
	}
	for (const auto& info : atlas_info_list) {
		Atlas* atlas = new Atlas();
		atlas->load(info.path, info.num_frame);
		for (int i = 0; i < atlas->get_size(); i++) {
			IMAGE* img = atlas->get_image(i);
			if (!check_image_valid(img))
				throw info.path;
		}
		atlas_pool[info.id] = atlas;
	}
	flip_image("player_attack_right", "player_attack_left", 5);
	flip_image("player_dead_right", "player_dead_left", 6);
	flip_image("player_fall_right", "player_fall_left", 5);
	flip_image("player_idle_right", "player_idle_left", 5);
	flip_image("player_jump_right", "player_jump_left", 5);
	flip_image("player_run_right", "player_run_left", 10);
	flip_image("player_roll_right", "player_roll_left", 7);

	flip_atlas("enemy_sword_left", "enemy_sword_right");
	flip_atlas("enemy_aim_left", "enemy_aim_right");
	flip_atlas("enemy_dash_in_air_left", "enemy_dash_in_air_right");
	flip_atlas("enemy_dash_on_floor_left", "enemy_dash_on_floor_right");
	flip_atlas("enemy_fall_left", "enemy_fall_right");
	flip_atlas("enemy_idle_left", "enemy_idle_right");
	flip_atlas("enemy_jump_left", "enemy_jump_right");
	flip_atlas("enemy_run_left", "enemy_run_right");
	flip_atlas("enemy_squat_left", "enemy_squat_right");
	flip_atlas("enemy_throw_barb_left", "enemy_throw_barb_right");
	flip_atlas("enemy_throw_silk_left", "enemy_throw_silk_right");
	flip_atlas("enemy_throw_sword_left", "enemy_throw_sword_right");

	flip_atlas("enemy_vfx_dash_in_air_left", "enemy_vfx_dash_in_air_right");
	flip_atlas("enemy_vfx_dash_on_floor_left", "enemy_vfx_dash_on_floor_right");

	load_audio(_T("barb_break"), _T(R"(resources/audio/barb_break.mp3)"));
	load_audio(_T("bgm"), _T(R"(resources/audio/bgm.mp3)"));
	load_audio(_T("bullet_time"), _T(R"(resources/audio/bullet_time.mp3)"));
	load_audio(_T("enemy_dash"), _T(R"(resources/audio/enemy_dash.mp3)"));
	load_audio(_T("enemy_hurt_1"), _T(R"(resources/audio/enemy_hurt_1.mp3)"));
	load_audio(_T("enemy_hurt_2"), _T(R"(resources/audio/enemy_hurt_2.mp3)"));
	load_audio(_T("enemy_hurt_3"), _T(R"(resources/audio/enemy_hurt_3.mp3)"));
	load_audio(_T("enemy_run"), _T(R"(resources/audio/enemy_run.mp3)"));
	load_audio(_T("enemy_throw_barbs"), _T(R"(resources/audio/enemy_throw_barbs.mp3)"));
	load_audio(_T("enemy_throw_silk"), _T(R"(resources/audio/enemy_throw_silk.mp3)"));
	load_audio(_T("enemy_throw_sword"), _T(R"(resources/audio/enemy_throw_sword.mp3)"));
	load_audio(_T("player_attack_1"), _T(R"(resources/audio/player_attack_1.mp3)"));
	load_audio(_T("player_attack_2"), _T(R"(resources/audio/player_attack_2.mp3)"));
	load_audio(_T("player_attack_3"), _T(R"(resources/audio/player_attack_3.mp3)"));
	load_audio(_T("player_dead"), _T(R"(resources/audio/player_dead.mp3)"));
	load_audio(_T("player_hurt"), _T(R"(resources/audio/player_hurt.mp3)"));
	load_audio(_T("player_jump"), _T(R"(resources/audio/player_jump.mp3)"));
	load_audio(_T("player_land"), _T(R"(resources/audio/player_land.mp3)"));
	load_audio(_T("player_roll"), _T(R"(resources/audio/player_roll.mp3)"));
	load_audio(_T("player_run"), _T(R"(resources/audio/player_run.mp3)"));
}

Atlas* ResourcesManager::find_atlas(const std::string& id) const {
	const auto& itor = atlas_pool.find(id);
	if (itor == atlas_pool.end())return nullptr;
	return itor->second;
}

IMAGE* ResourcesManager::find_image(const std::string& id) const {
	const auto& itor = image_pool.find(id);
	if (itor == image_pool.end())return nullptr;
	return itor->second;
}


//
//·­×ª
//

void ResourcesManager::flip_image(IMAGE* src_img, IMAGE* dst_img, int num_h) {
	int w = src_img->getwidth();
	int h = src_img->getheight();
	int w_frame = w / num_h;

	Resize(dst_img, w, h);
	DWORD* src_buffer = GetImageBuffer(src_img);
	DWORD* dst_buffer = GetImageBuffer(dst_img);
	for (int i = 0; i < num_h; i++) {
		int x_left = i * w_frame;
		int x_right = (i + 1) * w_frame;
		for (int y = 0; y < h; y++) {
			for (int x = x_left; x < x_right; x++) {
				int idx_src = y * w + x;
				int idx_dst = y * w + x_right - (x - x_left);
				dst_buffer[idx_dst] = src_buffer[idx_src];
			}
		}
	}
}

void ResourcesManager::flip_image(const std::string& src_id, const std::string dst_id, int num_h) {
	IMAGE* src_img = image_pool[src_id];
	IMAGE* dst_img = new IMAGE();

	flip_image(src_img, dst_img, num_h);

	image_pool[dst_id] = dst_img;
}

void ResourcesManager::flip_atlas(const std::string& src_id, const std::string dst_id) {
	Atlas* src_atlas = atlas_pool[src_id];
	Atlas* dst_atlas = new Atlas();

	for (int i = 0; i < src_atlas->get_size(); i++) {
		IMAGE img_filpped;
		flip_image(src_atlas->get_image(i), &img_filpped);
		dst_atlas->add_image(img_filpped);
	}

	atlas_pool[dst_id] = dst_atlas;
}

bool ResourcesManager::check_image_valid(IMAGE* img) {
	return GetImageBuffer(img);
}
