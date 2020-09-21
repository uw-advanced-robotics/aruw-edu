#include "ChassisTankDriveCommand.hpp"

#include <aruwlib/algorithms/math_user_utils.hpp>
#include <aruwlib/errors/create_errors.hpp>

#include "control/ControlOperatorInterfaceEdu.hpp"

using namespace aruwlib::control;

namespace aruwsrc {

namespace chassis {

ChassisTankDriveCommand::ChassisTankDriveCommand(ChassisSubsystem *const chassis, aruwlib::Drivers *drivers) :
        chassis(chassis), drivers(drivers) {
    if (chassis == nullptr) {
        /// \todo we need to fix the error handling system.
        RAISE_ERROR(drivers,
                    "nullptr exception",
                    aruwlib::errors::SUBSYSTEM,
                    aruwlib::errors::ADDING_NULLPTR_COMMAND);
    } else {
        this->addSubsystemRequirement(dynamic_cast<Subsystem*>(chassis));
    }
}

void ChassisTankDriveCommand::initialize() {}

void ChassisTankDriveCommand::execute() {
    /// \todo
    chassis->setDesiredOutput(0, 0, 0, 0);
}

void ChassisTankDriveCommand::end(bool) {
    chassis->setDesiredOutput(0, 0, 0, 0);
}

bool ChassisTankDriveCommand::isFinished() const {
    return false;
}

}  // namespace chassis

}  // namespace aruwsrc
