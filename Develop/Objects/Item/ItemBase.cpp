

/*

#include "ItemBase.h"
#include "DxLib.h"
#include "../Player/Player.h"
#include "../../Utility/Vector2D.h"

PickupItem::PickupItem() :
    floating_speed(1.0f),
    float_amplitude(8.0f),
    float_offset(0)
{

}

PickupItem::~PickupItem()
{
}

void PickupItem::Initialize()
{
    // Set the collision size (adjust as needed)
    collision.SetSize(D_OBJECT_SIZE, D_OBJECT_SIZE);
    z_layer = 1;
    mobility = eMobilityType::Movable;
}

void PickupItem::Update(float delta_second)
{
    // Make the mushroom float up and down
    float yOffset = float_amplitude * sin(float_offset + GetNowCount() * floating_speed * 0.001f);
    Vector2D newLocation = GetLocation();
    newLocation.y = GetLocation().y + yOffset;
    SetLocation(newLocation);
}

void PickupItem::OnHitCollision(GameObjectManager* hit_object)
{
    // Check if the collision is with the player
    Player* player = dynamic_cast<Player*>(hit_object);
    if (player != nullptr)
    {
        // Apply effect
        ApplyEffect(player);

        // Remove the item from the scene
        owner_scene->RemoveGameObject(this);
    }
}


void PickupItem::SetFloatingSpeed(float speed)
{
    floating_speed = speed;
}

void PickupItem::SetFloatAmplitude(float amplitude)
{
    float_amplitude = amplitude;
}

void PickupItem::SetFloatOffset(float offset)
{
    float_offset = offset;
}

*/