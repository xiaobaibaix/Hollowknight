#pragma once
#include "ManagerSingle.h"
#include "Collision_box.h"

#include <vector>


class CollisionManager: public ManagerSingle<CollisionManager>
{
	friend class ManagerSingle<CollisionManager>;
public:
	CollisionBox* create_collision_box();

	void destory_collision_box(CollisionBox* box);

	void process_collide();

	void on_debug_render();
private:
	CollisionManager() = default;
	~CollisionManager() = default;

private:
	std::vector<CollisionBox*> collision_box_list;
};
