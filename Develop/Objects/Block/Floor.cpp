#include "Floor.h"
#include "../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "DxLib.h"

Floor::Floor()
{

}

Floor::~Floor()
{

}

void Floor::Initialize()
{
	//画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/Block/floor.png")[0];

	// 可動性の設定
	mobility = eMobilityType::Stationary;

	//当たり判定を設定
	collision.SetSize(D_OBJECT_SIZE, D_OBJECT_SIZE);

	//オブジェクトタイプを設定
	collision.SetObjectType(eObjectType::eGround);

	//当たるオブジェクトタイプを設定
	collision.SetHitObjectType({ eObjectType::eItem, eObjectType::eEnemy });

	//当たり判定の描画フラグ
	SetDrawCollisionBox(false);
}

void Floor::Update(float delta_second)
{
	//当たり判定の位置を取得する
	Vector2D collisionPosition = collision.GetPosition();
	//当たり判定の位置を更新する
	collision.SetPosition(location);
}

void Floor::Draw(const Vector2D& screen_offset) const
{
	//オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}

void Floor::OnHitCollision(GameObjectManager* hit_object)
{
	//
}