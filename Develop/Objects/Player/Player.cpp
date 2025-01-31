#include "Player.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/Application.h"
#include "DxLib.h"

#define D_PLAYER_SPEED	(50.0f)
#define SCREEN_CENTER_X (D_WIN_MAX_X / 2) //x���W�̉�ʂ̒��S

Player* Player::instance = nullptr;

Player::Player() :
	move_animation(),
	dying_animation(),
	p_velocity(0.0f),
	player_state(ePlayerState::MOVE),
	now_direction_state(eDirectionState::LEFT),
	next_direction_state(eDirectionState::LEFT),
	food_count(0),
	animation_time(0.0f),
	animation_count(0),
	is_power_up(false),
	is_destroy(false),
	acceleration_rate(30.0f),
	deceleration_rate(50.0f),
	max_speed(D_PLAYER_SPEED),
	scroll_velocity(0.0f),
	screen_scroll_speed(300.0f)
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);


	//�����蔻���ݒ�
	collision.SetSize(D_OBJECT_SIZE, D_OBJECT_SIZE);

	//�I�u�W�F�N�g�^�C�v��ݒ�
	collision.SetObjectType(eObjectType::ePlayer);

	//������I�u�W�F�N�g�^�C�v��ݒ�
	collision.SetHitObjectType({ eObjectType::eItem, eObjectType::eGround, eObjectType::eEnemy });

	//�����蔻��̕`��t���O
	SetDrawCollisionBox(true);


	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;

	image = move_animation[0];

	//�G���[�`�F�b�N
	if (move_animation[0] == -1)
	{
		throw("�}���I�̉摜������܂���\n");
	}
}

void Player::Update(float delta_second)
{
	//�����蔻��̈ʒu���擾����
	Vector2D collisionPosition = collision.GetPosition();
	//�����蔻��̈ʒu���X�V����
	collision.SetPosition(location);

	//���͏�Ԃ̎擾
	Movement(delta_second);
	//�A�j���[�V�����̎擾
	if (player_state == MOVE)
	{
		AnimationControl(delta_second);
	}
	//�~�܂��Ă�Ƃ�
	else
	{
		image = move_animation[0];
	}
}

void Player::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

void Player::Finalize()
{
	// ���I�z��̉��
	move_animation.clear();
	dying_animation.clear();
}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void Player::OnHitCollision(GameObjectManager* hit_object)
{
	if (hit_object->GetCollision().object_type == eObjectType::eEnemy)
	{
		//is_destroy = true;
		//player_state = DIE;
	}
}

/// <summary>
/// �a��H�ׂ����擾
/// </summary>
/// <returns>�a��H�ׂ���</returns>
int Player::GetFoodCount() const
{
	return food_count;
}

/// <summary>
/// �v���C���[�̏�Ԃ��擾����
/// </summary>
/// <returns>�v���C���[�̏��</returns>
ePlayerState Player::GetPlayerState() const
{
	return player_state;
}

/// <summary>
/// �v���C���[���p���[�A�b�v���Ă邩�m�F����
/// </summary>
/// <returns>�v���C���[�̏��</returns>
bool Player::GetPowerUp() const
{
	return is_power_up;
}

/// <summary>
/// �p���[�_�E��������
/// </summary>
void Player::SetPowerDown()
{
	is_power_up = false;
}

