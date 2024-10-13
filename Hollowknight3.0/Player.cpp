#include "Player.h"

#include "ResourcesManager.h"
#include "Player_state_node.h"
#include "Bullet_time_manager.h"

Player::Player()
{
	is_facing_left = false;
	position = { 250,200 };
	logic_height = 120;
	hp = 100;

	hit_box->set_size({ 150,150 });
	hurt_box->set_size({ 40,80 });

	hit_box->set_layer_src(CollisionLayer::None);
	hit_box->set_layer_dst(CollisionLayer::Enemy);

	hurt_box->set_layer_src(CollisionLayer::Player);
	hurt_box->set_layer_dst(CollisionLayer::None);

	hit_box->set_enable(false);
	hurt_box->set_on_collide(
		[&]() {
			decrease_hp();
		}
	);

	timer_roll_cd.set_one_shot(true);
	timer_roll_cd.set_wait_time(CD_ROLL);
	timer_roll_cd.set_on_timeout(
		[&]() {
			is_roll_cd_comp = true;
		}
	);

	timer_attack_cd.set_one_shot(true);
	timer_attack_cd.set_wait_time(CD_ATTACK);
	timer_attack_cd.set_on_timeout(
		[&]() {
			is_attack_cd_comp = true;
		}
	);
	{
		AnimationGroup& animation = animation_pool["attack"];

		Animation& left = animation.left;
		left.set_interval(0.05f);
		left.set_loop(false);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_image("player_attack_left"), 5);

		Animation& right = animation.right;
		right.set_interval(0.05f);
		right.set_loop(false);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_image("player_attack_right"), 5);

	}

	{
		AnimationGroup& animation = animation_pool["dead"];

		Animation& left = animation.left;
		left.set_interval(0.1f);
		left.set_loop(false);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_image("player_dead_left"), 6);

		Animation& right = animation.right;
		right.set_interval(0.1f);
		right.set_loop(false);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_image("player_dead_right"), 6);

	}

	{
		AnimationGroup& animation = animation_pool["fall"];

		Animation& left = animation.left;
		left.set_interval(0.15f);
		left.set_loop(false);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_image("player_fall_left"), 5);

		Animation& right = animation.right;
		right.set_interval(0.15f);
		right.set_loop(false);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_image("player_fall_right"), 5);

	}

	{
		AnimationGroup& animation = animation_pool["idle"];

		Animation& left = animation.left;
		left.set_interval(0.15f);
		left.set_loop(true);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_image("player_idle_left"), 5);

		Animation& right = animation.right;
		right.set_interval(0.15f);
		right.set_loop(true);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_image("player_idle_right"), 5);

	}

	{
		AnimationGroup& animation = animation_pool["jump"];

		Animation& left = animation.left;
		left.set_interval(0.15f);
		left.set_loop(false);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_image("player_jump_left"), 5);

		Animation& right = animation.right;
		right.set_interval(0.15f);
		right.set_loop(false);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_image("player_jump_right"), 5);

	}

	{
		AnimationGroup& animation = animation_pool["roll"];

		Animation& left = animation.left;
		left.set_interval(0.05f);
		left.set_loop(false);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_image("player_roll_left"), 7);

		Animation& right = animation.right;
		right.set_interval(0.05f);
		right.set_loop(false);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_image("player_roll_right"), 7);

	}

	{
		AnimationGroup& animation = animation_pool["run"];

		Animation& left = animation.left;
		left.set_interval(0.075f);
		left.set_loop(true);
		left.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		left.add_frame(ResourcesManager::instence()->find_image("player_run_left"), 10);

		Animation& right = animation.right;
		right.set_interval(0.075f);
		right.set_loop(true);
		right.set_ancher_mode(Animation::AncherMode::BottomCenterd);
		right.add_frame(ResourcesManager::instence()->find_image("player_run_right"), 10);

	}

	animation_slash_up.set_interval(0.07f);
	animation_slash_up.set_loop(false);
	animation_slash_up.set_ancher_mode(Animation::AncherMode::Centerd);
	animation_slash_up.add_frame(ResourcesManager::instence()->find_image("player_vfx_attack_up"), 5);

	animation_slash_down.set_interval(0.07f);
	animation_slash_down.set_loop(false);
	animation_slash_down.set_ancher_mode(Animation::AncherMode::Centerd);
	animation_slash_down.add_frame(ResourcesManager::instence()->find_image("player_vfx_attack_down"), 5);

	animation_slash_left.set_interval(0.07f);
	animation_slash_left.set_loop(false);
	animation_slash_left.set_ancher_mode(Animation::AncherMode::Centerd);
	animation_slash_left.add_frame(ResourcesManager::instence()->find_image("player_vfx_attack_left"), 5);

	animation_slash_right.set_interval(0.07f);
	animation_slash_right.set_loop(false);
	animation_slash_right.set_ancher_mode(Animation::AncherMode::Centerd);
	animation_slash_right.add_frame(ResourcesManager::instence()->find_image("player_vfx_attack_right"), 5);

	animation_jump_vfx.set_interval(0.075f);
	animation_jump_vfx.set_loop(false);
	animation_jump_vfx.set_ancher_mode(Animation::AncherMode::BottomCenterd);
	animation_jump_vfx.add_frame(ResourcesManager::instence()->find_image("player_vfx_jump"), 5);
	animation_jump_vfx.set_on_finished(
		[&]() {
			is_jump_vfx_visible = false;
		}
	);

	animation_land_vfx.set_interval(0.1f);
	animation_land_vfx.set_loop(false);
	animation_land_vfx.set_ancher_mode(Animation::AncherMode::BottomCenterd);
	animation_land_vfx.add_frame(ResourcesManager::instence()->find_image("player_vfx_land"), 2);
	animation_land_vfx.set_on_finished(
		[&]() {
			is_land_vfx_visible = false;
		}
	);

	{
		state_machine.register_state("attack", new PlayerAttackState());
		state_machine.register_state("dead", new PlayerDeadState());
		state_machine.register_state("fall", new PlayerFallState());
		state_machine.register_state("idle", new PlayerIdleState());
		state_machine.register_state("jump", new PlayerJumpState());
		state_machine.register_state("roll", new PlayerRollState());
		state_machine.register_state("run", new PlayerRunState());

		state_machine.set_entry("idle");
	}

}

