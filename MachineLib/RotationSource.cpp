/**
 * @file RotationSource.cpp
 * @author Rebecca Kelly
 */

#include "pch.h"
#include "RotationSource.h"

#include "IRotationSink.h"

RotationSource::RotationSource()
{

}


void RotationSource::AddSink(IRotationSink* sink)
{
    mSinks.push_back(sink);
}

void RotationSource::RemoveSink(IRotationSink* sink)
{
    mSinks.erase(std::remove(mSinks.begin(), mSinks.end(), sink), mSinks.end());
}

void RotationSource::SetRotation(double rotation, double speed)
{
    mRotation = rotation;

    for(auto sink : mSinks)
    {
        sink->Rotate(rotation, speed);
    }
}

