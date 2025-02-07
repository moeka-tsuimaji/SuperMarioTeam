#include "Pole_down.h"
#include "../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "DxLib.h"

Pole_down::Pole_down()
{

}

Pole_down::~Pole_down()
{

}

void Pole_down::Initialize()
{
	//�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/pole_down.png")[0];
}

void Pole_down::Update(float delta_second)
{
	// ���͏����擾
	InputManager* input = InputManager::GetInstance();

	if (input->GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x = SCROLL_SPEED;
		location += velocity;
	}
}

void Pole_down::Draw(const Vector2D& screen_offset) const
{
	//�I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}

void Pole_down::OnHitCollision(GameObjectManager* hit_object)
{
	//
}