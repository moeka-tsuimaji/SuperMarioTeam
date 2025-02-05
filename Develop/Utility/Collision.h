#pragma once

#include"Vector2D.h"
#include <vector>

// �I�u�W�F�N�g�^�C�v
enum class eObjectType : unsigned char
{
	eNone,
	ePlayer,
	eEnemy,
	eGround,
	eBlock,
	eItem
	eItem,
	eFloor
};

//�����蔻��̃N���X
class Collision
{
public:
	bool is_blocking;	//�I�u�W�F�N�g�̓������~�߂��Ă��邩�m�F����ϐ�
	Vector2D box_size;	//�����蔻��̑傫��
	Vector2D pivot;		//�����蔻��ƃI�u�W�F�N�g�̃I�t�Z�b�g
	eObjectType object_type;	//�I�u�W�F�N�g�̃^�C�v
	std::vector<eObjectType> hit_object_type;	//�����鎑�i�����I�u�W�F�N�g

private:
	Vector2D position;

public:
	Collision();
	~Collision();

	//�����蔻��̈ʒu�ݒu
	void SetPosition(const Vector2D& pos);

	//�����蔻��̈ʒu�̎擾
	const Vector2D& GetPosition() const;

	//�����蔻��̑傫���ݒ�
	void SetSize(const float& width, const float& height);

	//�����蔻��̑傫���擾
	Vector2D GetSize();

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	void SetObjectType(const eObjectType& FUNC_objecttype);

	//������I�u�W�F�N�g�^�C�v�̐ݒ�
	void SetHitObjectType(const std::vector<eObjectType>& FUNC_hitobjecttype);

	//���������I�u�W�F�N�g�̃^�C�v�m�F
	bool IsCheckHitTarget(eObjectType FUNC_hitobject) const;

	//�����蔻�蓯�m���������Ă��邩�m�F
	bool CheckCollision(const Collision& other) const;
};

