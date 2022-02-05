#include "edu_pid.hpp"

#include "tap/algorithms/math_user_utils.hpp"

using tap::algorithms::limitVal;

namespace algorithms
{
float EduPid::runControllerDerivateError(float error, float dt)
{
    if (dt == 0) {
        return 0;
    }
    currErrorP = kp * error;
    currErrorI += ki * error * dt;
    currErrorD = kd * (error - prevError) / dt;
    prevError = error;
    currErrorI = limitVal<float>(currErrorI, -maxICumulative, maxICumulative);
    output = currErrorP + currErrorI + currErrorD;
    output = limitVal<float>(output, -maxOutput, maxOutput);
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
