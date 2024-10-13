#pragma once
#include "Character.h"
#include "ManagerSingle.h"

class CharacterManager:public ManagerSingle<CharacterManager>
{
	friend class ManagerSingle<CharacterManager>;
public:
	Character* get_enemy();

	Character* get_player();

	void on_input(const ExMessage& msg);

	void on_update(float delta);

	void on_render();

private:
	CharacterManager();
	~CharacterManager();

private:
	Character* enemy = nullptr;
	Character* player = nullptr;
};
