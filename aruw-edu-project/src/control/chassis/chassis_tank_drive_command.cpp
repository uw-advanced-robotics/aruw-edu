#include "chassis_tank_drive_command.hpp"

#include "aruwlib/algorithms/math_user_utils.hpp"
#include "aruwlib/errors/create_errors.hpp"

#include "control/control_operator_interface_edu.hpp"

using namespace aruwlib::control;

namespace control
{
namespace chassis
{
ChassisTankDriveCommand::ChassisTankDriveCommand(
    ChassisSubsystem *const chassis,
    aruwlib::Drivers *drivers)
    : chassis(chassis),
      drivers(drivers)
{
    if (chassis == nullptr)
    {
        return;
    }
    addSubsystemRequirement(dynamic_cast<Subsystem *>(chassis));
}

void ChassisTankDriveCommand::initialize() {}

void ChassisTankDriveCommand::execute()
{
    /// \todo
    chassis->setDesiredOutput(0, 0);
}

void ChassisTankDriveCommand::end(bool) { chassis->setDesiredOutput(0, 0); }

bool ChassisTankDriveCommand::isFinished() const { return false; }

}  // namespace chassis

}  // namespace control
