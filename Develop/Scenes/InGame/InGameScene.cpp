#include "InGameScene.h"
#include "../../Objects/Player/Player.h"
#include "../../Objects/Enemy/Kuribo.h"
#include "../../Objects/Pole/Flag.h"
#include "../../Objects/Pole/Pole.h"
#include "../../Objects/Pole/Pole_down.h"
#include "../../Objects/Block/Block.h"
#include "../../Objects/Block/HatenaBlock.h"
#include "../../Objects/Block/Floor.h"
#include "../../Objects/Block/Kai_block.h"
#include "../../Objects/Sky/Sora.h"
#include "../../Objects/Sky/Cloud1.h"
#include "../../Objects/Sky/Cloud2.h"
#include "../../Objects/Sky/Cloud3.h"
#include "../../Objects/Sky/Cloud4.h"
#include "../../Objects/Sky/Cloud5.h"
#include "../../Objects/Sky/Cloud6.h"
#include "../../Objects/Wood/Ha0.h"
#include "../../Objects/Wood/Ha1.h"
#include "../../Objects/Wood/Ha2.h"
#include "../../Objects/Wood/Mountain_Left.h"
#include "../../Objects/Wood/Mountain_Right.h"
#include "../../Objects/Wood/Mountain_Surface.h"
#include "../../Objects/Wood/Mountain_Surface1.h"
#include "../../Objects/Wood/Mountain_Surface2.h"
#include "../../Objects/Wood/Mountain_Up.h"
#include "../../Objects/Dokan/Dokan_left_down.h"
#include "../../Objects/Dokan/Dokan_left_up.h"
#include "../../Objects/Dokan/Dokan_right_down.h"
#include "../../Objects/Dokan/Dokan_right_up.h"
#include "../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "DxLib.h"
#include <fstream>

InGameScene::InGameScene()
	: back_ground_image(NULL)
	, back_ground_sound(NULL)
	, pause_flag(false)
	,player()
	,kuribo()
{

}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	//ステージデータ読み込み生成処理
	LoadMarioStageMapCSV();

	// スクリーンオフセットを設定
//	screen_offset.y = D_OBJECT_SIZE * 3.0f;

	// 背景画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	back_ground_image = rm->GetImages("Resource/Images/配置素材/NES---Super-Mario-Bros---World-1-1（修正版）.png")[0];
	
	// 既にBGMが流れていれば止める
	
	
	// BGMの読み込み
	back_ground_sound = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");

	PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK);

	//プレイヤーを生成する
	player = CreateObject<Player>(Vector2D(100.0f, 403.0f));

	//クリボーを生成する
	kuribo = CreateObject<Kuribo>(Vector2D(750.0f, 403.0f));
}

eSceneType InGameScene::Update(const float& delta_second)
{
	// 入力情報を取得
	InputManager* input = InputManager::GetInstance();

	if (input->GetKeyDown(KEY_INPUT_P) || input->GetButtonDown(XINPUT_BUTTON_START))
	{
		pause_flag = !pause_flag;
	}

	if (CheckSoundMem(back_ground_sound) != TRUE)
	{
		PlaySoundMem(back_ground_sound, DX_PLAYTYPE_LOOP, TRUE);
	}

	//if (!pause_flag)
	//{
	//	//親クラスの更新処理を呼び出す
	//	__super::Update(delta_second);

	//	if (player->GetDestroy())
	//	{
	//		return eSceneType::re_start;
	//	}
	//}
	//// リザルトシーンに遷移する
	//if (input->GetKeyDown(KEY_INPUT_SPACE))
	//{
	//	return eSceneType::result;
	//}
	//if (input->GetButtonDown(XINPUT_BUTTON_START))
	//{
	//	return eSceneType::result;
	//}

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

void InGameScene::Draw() const
{
	//// 背景画像の描画
	//DrawRotaGraph(0, 480, 2.0, 0.0, back_ground_image, TRUE);

	// 親クラスの描画処理を呼び出す
	__super::Draw();

	DrawFormatString(640, 240, GetColor(255, 255, 255), "インゲーム画面です");

}

void InGameScene::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::in_game;
}

