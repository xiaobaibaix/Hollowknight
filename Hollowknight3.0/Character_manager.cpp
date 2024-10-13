#include "Character_manager.h"
#include "Player.h"
#include "Bullet_time_manager.h"
#include "Enemy.h"

Character* CharacterManager::get_enemy() {
	return enemy;
}

Character* CharacterManager::get_player() {
	return player;
}

void CharacterManager::on_input(const ExMessage& msg) {
	player->on_input(msg);
}

void CharacterManager::on_update(float delta) {
	player->on_update(delta);
	enemy->on_update(delta);
}

void CharacterManager::on_render() {
	Bullet_time_manager::instence()->post_process();
	player->on_render();
	enemy->on_render();
}

CharacterManager::CharacterManager() {
	player = new Player();
	enemy = new Enemy();
}

CharacterManager::~CharacterManager() {
	delete enemy;
	delete player;
}
