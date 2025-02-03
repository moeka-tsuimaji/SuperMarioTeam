#include "Mountain_Right.h"
#include "../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "DxLib.h"

Mountain_Right::Mountain_Right()
{

}

Mountain_Right::~Mountain_Right()
{

}

void Mountain_Right::Initialize()
{
	//�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/mountain_right.png")[0];
}

void Mountain_Right::Update(float delta_second)
{
	// ���͏����擾
	InputManager* input = InputManager::GetInstance();

	/*if (input->GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x = -0.3f;
		location += velocity;
	}*/
}

void Mountain_Right::Draw(const Vector2D& screen_offset) const
{
	//�I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}
