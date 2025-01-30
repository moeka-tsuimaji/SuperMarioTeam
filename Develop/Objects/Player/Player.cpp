#include "Player.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/Application.h"
#include "DxLib.h"


#define D_PLAYER_SPEED	(50.0f)

Player* Player::instance = nullptr;

Player::Player() :
	move_animation(),
	dying_animation(),
	p_velocity(0.0f),
	player_state(ePlayerState::MOVE),
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

Player::~Player()
{

}

void Player::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);


	//当たり判定を設定
	collision.SetSize(D_OBJECT_SIZE, D_OBJECT_SIZE);

	//オブジェクトタイプを設定
	collision.SetObjectType(eObjectType::ePlayer);

	//当たるオブジェクトタイプを設定
	collision.SetHitObjectType({ eObjectType::eItem, eObjectType::eGround, eObjectType::eEnemy });

	//当たり判定の描画フラグ
	SetDrawCollisionBox(true);


	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;

	image = move_animation[0];

	//エラーチェック
	if (move_animation[0] == -1)
	{
		throw("マリオの画像がありません\n");
	}
}

void Player::Update(float delta_second)
{
	//当たり判定の位置を取得する
	Vector2D collisionPosition = collision.GetPosition();
	//当たり判定の位置を更新する
	collision.SetPosition(location);

	//入力状態の取得
	Movement(delta_second);
	//アニメーションの取得
	if (player_state == MOVE)
	{
		AnimationControl(delta_second);
	}
	//止まってるとき
	else
	{
		image = move_animation[0];
	}
}

void Player::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

void Player::Finalize()
{
	// 動的配列の解放
	move_animation.clear();
	dying_animation.clear();
}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void Player::OnHitCollision(GameObjectManager* hit_object)
{
	if (hit_object->GetCollision().object_type == eObjectType::eEnemy)
	{
		//is_destroy = true;
		//player_state = DIE;
	}
}

/// <summary>
/// 餌を食べた数取得
/// </summary>
/// <returns>餌を食べた数</returns>
int Player::GetFoodCount() const
{
	return food_count;
}

/// <summary>
/// プレイヤーの状態を取得する
/// </summary>
/// <returns>プレイヤーの状態</returns>
ePlayerState Player::GetPlayerState() const
{
	return player_state;
}

/// <summary>
/// プレイヤーがパワーアップしてるか確認する
/// </summary>
/// <returns>プレイヤーの状態</returns>
bool Player::GetPowerUp() const
{
	return is_power_up;
}

/// <summary>
/// パワーダウンさせる
/// </summary>
void Player::SetPowerDown()
{
	is_power_up = false;
}

bool Player::GetDestroy() const
{
	return is_destroy;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::Movement(float delta_second)
{
	// 入力状態の取得
	InputManager* input = InputManager::GetInstance();

	//移動処理
	if (input->GetKey(KEY_INPUT_RIGHT))
	{
		flip_flag = false;
		player_state = ePlayerState::MOVE;
		p_velocity.x = 1.0f;
	}
	else if (input->GetKey(KEY_INPUT_LEFT))
	{
		flip_flag = true;
		player_state = ePlayerState::MOVE;
		p_velocity.x = -1.0f;
	}
	else
	{
		p_velocity.x = 0.0f;
		player_state = ePlayerState::IDLE;
	}
	
	
	//// 現在パネルの状態を確認
	//ePanelID panel = StageData::GetPanelData(location);

	// 前回座標の更新
	old_location = location;

	//// 前回パネルの更新
	//old_panel = panel;

	// 移動量 * 速さ * 時間 で移動先を決定する
	location += p_velocity * D_PLAYER_SPEED * delta_second;

	//画面の中心から右側に行かないようにする
	if (location.x >= 320)
	{
		location.x = 320;
	}
	else if (location.x <= 10)
	{
		location.x = 10;
	}
}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::AnimationControl(float delta_second)
{
	// 移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 8.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 4)
		{
			animation_count = 0;
		}
		// 画像の設定
		image = move_animation[animation_num[animation_count]];
	}
}

//プレイヤーのインスタンス取得
Player* Player::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Player();
	}
	return instance;
}