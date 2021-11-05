#include "chassis_subsystem.hpp"

#include "tap/algorithms/math_user_utils.hpp"
#include "tap/communication/serial/remote.hpp"

using namespace tap;
using namespace tap::algorithms;

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
    leftSideOutput = leftSideOutput > MAX_CURRENT_OUTPUT ? MAX_CURRENT_OUTPUT : leftSideOutput;
    leftSideOutput = leftSideOutput < -MAX_CURRENT_OUTPUT ? -MAX_CURRENT_OUTPUT : leftSideOutput;

    rightSideOutput = rightSideOutput > MAX_CURRENT_OUTPUT ? MAX_CURRENT_OUTPUT : rightSideOutput;
    rightSideOutput = rightSideOutput < -MAX_CURRENT_OUTPUT ? -MAX_CURRENT_OUTPUT : rightSideOutput;
    rightSideOutput *= -1;

    leftFrontMotor.setDesiredOutput(leftSideOutput);
    leftBackMotor.setDesiredOutput(leftSideOutput);
    rightFrontMotor.setDesiredOutput(rightSideOutput);
    rightBackMotor.setDesiredOutput(rightSideOutput);
}

}  // namespace chassis

}  // namespace control
