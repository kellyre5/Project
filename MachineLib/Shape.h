/**
 * @file Shape.h
 * @author Rebecca Kelly
 *
 * Physics enabled shape for the machine
 */

#ifndef CANADIANEXPERIENCE_SHAPE_H
#define CANADIANEXPERIENCE_SHAPE_H

#include "Component.h"
#include "IRotationSink.h"
#include "PhysicsPolygon.h"

class ContactListener;

/**
 * Physics enabled shape for the machine
 */
class Shape : public Component, public IRotationSink
{
private:
    /// Composed polygon that handles drawing + physics.
    cse335::PhysicsPolygon mPolygon;

    /// radius of rotation
    double mRotation = 0;


public:
    /// Constructor
    Shape(Machine* machine);

    /// Copy operations disabled
    Shape(const Shape&) = delete;
    void operator=(const Shape&) = delete;

    void AddPoint(double x, double y) { mPolygon.AddPoint(x, y); }
    void Rectangle(double x, double y, double w, double h) { mPolygon.Rectangle(x, y, w, h); }
    void Circle(double radius) { mPolygon.Circle(radius); }
    void SetImage(const std::wstring &file) { mPolygon.SetImage(file); }
    void SetInitialPosition(double x, double y) { mPolygon.SetInitialPosition(x, y); }
    void SetPhysics(double d, double f, double r) { mPolygon.SetPhysics(d, f, r); }
    void SetDynamic() { mPolygon.SetDynamic(); }
    void SetKinematic() { mPolygon.SetKinematic(); }
    cse335::PhysicsPolygon* GetPhysics() { return &mPolygon; }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Update(double elapsed) override {}
    void PhysicsInstall(b2World* world, ContactListener* contactListener) override;
    void Reset() override;

    void Rotate(double rotation, double speed) override;
    void BottomCenteredRectangle(double width, double height);

    void SetInitialRotation(double rotation) { mRotation = rotation; }
};


#endif //CANADIANEXPERIENCE_SHAPE_H