#pragma once

#include "../SceneBase.h"

// ���U���g�V�[��
class ResultScene : public SceneBase
{
private:
	int back_ground_image;		// �w�i�摜
	int back_ground_sound;		// BGM
public:
	ResultScene();
	virtual ~ResultScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�����擾����
	virtual const eSceneType GetNowSceneType() const override;
};



