#include "Cloud2.h"
#include "../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "DxLib.h"

Cloud2::Cloud2()
{

}

Cloud2::~Cloud2()
{

}

void Cloud2::Initialize()
{
	//�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/cloud2.png")[0];
}

void Cloud2::Update(float delta_second)
{
	// ���͏����擾
	InputManager* input = InputManager::GetInstance();

	if (input->GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x = -0.3f;
		location += velocity;
	}
}

void Cloud2::Draw(const Vector2D& screen_offset) const
{
	//�I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}