/**
 * @file MachineSystem.h
 * @author Rebecca Kelly
 *
 * A Machine System class that displays machine A
 */

#ifndef CANADIANEXPERIENCE_MACHINESYSTEMA_H
#define CANADIANEXPERIENCE_MACHINESYSTEMA_H

#include "IMachineSystem.h"

class Machine;
class MachineAFactory;

/**
 * A MAchine System class that displays machine A
 */
class MachineSystem : public IMachineSystem
{
private:
    /// the machine for this machine system
    std::shared_ptr<Machine> mMachine;

    /// the location of the machine (in cm)
    wxPoint mLocation = wxPoint(0, 0);

    /// How many pixels there are for each CM
    double mPixelsPerCentimeter = 1.5;

    /// tge resources directory
    std::wstring mResourcesDir;

    /// current animation frame
    int mFrame = 0;

    /// frame rate in frames per second
    double mFrameRate = 30.0;

public:
    /// Constructor
    MachineSystem(std::wstring resourcesDir);

    /// Copy constructor (disabled)
    MachineSystem(const MachineSystem &) = delete;

    /// Assignment operator
    void operator=(const MachineSystem &) = delete;

    virtual void SetLocation(wxPoint location) override;
    virtual wxPoint GetLocation() override;

    virtual void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;
    virtual void SetMachineFrame(int frame) override;
    virtual void SetFrameRate(double rate) override;
    virtual void ChooseMachine(int machine) override;
    virtual int GetMachineNumber() override;
    virtual double GetMachineTime() override;

    /**
     * Set the flag from the control panel
     * @param flag Flag to set
     */
    virtual void SetFlag(int flag) override {}
};


#endif //CANADIANEXPERIENCE_MACHINESYSTEMA_H