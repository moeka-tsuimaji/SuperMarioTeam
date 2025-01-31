
#pragma once

#include "../GameObject.h"

// �v���C���[���
enum ePlayerState
{
	IDLE,		// �ҋ@���
	MOVE,		// �ړ����
	DIE,		// ���S���
};



/// <summary>
/// �v���C���[�N���X�i�p�b�N�}���j
/// </summary>
class Player : public GameObject
{
private:
	// �i�s�������
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};

public:
	
private:
	std::vector<int> move_animation;		// �ړ��̃A�j���[�V�����摜
	std::vector<int> dying_animation;		// ���S�̃A�j���[�V�����摜
	Vector2D old_location;					// �O���location
	Vector2D p_velocity;						// �ړ���
	ePlayerState player_state;				// �v���C���[���
	eDirectionState now_direction_state;	// ���ݐi�s�������
	eDirectionState next_direction_state;	// ����i�s�������
	int food_count;							// �a��H�ׂ���
	float animation_time;					// �A�j���[�V��������
	int animation_count;					// �A�j���[�V�����Y��
	bool is_power_up;						// �p���[�a��H�ׂ����H
	bool is_destroy;						// ���񂾏�ԂɂȂ������H
	static Player* instance;                //�v���C���[�̃C���X�^���X
	// �ړ��A�j���[�V�����̏���
	const int animation_num[4] = { 0, 1, 2, 1, };

	float acceleration_rate;	//�����x
	float deceleration_rate;	//�����x
	float max_speed;			//�ō����x
	float scroll_velocity;		//�X�N���[�������x
	float screen_scroll_speed;	//�X�N���[�����x

public:
	Player();
	virtual ~Player();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	
	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObjectManager* hit_object) override;

public:
	/// <summary>
	/// �a��H�ׂ����擾
	/// </summary>
	/// <returns>�a��H�ׂ���</returns>
	int GetFoodCount() const;

	/// <summary>
	/// �v���C���[�̏�Ԃ��擾����
	/// </summary>
	/// <returns>�v���C���[�̏��</returns>
	ePlayerState GetPlayerState() const;

	/// <summary>
	/// �v���C���[���p���[�A�b�v���Ă邩�m�F����
	/// </summary>
	/// <returns>�v���C���[�̏��</returns>
	bool GetPowerUp() const;

	/// <summary>
	/// �p���[�_�E��������
	/// </summary>
	void SetPowerDown();

	/// <summary>
	/// �v���C���[���p���[�A�b�v���Ă邩�m�F����
	/// </summary>
	/// <returns>�v���C���[�̏��</returns>
	bool GetDestroy() const;

	//��ʃI�t�Z�b�g�ݒu
	void SetScreenOffset(const Vector2D& offset);

private:
	// �X�e�[�W���X�N���[������
	void ApplyScreenScroll(float next_location_x, float current_offset_x);

	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void Movement(float delta_second);
	/// <summary>
	/// �A�j���[�V��������
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void AnimationControl(float delta_second);

public:
	//�C���X�^���X�擾
	static Player* GetInstance();
};
