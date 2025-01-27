#include "Kai_block.h"
#include"../../Utility/ResourceManager.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

Kai_block::Kai_block()
{

}

Kai_block::~Kai_block()
{

}

void Kai_block::Initialize()
{
	//�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/Block/kai_block.png")[0];
	velocity = 0.0f;
}

void Kai_block::Update(float delta_second)
{
	// ���͏����擾
	InputManager* input = InputManager::GetInstance();

	if (input->GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x = -0.3f;
		location += velocity;
	}

}

void Kai_block::Draw(const Vector2D& screen_offset) const
{


	//�I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);


}

void Kai_block::OnHitCollision(GameObjectManager* hit_object)
{
	//
}