#include "Enemy_state_node.h"

#include "Enemy.h"
#include "Character_manager.h"

EnemyAimState::EnemyAimState()
{
	timer.set_wait_time(0.5f);
	timer.set_one_shot(true);
	timer.set_on_timeout(
		[&]() {
			Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();
			enemy->set_gravity_enable(true);
			enemy->switch_state("dash_in_air");
		}
	);
}

EnemyAimState::~EnemyAimState()
{
}

void EnemyAimState::on_enter()
{
	CharacterManager::instence()->get_enemy()->set_animation("aim");

	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();
	enemy->set_gravity_enable(false);
	enemy->set_velocity({ 0,0 });
	timer.restart();
}

void EnemyAimState::on_update(float delta)
{
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();

	timer.on_update(delta);

	if (enemy->get_hp() <= 0)
		enemy->switch_state("dead");
}
//！！！！！！！！！！！！！！！！！！！！！！！！
EnemyDashInAirState::EnemyDashInAirState()
{
}

EnemyDashInAirState::~EnemyDashInAirState()
{
}

void EnemyDashInAirState::on_enter()
{
	CharacterManager::instence()->get_enemy()->set_animation("dash_in_air");

	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();
	const Character* player = CharacterManager::instence()->get_player();

	Vector2D pos_target = { player->get_position().x,player->get_floor_y() };

	enemy->set_velocity((pos_target - enemy->get_position()).normalize() * SPEED_DASH);
	enemy->set_dashing_in_air(true);
	enemy->set_gravity_enable(false);
	enemy->on_dash();

	play_audio(_T("enemy_dash"));
}

void EnemyDashInAirState::on_update(float delta)
{
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();

	if (enemy->get_hp() <= 0)
		enemy->switch_state("dead");
	else if (enemy->is_on_floor())
		enemy->switch_state("idle");
}

void EnemyDashInAirState::on_exit()
{
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();

	enemy->set_gravity_enable(true);
	enemy->set_dashing_in_air(false);
	enemy->get_hit_box()->set_enable(false);
}

//！！！！！！！！！！！！！！！！！！！！！！！！

EnemyDashOnFloorState::EnemyDashOnFloorState()
{
	timer.set_wait_time(0.5f);
	timer.set_one_shot(true);
	timer.set_on_timeout(
		[&]() {
			Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();
			enemy->set_dashing_on_floor(false);
		}
	);
}

EnemyDashOnFloorState::~EnemyDashOnFloorState()
{
}

void EnemyDashOnFloorState::on_enter()
{
	CharacterManager::instence()->get_enemy()->set_animation("dash_on_floor");

	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();

	enemy->set_velocity({enemy->get_facing_left()?-SPEED_DASH:SPEED_DASH,0});
	enemy->set_dashing_on_floor(true);
	enemy->on_dash();
	timer.restart();

	play_audio(_T("enemy_dash"));
}

void EnemyDashOnFloorState::on_update(float delta)
{
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();

	timer.on_update(delta);

	if (enemy->get_hp() <= 0)
		enemy->switch_state("dead");
	else if (!enemy->get_dashing_on_floor())
		enemy->switch_state("idle");
}

void EnemyDashOnFloorState::on_exit()
{
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();
	enemy->get_hit_box()->set_enable(false);
}

//！！！！！！！！！！！！！！！！！！！！！！！！

void EnemyDeadState::on_enter()
{
	MessageBox(GetHWnd(), _T("載挫��宸劔嬬佩。"), _T("薬媾撹孔��"),MB_OK);
	exit(0);
}
//！！！！！！！！！！！！！！！！！！！！！！！！

EnemyFallState::EnemyFallState()
{
}

EnemyFallState::~EnemyFallState()
{
}

void EnemyFallState::on_enter()
{
	CharacterManager::instence()->get_enemy()->set_animation("fall");

}

void EnemyFallState::on_update(float delta)
{
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();

	if (enemy->get_hp() <= 0)
		enemy->switch_state("dead");
	else if (enemy->is_on_floor())
		enemy->switch_state("idle");
}
//！！！！！！！！！！！！！！！！！！！！！！！！

