#pragma once

#include "../Objects/GameObjectManager.h"
#include <vector>
#include <string>

/// <summary>
/// �V�[���^�C�v
/// </summary>
enum class eSceneType
{
	title,
	in_game,
	re_start,
	result,
	help,
	exit,
};


/// <summary>
/// �V�[�����N���X
/// </summary>
class SceneBase
{
protected:
	// �e�V�[�������L������
	std::vector<GameObjectManager*>	create_list;	// �������s���I�u�W�F�N�g���X�g
	std::vector<GameObjectManager*>	object_list;	// �X�V�ƕ`����s���I�u�W�F�N�g���X�g
	std::vector<GameObjectManager*>	destroy_list;	// �j�����s���I�u�W�F�N�g���X�g
	Vector2D						screen_offset;	// �X�N���[���I�t�Z�b�g

public:
	SceneBase() :
		create_list(),
		object_list(),
		destroy_list(),
		screen_offset(0.0f)
	{

	}
	virtual ~SceneBase()
	{
		// ����Y��h�~
		Finalize();
	}

public:
	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize()
	{
	}

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	/// <returns>���̃V�[���^�C�v���</returns>
	virtual eSceneType Update(const float& delta_second)
	{
		// ��������I�u�W�F�N�g������΁A�I�u�W�F�N�g���X�g���ɑ}������
		if (!create_list.empty())
		{
			for (GameObjectManager* obj : create_list)
			{
				// ���C���[������ɏ��Ԃ����ւ���
				int z_layer = obj->GetZLayer();
				std::vector<GameObjectManager*>::iterator itr = object_list.begin();	// �I�u�W�F�N�g���X�g�̐擪
				// ���X�g�̖����ɂȂ�܂ő�������
				for (; itr != object_list.end(); itr++)
				{
					// Z���C���[���傫���ꏊ�ɗv�f��ǉ�����
					// �� itr->ZLayer{1, 1, 2, 3}�Az_layer = 2 �̎�
					//    itr->ZLayer{1, 1, 2, z_layer, 3}�Ƃ���
					if (z_layer < (*itr)->GetZLayer())
					{
						break;
					}
				}
				// ���X�g�̓r���ɑ}������
				object_list.insert(itr, obj);
			}
			// �������X�g���������
			create_list.clear();
		}

		// ���X�g���̃I�u�W�F�N�g���X�V����
		for (GameObjectManager* obj : object_list)
		{
			obj->Update(delta_second);
		}

		// �����蔻��m�F����
		for (int i = 0; i < object_list.size(); i++)
		{
			if (eMobilityType::Stationary == object_list[i]->GetMobility())
			{
				continue;
			}

			for (int j = 0; j < object_list.size(); j++)
			{
				if (i == j)
				{
					continue;
				}

				CheckCollision(object_list[i], object_list[j]);
			}
		}

		// �j�����X�g������łȂ��ꍇ�A���X�g���̃I�u�W�F�N�g��j������
		if (!destroy_list.empty())
		{
			for (GameObjectManager* obj : destroy_list)
			{
				std::vector<GameObjectManager*>::iterator itr = object_list.begin();	// �I�u�W�F�N�g���X�g�̐擪
				// ���X�g�̖����ɂȂ�܂ő�������
				for (; itr != object_list.end(); itr++)
				{
					// ���X�g���ɂ���΁A�폜����
					if ((*itr) == obj)
					{
						object_list.erase(itr);
						obj->Finalize();
						delete obj;
						break;
					}
				}
			}
			// ���I�z��̊J��
			destroy_list.clear();
		}

		// ���݂̃V�[������ԋp����
		return GetNowSceneType();
	}

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw() const
	{
		// �I�u�W�F�N�g���X�g���̃I�u�W�F�N�g��`�悷��
		for (GameObjectManager* obj : object_list)
		{
			obj->Draw(screen_offset);
			obj->DrawCollision(screen_offset);
		}
	}

	/// <summary>
	/// �I��������
	/// </summary>
	virtual void Finalize()
	{
		// �I�u�W�F�N�g���X�g���̃I�u�W�F�N�g��j������
		DestoryAllObject();

		// ���I�z��̉��
		if (!create_list.empty())
		{
			create_list.clear();
		}
		if (!destroy_list.empty())
		{
			destroy_list.clear();
		}
	}

