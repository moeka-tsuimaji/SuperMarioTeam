
#pragma once

#include "../GameObject.h"

// プレイヤー状態
enum eKuriboState
{
	WALK,		// 移動状態
};

/// <summary>
/// プレイヤークラス（パックマン）
/// </summary>
class Kuribo : public GameObject
{
private:
	// 進行方向状態
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};

public:

private:
	std::vector<int> move_animation;		// 移動のアニメーション画像
	std::vector<int> dying_animation;		// 死亡のアニメーション画像
	Vector2D old_location;					// 前回のlocation
	Vector2D k_velocity;						// 移動量
	eKuriboState kuribo_state;				// プレイヤー状態
	eDirectionState now_direction_state;	// 現在進行方向状態
	eDirectionState next_direction_state;	// 次回進行方向状態
	int food_count;							// 餌を食べた数
	float animation_time;					// アニメーション時間
	int animation_count;					// アニメーション添字
	//ePanelID old_panel;						// 前回パネル情報
	bool is_power_up;						// パワー餌を食べたか？
	bool is_destroy;						// 死んだ状態になったか？
	static Kuribo* instance;                //プレイヤーのインスタンス
	// 移動アニメーションの順番
	const int animation_num[4] = { 0, 1, 2, 1, };

public:
	Kuribo();
	virtual ~Kuribo();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectManager* hit_object) override;

public:
	
	/// <summary>
	/// プレイヤーの状態を取得する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	//eKuriboState GetKuriboState() const;

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Movement(float delta_second);
	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void AnimationControl(float delta_second);

public:
	//インスタンス取得
	static Kuribo* GetInstance();
};
