/**
 * @file Machine.cpp
 * @author Rebecca Kelly
 */

#include "pch.h"
#include "Machine.h"
#include "Component.h"
#include "b2_world.h"
#include "ContactListener.h"

/// Gravity in meters per second per second
const float Gravity = -9.8f;

/// Number of velocity update iterations per step
const int VelocityIterations = 6;

/// Number of position update iterations per step
const int PositionIterations = 2;

/**
 * Constructor
 */
Machine::Machine(int machineNumber) : mMachineNumber(machineNumber)
{
}

/**
 * Add a component to the machine
 * @param component Component to add
 */
void Machine::AddComponent(std::shared_ptr<Component> component)
{
    mComponents.push_back(component);
}

/**
 * Draw the entire machine
 *
 * This is called AFTER MachineSystemA has already set up:
 *   - Translate(machine location)
 *   - Scale(cm to pixels + flipped Y)
 */
void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // graphics->SetPen(*wxRED_PEN);
    // graphics->StrokeLine(-300, 0, 300, 0);
    // graphics->StrokeLine(0, 0, 0, 25);
    // graphics->StrokeLine(-300, 0, -300, 300);
    // graphics->StrokeLine(300, 0, 300, 300);
    //
    // wxFont font(wxSize(0, 20),
    //             wxFONTFAMILY_SWISS,
    //             wxFONTSTYLE_NORMAL,
    //             wxFONTWEIGHT_NORMAL);
    // graphics->SetFont(font, *wxBLACK);
    //
    // graphics->PushState();
    // graphics->Translate(-70, 50);   // where you want the text in cm
    // graphics->Scale(1, -1);         // flip just for the text
    // graphics->DrawText(L"Am I upside down?", 0, 0); // must be 0,0
    // graphics->PopState();


    for (auto component : mComponents)
    {
        component->Draw(graphics);
    }
}

/**
 * Set the current animation frame
 * @param frame Frame number
 */
void Machine::SetMachineFrame(int frame)
{
    mFrame = frame;

    // Later update motors, belts, pulleys, physics steps, etc.
}

/**
* Reset the machine
*/
void Machine::Reset()
{
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));

    mWorld->SetContactListener(&mContactListener);

    for (auto component : mComponents)
    {
        component->PhysicsInstall(mWorld.get(), &mContactListener);
        component->Reset();
    }
}

/**
 * Update the machine on the screen
 * @param elapsed the amount of time elapsed since last update
 */
void Machine::Update(double elapsed)
{
    for (auto component : mComponents)
    {
        component->Update(elapsed);
    }

    if (mWorld)
    {
        mWorld->Step(elapsed, VelocityIterations, PositionIterations);
    }

}

