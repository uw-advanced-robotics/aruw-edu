#include "control/chassis/chassis_subsystem.hpp"

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
    leftSideOutput = aruwlib::algorithms::limitVal<float>(
        leftSideOutput,
        -MAX_CURRENT_OUTPUT,
        MAX_CURRENT_OUTPUT);
    rightSideOutput = aruwlib::algorithms::limitVal<float>(
        rightSideOutput,
        -MAX_CURRENT_OUTPUT,
        MAX_CURRENT_OUTPUT);
    leftFrontMotor.setDesiredOutput(leftSideOutput);
    leftBackMotor.setDesiredOutput(leftSideOutput);
    rightFrontMotor.setDesiredOutput(-rightSideOutput);
    rightBackMotor.setDesiredOutput(-rightSideOutput);
}
}  // namespace chassis
}  // namespace control
