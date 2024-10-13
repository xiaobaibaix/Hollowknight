#include "Enemy.h"

#include "CollisionManager.h"
#include "ResourcesManager.h"
#include "Enemy_state_node.h"

Enemy::Enemy()
{
	is_facing_left = true;
	position = { 1050,200 };
	logic_height = 150;

	hit_box->set_size({ 50,80 });
	hurt_box->set_size({100,180});

	hit_box->set_layer_src(CollisionLayer::None);
	hit_box->set_layer_dst(CollisionLayer::Player);

	hurt_box->set_layer_src(CollisionLayer::Enemy);
	hurt_box->set_layer_dst(CollisionLayer::None);

	hurt_box->set_on_collide(
		[&]() {
			decrease_hp();
		}
	);

	collision_box_silk = CollisionManager::instence()->create_collision_box();
	collision_box_silk->set_enable(false);
	collision_box_silk->set_layer_src(CollisionLayer::None);
	collision_box_silk->set_layer_dst(CollisionLayer::Player);
	collision_box_silk->set_size({250,250});

	{
		AnimationGroup& animation = animation_pool["aim"];

		Animation& left = animation.left;
		left.set_interval(0.05f);
		left.set_loop(false);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_atlas("enemy_aim_left"));

		Animation& right = animation.right;
		right.set_interval(0.05f);
		right.set_loop(false);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_atlas("enemy_aim_left"));

	}

	{
		AnimationGroup& animation = animation_pool["dash_in_air"];

		Animation& left = animation.left;
		left.set_interval(0.05f);
		left.set_loop(true);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_atlas("enemy_dash_in_air_left"));

		Animation& right = animation.right;
		right.set_interval(0.05f);
		right.set_loop(true);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_atlas("enemy_dash_in_air_right"));

	}

	{
		AnimationGroup& animation = animation_pool["dash_on_floor"];

		Animation& left = animation.left;
		left.set_interval(0.05f);
		left.set_loop(true);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_atlas("enemy_dash_on_floor_left"));

		Animation& right = animation.right;
		right.set_interval(0.05f);
		right.set_loop(true);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_atlas("enemy_dash_on_floor_right"));

	}

	{
		AnimationGroup& animation = animation_pool["fall"];

		Animation& left = animation.left;
		left.set_interval(0.1f);
		left.set_loop(true);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_atlas("enemy_fall_left"));

		Animation& right = animation.right;
		right.set_interval(0.1f);
		right.set_loop(true);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_atlas("enemy_fall_right"));

	}

	{
		AnimationGroup& animation = animation_pool["idle"];

		Animation& left = animation.left;
		left.set_interval(0.1f);
		left.set_loop(true);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_atlas("enemy_idle_left"));

		Animation& right = animation.right;
		right.set_interval(0.1f);
		right.set_loop(true);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_atlas("enemy_idle_right"));

	}

	{
		AnimationGroup& animation = animation_pool["jump"];

		Animation& left = animation.left;
		left.set_interval(0.1f);
		left.set_loop(false);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_atlas("enemy_jump_left"));

		Animation& right = animation.right;
		right.set_interval(0.1f);
		right.set_loop(false);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_atlas("enemy_jump_right"));

	}

	{
		AnimationGroup& animation = animation_pool["run"];

		Animation& left = animation.left;
		left.set_interval(0.05f);
		left.set_loop(true);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_atlas("enemy_run_left"));

		Animation& right = animation.right;
		right.set_interval(0.05f);
		right.set_loop(true);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_atlas("enemy_run_right"));

	}

	{
		AnimationGroup& animation = animation_pool["squat"];

		Animation& left = animation.left;
		left.set_interval(0.05f);
		left.set_loop(false);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_atlas("enemy_squat_left"));

		Animation& right = animation.right;
		right.set_interval(0.05f);
		right.set_loop(false);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_atlas("enemy_squat_right"));

	}

	{
		AnimationGroup& animation = animation_pool["throw_barb"];

		Animation& left = animation.left;
		left.set_interval(0.1f);
		left.set_loop(false);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_atlas("enemy_throw_barb_left"));

		Animation& right = animation.right;
		right.set_interval(0.1f);
		right.set_loop(false);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_atlas("enemy_throw_barb_right"));

	}

	{
		AnimationGroup& animation = animation_pool["throw_silk"];

		Animation& left = animation.left;
		left.set_interval(0.1f);
		left.set_loop(true);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_atlas("enemy_throw_silk_left"));

		Animation& right = animation.right;
		right.set_interval(0.1f);
		right.set_loop(true);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_atlas("enemy_throw_silk_right"));

	}

	{
		AnimationGroup& animation = animation_pool["throw_sword"];

		Animation& left = animation.left;
		left.set_interval(0.05f);
		left.set_loop(false);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_atlas("enemy_throw_sword_left"));

		Animation& right = animation.right;
		right.set_interval(0.05f);
		right.set_loop(false);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_atlas("enemy_throw_sword_right"));

	}

	animation_silk.set_interval(0.1f);
	animation_silk.set_loop(false);
	animation_silk.set_ancher_mode(Animation::AncherMode::Centerd);
	animation_silk.add_frame(ResourcesManager::instence()->find_atlas("silk"));

	{
		Animation& left = animation_dash_in_air_vfx.left;
		left.set_interval(0.1f);
		left.set_loop(false);
		left.set_ancher_mode(Animation::AncherMode::Centerd);
		left.add_frame(ResourcesManager::instence()->find_atlas("enemy_vfx_dash_in_air_left"));

		Animation& right = animation_dash_in_air_vfx.right;
		right.set_interval(0.1f);
		right.set_loop(false);
		right.set_ancher_mode(Animation::AncherMode::Centerd);
		right.add_frame(ResourcesManager::instence()->find_atlas("enemy_vfx_dash_in_air_right"));
	}
	{
		Animation& left = animation_dash_on_floor_vfx.left;
		left.set_interval(0.1f);
		left.set_loop(false);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_atlas("enemy_vfx_dash_on_floor_left"));

		Animation& right = animation_dash_on_floor_vfx.right;
		right.set_interval(0.1f);
		right.set_loop(false);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_atlas("enemy_vfx_dash_on_floor_right"));
	}

	{
		state_machine.register_state("aim", new EnemyAimState());
		state_machine.register_state("dash_in_air", new EnemyDashInAirState());
		state_machine.register_state("dash_on_floor", new EnemyDashOnFloorState());
		state_machine.register_state("dead", new EnemyDeadState());
		state_machine.register_state("fall", new EnemyFallState());
		state_machine.register_state("idle", new EnemyIdleState());
		state_machine.register_state("run", new EnemyRunState());
		state_machine.register_state("jump", new EnemyJumpState());
		state_machine.register_state("squat", new EnemySquatState());
		state_machine.register_state("throw_barb", new EnemyThrowBarbState());
		state_machine.register_state("throw_silk", new EnemyThrowSilkState());
		state_machine.register_state("throw_sword", new EnemyThrowSwordState());

		state_machine.set_entry("idle");
	}
}