EnemyIdleState::EnemyIdleState()
{
	timer.set_one_shot(true);
	timer.set_on_timeout(
		[&]() {
			Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();
			
			int rand_num = range_random(0, 100);
			if (enemy->get_hp() > 5) {
				if (rand_num <= 25) {
					if (!enemy->is_on_floor())
						enemy->switch_state("fall");
					else
						enemy->switch_state("jump");
				}
				else if (rand_num <= 50) {
					if (!enemy->is_on_floor())
						enemy->switch_state("fall");
					else
						enemy->switch_state("run");
				}
				else if (rand_num <= 80)
					enemy->switch_state("squat");
				else if (rand_num<=90) 					
					enemy->switch_state("throw_silk");
				else 
					enemy->switch_state("throw_sword");
			}
			else{
				if (rand_num <= 25) {
					if (!enemy->is_on_floor())
						enemy->switch_state("fall");
					else
						enemy->switch_state("jump");
				}
				else if (rand_num <= 60)
					enemy->switch_state("throw_sword");
				else if (rand_num <= 80)
					enemy->switch_state("throw_silk");
				else if (rand_num <= 90)
					enemy->switch_state("throw_barb");
				else
					enemy->switch_state("squat");
			}
		}
	);
}

EnemyIdleState::~EnemyIdleState()
{
}

void EnemyIdleState::on_enter()
{
	CharacterManager::instence()->get_enemy()->set_animation("idle");

	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();
	enemy->set_velocity({ 0,0 });

	float wait_time = 0;
	if (enemy->get_hp() > 5)
		wait_time = range_random(0, 2) * 0.25f;
	else
		wait_time = range_random(0, 1) * 0.25f;

	timer.set_wait_time(wait_time);
	timer.restart();
}

void EnemyIdleState::on_update(float delta)
{
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();

	timer.on_update(delta);

	if (enemy->get_hp() <= 0)
		enemy->switch_state("dead");
	else if (enemy->get_velocity().y>0)
		enemy->switch_state("fall");
}

void EnemyIdleState::on_exit()
{
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();
	enemy->set_facing_left(enemy->get_position().x > CharacterManager::instence()->get_player()->get_position().x);
}
//！！！！！！！！！！！！！！！！！！！！！！！！

EnemyJumpState::EnemyJumpState()
{
}

EnemyJumpState::~EnemyJumpState()
{
}

void EnemyJumpState::on_enter()
{
	CharacterManager::instence()->get_enemy()->set_animation("jump");
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();

	enemy->set_velocity({ 0,-SPEED_JUMP });

}

void EnemyJumpState::on_update(float delta)
{
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();

	if (enemy->get_hp() <= 0)
		enemy->switch_state("dead");
	else if (enemy->get_velocity().y > 0) {
		int rand_num = range_random(0, 100);
		if (enemy->get_hp() > 5) {
			if (rand_num <= 50)
				enemy->switch_state("aim");
			else if (rand_num <= 80)
				enemy->switch_state("fall");
			else
				enemy->switch_state("throw_silk");
		}
		else {
			if (rand_num <= 50)
				enemy->switch_state("throw_silk");
			else if (rand_num <= 80)
				enemy->switch_state("fall");
			else
				enemy->switch_state("aim");
		}
	}
}
//！！！！！！！！！！！！！！！！！！！！！！！！

EnemyRunState::EnemyRunState()
{
}

EnemyRunState::~EnemyRunState()
{
}

void EnemyRunState::on_enter()
{
	CharacterManager::instence()->get_enemy()->set_animation("run");

	play_audio(_T("enemy_run"),true);
}

void EnemyRunState::on_update(float delta)
{
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();

	const Vector2D& pos_enemy = enemy->get_position();
	const Vector2D& pos_player = CharacterManager::instence()->get_player()->get_position();
	enemy->set_velocity({pos_enemy.x<pos_player.x?SPEED_RUN:-SPEED_RUN ,0});

	if (enemy->get_hp() <= 0)
		enemy->switch_state("dead");
	else if (abs(pos_enemy.x-pos_player.x)<=MIN_DIS) {
		int rand_num = range_random(0, 100);
		if (enemy->get_hp() > 5) {
			if (rand_num <= 75)
				enemy->switch_state("squat");
			else
				enemy->switch_state("throw_silk");
		}
		else {
			if (rand_num <= 75)
				enemy->switch_state("throw_silk");
			else
				enemy->switch_state("squat");
		}
		stop_audio(_T("enemy_run"));
	}
}

void EnemyRunState::on_exit()
{
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();
	enemy->set_velocity({ 0,0 });
}

//！！！！！！！！！！！！！！！！！！！！！！！！

