#include "Character.h"
#include "CollisionManager.h"


Character::Character()
{
	hit_box = CollisionManager::instence()->create_collision_box();
	hurt_box = CollisionManager::instence()->create_collision_box();

	timer_invulnerable_blink.set_wait_time(0.075f);
	timer_invulnerable_blink.set_one_shot(false);
	timer_invulnerable_blink.set_on_timeout(
		[&]() {
			is_blink_invisible = !is_blink_invisible;
		}
	);

	timer_invulnerable_status.set_wait_time(1.0f);
	timer_invulnerable_status.set_one_shot(true);
	timer_invulnerable_status.set_on_timeout(
		[&]() {
			is_invulnerable = false;
		}
	);
}

Character::~Character()
{
	CollisionManager::instence()->destory_collision_box(hit_box);
	CollisionManager::instence()->destory_collision_box(hurt_box);
}

void Character::decrease_hp() {
	if (is_invulnerable)return;
	hp -= 1;
	if (hp > 0) {
		make_invulnerable();
	}
	on_hurt();
}

int Character::get_hp() {
	return hp;
}

void Character::set_position(const Vector2D& vec) {
	position = vec;
}

const Vector2D& Character::get_position() const {
	return position;
}

void Character::set_velocity(const Vector2D& vec) {
	velocity = vec;
}

const Vector2D& Character::get_velocity() const {
	return velocity;
}

Vector2D Character::get_logic_center() const {
	return Vector2D(position.x, position.y - logic_height / 2);
}

void Character::set_gravity_enable(bool flag) {
	enable_gravity = flag;
}

CollisionBox* Character::get_hit_box() {
	return hit_box;
}

CollisionBox* Character::get_hurt_box() {
	return hurt_box;
}

bool Character::is_on_floor() const {
	return position.y >= FLOOR_Y;
}

float Character::get_floor_y() const {
	return FLOOR_Y;
}

//Ê¹ÎÞµÐ
void Character::make_invulnerable() {
	is_invulnerable = true;
	timer_invulnerable_status.restart();
}

void Character::on_input(const ExMessage& msg) {}

void Character::on_update(float delta) {
	state_machine.on_update(delta);

	if (hp <= 0)
		velocity.x = 0;
	if (enable_gravity)
		velocity.y += GRAVITY * delta;

	position += velocity * delta;

	if (position.y >= FLOOR_Y) {
		position.y = FLOOR_Y;
		velocity.y = 0;
	}

	if (position.x <= 0)position.x = 0;
	if (position.x >= getwidth())position.x = (float)getwidth();

	hurt_box->set_position(get_logic_center());

	timer_invulnerable_status.on_update(delta);
	if (is_invulnerable)timer_invulnerable_blink.on_update(delta);

	if (!current_animation)return;

	Animation& aniamtion = (is_facing_left ? current_animation->left : current_animation->right);

	aniamtion.on_update(delta);
	aniamtion.set_position(position);
}

void Character::on_render() {
	if (!current_animation || (is_invulnerable && is_blink_invisible))return;
	(is_facing_left ? current_animation->left : current_animation->right).on_render();
}

void Character::on_hurt() {}

void Character::switch_state(const std::string& id) {
	state_machine.switch_to(id);
}

void Character::set_animation(const std::string& id) {
	current_animation = &animation_pool[id];

	current_animation->left.reset();
	current_animation->right.reset();
}
