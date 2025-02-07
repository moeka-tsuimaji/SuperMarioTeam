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

	
	//�����蔻���ݒ�
	collision.SetSize(D_OBJECT_SIZE, D_OBJECT_SIZE);

	//�I�u�W�F�N�g�^�C�v��ݒ�
	collision.SetObjectType(eObjectType::eEnemy);

	//������I�u�W�F�N�g�^�C�v��ݒ�
	collision.SetHitObjectType({ eObjectType::ePlayer, eObjectType::eGround });

	//�����蔻��̕`��t���O
	SetDrawCollisionBox(false);

	// ���C���[�̐ݒ�
	z_layer = 4;

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
	//�����蔻��̈ʒu���擾����
	Vector2D collisionPosition = collision.GetPosition();
	//�����蔻��̈ʒu���X�V����
	collision.SetPosition(location);


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
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		//kuribo�����ł���
		owner_scene->DestroyObject(this);
	}
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


	if (location.y > 403)
	{
		location.y = 403;
	}

	k_velocity.y += 0.12f;
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
		if (animation_count >= 2)
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