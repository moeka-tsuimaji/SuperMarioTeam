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
	//画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/Block/block.png")[0];
	velocity = 0.0f;
}

void Block::Update(float delta_second)
{
	// 入力情報を取得
	InputManager* input = InputManager::GetInstance();

	
	if (input->GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x = -0.3f;
		location += velocity;
	}
}

void Block::Draw(const Vector2D& screen_offset) const
{
	

	//オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);

	
}

void Block::OnHitCollision(GameObjectManager* hit_object)
{
	//
}