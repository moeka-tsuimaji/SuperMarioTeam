#pragma once

#include "../GameObject.h"

class Mario : public GameObject
{

private:

public:
	Mario();
	virtual ~Mario();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};