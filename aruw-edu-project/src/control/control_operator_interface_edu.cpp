#include "control_operator_interface_edu.hpp"

#include "tap/algorithms/math_user_utils.hpp"
#include "tap/drivers.hpp"
#include "tap/drivers_singleton.hpp"

namespace control
{
float ControlOperatorInterfaceEdu::getChassisLeftTankInput()
{
    /// \todo
<<<<<<< HEAD
    return drivers->remote.getChannel(Remote::Channel::LEFT_VERTICAL);
=======
    return drivers->remote.getChannel(tap::Remote::Channel::LEFT_VERTICAL);
>>>>>>> d951315c07b73160f91b6017d936fa6f970af5f6
}

float ControlOperatorInterfaceEdu::getChassisRightTankInput()
{
    /// \todo
<<<<<<< HEAD
    return drivers->remote.getChannel(Remote::Channel::RIGHT_VERTICAL);
=======
    return drivers->remote.getChannel(tap::Remote::Channel::RIGHT_VERTICAL);
>>>>>>> d951315c07b73160f91b6017d936fa6f970af5f6
}
}  // namespace control
