#include "Collision_box.h"

void CollisionBox::set_enable(bool flag) {
	this->enable = flag;
}

void CollisionBox::set_layer_src(CollisionLayer layer) {
	layer_src = layer;
}

void CollisionBox::set_layer_dst(CollisionLayer layer) {
	layer_dst = layer;
}

void CollisionBox::set_on_collide(std::function<void()> on_collide) {
	this->on_collide = on_collide;
}

void CollisionBox::set_size(const Vector2D& vec) {
	size = vec;
}

const Vector2D& CollisionBox::get_size() {
	return size;
}

void CollisionBox::set_position(const Vector2D& vec) {
	position = vec;
}
