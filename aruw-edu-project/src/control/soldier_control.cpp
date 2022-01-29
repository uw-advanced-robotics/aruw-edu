#include "tap/control/command_mapper.hpp"
#include "tap/drivers_singleton.hpp"

#include "agitator/agitator_rotate_command.hpp"
#include "agitator/agitator_subsystem.hpp"
#include "chassis/chassis_subsystem.hpp"
#include "chassis/chassis_tank_drive_command.hpp"
#include "tap/control/hold_command_mapping.hpp"

using tap::DoNotUse_getDrivers;
using tap::Remote;
using tap::control::CommandMapper;

/*
 * NOTE: We are using the DoNotUse_getDrivers() function here
 *      because this file defines all subsystems and command
 *      and thus we must pass in the single statically allocated
 *      Drivers class to all of these objects.
 */
static tap::driversFunc drivers = tap::DoNotUse_getDrivers;

namespace control
{
    ControlOperatorInterfaceEdu controlOperatorInterfaceEdu(drivers());

/* define subsystems --------------------------------------------------------*/

chassis::ChassisSubsystem chassisSubsystem(drivers());
agitator::AgitatorSubsystem agitatorSubsystem(drivers());


/* define commands ----------------------------------------------------------*/
agitator::AgitatorRotateCommand agitatorRotateCommand(&agitatorSubsystem, M_PI/4);
chassis::ChassisTankDriveCommand chassisTankDriveCommand(&chassisSubsystem, drivers());
/* define command mappings --------------------------------------------------*/

tap::control::HoldCommandMapping holdCommandMapping(drivers(), {&agitatorRotateCommand}, tap::control::RemoteMapState(Remote::Switch::LEFT_SWITCH, Remote::SwitchState::UP));

/* register subsystems here -------------------------------------------------*/
void registerSoldierSubsystems(tap::Drivers *drivers) {
    drivers->commandScheduler.registerSubsystem(&chassisSubsystem);
}

/* initialize subsystems ----------------------------------------------------*/
void initializeSubsystems() {}

/* set any default commands to subsystems here ------------------------------*/
void setDefaultSoldierCommands(tap::Drivers *drivers) {
    chassisSubsystem.setDefaultCommand(&chassisTankDriveCommand);
}

/* add any starting commands to the scheduler here --------------------------*/
void startSoldierCommands(tap::Drivers *) {}

/* register io mappings here ------------------------------------------------*/
void registerSoldierIoMappings(tap::Drivers *) {}

void initSubsystemCommands(tap::Drivers *drivers)
{
    initializeSubsystems();
    registerSoldierSubsystems(drivers);
    setDefaultSoldierCommands(drivers);
    startSoldierCommands(drivers);
    registerSoldierIoMappings(drivers);
}

}  // namespace control
