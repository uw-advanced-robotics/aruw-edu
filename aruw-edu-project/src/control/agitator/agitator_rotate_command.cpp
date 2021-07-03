#include "agitator_rotate_command.hpp"

#include <cmath>

#include "aruwlib/algorithms/math_user_utils.hpp"
#include "aruwlib/control/command.hpp"

#include "control/agitator/agitator_subsystem.hpp"

namespace control
{
namespace agitator
{
void AgitatorRotateCommand::initialize()
{
    if (agitator->calibrated())
    {
        agitator->setDesiredAngle(agitator->getAngle() + rotateAngle);
    }
}

void AgitatorRotateCommand::end(bool) { agitator->setDesiredAngle(agitator->getAngle()); }

bool AgitatorRotateCommand::isFinished() const
{
    return aruwlib::algorithms::compareFloatClose(
        agitator->getAngle(),
        agitator->getDesiredAngle(),
        FINISHED_EPSILON);
}
}  // namespace agitator
}  // namespace control
