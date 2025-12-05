/**
 * @file Machine1Factory.h
 * @author Rebecca Kelly
 *
 * The factory that creates the first machine
 */

#ifndef CANADIANEXPERIENCE_MACHINE1FACTORY_H
#define CANADIANEXPERIENCE_MACHINE1FACTORY_H

#include <memory>
#include <string>

class Machine;
/**
 * Factory that creates the first machine
 */
class MachineAFactory
{
private:
    /// Path to the resources directory
    std::wstring mResourcesDir;

    /// Path to the images directory
    std::wstring mImagesDir;

public:
    MachineAFactory(std::wstring resourcesDir);

    /// Default constructor (disabled)
    MachineAFactory() = delete;

    /// Copy constructor (disabled)
    MachineAFactory(const MachineAFactory &) = delete;

    /// Assignment operator (disabled)
    void operator=(const MachineAFactory &) = delete;

    /// create the machine 1
    std::shared_ptr<Machine> Create();
};


#endif //CANADIANEXPERIENCE_MACHINE1FACTORY_H