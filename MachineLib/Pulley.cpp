/**
 * @file Pulley.cpp
 * @author Rebecca Kelly
 */

#include "pch.h"
#include "Pulley.h"
#include "Machine.h"
#include "PhysicsPolygon.h"
#include "Component.h"

Pulley::Pulley(double radius, Machine* machine)
        : Component(machine), mRadius(radius)
{
    mPolygon.Circle(radius);
    mSource.SetRadius(radius);
    mPolygon.SetKinematic();
}

void Pulley::SetPosition(double x, double y)
{
    mPosition = wxPoint2DDouble(x, y);
    mPolygon.SetInitialPosition(x, y);
}

void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mPolygon.Draw(graphics);
}

void Pulley::PhysicsInstall(b2World* world, ContactListener*)
{
    std::shared_ptr<b2World> wrap(world, [](b2World*){});
    mPolygon.InstallPhysics(wrap);
}

void Pulley::Reset()
{
    mRotation = 0;
}

void Pulley::Rotate(double rotation, double speed)
{
    // Motor tells pulley “rotate at this speed”
    mPolygon.SetAngularVelocity(speed);

    mRotation = rotation;

    // Pass rotation downstream if driving another pulley
    mSource.SetRotation(rotation, speed);
}

void Pulley::Drive(Pulley* other)
{
    mSource.AddSink(other);
}