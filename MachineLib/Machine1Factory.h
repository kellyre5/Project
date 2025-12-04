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
class Machine1Factory
{
private:
    /// Path to the resources directory
    std::wstring mResourcesDir;

    /// Path to the images directory
    std::wstring mImagesDir;

public:
    Machine1Factory(std::wstring resourcesDir);

    /// Default constructor (disabled)
    Machine1Factory() = delete;

    /// Copy constructor (disabled)
    Machine1Factory(const Machine1Factory &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Machine1Factory &) = delete;

    /// create the machine 1
    std::shared_ptr<Machine> Create();
};


#endif //CANADIANEXPERIENCE_MACHINE1FACTORY_H