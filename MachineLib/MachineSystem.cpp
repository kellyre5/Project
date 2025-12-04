/**
 * @file MachineSystem.cpp
 * @author Rebecc Kelly
 */

#include "pch.h"
#include "MachineSystem.h"
#include "Machine.h"
#include "MachineCFactory.h"
#include "Machine1Factory.h"

using namespace std;

/**
 * Constructor
 */
MachineSystem::MachineSystem(wstring resourcesDir) : mResourcesDir(resourcesDir)
{
    Machine1Factory factory(mResourcesDir);
    mMachine = factory.Create();

    mMachine->Reset();

    mFrame = 0;

    // later:
    // ChooseMachine(1)
}

/**
* Set the position for the root of the machine
* @param location The x,y location to place the machine
*/
void MachineSystem::SetLocation(wxPoint location)
{
    mLocation = location;
}

/**
 * Get the location of hte machine
 * @return Location x,y in pixels as a point
 */
wxPoint MachineSystem::GetLocation()
{
    return mLocation;
}

/**
* Draw the machine at the currently specified location
* @param graphics Graphics object to render to
*/
void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->SetInterpolationQuality(wxINTERPOLATION_BEST);

    graphics->PushState();
    graphics->Translate(mLocation.x, mLocation.y);
    graphics->Scale(mPixelsPerCentimeter, -mPixelsPerCentimeter);

    mMachine->Draw(graphics);

    graphics->PopState();
}

/**
* Set the current machine animation frame
* @param frame Frame number
*/
void MachineSystem::SetMachineFrame(int frame)
{
    if (!mMachine)
    {
        return;
    }

    if (frame < mFrame)
    {
        mFrame = 0;
        mMachine->Reset();
    }

    for ( ; mFrame < frame; mFrame++)
    {
        mMachine->Update(1.0 / mFrameRate);
    }
}

/**
 * Set the expected frame rate in frames per second
 * @param rate Frame rate in frames per second
 */
void MachineSystem::SetFrameRate([[maybe_unused]] double rate)
{
    mFrameRate = rate;
}

/**
* Set the machine number
* @param machine An integer number. Each number makes a different machine
*/
void MachineSystem::ChooseMachine(int machine)
{
    if(machine == 1 || machine == 17)
    {
        Machine1Factory factory(mResourcesDir);
        mMachine = factory.Create();
        mMachine->Reset();
        mFrame = 0;
    }
}

/**
 * Get the current machine number
 * @return Machine number integer
 */
int MachineSystem::GetMachineNumber()
{
    return mMachine->GetMachineNumber();
}

/**
 * Get the current machine time.
 * @return Machine time in seconds
 */
double MachineSystem::GetMachineTime()
{
    return mFrame / mFrameRate;
}