#include "GameObjectManager.h"
#include "../Utility/InputManager.h"
#include "../Scenes/SceneBase.h"
#include "DxLib.h"

GameObjectManager::GameObjectManager() :
	owner_scene(nullptr),
	location(0.0f),
	image(NULL),
	z_layer(0),
	mobility(eMobilityType::Stationary),
	velocity(0),
	flip_flag(false),
	draw_collision_box(false)
{

}

GameObjectManager::~GameObjectManager()
{

}

/// <summary>
/// ����������
/// </summary>
void GameObjectManager::Initialize()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void GameObjectManager::Update(float delta_second)
{
	
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset">�I�t�Z�b�g�l</param>
void GameObjectManager::Draw(const Vector2D& screen_offset) const
{
	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE, this->flip_flag);
}

/// <summary>
/// �f�o�b�O�p�����蔻��`�揈��
/// </summary>
void GameObjectManager::DrawCollision(const Vector2D& screen_offset) const
{
	if (draw_collision_box)
	{
		//�����蔻��̈ʒu���擾����
		Vector2D min = collision.GetPosition() - (collision.box_size / 2) + collision.pivot + screen_offset;
		Vector2D max = collision.GetPosition() + (collision.box_size / 2) + collision.pivot + screen_offset;

		//�����蔻���`�悷��
		DrawBoxAA(min.x, min.y, max.x, max.y, GetColor(255, 0, 0), false);
	}
}

/// <summary>
/// �I��������
/// </summary>
void GameObjectManager::Finalize()
{

}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void GameObjectManager::OnHitCollision(GameObjectManager* hit_object)
{

}

//�����蔻��̏Փ˖ʂ�Ԃ�
eCollisionSide GameObjectManager::GetCollisionSide(const GameObjectManager& other) const
{
	Vector2D thisMin = collision.GetPosition() - (collision.box_size / 2) + collision.pivot;
	Vector2D thisMax = collision.GetPosition() + (collision.box_size / 2) + collision.pivot;

	Vector2D otherMin = other.collision.GetPosition() - (other.collision.box_size / 2) + other.collision.pivot;
	Vector2D otherMax = other.collision.GetPosition() + (other.collision.box_size / 2) + other.collision.pivot;

	float leftOverlap = otherMax.x - thisMin.x;
	float rightOverlap = thisMax.x - otherMin.x;
	float topOverlap = otherMax.y - thisMin.y;
	float bottomOverlap = thisMax.y - otherMin.y;

	//�Փ˂��Ă��Ȃ��ꍇ
	if (leftOverlap <= 0.0f || rightOverlap <= 0.0f || topOverlap <= 0.0f || bottomOverlap <= 0.0f)
	{
		return eCollisionSide::None;
	}

	//�ǂ̖ʂ��ł��d�Ȃ��Ă��邩���r
	if (topOverlap < bottomOverlap && topOverlap < leftOverlap && topOverlap < rightOverlap)
	{
		return eCollisionSide::Top;
	}
	else if (bottomOverlap < topOverlap && bottomOverlap < leftOverlap && bottomOverlap < rightOverlap) 
	{
		return eCollisionSide::Bottom;
	}
	else if (leftOverlap < rightOverlap)
	{
		return eCollisionSide::Left;
	}
	else 
	{
		return eCollisionSide::Right;
	}
}

/// <summary>
/// ���L�V�[�����̐ݒ�
/// </summary>
/// <param name="scene">���L�V�[�����</param>
void GameObjectManager::SetOwnerScene(SceneBase* scene)
{
	this->owner_scene = scene;
}

/// <summary>
/// �ʒu���W�擾����
/// </summary>
/// <returns>�ʒu���W���</returns>
const Vector2D& GameObjectManager::GetLocation() const
{
	return location;
}

/// <summary>
/// �ʒu���ύX����
/// </summary>
/// <param name="location">�ύX�������ʒu���</param>
void GameObjectManager::SetLocation(const Vector2D& location)
{
	this->location = location;
}

/// <summary>
/// �����蔻��擾����
/// </summary>
/// <returns>�����蔻����</returns>
Collision GameObjectManager::GetCollision() const
{
	return collision;
}

/// <summary>
/// Z���C���[���擾����
/// </summary>
/// <returns>Z���C���[���</returns>
const int GameObjectManager::GetZLayer() const
{
	return z_layer;
}

/// <summary>
/// �������̎擾����
/// </summary>
/// <returns>�������</returns>
const eMobilityType GameObjectManager::GetMobility() const
{
	return mobility;
}

/// <summary>
/// �f�o�b�O�p�����蔻��\���t���O��ݒ肷��
/// </summary>
void GameObjectManager::SetDrawCollisionBox(bool flag)
{
	draw_collision_box = flag;
}