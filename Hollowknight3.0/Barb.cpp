#include "Barb.h"

#include "CollisionManager.h"
#include "ResourcesManager.h"
#include "Character_manager.h"
#include "util.h"

Barb::Barb()
{
	diff_period = range_random(0, 6);

	animation_loose.set_interval(0.15f);
	animation_loose.set_loop(true);
	animation_loose.set_ancher_mode(Animation::AncherMode::Centerd);
	animation_loose.add_frame(ResourcesManager::instence()->find_atlas("enemy_barb_loose"));

	animation_break.set_interval(0.1f);
	animation_break.set_loop(false);
	animation_break.set_ancher_mode(Animation::AncherMode::Centerd);
	animation_break.add_frame(ResourcesManager::instence()->find_atlas("enemy_barb_break"));
	animation_break.set_on_finished(
		[&]() {
			is_valid = false;
		}
	);

	collsition_box = CollisionManager::instence()->create_collision_box();
	collsition_box->set_layer_src(CollisionLayer::Enemy);
	collsition_box->set_layer_dst(CollisionLayer::Player);
	collsition_box->set_size({ 20,20 });
	collsition_box->set_on_collide(
		[&]() {
			on_break();
		}
	);

	timer_idle.set_wait_time((float)range_random(3, 10));
	timer_idle.set_one_shot(true);
	timer_idle.set_on_timeout(
		[&]() {
			if (stage == Stage::Idle) {
				stage = Stage::Aim;
				base_position = cur_position;
			}
		}
	);

	timer_aim.set_wait_time(0.75f);
	timer_aim.set_one_shot(true);
	timer_aim.set_on_timeout(
		[&]() {
			if (stage == Stage::Aim) {
				stage = Stage::Dash;
				const Vector2D& pos_player = CharacterManager::instence()->get_player()->get_position();
				Velovity = (pos_player - cur_position).normalize() * SPEED_DASH;
			}
		}
	);

}

Barb::~Barb()
{
	CollisionManager::instence()->destory_collision_box(collsition_box);
}

void Barb::on_update(float delta)
{
	//更新定时器
	if (stage == Stage::Idle)
		timer_idle.on_update(delta);
	if (stage == Stage::Aim)
		timer_aim.on_update(delta);

	//更新移动逻辑
	total_delta_time += delta;
	switch (stage) {
	case Barb::Stage::Idle:
		cur_position.y = base_position.y + 30*sin(total_delta_time * 2 + diff_period);
		break;
	case Barb::Stage::Aim:
		cur_position.x = base_position.x + range_random(-10, 10);
		break;
	case Barb::Stage::Dash:
		cur_position += Velovity * delta;
		if (cur_position.y >= CharacterManager::instence()->get_player()->get_floor_y())
			on_break();
		if (cur_position.y < 0)
			is_valid = false;
		break;
	case Barb::Stage::Break:
		break;
	}
	collsition_box->set_position(cur_position);

	//动画更新
	animation_cur = (stage == Stage::Break ? &animation_break : &animation_loose);
	animation_cur->set_position(cur_position);
	animation_cur->on_update(delta);

}

void Barb::on_render()
{
	if(is_valid)animation_cur->on_render();
}

void Barb::reset() {
	is_valid = true;
	timer_idle.restart();
	timer_aim.restart();
	diff_period = range_random(0, 6);
	total_delta_time = 0;
	base_position = { 0,0 };
	cur_position = { 0,0 };
	Velovity = { 0,0 };
	stage = Stage::Idle;
	animation_cur = &animation_loose;

}

void Barb::on_break()
{
	if (stage == Stage::Break)return;

	stage = Stage::Break;
	collsition_box->set_enable(false);
	

	play_audio(_T("barb_break"));
}
