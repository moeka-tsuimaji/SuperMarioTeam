#include "ResultScene.h"
#include "../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "DxLib.h"

ResultScene::ResultScene()
	: back_ground_image(NULL)
	, back_ground_sound(NULL)
{

}

ResultScene::~ResultScene()
{

}

void ResultScene::Initialize()
{
	// スクリーンオフセットを設定
	screen_offset.y = D_OBJECT_SIZE * 3.0f;

	// 背景画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	back_ground_image = rm->GetImages("Resource/Images/siro1.png")[0];
	// BGMの読み込み
	back_ground_sound = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");

	PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK);
}

eSceneType ResultScene::Update(const float& delta_second)
{
	// 入力情報を取得
	InputManager* input = InputManager::GetInstance();

	// タイトルシーンに遷移する
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::title;
	}
	if (input->GetButtonDown(XINPUT_BUTTON_START))
	{
		return eSceneType::title;
	}

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

void ResultScene::Draw() const
{
	// 背景画像の描画
	DrawRotaGraph(320, 240, 1.0, 0.0, back_ground_image, TRUE);

	// 親クラスの描画処理を呼び出す
	__super::Draw();

	DrawFormatString(640, 240, GetColor(255, 255, 255), "インゲーム画面です");

}

void ResultScene::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

const eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::result;
}
