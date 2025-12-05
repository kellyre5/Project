/**
 * @file RotationSource.h
 * @author Rebecca Kelly
 *
 * A source of rotation that gives energy
 */

#ifndef CANADIANEXPERIENCE_ROTATIONSOURCE_H
#define CANADIANEXPERIENCE_ROTATIONSOURCE_H

#include <vector>

class IRotationSink;

/**
 * Rotation source that drives
 */
class RotationSource
{
private:
    std::vector<IRotationSink*> mSinks;

    /// current rotation value
    double mRotation = 0;
    /// radius of rotating thing
    double mRadius = 0;

public:
    RotationSource();

    /// Copy constructor (disabled)
    RotationSource(const RotationSource &) = delete;

    /// Assignment operator (disabled)
    void operator=(const RotationSource &) = delete;

    void AddSink(IRotationSink* sink);
    void RemoveSink(IRotationSink* sink);

    void SetRotation(double rotation, double speed);
    double GetRotation() const { return mRotation; }

    void SetRadius(double radius) { mRadius = radius; }
    double GetRadius() const { return mRadius; }

};


#endif //CANADIANEXPERIENCE_ROTATIONSOURCE_H