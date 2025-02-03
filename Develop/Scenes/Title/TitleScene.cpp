#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "../../Objects/UI/Mario.h"
#include "../../Objects/UI/Time.h"
#include "../../Objects/UI/World.h"
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

	//mario_Uiを生成する
	mario = CreateObject<Mario>(Vector2D(150.0f, 15.0f));
	//time_Uiを生成する
	time = CreateObject<Time>(Vector2D(500.0f, 15.0f));
	//_Uiを生成する
	world = CreateObject<World>(Vector2D(380.0f, 15.0f));
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

	// 親クラスの描画処理を呼び出す
	__super::Draw();

	//// UI系の描画処理
	//if (pause_flag)
	//{
	//	DrawString(10, 10, " P A U S E ", GetColor(255, 255, 255), TRUE);
	//}
}

void TitleScene::Finalize()
{
	// 親クラスの終了時処理を呼び出す
 	__super::Finalize();

	StopSoundMem(back_ground_sound);
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::title;
}
