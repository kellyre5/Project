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
    // 1) Motor box – a rectangle that sits on the beam
    //    Dimensions chosen to match the motor-box.png aspect ratio
    //
    const double BoxWidth = 84;   // Width in centimeters
    const double BoxHeight = 60;  // Height in centimeters (taller rectangle)

    // Create box with bottom-left corner at origin
    mBox.Rectangle(-BoxWidth/2, 0, BoxWidth, BoxHeight);
    mBox.SetImage(mImagesDir + L"/motor-box.png");
    mBox.SetPhysics(1.0, 0.5, 0.3);   // static collider

    //
    // 2) Wheel – circle centered inside the box
    //    Position it in the center of the box vertically
    //
    const double WheelRadius = 25;    // Radius in centimeters
    mWheel.Circle(WheelRadius);
    mWheel.SetImage(mImagesDir + L"/wheel.png");

    //
    // 3) Runner – positioned at the top of the box
    //    The runner sprite should appear at the top of the motor box
    //
    mRunner.SetImage(mImagesDir + L"/motor-idle.png");
    // Runner dimensions - adjust to match the PNG aspect ratio
    const double RunnerWidth = 50;
    const double RunnerHeight = 55;
    mRunner.BottomCenteredRectangle(RunnerWidth, RunnerHeight);

    // Store box dimensions for later use
    mBoxHeight = BoxHeight;
    mBoxWidth = BoxWidth;

    mRunnerFrames[0] = mImagesDir + L"/motor-active-1.png";
    mRunnerFrames[1] = mImagesDir + L"/motor-active-2.png";
    mRunnerFrames[2] = mImagesDir + L"/motor-active-3.png";
    mRunnerFrames[3] = mImagesDir + L"/motor-active-4.png";
}

void Motor::SetPosition(double x, double y)
{
    mPosition = wxPoint2DDouble(x, y);
    mBox.SetInitialPosition(x, y);
}

void Motor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mBox.Draw(graphics);
    double wheelY = mPosition.m_y + mBoxHeight / 2.0;
    double wheelX = mPosition.m_x - 15;
    mWheel.DrawPolygon(graphics, wheelX, wheelY, mRotation);

    double runnerY = mPosition.m_y + 3;
    double runnerX = mPosition.m_x - 15;
    mRunner.DrawPolygon(graphics, runnerX, runnerY, 0);
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
    mRotation = 0;
    mActive = mInitiallyActive;
    mRunnerFrame = 0;
    mSource.SetRotation(0, 0);
    mRunnerFrameTime = 0.0;

    if (mActive)
    {
        mRunner.SetImage(mRunnerFrames[0]);
    }
    else
    {
        mRunner.SetImage(mImagesDir + L"/motor-idle.png");
    }
}

/**
 * Update the motor when it rotates
 * @param elapsed teh tiem since the last update
 */
void Motor::Update(double elapsed)
{
    if (!mActive)
    {
        mSource.SetRotation(mRotation, 0);
        return;
    }

    mSource.SetRotation(mRotation, mSpeed);

    mRotation -= mSpeed * elapsed;

    mRunnerFrameTime += elapsed;
    if (mRunnerFrameTime >= mRunnerFrameDuration)
    {
        mRunnerFrameTime -= mRunnerFrameDuration;
        mRunnerFrame = (mRunnerFrame + 1) % 4;

        mRunner.SetImage(mRunnerFrames[mRunnerFrame]);
    }
}

void Motor::BeginContact(b2Contact* contact)
{

    if (!mActive)
    {
        // Switch motor to active
        std::cout << "Active" << std::endl;
        mActive = true;
        mRunnerFrame = 0;
        mRunnerFrameTime = 0.0;
        mRunner.SetImage(mRunnerFrames[mRunnerFrame]);
    }
}

wxPoint2DDouble Motor::GetShaftPosition()
{
    double wheelX = mPosition.m_x - 15;
    double wheelY = mPosition.m_y + mBoxHeight / 2.0;
    return wxPoint2DDouble(wheelX, wheelY);
}