Player::~Player()
{
}

void Player::on_input(const ExMessage& msg) {
	if (hp <= 0)return;

	switch (msg.message) {
	case WM_KEYDOWN:
		switch (msg.vkcode) {
		case 0x41://A
		case VK_LEFT:
			is_left_key_down = true;
			break;
		case 0x44://D
		case VK_RIGHT:
			is_right_key_down = true;
			break;
		case 0x57://W
		case VK_UP:
			is_jump_key_down = true;
			break;
		case 0x53://S
		case VK_DOWN:
			is_roll_key_down = true;
			break;
		}
		break;
	case WM_KEYUP:
		switch (msg.vkcode) {
		case 0x41://A
		case VK_LEFT:
			is_left_key_down = false;
			break;
		case 0x44://D
		case VK_RIGHT:
			is_right_key_down = false;
			break;
		case 0x57://W
		case VK_UP:
			is_jump_key_down = false;
			break;
		case 0x53://S
		case VK_DOWN:
			is_roll_key_down = false;
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		is_attack_key_down = true;
		update_attack_dir(msg.x, msg.y);
		break;
	case WM_LBUTTONUP:
		is_attack_key_down = false;
		break;
	case WM_RBUTTONDOWN:
		play_audio(_T("bullet_time"));
		Bullet_time_manager::instence()->set_status(Bullet_time_manager::Status::Entering);
		break;
	case WM_RBUTTONUP:
		stop_audio(_T("bullet_time"));
		Bullet_time_manager::instence()->set_status(Bullet_time_manager::Status::Exiting);
		break;
	}
}

void Player::on_update(float delta) {
	if (hp > 0 && !is_rolling)
		velocity.x = get_move_axis() * SPEED_RUN;
	if (get_move_axis() != 0)
		is_facing_left = (get_move_axis() < 0);

	timer_roll_cd.on_update(delta);
	timer_attack_cd.on_update(delta);

	animation_jump_vfx.on_update(delta);
	animation_land_vfx.on_update(delta);

	if (is_attacking) {
		current_slash_animation->set_position(get_logic_center());
		current_slash_animation->on_update(delta);
	}
	Character::on_update(delta);
}

void Player::on_render() {
	if (is_jump_vfx_visible)
		animation_jump_vfx.on_render();
	if (is_land_vfx_visible)
		animation_land_vfx.on_render();
	//当前玩家动画
	Character::on_render();

	if (is_attacking)
		current_slash_animation->on_render();
}

void Player::on_hurt() {
	play_audio(_T("player_hurt"));



}

void Player::set_rolling(bool flag) {
	is_rolling = flag;
}

bool Player::get_rolling() const {
	return is_rolling;
}

bool Player::can_roll() const {
	return is_roll_cd_comp && !is_rolling && is_roll_key_down;
}

void Player::set_attacking(bool flag) {
	is_attacking = flag;
}

bool Player::get_attacking() const {
	return is_attacking;
}

bool Player::can_attck() const {
	return is_attack_cd_comp && !is_attacking && is_attack_key_down;
}

bool Player::can_jump() const {
	return is_on_floor() && is_jump_key_down;
}

int Player::get_move_axis() const {
	return is_right_key_down - is_left_key_down;
}

Player::AttackDir Player::get_attack_dir() const {
	return attack_dir;
}

void Player::on_jump() {
	velocity.y -= SPEED_JUMP;
	is_jump_vfx_visible = true;
	animation_jump_vfx.set_position(position);
	animation_jump_vfx.reset();
}

void Player::on_land() {
	is_land_vfx_visible = true;
	animation_land_vfx.set_position(position);
	animation_land_vfx.reset();
}

void Player::on_roll() {
	timer_roll_cd.restart();
	is_roll_cd_comp = false;
	velocity.x = is_facing_left ? -SPEED_ROLL : SPEED_ROLL;
}

void Player::on_attack() {
	timer_attack_cd.restart();
	is_attack_cd_comp = false;
	switch (attack_dir) {
	case Player::AttackDir::Up:
		current_slash_animation = &animation_slash_up;
		break;
	case Player::AttackDir::Down:
		current_slash_animation = &animation_slash_down;
		break;
	case Player::AttackDir::Left:
		current_slash_animation = &animation_slash_left;
		break;
	case Player::AttackDir::Right:
		current_slash_animation = &animation_slash_right;
		break;
	}
	current_slash_animation->set_position(get_logic_center());
	current_slash_animation->reset();
}

void Player::update_attack_dir(int x, int y) {
	static const float PI = 3.141592654f;
	float angle = std::atan2(y - position.y, x - position.x);//[-PI,PI]

	if (angle >= -PI / 4 && angle < PI / 4)
		attack_dir = AttackDir::Right;
	else if (angle >= PI / 4 && angle < 3 * PI / 4)
		attack_dir = AttackDir::Down;
	else if ((angle >= 3 * PI / 4 && angle <= PI) || (angle >= -PI && angle < -3 * PI / 4))
		attack_dir = AttackDir::Left;
	else
		attack_dir = AttackDir::Up;
}
