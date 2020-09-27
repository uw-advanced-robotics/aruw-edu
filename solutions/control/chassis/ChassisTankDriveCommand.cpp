#include "control/chassis/ChassisTankDriveCommand.hpp"

#include <aruwlib/algorithms/math_user_utils.hpp>
#include <aruwlib/errors/create_errors.hpp>

#include "control/ControlOperatorInterfaceEdu.hpp"

using namespace aruwlib::control;

namespace control
{
namespace chassis
{
ChassisTankDriveCommand::ChassisTankDriveCommand(
    ChassisSubsystem *const chassis,
    aruwlib::Drivers *drivers,
    ControlOperatorInterfaceEdu *controlOperatorInterfaceEdu)
    : chassis(chassis),
      drivers(drivers),
      controlOperatorInterfaceEdu(controlOperatorInterfaceEdu)
{
    if (chassis == nullptr)
    {
        RAISE_ERROR(
            drivers,
            "nullptr exception",
            aruwlib::errors::SUBSYSTEM,
            aruwlib::errors::ADDING_NULLPTR_COMMAND);
    }
    else
    {
        this->addSubsystemRequirement(dynamic_cast<Subsystem *>(chassis));
    }
}

void ChassisTankDriveCommand::initialize() {}

void ChassisTankDriveCommand::execute()
{
    chassis->setDesiredOutput(
        controlOperatorInterfaceEdu->getChassisXLeftTankInput() *
            ChassisSubsystem::MAX_CURRENT_OUTPUT,
        controlOperatorInterfaceEdu->getChassisYLeftTankInput() *
            ChassisSubsystem::MAX_CURRENT_OUTPUT);
}

void ChassisTankDriveCommand::end(bool) { chassis->setDesiredOutput(0, 0); }

bool ChassisTankDriveCommand::isFinished() const { return false; }
}  // namespace chassis
}  // namespace control
