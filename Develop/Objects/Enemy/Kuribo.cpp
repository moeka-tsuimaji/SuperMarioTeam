#include "Kuribo.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/Application.h"
#include "DxLib.h"

#define D_KURIBO_SPEED	(20.0f)

Kuribo* Kuribo::instance = nullptr;

Kuribo::Kuribo() :
	move_animation(),
	dying_animation(),
	k_velocity(0.0f),
	kuribo_state(eKuriboState::WALK),
	now_direction_state(eDirectionState::LEFT),
	next_direction_state(eDirectionState::LEFT),
	food_count(0),
	animation_time(0.0f),
	animation_count(0),
	//old_panel(ePanelID::NONE),
	is_power_up(false),
	is_destroy(false)
{

}

Kuribo::~Kuribo()
{

}

void Kuribo::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);

	
	//当たり判定を設定
	collision.SetSize(D_OBJECT_SIZE, D_OBJECT_SIZE);

	//オブジェクトタイプを設定
	collision.SetObjectType(eObjectType::eEnemy);

	//当たるオブジェクトタイプを設定
	collision.SetHitObjectType({ eObjectType::ePlayer, eObjectType::eGround });

	//当たり判定の描画フラグ
	SetDrawCollisionBox(false);

	// レイヤーの設定
	z_layer = 4;

	// 可動性の設定
	mobility = eMobilityType::Movable;

	image = move_animation[0];

	kuribo_state = eKuriboState::WALK;


	//エラーチェック
	if (move_animation[0] == -1)
	{
		throw("マリオの画像がありません\n");
	}
}

void Kuribo::Update(float delta_second)
{
	//当たり判定の位置を取得する
	Vector2D collisionPosition = collision.GetPosition();
	//当たり判定の位置を更新する
	collision.SetPosition(location);


	//入力状態の取得
	Movement(delta_second);
	//アニメーションの取得
	if (kuribo_state == WALK)
	{
		AnimationControl(delta_second);
	}
	//止まってるとき
	else
	{
		image = move_animation[0];
	}
}

void Kuribo::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

void Kuribo::Finalize()
{
	// 動的配列の解放
	move_animation.clear();
	dying_animation.clear();
}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void Kuribo::OnHitCollision(GameObjectManager* hit_object)
{
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		//kuriboを消滅する
		owner_scene->DestroyObject(this);
	}
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Kuribo::Movement(float delta_second)
{
	// 入力状態の取得
	InputManager* input = InputManager::GetInstance();

	
		k_velocity.x = -1.0f;


	//// 現在パネルの状態を確認
	//ePanelID panel = StageData::GetPanelData(location);

	// 前回座標の更新
	old_location = location;

	//// 前回パネルの更新
	//old_panel = panel;

	// 移動量 * 速さ * 時間 で移動先を決定する
	location += k_velocity * D_KURIBO_SPEED * delta_second;


	if (location.y > 403)
	{
		location.y = 403;
	}

	k_velocity.y += 0.12f;
}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Kuribo::AnimationControl(float delta_second)
{
	// 移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 8.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}
		// 画像の設定
		image = move_animation[animation_num[animation_count]];
	}
}

//プレイヤーのインスタンス取得
Kuribo* Kuribo::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Kuribo();
	}
	return instance;
}