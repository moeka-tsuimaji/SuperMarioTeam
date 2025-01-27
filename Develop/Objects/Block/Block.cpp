#include "Block.h"
#include"../../Utility/ResourceManager.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

Block::Block()
{

}

Block::~Block()
{

}

void Block::Initialize()
{
	//�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/Block/block.png")[0];
	velocity = 0.0f;
}

void Block::Update(float delta_second)
{
	// ���͏����擾
	InputManager* input = InputManager::GetInstance();

	
	if (input->GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x = -0.3f;
		location += velocity;
	}
}

void Block::Draw(const Vector2D& screen_offset) const
{
	

	//�I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);

	
}

void Block::OnHitCollision(GameObjectManager* hit_object)
{
	//
}