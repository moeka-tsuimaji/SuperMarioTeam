#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObject.h"



// メインゲームシーン
class InGameScene : public SceneBase
{
private:
	int back_ground_image;		// 背景画像
	int back_ground_sound;		// BGM
	bool pause_flag;            //一時停止フラグ
	class Player* player;       //プレイヤー情報
	class Kuribo* kuribo;       //クリボー情報

public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;

private:
	/// <summary>
	/// ステージマップ読み込み処理
	/// </summary>
	void LoadMarioStageMapCSV();
};