bool Player::GetDestroy() const
{
	return is_destroy;
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Player::Movement(float delta_second)
{
	//���͏�Ԃ��擾
	InputManager* input = InputManager::GetInstance();

	//�^�[�Q�b�g���x
	float target_velocity_x = 0.0f;

	if (input->GetKey(KEY_INPUT_RIGHT))
	{
		flip_flag = false;
		player_state = ePlayerState::MOVE;
		target_velocity_x = 1.0f; // �E�����̑��x
	}
	else if (input->GetKey(KEY_INPUT_LEFT))
	{
		flip_flag = true;
		player_state = ePlayerState::MOVE;
		target_velocity_x = -1.0f; // �������̑��x
	}
	else
	{
		player_state = ePlayerState::IDLE;
	}


	//���������������鏈��
	if (target_velocity_x != 0.0f) {
		//����
		if (p_velocity.x > 0 && target_velocity_x < 0 || p_velocity.x < 0 && target_velocity_x > 0)
		{
			p_velocity.x = 0.0f;
		}
		p_velocity.x += target_velocity_x * acceleration_rate * delta_second;

		//�ō����x
		if (p_velocity.x > max_speed)
		{
			p_velocity.x = max_speed;
		}
		else if (p_velocity.x < -max_speed)
		{
			p_velocity.x = -max_speed;
		}
	}
	else
	{
		//����
		if (abs(p_velocity.x) > 0)
		{
			float deceleration = deceleration_rate * delta_second;
			if (p_velocity.x > 0)
			{
				p_velocity.x = (p_velocity.x - deceleration) > 0 ? (p_velocity.x - deceleration) : 0;
			}
			else
			{
				p_velocity.x = (p_velocity.x + deceleration) < 0 ? (p_velocity.x + deceleration) : 0;
			}
		}
	}

	Vector2D next_location = location + (p_velocity * delta_second);
	old_location = location;

	//���݂̉�ʃI�t�Z�b�g���v�Z
	float current_offset_x = 0.0f;
	if (owner_scene != nullptr)
	{
		current_offset_x = owner_scene->GetScreenOffset().x;
	}

	//�v���C���[���ړ��ł�����W�͈͐���
	float screen_limit_left = SCREEN_CENTER_X + current_offset_x - (float)D_WIN_MAX_X;
	float screen_limit_right = SCREEN_CENTER_X + current_offset_x + (float)D_WIN_MAX_X;

	if (next_location.x < screen_limit_left)
	{
		next_location.x = screen_limit_left;
	}
	else if (next_location.x > screen_limit_right)
	{
		next_location.x = screen_limit_right;
	}

	//�X�e�[�W�X�N���[������
	float target_scroll_amount = 0.0f;
	bool should_center_player = false;

	//��ʒ��S
	float center_x = SCREEN_CENTER_X + current_offset_x;

	//�v���C���[����ʒ��S���E�ֈړ����Ă���΃X�e�[�W���X�N���[������
	if (abs(location.x - center_x) <= D_OBJECT_SIZE && p_velocity.x > 0)
	{
		target_scroll_amount = -p_velocity.x;
		should_center_player = true;
	}
	else
	{
		target_scroll_amount = 0;
		should_center_player = false;
	}


	//�X�e�[�W�X�N���[�����K�v�ł���Ύ�������
	if (target_scroll_amount != 0)
	{
		//�X�N���[�����镪���v�Z����
		scroll_velocity = target_scroll_amount;
	}
	else
	{
		scroll_velocity = 0.0f;
	}

	ApplyScreenScroll(scroll_velocity, delta_second);

	//���W���X�V
	location.x = next_location.x;
	location.y = next_location.y;
}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Player::AnimationControl(float delta_second)
{
	// �ړ����̃A�j���[�V����
	animation_time += delta_second;
	if (animation_time >= (1.0f / 8.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 4)
		{
			animation_count = 0;
		}
		// �摜�̐ݒ�
		image = move_animation[animation_num[animation_count]];
	}
}

//�v���C���[�̃C���X�^���X�擾
Player* Player::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Player();
	}
	return instance;
}

//��ʃI�t�Z�b�g��ݒu
void Player::SetScreenOffset(const Vector2D& offset)
{
	if (owner_scene != nullptr)
	{
		owner_scene->screen_offset = offset;
	}
}

//�X�e�[�W���X�N���[��������
void Player::ApplyScreenScroll(float velocity_x, float delta_second)
{
	float current_offset_x = 0.0f;
	if (owner_scene != nullptr)
	{
		current_offset_x = owner_scene->GetScreenOffset().x;
	}

	float scroll_amount = velocity_x * delta_second;

	Vector2D new_offset(current_offset_x + scroll_amount, 0.0f);
	SetScreenOffset(new_offset);
}