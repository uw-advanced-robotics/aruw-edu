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
<<<<<<< HEAD
    if (leftSideOutput - MAX_CURRENT_OUTPUT >= 0)
    {
        leftSideOutput = MAX_CURRENT_OUTPUT
    } else if (leftSideOutput + MAX_CURRENT_OUTPUT <= 0)
    {
        leftSideOutput = -MAX_CURRENT_OUTPUT
    }
    if (rightSideOutput - MAX_CURRENT_OUTPUT >= 0)
    {
        rightSideOutput = MAX_CURRENT_OUTPUT
    } else if (rightSideOutput + MAX_CURRENT_OUTPUT <= 0)
    {
        rightSideOutput = -MAX_CURRENT_OUTPUT
    }
    leftFrontMotor.setDesiredOutput(leftSideOutput)
    leftBackMotor.setDesiredOutput(leftSideOutput)
    rightFrontMotor.setDesiredOutput(-rightSideOutput)
    rightBackMotor.setDesiredOutput(-rightSideOutput)
=======
    if (leftSideOutput > MAX_CURRENT_OUTPUT) {
        leftSideOutput = MAX_CURRENT_OUTPUT;
    } if (leftSideOutput < -MAX_CURRENT_OUTPUT) {
        leftSideOutput = -MAX_CURRENT_OUTPUT;
    }
    if (rightSideOutput > MAX_CURRENT_OUTPUT) {
        rightSideOutput = MAX_CURRENT_OUTPUT;
    } if (rightSideOutput < -MAX_CURRENT_OUTPUT) {
        rightSideOutput = -MAX_CURRENT_OUTPUT;
    }
    leftFrontMotor.setDesiredOutput(leftSideOutput);
    leftBackMotor.setDesiredOutput(leftSideOutput);
    rightFrontMotor.setDesiredOutput(-rightSideOutput);
    rightBackMotor.setDesiredOutput(-rightSideOutput);
>>>>>>> d951315c07b73160f91b6017d936fa6f970af5f6
}

}  // namespace chassis

}  // namespace control
