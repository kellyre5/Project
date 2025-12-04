/**
 * @file ComponentTest.cpp
 * @author Rebecca Kelly
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Component.h>
#include <Machine.h>
#include <wx/graphics.h>

TEST(ComponentTest, Constructor)
{
    Machine machine(1);
    Component component(&machine);

    ASSERT_TRUE(true);   // If it constructs, we pass
}

TEST(ComponentTest, MachinePointer)
{
    Machine machine(1);
    Component component(&machine);

    // This assumes you have a GetMachine() method OR
    // the Component stores its pointer privately but Update uses it safely.
    // If you don't have GetMachine(), remove this assertion.
    ASSERT_EQ(&machine, component.GetMachine());
}

TEST(ComponentTest, Update)
{
    Machine machine(1);
    Component component(&machine);

    ASSERT_NO_THROW(component.Update(0.1));
}

TEST(ComponentTest, Draw)
{
    Machine machine(1);
    Component component(&machine);

    wxBitmap bmp(100, 100);
    wxMemoryDC dc(bmp);

    wxGraphicsContext* gcRaw = wxGraphicsContext::Create(dc);

    // Wrap raw pointer into shared_ptr with default deleter
    std::shared_ptr<wxGraphicsContext> graphics(gcRaw);

    ASSERT_NO_THROW(component.Draw(graphics));
}

TEST(ComponentTest, Reset)
{
    Machine machine(1);
    Component component(&machine);

    ASSERT_NO_THROW(component.Reset());
}








