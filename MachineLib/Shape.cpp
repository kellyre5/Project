/**
 * @file Shape.cpp
 * @author Rebecca Kelly
 */

#include "pch.h"
#include "Shape.h"
#include "Machine.h"

Shape::Shape(Machine* machine) : Component(machine)
{
}

/**
 * Draw the shape.
 */
void Shape::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mPolygon.Draw(graphics);
}

/**
 * Install physics for this shape.
 */
void Shape::PhysicsInstall(b2World* world, ContactListener* contactListener)
{
    std::shared_ptr<b2World> wrapper(world, [](b2World*){});
    mPolygon.InstallPhysics(wrapper);
}

/**
 * Reset shape to original state.
 *
 * Re-creates physics state from initial position/rotation.
 */
void Shape::Reset()
{

}