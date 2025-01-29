#include "GameObjectManager.h"
#include "../Utility/InputManager.h"
#include "../Scenes/SceneBase.h"
#include "DxLib.h"

GameObjectManager::GameObjectManager() :
	owner_scene(nullptr),
	location(0.0f),
	image(NULL),
	z_layer(0),
	mobility(eMobilityType::Stationary),
	velocity(0),
	flip_flag(false),
	draw_collision_box(false)
{

}

GameObjectManager::~GameObjectManager()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void GameObjectManager::Initialize()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void GameObjectManager::Update(float delta_second)
{
	
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset">オフセット値</param>
void GameObjectManager::Draw(const Vector2D& screen_offset) const
{
	// オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE, this->flip_flag);
}

/// <summary>
/// デバッグ用当たり判定描画処理
/// </summary>
void GameObjectManager::DrawCollision(const Vector2D& screen_offset) const
{
	if (draw_collision_box)
	{
		//当たり判定の位置を取得する
		Vector2D min = collision.GetPosition() - (collision.box_size / 2) + collision.pivot + screen_offset;
		Vector2D max = collision.GetPosition() + (collision.box_size / 2) + collision.pivot + screen_offset;

		//当たり判定を描画する
		DrawBoxAA(min.x, min.y, max.x, max.y, GetColor(255, 0, 0), false);
	}

}

/// <summary>
/// 終了時処理
/// </summary>
void GameObjectManager::Finalize()
{

}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void GameObjectManager::OnHitCollision(GameObjectManager* hit_object)
{

}

/// <summary>
/// 所有シーン情報の設定
/// </summary>
/// <param name="scene">所有シーン情報</param>
void GameObjectManager::SetOwnerScene(SceneBase* scene)
{
	this->owner_scene = scene;
}

/// <summary>
/// 位置座標取得処理
/// </summary>
/// <returns>位置座標情報</returns>
const Vector2D& GameObjectManager::GetLocation() const
{
	return location;
}

/// <summary>
/// 位置情報変更処理
/// </summary>
/// <param name="location">変更したい位置情報</param>
void GameObjectManager::SetLocation(const Vector2D& location)
{
	this->location = location;
}

/// <summary>
/// 当たり判定取得処理
/// </summary>
/// <returns>当たり判定情報</returns>
Collision GameObjectManager::GetCollision() const
{
	return collision;
}

/// <summary>
/// Zレイヤー情報取得処理
/// </summary>
/// <returns>Zレイヤー情報</returns>
const int GameObjectManager::GetZLayer() const
{
	return z_layer;
}

/// <summary>
/// 可動性情報の取得処理
/// </summary>
/// <returns>可動性情報</returns>
const eMobilityType GameObjectManager::GetMobility() const
{
	return mobility;
}

/// <summary>
/// デバッグ用当たり判定表示フラグを設定する
/// </summary>
void GameObjectManager::SetDrawCollisionBox(bool flag)
{
	draw_collision_box = flag;
}