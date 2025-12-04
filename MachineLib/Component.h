/**
 * @file Component.h
 * @author Rebecca Kelly
 *
 * The components that make uo the machine
 */

#ifndef CANADIANEXPERIENCE_COMPONENT_H
#define CANADIANEXPERIENCE_COMPONENT_H

#include <memory>

class Machine;
class wxGraphicsContext;
class b2World;
class b2ContactListener;
class ContactListener;

/**
 * The components that make up the machine
 * Base class for the parts
 */
class Component
{
private:
    /// The machine that owns this component (non-owning pointer)
    Machine* mMachine;

    /// Optional draw layer (0 = default)
    int mLayer = 0;

public:
    virtual ~Component() = default;
    /// Constructor
    Component(Machine* machine);

    /// Copy operations disabled
    Component(const Component&) = delete;
    void operator=(const Component&) = delete;

    /**
     * Update the component in time.
     * @param elapsed Elapsed time in seconds
     */
    virtual void Update(double elapsed) {}

    /**
     * Draw the component.
     * Coordinates are in centimeters, with +Y up.
     * @param graphics Graphics context
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) {}

    /**
     * Install this component into the physics system.
     * @param world Box2D physics world
     * @param contactListener Contact listener for collisions
     */
    virtual void PhysicsInstall(b2World* world, ContactListener* contactListener) {}


    /**
     * Reset the component to its initial state.
     */
    virtual void Reset() {}

    /// Get the owning machine
    Machine* GetMachine() const { return mMachine; }

    /// Get the draw layer
    int GetLayer() const { return mLayer; }

    /// Set the draw layer
    void SetLayer(int layer) { mLayer = layer; }
};


#endif //CANADIANEXPERIENCE_COMPONENT_H