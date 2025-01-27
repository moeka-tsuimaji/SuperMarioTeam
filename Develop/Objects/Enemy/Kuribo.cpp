#include "Kuribo.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/Application.h"
#include "DxLib.h"

#define D_KURIBO_SPEED	(20.0f)

Kuribo* Kuribo::instance = nullptr;

Kuribo::Kuribo() :
	move_animation(),
	dying_animation(),
	k_velocity(0.0f),
	kuribo_state(eKuriboState::WALK),
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

Kuribo::~Kuribo()
{

}

void Kuribo::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);

	//// �����蔻��̐ݒ�
	//collision.is_blocking = true;
	//collision.object_type = eObjectType::player;
	//collision.hit_object_type.push_back(eObjectType::enemy);
	//collision.hit_object_type.push_back(eObjectType::wall);
	//collision.hit_object_type.push_back(eObjectType::food);
	//collision.hit_object_type.push_back(eObjectType::power_food);
	//collision.hit_object_type.push_back(eObjectType::special);
	//collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
	mobility = eMobilityType::Movable;

	image = move_animation[0];

	kuribo_state = eKuriboState::WALK;


	//�G���[�`�F�b�N
	if (move_animation[0] == -1)
	{
		throw("�}���I�̉摜������܂���\n");
	}
}

void Kuribo::Update(float delta_second)
{
	//���͏�Ԃ̎擾
	Movement(delta_second);
	//�A�j���[�V�����̎擾
	if (kuribo_state == WALK)
	{
		AnimationControl(delta_second);
	}
	//�~�܂��Ă�Ƃ�
	else
	{
		image = move_animation[0];
	}
}

void Kuribo::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

void Kuribo::Finalize()
{
	// ���I�z��̉��
	move_animation.clear();
	dying_animation.clear();
}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void Kuribo::OnHitCollision(GameObjectManager* hit_object)
{

}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Kuribo::Movement(float delta_second)
{
	// ���͏�Ԃ̎擾
	InputManager* input = InputManager::GetInstance();

	
		k_velocity.x = -1.0f;


	//// ���݃p�l���̏�Ԃ��m�F
	//ePanelID panel = StageData::GetPanelData(location);

	// �O����W�̍X�V
	old_location = location;

	//// �O��p�l���̍X�V
	//old_panel = panel;

	// �ړ��� * ���� * ���� �ňړ�������肷��
	location += k_velocity * D_KURIBO_SPEED * delta_second;

}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Kuribo::AnimationControl(float delta_second)
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
Kuribo* Kuribo::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Kuribo();
	}
	return instance;
}