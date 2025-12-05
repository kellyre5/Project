/**
 * @file Motor.h
 * @author Rebecca Kelly
 *
 * The motor that runs the machine
 */

#ifndef CANADIANEXPERIENCE_MOTOR_H
#define CANADIANEXPERIENCE_MOTOR_H

#include "Component.h"
#include <b2_world_callbacks.h>
#include "PhysicsPolygon.h"
#include "RotationSource.h"
#include <memory>

class ContactListener;
/**
 * The motor that runs the machine
 * Rotation SOurce
 */
class Motor : public Component, public b2ContactListener
{
private:
    /// Box polygon
    cse335::PhysicsPolygon mBox;

    /// Wheel polygon
    cse335::Polygon mWheel;

    /// Runner polygon
    cse335::Polygon mRunner;

    /// Position in centimeters
    wxPoint2DDouble mPosition;

    /// images directory
    std::wstring mImagesDir;

    double mRotation = 0;     // current angle, in radians
    double mSpeed = 0.1;      // rotations per second (or any value you pick)

    /// Is the motor currently active?
    bool mActive = false;

    int    mRunnerFrame        = 0;
    double mRunnerFrameTime    = 0.0;
    double mRunnerFrameDuration = 0.1;

    /// File names for runner animation
    std::wstring mRunnerFrames[4];

    /// width fo the box
    int mBoxWidth;
    /// height of the box
    int mBoxHeight;
    /// determine f the machine is initially active
    bool mInitiallyActive = false;
    /// the rotation source object this is
    RotationSource mSource;

public:
    Motor(Machine* machine, std::wstring imagesDir);

    /// Copy operations disabled
    Motor(const Motor&) = delete;
    void operator=(const Motor&) = delete;

    void SetPosition(double x, double y);

    wxPoint2DDouble GetShaftPosition();

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void PhysicsInstall(b2World* world, ContactListener* contactListener) override;

    void Reset() override;

    void Update(double elapsed) override;

    void BeginContact(b2Contact* contact) override;

    /**
     * Set the initial state of the motor
     * @param active bool
     */
    void SetInitiallyActive(bool active) { mInitiallyActive = active; }

    /**
     * Set the speed
     * @param speed the speed to set
     */
    void SetSpeed(double speed) { mSpeed = speed; }

    /**
     * Get the rotation source
     * @return the source this is
     */
    RotationSource* GetSource() { return &mSource; }

};


#endif //CANADIANEXPERIENCE_MOTOR_H