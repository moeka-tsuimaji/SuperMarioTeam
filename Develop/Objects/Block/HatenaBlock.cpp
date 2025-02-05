#include "HatenaBlock.h"
#include "../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "DxLib.h"

HatenaBlock::HatenaBlock()
{

}

HatenaBlock::~HatenaBlock()
{

}

void HatenaBlock::Initialize()
{
	//�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	//image = rm->GetImages("Resource/Images/Block/hatena.png")[0];
	hatena = rm->GetImages("Resource/Images/Block/hatena.png",4,4,1,32,32);
	image = hatena[0];

	// �����̐ݒ�
	mobility = eMobilityType::Stationary;

	//�����蔻���ݒ�
	collision.SetSize(D_OBJECT_SIZE, D_OBJECT_SIZE);

	//�I�u�W�F�N�g�^�C�v��ݒ�
	collision.SetObjectType(eObjectType::eBlock);

	//������I�u�W�F�N�g�^�C�v��ݒ�
	collision.SetHitObjectType({ eObjectType::eItem, eObjectType::eEnemy });

	//�����蔻��̕`��t���O
	SetDrawCollisionBox(false);
}

void HatenaBlock::Update(float delta_second)
{
	//�����蔻��̈ʒu���擾����
	Vector2D collisionPosition = collision.GetPosition();
	//�����蔻��̈ʒu���X�V����
	collision.SetPosition(location);
}

void HatenaBlock::Draw(const Vector2D& screen_offset) const
{
	//�I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}

void HatenaBlock::OnHitCollision(GameObjectManager* hit_object)
{
	//
}