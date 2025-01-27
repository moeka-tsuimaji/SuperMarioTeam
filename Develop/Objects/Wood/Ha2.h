#pragma once

#include "../GameObject.h"

class Ha2 : public GameObject
{

private:

public:
	Ha2();
	virtual ~Ha2();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

};




;