EnemySquatState::EnemySquatState()
{
	timer.set_wait_time(0.5f);
	timer.set_one_shot(true);
	timer.set_on_timeout(
		[&]() {
			Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();
			enemy->switch_state("dash_on_floor");
		}
	);
}

EnemySquatState::~EnemySquatState()
{
}

void EnemySquatState::on_enter()
{
	CharacterManager::instence()->get_enemy()->set_animation("squat");
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();

	enemy->set_facing_left(enemy->get_position().x > CharacterManager::instence()->get_player()->get_position().x);
	timer.restart();
}

void EnemySquatState::on_update(float delta)
{
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();

	timer.on_update(delta);

	if (enemy->get_hp() <= 0)
		enemy->switch_state("dead");

}
//！！！！！！！！！！！！！！！！！！！！！！！！

EnemyThrowBarbState::EnemyThrowBarbState()
{
	timer.set_wait_time(0.8f);
	timer.set_one_shot(true);
	timer.set_on_timeout(
		[&]() {
			Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();
			enemy->switch_state("idle");
			enemy->throw_barbs();
		}
	);
}

EnemyThrowBarbState::~EnemyThrowBarbState()
{
}

void EnemyThrowBarbState::on_enter()
{
	CharacterManager::instence()->get_enemy()->set_animation("throw_barb");

	timer.restart();

	play_audio(_T("enemy_throw_barbs"));
}

void EnemyThrowBarbState::on_update(float delta)
{
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();

	timer.on_update(delta);

	if (enemy->get_hp() <= 0)
		enemy->switch_state("dead");
}
//！！！！！！！！！！！！！！！！！！！！！！！！

EnemyThrowSilkState::EnemyThrowSilkState()
{
	timer.set_wait_time(0.9f);
	timer.set_one_shot(true);
	timer.set_on_timeout(
		[&]() {
			Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();
			
			enemy->set_gravity_enable(true);
			enemy->set_throwing_silk(false);

			if (!enemy->is_on_floor() && enemy->get_hp() > 5 && range_random(0, 100) <= 25)
				enemy->switch_state("aim");
			else if (!enemy->is_on_floor())
				enemy->switch_state("fall");
			else
				enemy->switch_state("idle");
		}
	);
}

EnemyThrowSilkState::~EnemyThrowSilkState()
{
}

void EnemyThrowSilkState::on_enter()
{
	CharacterManager::instence()->get_enemy()->set_animation("throw_silk");
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();

	enemy->set_gravity_enable(false);
	enemy->set_throwing_silk(true);
	enemy->set_velocity({ 0,0 });
	enemy->on_throw_silk();

	timer.restart();

	play_audio(_T("enemy_throw_silk"));
}

void EnemyThrowSilkState::on_update(float delta)
{
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();

	timer.on_update(delta);

	if (enemy->get_hp() <= 0)
		enemy->switch_state("dead");
}
//！！！！！！！！！！！！！！！！！！！！！！！！

EnemyThrowSwordState::EnemyThrowSwordState()
{
	timer_throw.set_wait_time(0.65f);
	timer_throw.set_one_shot(true);
	timer_throw.set_on_timeout(
		[&]() {
			Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();
			
			enemy->throw_sword();

			play_audio(_T("enemy_throw_sword"));
		}
	);

	timer_switch.set_wait_time(1.0f);
	timer_switch.set_one_shot(true);
	timer_switch.set_on_timeout(
		[&]() {
			Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();

			int rand_num = range_random(0, 100);

			if (enemy->get_hp()>5) {
				if (rand_num <= 50)
					enemy->switch_state("squat");
				else if (rand_num <= 80)
					enemy->switch_state("jump");
				else
					enemy->switch_state("idle");
			}
			else {
				if (rand_num <= 50)
					enemy->switch_state("jump");
				else if (rand_num <= 80)
					enemy->switch_state("throw_silk");
				else
					enemy->switch_state("idle");
			}
		}
	);
}

EnemyThrowSwordState::~EnemyThrowSwordState()
{
}

void EnemyThrowSwordState::on_enter()
{
	CharacterManager::instence()->get_enemy()->set_animation("throw_sword");

	timer_throw.restart();
	timer_switch.restart();
}

void EnemyThrowSwordState::on_update(float delta)
{
	Enemy* enemy = (Enemy*)CharacterManager::instence()->get_enemy();

	timer_throw.on_update(delta);
	timer_switch.on_update(delta);

	if (enemy->get_hp() <= 0)
		enemy->switch_state("dead");
}
