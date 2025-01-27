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
	// �X�N���[���I�t�Z�b�g��ݒ�
	screen_offset.y = D_OBJECT_SIZE * 3.0f;

	// �w�i�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	back_ground_image = rm->GetImages("Resource/Images/siro1.png")[0];
	// BGM�̓ǂݍ���
	back_ground_sound = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");

	PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK);
}

eSceneType ResultScene::Update(const float& delta_second)
{
	// ���͏����擾
	InputManager* input = InputManager::GetInstance();

	// �^�C�g���V�[���ɑJ�ڂ���
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::title;
	}
	if (input->GetButtonDown(XINPUT_BUTTON_START))
	{
		return eSceneType::title;
	}

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update(delta_second);
}

void ResultScene::Draw() const
{
	// �w�i�摜�̕`��
	DrawRotaGraph(320, 240, 1.0, 0.0, back_ground_image, TRUE);

	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

	DrawFormatString(640, 240, GetColor(255, 255, 255), "�C���Q�[����ʂł�");

}

void ResultScene::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

const eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::result;
}
