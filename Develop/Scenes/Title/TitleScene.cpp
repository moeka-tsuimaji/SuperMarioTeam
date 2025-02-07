#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "DxLib.h"

TitleScene::TitleScene()
	: back_ground_image(NULL)
	, back_ground_sound(NULL)
	,mario()
	,time()
	,world()
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	//// スクリーンオフセットを設定
	//screen_offset.y = D_OBJECT_SIZE * 3.0f;

	// 背景画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	back_ground_image = rm->GetImages("Resource/Images/title.png")[0];
	// BGMの読み込み
	back_ground_sound = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");

	PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK);

	//UIの読み込み
	mario = rm->GetImages("Resource/Images/UI/name_mario.png")[0];
	time = rm->GetImages("Resource/Images/UI/time.png")[0];
	world = rm->GetImages("Resource/Images/UI/world.png")[0];
}

eSceneType TitleScene::Update(const float& delta_second)
{
	// 入力情報を取得
	InputManager* input = InputManager::GetInstance();

	// インゲームシーンに遷移する
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::in_game;
	}
	if (input->GetButtonDown(XINPUT_BUTTON_START))
	{
		return eSceneType::in_game;
	}

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

void TitleScene::Draw() const
{
	// 背景画像の描画
	DrawRotaGraph(320, 240, 1.0, 0.0, back_ground_image, TRUE);
	//UIの描画
	DrawRotaGraph(150, 15, 1.0, 0.0, mario, TRUE);
	DrawRotaGraph(500, 15, 1.0, 0.0, time, TRUE);
	DrawRotaGraph(380, 15, 1.0, 0.0, world, TRUE);

	// 親クラスの描画処理を呼び出す
	__super::Draw();

}

void TitleScene::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::title;
}
