#pragma once

#include "Vector2D.h"
#include "Collision_layer.h"

#include <functional>

class CollisionManager;
class CollisionBox {
	friend class CollisionManager;
private:
	CollisionBox() = default;
	~CollisionBox() = default;

private:
	Vector2D size;
	Vector2D position;
	bool enable = true;
	std::function<void()> on_collide;
	CollisionLayer layer_src = CollisionLayer::None;
	CollisionLayer layer_dst = CollisionLayer::None;


public:
	void set_enable(bool flag);

	void set_layer_src(CollisionLayer layer);

	void set_layer_dst(CollisionLayer layer);

	void set_on_collide(std::function<void()> on_collide);

	void set_size(const Vector2D& vec);

	const Vector2D& get_size();

	void set_position(const Vector2D& vec);

};