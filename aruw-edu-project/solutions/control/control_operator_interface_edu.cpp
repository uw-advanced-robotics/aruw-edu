#include "control/control_operator_interface_edu.hpp"

#include "aruwlib/algorithms/math_user_utils.hpp"
#include "aruwlib/drivers.hpp"
#include "aruwlib/drivers_singleton.hpp"

namespace control
{
float ControlOperatorInterfaceEdu::getChassisLeftTankInput()
{
    return drivers->remote.getChannel(aruwlib::Remote::Channel::LEFT_VERTICAL);
}

float ControlOperatorInterfaceEdu::getChassisRightTankInput()
{
    return drivers->remote.getChannel(aruwlib::Remote::Channel::RIGHT_VERTICAL);
}
}  // namespace control
