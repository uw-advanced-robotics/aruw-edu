#ifndef ROBOT_CONTROL_HPP_
#define ROBOT_CONTROL_HPP_

class aruwlib::Drivers;

namespace control
{
void initSubsystemCommands(aruwlib::Drivers *drivers);
}  // namespace control

#endif  // ROBOT_CONTROL_HPP_