void InGameScene::LoadMarioStageMapCSV()
{
	FILE* fp = NULL;
	std::string file_name = "Resource/Map/MarioStageMap.csv";

	//指定されたファイルを開く
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	//エラーチェック
	if (result != 0)
	{
		throw (file_name + "が開けません");
	}

	int x = 0;
	int y = 0;

	//ファイル内の文字を確認する
	while (true)
	{
		//ファイルから1文字抽出する
		int c = fgetc(fp);

		//抽出した文字がEOFならループ終了
		if (c == EOF)
		{
			break;
		}
		////Aなら、マリオを生成
		//else if (c == 'A')
		//{
		//	Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
		//	CreateObject<Player>(generate_location);
		//	x++;
		//}
		
		//bなら、ブロックを生成
		else if (c == 'b')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Block>(generate_location);
			x++;
		}
		//?なら、ハテナブロックを生成
		else if (c == '?')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<HatenaBlock>(generate_location);
			x++;
		}
		//_なら、茶色床を作成
		else if (c == '_')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Floor>(generate_location);
			x++;
		}
		//^なら、kai_blockを作成
		else if (c == '^')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Kai_block>(generate_location);
			x++;
		}
		//sなら、空を生成
		else if (c == 's')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Sora>(generate_location);
			x++;
		}
		//*なら、cloud1を生成
		else if (c == '*')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Cloud1>(generate_location);
			x++;
		}
		//cなら、cloud2を生成
		else if (c == 'c')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Cloud2>(generate_location);
			x++;
		}
		//lなら、cloud3を生成
		else if (c == 'l')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Cloud3>(generate_location);
			x++;
		}
		//oなら、cloud4を生成
		else if (c == 'o')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Cloud4>(generate_location);
			x++;
		}
		//uなら、cloud5を生成
		else if (c == 'u')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Cloud5>(generate_location);
			x++;
		}
		//dなら、cloud6を生成
		else if (c == 'd')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Cloud6>(generate_location);
			x++;
		}
		//#なら、ha0を生成
		else if (c == '#')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Ha0>(generate_location);
			x++;
		}
		//hなら、ha1を生成
		else if (c == 'h')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Ha1>(generate_location);
			x++;
		}
		//aなら、ha2を生成
		else if (c == 'a')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Ha2>(generate_location);
			x++;
		}
		//aなら、mountain_leftを生成
		else if (c == '+')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Mountain_Left>(generate_location);
			x++;
		}
		//aなら、mountain_rightを生成
		else if (c == 'M')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Mountain_Right>(generate_location);
			x++;
		}
		//aなら、mountain_surfaceを生成
		else if (c == 'O')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Mountain_Surface>(generate_location);
			x++;
		}
		//aなら、mountain_surface1を生成
		else if (c == 'U')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Mountain_Surface1>(generate_location);
			x++;
		}
		//aなら、mountain_surface2を生成
		else if (c == 'N')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Mountain_Surface2>(generate_location);
			x++;
		}
		//aなら、mountain_upを生成
		else if (c == 'T')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Mountain_Up>(generate_location);
			x++;
		}
		//%なら、dokan_left_downを生成
		else if (c == 'D')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Dokan_left_down>(generate_location);
			x++;
		}
			//Dなら、dokan_left_upを生成
		else if (c == '%')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Dokan_left_up>(generate_location);
			x++;
		}
		//Kなら、dokan_right_downを生成
		else if (c == 'K')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Dokan_right_down>(generate_location);
			x++;
		}
		//Aなら、dokan_right_upを生成
		else if (c == 'A')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Dokan_right_up>(generate_location);
			x++;
		}
		//fなら、flag.pngを生成
		else if (c == 'f')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Flag>(generate_location);
			x++;
		}
		//Aなら、pole_downを生成
		else if (c == 'p')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Pole_down>(generate_location);
			x++;
		}
		//Aなら、dokan_right_upを生成
		else if (c == 'P')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Pole>(generate_location);
			x++;
		}
		//空白文字なら、生成しないで次の文字を見る
		else if (c == ' ')
		{
			x++;
		}
		//改行文字なら、次の行を見る
		else if (c == '\n')
		{
			x = 0;
			y++;
		}
	}

	// 開いたファイルを閉じる
	fclose(fp);
}