/**
 * @file Motor.cpp
 * @author Rebecca Kelly
 */

#include "pch.h"
#include <b2_contact.h>
#include "Motor.h"
#include "Machine.h"
#include "ContactListener.h"


Motor::Motor(Machine* machine, std::wstring imagesDir) : Component(machine), mImagesDir(imagesDir)
{

    //
    // 1) Motor box – a square that sits on the beam
    //
    const double BoxSize = 80;     // tune this to match how big you want it

    // bottom-left at (-BoxSize/2, 0), height BoxSize
    mBox.Rectangle(-BoxSize/2, 0, BoxSize, BoxSize);
    mBox.SetImage(mImagesDir + L"/motor-box.png");
    mBox.SetPhysics(1.0, 0.5, 0.3);   // static collider
    // position set later in SetPosition

    //
    // 2) Wheel – circle centered inside the box
    //
    const double WheelRadius = 30;    // tweak so circle fills the box nicely
    mWheel.Circle(WheelRadius);
    mWheel.SetImage(mImagesDir + L"/wheel.png");
    //mWheel.SetPhysics(1.0, 0.5, 0.3);

    //
    // 3) Runner – ordinary Polygon (no physics)
    //     bottom-centered rectangle with the idle runner sprite
    //
    mRunner.SetImage(mImagesDir + L"/motor-idle.png");
    // 40x70-ish is usually nice; adjust to match the PNG
    mRunner.BottomCenteredRectangle(40, 70);

    mRunnerFrames[0] = mImagesDir + L"/motor-active-1.png";
    mRunnerFrames[1] = mImagesDir + L"/motor-active-2.png";
    mRunnerFrames[2] = mImagesDir + L"/motor-active-3.png";
    mRunnerFrames[3] = mImagesDir + L"/motor-active-4.png";
}

void Motor::SetPosition(double x, double y)
{
    mPosition = wxPoint2DDouble(x, y);

    mBox.SetInitialPosition(x, y);
    const double boxSize = 80;       // same constant as ctor
    const double wheelCenterY = y + boxSize / 2.0;
    //mWheel.SetInitialPosition(x, wheelCenterY);
}

void Motor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mBox.Draw(graphics);
    const double BoxSize = 80;
    double wheelY = mPosition.m_y + BoxSize / 2.0;

    mWheel.DrawPolygon(graphics, mPosition.m_x, wheelY, mRotation);
    double runnerY = mPosition.m_y + 10;  // tweak this multiplier
    mRunner.DrawPolygon(graphics, mPosition.m_x, runnerY, 0);
}

void Motor::PhysicsInstall(b2World* world, ContactListener* contactListener)
{

    std::shared_ptr<b2World> wrap(world, [](b2World*){});
    mBox.InstallPhysics(wrap);

    if (contactListener != nullptr && mBox.GetBody() != nullptr)
    {
        contactListener->Add(mBox.GetBody(), this);
    }
}

/**
 * Reset the motor when it is not on
 */
void Motor::Reset()
{

    mBox.SetInitialPosition(mPosition.m_x, mPosition.m_y);
    //mWheel.SetInitialPosition(mPosition.m_x, mPosition.m_y);
    mRotation = 0;
    mActive = false;
    mSpeed = 0.1;
    mRunnerFrame      = 0;
    mRunnerFrameTime  = 0.0;
    mRunner.SetImage(mImagesDir + L"/motor-idle.png");
}

/**
 * Update the motor when it rotates
 * @param elapsed teh tiem since the last update
 */
void Motor::Update(double elapsed)
{
    if (!mActive)
    {
        return;
    }
    mRotation -= mSpeed * elapsed * M_PI;

    mRunnerFrameTime += elapsed;
    if (mRunnerFrameTime >= mRunnerFrameDuration)
    {
        // Advance frame and wrap around [0..3]
        mRunnerFrameTime -= mRunnerFrameDuration;
        mRunnerFrame = (mRunnerFrame + 1) % 4;

        mRunner.SetImage(mRunnerFrames[mRunnerFrame]);
    }
}

void Motor::BeginContact(b2Contact* contact)
{
    // Because the dispatcher only forwards contacts involving mBox's body,
    // we already know "something hit the box" here.

    if (!mActive)
    {
        // Switch motor to active state
        mActive = true;

        // Optionally change the runner sprite to a "running" version
        // (make sure the file exists in your images folder)
        mRunnerFrame     = 0;
        mRunnerFrameTime = 0.0;
        mRunner.SetImage(mRunnerFrames[mRunnerFrame]);
    }
}

