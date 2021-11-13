#include "edu_pid.hpp"

#include "tap/algorithms/math_user_utils.hpp"

using tap::algorithms::limitVal;

namespace algorithms
{
float EduPid::runControllerDerivateError(float error, float dt)
{
    /// \todo
    if (dt == 0.0) {
        return 0.0f;
    }
    currErrorP = kp * error;
    currErrorD = (error - prevError) / dt;
    currErrorD = kd * currErrorD;
    prevError = error;
    currErrorI = currErrorI + (ki * error * dt);
    currErrorI = maxICumulative == 0.0 ? 0.0 : tap::algorithms::limitVal(currErrorI, -maxICumulative, maxICumulative);
    output = currErrorI + currErrorP + currErrorD;
    output = maxOutput == 0.0 ? 0.0 : tap::algorithms::limitVal(output, -maxOutput, maxOutput);
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
