#include "edu_pid.hpp"

#include "tap/algorithms/math_user_utils.hpp"

using tap::algorithms::limitVal;

namespace algorithms
{
    float EduPid::runControllerDerivateError(float error, float dt)
    
{
    /// \todo
    if (dt <= 0) {
        return output;
    }
    EduPid::currErrorP = kp * error;
    EduPid::currErrorI = currErrorI + (error * dt) * ki;
    EduPid::currErrorD = ((error - prevError) / dt) * kd;
    currErrorI = limitVal(currErrorI, -maxICumulative, maxICumulative);
    prevError = error;
    output =  EduPid::currErrorP + EduPid::currErrorI + EduPid::currErrorD;
    output = limitVal(output, -maxOutput, maxOutput);
    
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
