#include "Dokan_left_up.h"
#include "../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "DxLib.h"

Dokan_left_up::Dokan_left_up()
{

}

Dokan_left_up::~Dokan_left_up()
{

}

void Dokan_left_up::Initialize()
{
	//�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/dokan_left_up.png")[0];
}

void Dokan_left_up::Update(float delta_second)
{
	// ���͏����擾
	InputManager* input = InputManager::GetInstance();

	/*if (input->GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x = -0.3f;
		location += velocity;
	}*/
}

void Dokan_left_up::Draw(const Vector2D& screen_offset) const
{
	//�I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}