Enemy::~Enemy()
{
	CollisionManager::instence()->destory_collision_box(collision_box_silk);
}

void Enemy::on_update(float delta)
{
	if (velocity.x >= 0.0001f)
		is_facing_left = (velocity.x < 0);

	Character::on_update(delta);

	if (is_throwing_silk) {
		collision_box_silk->set_position(get_logic_center());
		animation_silk.set_position(get_logic_center());
		animation_silk.on_update(delta);
	}
	if (is_dashing_in_air || is_dashing_on_floor){
		animation_cur_dash->set_position(is_dashing_in_air ? get_logic_center() : position);
		animation_cur_dash->on_update(delta);
		hit_box->set_position(get_logic_center());
	}

	for (Barb* barb : barb_list)
		barb->on_update(delta);
	for (Sword* sword : sword_list)
		sword->on_update(delta);

	barb_list.erase(std::remove_if(
		barb_list.begin(), barb_list.end(), [](Barb* barb) {
			bool can_remove = !barb->check_valid();
			if(can_remove)delete barb;
			return can_remove;
		}
	),barb_list.end());

	sword_list.erase(std::remove_if(
		sword_list.begin(), sword_list.end(), [](Sword* sword) {
			bool can_remove = !sword->check_valid();
			if (can_remove)delete sword;
			return can_remove;
		}
	), sword_list.end());
}

void Enemy::on_render()
{
	for (Barb* barb : barb_list)
		barb->on_render();
	for (Sword* sword : sword_list)
		sword->on_render();

	Character::on_render();

	if (is_throwing_silk)
		animation_silk.on_render();

	if (is_dashing_in_air || is_dashing_on_floor) {
		animation_cur_dash->on_render();
	}
}

void Enemy::on_hurt()
{
	switch (range_random(1,3)) {
	case 1:
		play_audio(_T("enemy_hurt_1"));
		break;
	case 2:
		play_audio(_T("enemy_hurt_2"));
		break;
	case 3:
		play_audio(_T("enemy_hurt_3"));
		break;
	}
}

void Enemy::throw_barbs()
{
	int num_new_barb = range_random(3, 6);
	int w_grid = getwidth()/num_new_barb;

	for (int i = 0; i < num_new_barb;i++) {
		Barb* barb = nullptr;
		for (Barb* barb_ : barb_list) {
			if (!barb_->check_valid()) {
				barb_->reset();
				barb = barb_;
				break;
			}
		}
		if (!barb) {
			barb = new Barb();
			barb_list.push_back(barb);
		}
		int rand_x = range_random(w_grid * i, w_grid * (i + 1));
		int rand_y = range_random(250,500);
		barb->set_position({ (float)rand_x,(float)rand_y });
	}
}

void Enemy::throw_sword()
{
	Sword* sword = new Sword(get_logic_center(), is_facing_left);
	sword_list.push_back(sword);
}

void Enemy::on_dash()
{
	if (is_dashing_in_air)
		animation_cur_dash = velocity.x < 0 ? &animation_dash_in_air_vfx.left: &animation_dash_in_air_vfx.right;
	else
		animation_cur_dash = velocity.x < 0 ? &animation_dash_on_floor_vfx.left : &animation_dash_on_floor_vfx.right;

	animation_cur_dash->reset();

	hit_box->set_enable(true);
	hit_box->set_position(get_logic_center());
}

void Enemy::on_throw_silk()
{
	collision_box_silk->set_enable(true);
	animation_silk.reset();
}
