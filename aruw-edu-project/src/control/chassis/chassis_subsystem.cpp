#include "chassis_subsystem.hpp"

#include "aruwlib/algorithms/math_user_utils.hpp"
#include "aruwlib/communication/remote.hpp"

using namespace aruwlib;
using namespace aruwlib::algorithms;

namespace control
{
namespace chassis
{
void ChassisSubsystem::initialize()
{
    leftFrontMotor.initialize();
    leftBackMotor.initialize();
    rightFrontMotor.initialize();
    rightBackMotor.initialize();
}

void ChassisSubsystem::refresh() {}

void ChassisSubsystem::setDesiredOutput(int16_t leftSideOutput, int16_t rightSideOutput)
{
    /// \todo
}

}  // namespace chassis

}  // namespace control
