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
	//// �X�N���[���I�t�Z�b�g��ݒ�
	//screen_offset.y = D_OBJECT_SIZE * 3.0f;

	// �w�i�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	back_ground_image = rm->GetImages("Resource/Images/title.png")[0];
	// BGM�̓ǂݍ���
	back_ground_sound = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");

	PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK);

	//UI�̓ǂݍ���
	mario = rm->GetImages("Resource/Images/UI/name_mario.png")[0];
	time = rm->GetImages("Resource/Images/UI/time.png")[0];
	world = rm->GetImages("Resource/Images/UI/world.png")[0];
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
	//UI�̕`��
	DrawRotaGraph(150, 15, 1.0, 0.0, mario, TRUE);
	DrawRotaGraph(500, 15, 1.0, 0.0, time, TRUE);
	DrawRotaGraph(380, 15, 1.0, 0.0, world, TRUE);

	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

}

void TitleScene::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::title;
}
