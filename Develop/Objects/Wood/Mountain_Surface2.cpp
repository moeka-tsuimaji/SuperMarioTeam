#include "Mountain_Surface2.h"
#include "../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "DxLib.h"

Mountain_Surface2::Mountain_Surface2()
{

}

Mountain_Surface2::~Mountain_Surface2()
{

}

void Mountain_Surface2::Initialize()
{
	//画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/mountain_surface2.png")[0];
}

void Mountain_Surface2::Update(float delta_second)
{
	// 入力情報を取得
	InputManager* input = InputManager::GetInstance();

	if (input->GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x = SCROLL_SPEED;
		location += velocity;
	}
}

void Mountain_Surface2::Draw(const Vector2D& screen_offset) const
{
	//オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}

