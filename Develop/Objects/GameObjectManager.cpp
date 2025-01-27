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
	flip_flag(false)
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

