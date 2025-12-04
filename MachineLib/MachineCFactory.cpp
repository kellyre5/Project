/**
 * @file MachineCFactory.cpp
 * @author Anik Momtaz
 */

#include "pch.h"
#include "MachineCFactory.h"
#include "Machine.h"
#include "Shape.h"
#include "Motor.h"

/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Directory containing the machine resources
 */
MachineCFactory::MachineCFactory(std::wstring resourcesDir) :mResourcesDir(resourcesDir)
{
    mImagesDir = resourcesDir + ImagesDirectory;
}

/**
 * Create a machine
 * @return Pointer to newly created machine
 */
std::shared_ptr<Machine> MachineCFactory::Create()
{
    auto machine = std::make_shared<Machine>(1);

    // Notice: All dimensions are in centimeters and assume the Y axis is positive in the up direction.

    const double FloorWidth = 600;
    const double FloorHeight = 15;

    auto floor = std::make_shared<Shape>();
    floor->Rectangle(-FloorWidth/2, -FloorHeight, FloorWidth, FloorHeight);
    floor->SetImage(mImagesDir + L"/floor.png");
    floor->SetInitialPosition(0, -40);
    machine->AddComponent(floor);

    const double BeamWidth = 240;

    auto beam = std::make_shared<Shape>();
    beam->Rectangle(-FloorWidth/2, -FloorHeight, BeamWidth, FloorHeight);
    beam->SetImage(mImagesDir + L"/beam.png");
    beam->SetInitialPosition(FloorWidth/2-BeamWidth/2, 120);
    machine->AddComponent(beam);

    auto wedge = std::make_shared<Shape>();
    wedge->AddPoint(-25, 0);
    wedge->AddPoint(25, 0);
    wedge->AddPoint(25, 4.5);
    wedge->AddPoint(-25, 25);
    wedge->SetImage(mImagesDir + L"/wedge.png");
    wedge->SetInitialPosition(-95, 120);
    machine->AddComponent(wedge);

    auto basketball = std::make_shared<Shape>();
    basketball->Circle(16);
    basketball->SetImage(mImagesDir + L"/basketball.png");
    basketball->SetInitialPosition(-95, 220);
    basketball->SetDynamic();
    basketball->SetPhysics(1, 0.5, 0.5);
    machine->AddComponent(basketball);

    auto motor = std::make_shared<Motor>(mImagesDir);
    motor->SetPosition(80, 120);
    motor->SetInitiallyActive(false);      // Initially idle
    motor->SetSpeed(0.25);
    machine->AddComponent(motor);

    return machine;
}
