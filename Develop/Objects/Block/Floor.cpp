#include "Floor.h"
#include "../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "DxLib.h"

Floor::Floor()
{

}

Floor::~Floor()
{

}

void Floor::Initialize()
{
	//�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/Block/floor.png")[0];



	//// �����蔻��̐ݒ�
	//collision.is_blocking = true;
	//collision.object_type = eObjectType::player;
	//collision.hit_object_type.push_back(eObjectType::enemy);
	//collision.hit_object_type.push_back(eObjectType::wall);
	//collision.hit_object_type.push_back(eObjectType::food);
	//collision.hit_object_type.push_back(eObjectType::power_food);
	//collision.hit_object_type.push_back(eObjectType::special);
	//collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;


	/******************************************************************************************************************/

	//�����蔻���ݒ�
	collision.SetSize(D_OBJECT_SIZE, D_OBJECT_SIZE);

	//�I�u�W�F�N�g�^�C�v��ݒ�
	collision.SetObjectType(eObjectType::eGround);

	//������I�u�W�F�N�g�^�C�v��ݒ�
	collision.SetHitObjectType({ eObjectType::eItem, eObjectType::eEnemy });

	//�����蔻��̕`��t���O
	SetDrawCollisionBox(false);
	collision.SetObjectType(eObjectType::eFloor);

	//������I�u�W�F�N�g�^�C�v��ݒ�
	collision.SetHitObjectType({ eObjectType::ePlayer, eObjectType::eEnemy });

	//�����蔻��̕`��t���O
	SetDrawCollisionBox(true);

	/******************************************************************************************************************/



}

void Floor::Update(float delta_second)
{

	//�����蔻��̈ʒu���擾����
	Vector2D collisionPosition = collision.GetPosition();
	//�����蔻��̈ʒu���X�V����
	collision.SetPosition(location);


	// ���͏����擾
	InputManager* input = InputManager::GetInstance();

	if (input->GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x = -0.3f;
		location += velocity;
	}
}

void Floor::Draw(const Vector2D& screen_offset) const
{
	//�I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}

void Floor::OnHitCollision(GameObjectManager* hit_object)
{
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{

	}
}