/**
 * @file RotationSink.h
 * @author Rebecca Kelly
 *
 * The rotation sink
 * Uses energy
 * Interface
 */

#ifndef CANADIANEXPERIENCE_ROTATIONSINK_H
#define CANADIANEXPERIENCE_ROTATIONSINK_H

/**
 * Rotation sink interface
 */
class IRotationSink
{
private:

public:
    virtual void Rotate(double rotation, double speed) = 0;
};


#endif //CANADIANEXPERIENCE_ROTATIONSINK_H