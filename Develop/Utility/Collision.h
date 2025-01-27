#pragma once

#include"Vector2D.h"
#include <vector>

// オブジェクトタイプ
enum class eObjectType : unsigned char
{
	eNone,
	ePlayer,
	eEnemy,
	eGround,
	eItem
};

//当たり判定のクラス
class Collision
{
public:
	bool is_blocking;
	Vector2D box_size;
	Vector2D pivot;
	eObjectType object_type;
	std::vector<eObjectType> hit_object_type;

public:
	Collision() :
		is_blocking(false),
		object_type(eObjectType::eNone),
		hit_object_type()
	{

	}
	~Collision()
	{
		hit_object_type.clear();
	}
	bool IsCheckHitTarget(eObjectType hit_object) const;
};

