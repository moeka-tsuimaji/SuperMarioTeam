#include "Mountain_Left.h"
#include "../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "DxLib.h"

Mountain_Left::Mountain_Left()
{

}

Mountain_Left::~Mountain_Left()
{

}

void Mountain_Left::Initialize()
{
	//画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/mountain_left.png")[0];
}

void Mountain_Left::Update(float delta_second)
{
	// 入力情報を取得
	InputManager* input = InputManager::GetInstance();

	if (input->GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x = SCROLL_SPEED;
		location += velocity;
	}
}

void Mountain_Left::Draw(const Vector2D& screen_offset) const
{
	//オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}
