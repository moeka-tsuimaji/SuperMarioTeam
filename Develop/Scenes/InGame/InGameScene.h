#pragma once

#include "../SceneBase.h"
#include "../../Objects/GameObject.h"



// ���C���Q�[���V�[��
class InGameScene : public SceneBase
{
private:
	int back_ground_image;		// �w�i�摜
	int back_ground_sound;		// BGM
	bool pause_flag;            //�ꎞ��~�t���O
	class Player* player;       //�v���C���[���
	class Kuribo* kuribo;       //�N���{�[���

public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�����擾����
	virtual const eSceneType GetNowSceneType() const override;

private:
	/// <summary>
	/// �X�e�[�W�}�b�v�ǂݍ��ݏ���
	/// </summary>
	void LoadMarioStageMapCSV();
};

