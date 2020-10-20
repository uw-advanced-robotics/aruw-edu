#include "algorithms/EduPid.hpp"

#include <aruwlib/algorithms/math_user_utils.hpp>

using aruwlib::algorithms::limitVal;

namespace algorithms
{
float EduPid::runControllerDerivateError(float error, float dt)
{
    if (dt == 0.0f)
    {
        return 0.0f;
    }
    currErrorP = kp * error;
    currErrorI += ki * error * dt;
    currErrorD = kd * (error - prevError) / dt;
    prevError = error;

    currErrorI =
        maxICumulative == 0.0 ? 0.0 : limitVal<float>(currErrorI, -maxICumulative, maxICumulative);
    output = currErrorP + currErrorI + currErrorD;
    output = maxOutput == 0.0 ? 0.0 : limitVal<float>(output, -maxOutput, maxOutput);
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
