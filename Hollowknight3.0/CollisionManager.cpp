#include "CollisionManager.h"

#include <graphics.h>

CollisionBox* CollisionManager::create_collision_box() {
	CollisionBox* box = new CollisionBox();
	collision_box_list.push_back(box);
	return box;
}

void CollisionManager::destory_collision_box(CollisionBox* box) {
	collision_box_list.erase(std::remove(collision_box_list.begin(),
		collision_box_list.end(), box));
}

void CollisionManager::process_collide() {
	for (CollisionBox* box_src : collision_box_list) {
		if (!box_src->enable || box_src->layer_dst == CollisionLayer::None)
			continue;

		for (CollisionBox* box_dst : collision_box_list) {
			if (!box_dst->enable || box_dst == box_src ||
				box_src->layer_dst != box_dst->layer_src)
				continue;

			bool is_collide_x = (
				max(box_src->position.x + box_src->size.x / 2,
					box_dst->position.x + box_dst->size.x / 2)
				- min(box_src->position.x - box_src->size.x / 2,
					box_dst->position.x - box_dst->size.x / 2)
				<= box_src->size.x + box_dst->size.x);
			bool is_collide_y = (
				max(box_src->position.y + box_src->size.y / 2,
					box_dst->position.y + box_dst->size.y / 2)
				- min(box_src->position.y - box_src->size.y / 2,
					box_dst->position.y - box_dst->size.y / 2)
				<= box_src->size.y + box_dst->size.y);

			if (is_collide_x && is_collide_y && box_dst->on_collide)
				box_dst->on_collide();
		}
	}
}

void CollisionManager::on_debug_render() {
	for (CollisionBox* box : collision_box_list) {
		if (!box->enable)continue;
		setlinecolor(box->enable ? RGB(255, 0, 0) : RGB(255, 255, 255));
		rectangle(
			(int)(box->position.x - box->size.x / 2),
			(int)(box->position.y - box->size.y / 2),
			(int)(box->position.x + box->size.x / 2),
			(int)(box->position.y + box->size.y / 2)
		);
	}
}
