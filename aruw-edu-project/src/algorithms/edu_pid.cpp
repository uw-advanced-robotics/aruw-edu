#include "edu_pid.hpp"

#include "tap/algorithms/math_user_utils.hpp"

using tap::algorithms::limitVal;

namespace algorithms
{
float EduPid::runControllerDerivateError(float error, float dt)
{
    /// \todo
    currErrorP = kp * error;
    currErrorD = (error - prevError) / dt;
    currErrorD = kd * currErrorD;
    prevError = error;
    currErrorI = currErrorI + (error * dt);
    currErrorI = ki * currErrorI;
    tap::algorithms::limitVal(currErrorI, -maxICumulative, maxICumulative);
    output = currErrorI + currErrorP + currErrorD;
    tap::algorithms::limitVal(output, -maxOutput, maxOutput);
    return output;
}

void EduPid::reset()
{
    currErrorP = 0.0f;
    currErrorI = 0.0f;
    currErrorD = 0.0f;
    output = 0.0f;
}
}  // namespace algorithms
