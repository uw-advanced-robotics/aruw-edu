#include "control/ControlOperatorInterfaceEdu.hpp"

#include <aruwlib/DriversSingleton.hpp>
#include <aruwlib/algorithms/math_user_utils.hpp>

namespace control
{
float ControlOperatorInterfaceEdu::getChassisXLeftTankInput()
{
    return drivers->remote.getChannel(aruwlib::Remote::Channel::LEFT_VERTICAL);
}

float ControlOperatorInterfaceEdu::getChassisYLeftTankInput()
{
    return drivers->remote.getChannel(aruwlib::Remote::Channel::RIGHT_VERTICAL);
}
}  // namespace control
