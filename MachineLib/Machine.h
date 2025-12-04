/**
 * @file Machine.h
 * @author Rebecca Kelly
 *
 * The complete machine
 */

#ifndef CANADIANEXPERIENCE_MACHINE_H
#define CANADIANEXPERIENCE_MACHINE_H


#include <memory>
#include <vector>
#include <string>
#include <wx/graphics.h>
#include "ContactListener.h"

class Component;
class b2World;

/**
 * A machine composed of components in centimeter units.
 */
class Machine
{
private:
    /// Machine number
    int mMachineNumber = 1;

    /// Current animation frame
    int mFrame = 0;

    /// frame rate
    double mFrameRate = 30;

    /// Components belonging to the machine
    std::vector<std::shared_ptr<Component>> mComponents;

    /// Box2D world
    std::shared_ptr<b2World> mWorld;

    /// Dispatching contact listener for this machine
    ContactListener mContactListener;

public:
    /// Constructor
    Machine(int machineNumber);

    /// Add a component to the machine
    void AddComponent(std::shared_ptr<Component> component);

    /// Draw the machine (in centimeter coordinates)
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /// Set animation frame
    void SetMachineFrame(int frame);

    /**
     * Get the machine number
     * @return the machine  number
     */
    int GetMachineNumber() const { return mMachineNumber; }

    const std::vector<std::shared_ptr<Component>>& GetComponents() const { return mComponents; }

    void Reset();
    void Update(double elapsed);

    void SetFrameRate(double rate) { mFrameRate = rate; }
};


#endif //CANADIANEXPERIENCE_MACHINE_H