	/// <summary>
	/// ���݂̃V�[���^�C�v�擾����
	/// </summary>
	/// <returns>���݂̃V�[���^�C�v���</returns>
	virtual const eSceneType GetNowSceneType() const = 0;

	/// <summary>
	/// �����蔻��m�F����
	/// </summary>
	/// <param name="target">1�ڂ̃Q�[���I�u�W�F�N�g</param>
	/// <param name="partner">2�ڂ̃Q�[���I�u�W�F�N�g</param>
	virtual void CheckCollision(GameObjectManager* target, GameObjectManager* partner)
	{
		//�I�u�W�F�N�g�^�C�v���m�F�������蔻�蓯�m���������Ă��邩�m�F����
		if (!target->GetCollision().IsCheckHitTarget(partner->GetCollision().object_type))
		{
			return;
		}
		//�����蔻����m�F
		if (target->GetCollision().CheckCollision(partner->GetCollision()))
		{
			target->OnHitCollision(partner);
		}
	}

public:
	/// <summary>
	/// �Q�[���I�u�W�F�N�g��������
	/// </summary>
	/// <typeparam name="OBJECT">��������Q�[���I�u�W�F�N�g�N���X</typeparam>
	/// <param name="generate_location">�����ʒu</param>
	/// <returns>���������Q�[���I�u�W�F�N�g�̃|�C���^</returns>
	template <class OBJECT>
	OBJECT* CreateObject(const Vector2D& generate_location)
	{
		// ��������Q�[���I�u�W�F�N�g�N���X�𓮓I�m��
		OBJECT* new_instance = new OBJECT();
		// GameObjectBase���p�����Ă��邩�m�F
		GameObjectManager* new_object = dynamic_cast<GameObjectManager*>(new_instance);
		// �G���[�`�F�b�N
		if (new_object == nullptr)
		{
			// ���I�m�ۂ����������̊J��
			delete new_instance;
			// ��O�e�L�X�g��ʒm
			throw std::string("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
			return nullptr;
		}
		// �V�[�����̐ݒ�
		new_object->SetOwnerScene(this);
		// �I�u�W�F�N�g�̏�����
		new_object->Initialize();
		// �ʒu���̐ݒ�
		new_object->SetLocation(generate_location);
		// �����I�u�W�F�N�g���X�g�̖����Ɋi�[����
		create_list.push_back(new_object);
		// ���������Q�[���I�u�W�F�N�g�̃|�C���^��Ԃ�
		return new_instance;
	}

	/// <summary>
	/// �I�u�W�F�N�g�j������
	/// </summary>
	/// <param name="target">�j�����s���Q�[���I�u�W�F�N�g�̃|�C���^</param>
	void DestroyObject(GameObjectManager* target)
	{
		// �k���|�`�F�b�N
		if (target == nullptr)
		{
			return;
		}

		// �j���I�u�W�F�N�g���X�g���ɂ���΁A�ǉ����Ȃ�
		for (GameObjectManager* obj : destroy_list)
		{
			if (obj == target)
			{
				return;
			}
		}

		// �j�����s���I�u�W�F�N�g���X�g�ɒǉ�����
		destroy_list.push_back(target);
	}

	/// <summary>
	/// �X�N���[���I�t�Z�b�g���擾����
	/// </summary>
	/// <returns>�X�N���[���I�t�Z�b�g�l</returns>
	const Vector2D GetScreenOffset() const
	{
		return screen_offset;
	}

private:
	/// <summary>
	/// �V�[�����I�u�W�F�N�g�j������
	/// </summary>
	void DestoryAllObject()
	{
		// �I�u�W�F�N�g���X�g����Ȃ珈�����I������
		if (object_list.empty())
		{
			return;
		}
		// �I�u�W�F�N�g���X�g���̃I�u�W�F�N�g���폜����
		for (GameObjectManager* obj : object_list)
		{
			obj->Finalize();
			delete obj;
		}
		// ���I�z��̉��
		object_list.clear();
	}
};
