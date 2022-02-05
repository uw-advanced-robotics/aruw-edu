#include "edu_pid.hpp"

#include "tap/algorithms/math_user_utils.hpp"

using tap::algorithms::limitVal;

namespace algorithms
{
float EduPid::runControllerDerivateError(float error, float dt)
{
    /// \todo 
    currErrorP = kp * error;
    currErrorI += 
    currErrorD = kd * dt * (error - prevError);
    currErrorI = limitVal(currErrorI, 0, maxICumulative);
    output = currErrorP + currErrorI + currErrorD;
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
