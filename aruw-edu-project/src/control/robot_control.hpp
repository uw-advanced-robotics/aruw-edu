#ifndef ROBOT_CONTROL_HPP_
#define ROBOT_CONTROL_HPP_

class tap::Drivers;

namespace control
{
void initSubsystemCommands(tap::Drivers *drivers);
}  // namespace control

#endif  // ROBOT_CONTROL_HPP_
