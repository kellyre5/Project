/**
 * @file Pulley.h
 * @author Rebecca Kelly
 *
 * The pulley class attached to the motor
 */

#ifndef CANADIANEXPERIENCE_PULLEY_H
#define CANADIANEXPERIENCE_PULLEY_H

#include "Component.h"
#include "PhysicsPolygon.h"
#include "RotationSource.h"
#include "IRotationSink.h"

/**
 * The pulley class attached to the motor
 * A sink and source
 */
class Pulley: public Component, public IRotationSink
{
private:
    /// Center position
    wxPoint2DDouble mPosition;

    /// Pulley radius in cm
    double mRadius;

    /// Current rotation (turns 0–1)
    double mRotation = 0;

    /// Polygon used to draw the pulley
    cse335::PhysicsPolygon mPolygon;

    /// Rotation source (pulley can drive another pulley)
    RotationSource mSource;

public:
    Pulley(double radius, Machine* machine);

    /// Copy disabled
    Pulley(const Pulley&) = delete;
    void operator=(const Pulley&) = delete;

    /**
     * Set the pulley
     * @param file the pulley mage file
     */
    void SetImage(const std::wstring& file) { mPolygon.SetImage(file); };
    void SetPosition(double x, double y);

    /**
     * Get the position of the pulley
     * @return the position
     */
    wxPoint2DDouble GetPosition() { return mPosition; };

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void PhysicsInstall(b2World* world, ContactListener* contact) override;
    void Reset() override;

    void Rotate(double rotation, double speed) override;

    /**
     * Get the source
     * @return the source this pulley is
     */
    RotationSource* GetSource() { return &mSource; }

    /**
     * Update pulley
     */
    void Update(double) override {}

    void Drive(Pulley* other);
};


#endif //CANADIANEXPERIENCE_PULLEY_H