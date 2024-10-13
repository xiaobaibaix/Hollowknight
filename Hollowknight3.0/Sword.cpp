#include "Sword.h"
#include "ResourcesManager.h"
#include "CollisionManager.h"

Sword::Sword(const Vector2D& pos, bool move_left)
{
	animation.set_interval(0.1f);
	animation.set_loop(true);
	animation.set_ancher_mode(Animation::AncherMode::Centerd);
	animation.add_frame(ResourcesManager::instence()->find_atlas(move_left ? "enemy_sword_left" : "enemy_sword_right"));

	collsition_box = CollisionManager::instence()->create_collision_box();
	collsition_box->set_layer_src(CollisionLayer::None);
	collsition_box->set_layer_dst(CollisionLayer::Player);
	collsition_box->set_size({ 195,10 });

	this->position = pos;
	this->Velovity = {move_left? -SPEED_MOVE: SPEED_MOVE,0};
}

Sword::~Sword()
{
	CollisionManager::instence()->destory_collision_box(collsition_box);
}

void Sword::on_update(float delta)
{
	position += Velovity * delta;
	animation.set_position(position);
	collsition_box->set_position(position);

	animation.on_update(delta);

	if (position.x <= -200 || position.x >= getwidth() + 200)
		is_valid = false;
}

void Sword::on_render()
{
	animation.on_render();
}
