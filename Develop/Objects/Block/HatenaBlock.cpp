#include "HatenaBlock.h"
#include "../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "DxLib.h"

HatenaBlock::HatenaBlock()
{

}

HatenaBlock::~HatenaBlock()
{

}

void HatenaBlock::Initialize()
{
	//画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	//image = rm->GetImages("Resource/Images/Block/hatena.png")[0];
	hatena = rm->GetImages("Resource/Images/Block/hatena.png",4,4,1,32,32);
	image = hatena[0];

	// 可動性の設定
	mobility = eMobilityType::Stationary;

	//当たり判定を設定
	collision.SetSize(D_OBJECT_SIZE, D_OBJECT_SIZE);

	//オブジェクトタイプを設定
	collision.SetObjectType(eObjectType::eBlock);

	//当たるオブジェクトタイプを設定
	collision.SetHitObjectType({ eObjectType::eItem, eObjectType::eEnemy });

	//当たり判定の描画フラグ
	SetDrawCollisionBox(false);
}

void HatenaBlock::Update(float delta_second)
{
	//当たり判定の位置を取得する
	Vector2D collisionPosition = collision.GetPosition();
	//当たり判定の位置を更新する
	collision.SetPosition(location);
}

void HatenaBlock::Draw(const Vector2D& screen_offset) const
{
	//オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}

void HatenaBlock::OnHitCollision(GameObjectManager* hit_object)
{
	//
}