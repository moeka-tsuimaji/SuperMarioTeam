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
	//�X�e�[�W�f�[�^�ǂݍ��ݐ�������
	LoadMarioStageMapCSV();

	// �X�N���[���I�t�Z�b�g��ݒ�
//	screen_offset.y = D_OBJECT_SIZE * 3.0f;

	// �w�i�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	back_ground_image = rm->GetImages("Resource/Images/�z�u�f��/NES---Super-Mario-Bros---World-1-1�i�C���Łj.png")[0];
	
	// ����BGM������Ă���Ύ~�߂�
	
	
	// BGM�̓ǂݍ���
	back_ground_sound = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");

	PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK);

	//�v���C���[�𐶐�����
	player = CreateObject<Player>(Vector2D(100.0f, 403.0f));

	//�N���{�[�𐶐�����
	kuribo = CreateObject<Kuribo>(Vector2D(750.0f, 403.0f));
}

eSceneType InGameScene::Update(const float& delta_second)
{
	// ���͏����擾
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
	//	//�e�N���X�̍X�V�������Ăяo��
	//	__super::Update(delta_second);

	//	if (player->GetDestroy())
	//	{
	//		return eSceneType::re_start;
	//	}
	//}
	//// ���U���g�V�[���ɑJ�ڂ���
	//if (input->GetKeyDown(KEY_INPUT_SPACE))
	//{
	//	return eSceneType::result;
	//}
	//if (input->GetButtonDown(XINPUT_BUTTON_START))
	//{
	//	return eSceneType::result;
	//}

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update(delta_second);
}

void InGameScene::Draw() const
{
	//// �w�i�摜�̕`��
	//DrawRotaGraph(0, 480, 2.0, 0.0, back_ground_image, TRUE);

	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

	DrawFormatString(640, 240, GetColor(255, 255, 255), "�C���Q�[����ʂł�");

}

void InGameScene::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
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

	//�w�肳�ꂽ�t�@�C�����J��
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw (file_name + "���J���܂���");
	}

	int x = 0;
	int y = 0;

	//�t�@�C�����̕������m�F����
	while (true)
	{
		//�t�@�C������1�������o����
		int c = fgetc(fp);

		//���o����������EOF�Ȃ烋�[�v�I��
		if (c == EOF)
		{
			break;
		}
		////A�Ȃ�A�}���I�𐶐�
		//else if (c == 'A')
		//{
		//	Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
		//	CreateObject<Player>(generate_location);
		//	x++;
		//}
		
		//b�Ȃ�A�u���b�N�𐶐�
		else if (c == 'b')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Block>(generate_location);
			x++;
		}
		//?�Ȃ�A�n�e�i�u���b�N�𐶐�
		else if (c == '?')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<HatenaBlock>(generate_location);
			x++;
		}
		//_�Ȃ�A���F�����쐬
		else if (c == '_')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Floor>(generate_location);
			x++;
		}
		//^�Ȃ�Akai_block���쐬
		else if (c == '^')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Kai_block>(generate_location);
			x++;
		}
		//s�Ȃ�A��𐶐�
		else if (c == 's')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Sora>(generate_location);
			x++;
		}
		//*�Ȃ�Acloud1�𐶐�
		else if (c == '*')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Cloud1>(generate_location);
			x++;
		}
		//c�Ȃ�Acloud2�𐶐�
		else if (c == 'c')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Cloud2>(generate_location);
			x++;
		}
		//l�Ȃ�Acloud3�𐶐�
		else if (c == 'l')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Cloud3>(generate_location);
			x++;
		}
		//o�Ȃ�Acloud4�𐶐�
		else if (c == 'o')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Cloud4>(generate_location);
			x++;
		}
		//u�Ȃ�Acloud5�𐶐�
		else if (c == 'u')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Cloud5>(generate_location);
			x++;
		}
		//d�Ȃ�Acloud6�𐶐�
		else if (c == 'd')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Cloud6>(generate_location);
			x++;
		}
		//#�Ȃ�Aha0�𐶐�
		else if (c == '#')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Ha0>(generate_location);
			x++;
		}
		//h�Ȃ�Aha1�𐶐�
		else if (c == 'h')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Ha1>(generate_location);
			x++;
		}
		//a�Ȃ�Aha2�𐶐�
		else if (c == 'a')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Ha2>(generate_location);
			x++;
		}
		//a�Ȃ�Amountain_left�𐶐�
		else if (c == '+')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Mountain_Left>(generate_location);
			x++;
		}
		//a�Ȃ�Amountain_right�𐶐�
		else if (c == 'M')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Mountain_Right>(generate_location);
			x++;
		}
		//a�Ȃ�Amountain_surface�𐶐�
		else if (c == 'O')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Mountain_Surface>(generate_location);
			x++;
		}
		//a�Ȃ�Amountain_surface1�𐶐�
		else if (c == 'U')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Mountain_Surface1>(generate_location);
			x++;
		}
		//a�Ȃ�Amountain_surface2�𐶐�
		else if (c == 'N')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Mountain_Surface2>(generate_location);
			x++;
		}
		//a�Ȃ�Amountain_up�𐶐�
		else if (c == 'T')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Mountain_Up>(generate_location);
			x++;
		}
		//%�Ȃ�Adokan_left_down�𐶐�
		else if (c == 'D')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Dokan_left_down>(generate_location);
			x++;
		}
			//D�Ȃ�Adokan_left_up�𐶐�
		else if (c == '%')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Dokan_left_up>(generate_location);
			x++;
		}
		//K�Ȃ�Adokan_right_down�𐶐�
		else if (c == 'K')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Dokan_right_down>(generate_location);
			x++;
		}
		//A�Ȃ�Adokan_right_up�𐶐�
		else if (c == 'A')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Dokan_right_up>(generate_location);
			x++;
		}
		//f�Ȃ�Aflag.png�𐶐�
		else if (c == 'f')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Flag>(generate_location);
			x++;
		}
		//A�Ȃ�Apole_down�𐶐�
		else if (c == 'p')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Pole_down>(generate_location);
			x++;
		}
		//A�Ȃ�Adokan_right_up�𐶐�
		else if (c == 'P')
		{
			Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Pole>(generate_location);
			x++;
		}
		//�󔒕����Ȃ�A�������Ȃ��Ŏ��̕���������
		else if (c == ' ')
		{
			x++;
		}
		//���s�����Ȃ�A���̍s������
		else if (c == '\n')
		{
			x = 0;
			y++;
		}
	}

	// �J�����t�@�C�������
	fclose(fp);
}