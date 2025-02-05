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
	//// �X�N���[���I�t�Z�b�g��ݒ�
	//screen_offset.y = D_OBJECT_SIZE * 3.0f;

	// �w�i�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	back_ground_image = rm->GetImages("Resource/Images/title.png")[0];
	// BGM�̓ǂݍ���
	back_ground_sound = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");

	PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK);

	//mario_Ui�𐶐�����
	mario = CreateObject<Mario>(Vector2D(150.0f, 15.0f));
	//time_Ui�𐶐�����
	time = CreateObject<Time>(Vector2D(500.0f, 15.0f));
	//_Ui�𐶐�����
	world = CreateObject<World>(Vector2D(380.0f, 15.0f));
}

eSceneType TitleScene::Update(const float& delta_second)
{
	// ���͏����擾
	InputManager* input = InputManager::GetInstance();

	// �C���Q�[���V�[���ɑJ�ڂ���
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::in_game;
	}
	if (input->GetButtonDown(XINPUT_BUTTON_START))
	{
		return eSceneType::in_game;
	}

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update(delta_second);
}

void TitleScene::Draw() const
{
	// �w�i�摜�̕`��
	DrawRotaGraph(320, 240, 1.0, 0.0, back_ground_image, TRUE);

	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

	//// UI�n�̕`�揈��
	//if (pause_flag)
	//{
	//	DrawString(10, 10, " P A U S E ", GetColor(255, 255, 255), TRUE);
	//}
}

void TitleScene::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
 	__super::Finalize();

	StopSoundMem(back_ground_sound);
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::title;
}
