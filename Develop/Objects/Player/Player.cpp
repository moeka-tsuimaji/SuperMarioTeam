#include "Player.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/Application.h"
#include "DxLib.h"


#define D_PLAYER_SPEED	(50.0f)

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
	//old_panel(ePanelID::NONE),
	is_power_up(false),
	is_destroy(false)
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
	// ���͏�Ԃ̎擾
	InputManager* input = InputManager::GetInstance();

	//�ړ�����
	if (input->GetKey(KEY_INPUT_RIGHT))
	{
		flip_flag = false;
		player_state = ePlayerState::MOVE;
		p_velocity.x = 1.0f;
	}
	else if (input->GetKey(KEY_INPUT_LEFT))
	{
		flip_flag = true;
		player_state = ePlayerState::MOVE;
		p_velocity.x = -1.0f;
	}
	else
	{
		p_velocity.x = 0.0f;
		player_state = ePlayerState::IDLE;
	}
	
	
	//// ���݃p�l���̏�Ԃ��m�F
	//ePanelID panel = StageData::GetPanelData(location);

	// �O����W�̍X�V
	old_location = location;

	//// �O��p�l���̍X�V
	//old_panel = panel;

	// �ړ��� * ���� * ���� �ňړ�������肷��
	location += p_velocity * D_PLAYER_SPEED * delta_second;

	//��ʂ̒��S����E���ɍs���Ȃ��悤�ɂ���
	if (location.x >= 320)
	{
		location.x = 320;
	}
	else if (location.x <= 10)
	{
		location.x = 10;
	}
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