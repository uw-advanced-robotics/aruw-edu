#include "EduPid.hpp"

#include <aruwlib/algorithms/math_user_utils.hpp>

using aruwlib::algorithms::limitVal;

namespace algorithms
{
float EduPid::runControllerDerivateError(float error, float dt)
{
    /// \todo
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
