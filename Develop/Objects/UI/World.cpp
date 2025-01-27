#include "World.h"
#include "../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "DxLib.h"

World::World()
{

}

World::~World()
{

}

void World::Initialize()
{
	//�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/UI/world.png")[0];
}

void World::Update(float delta_second)
{

}

void World::Draw(const Vector2D& screen_offset) const
{
	//�I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}

