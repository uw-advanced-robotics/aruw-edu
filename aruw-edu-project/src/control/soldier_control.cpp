#include "tap/control/command_mapper.hpp"
#include "tap/drivers_singleton.hpp"

#include "agitator/agitator_rotate_command.hpp"
#include "agitator/agitator_subsystem.hpp"
#include "chassis/chassis_subsystem.hpp"
#include "chassis/chassis_tank_drive_command.hpp"

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
<<<<<<< HEAD
    ControlOperatorInterfaceEdu control(drivers);
/* define subsystems --------------------------------------------------------*/
    ChassisSubsystem chassisSubsystem(drivers);
    ChassisTankDriveCommand chassisTankDrive(&chassisSubsystem, drivers());
=======
    ControlOperatorInterfaceEdu control(drivers());
/* define subsystems --------------------------------------------------------*/
ChassisSubsystem chassisSubsystem(drivers());
ChassisTankDriveCommand chassisTankDrive(&chassisSubsystem, drivers());
>>>>>>> d951315c07b73160f91b6017d936fa6f970af5f6
/* define commands ----------------------------------------------------------*/

/* define command mappings --------------------------------------------------*/

/* register subsystems here -------------------------------------------------*/
void registerSoldierSubsystems(tap::Drivers *drivers) {
<<<<<<< HEAD
    commandScheduler.registerSubsystem(&chassisSubsystem, drivers());
    commandScheduler.registerSubsystem(&chassisTankDrive, drivers());

=======
    drivers->commandScheduler.registerSubsystems(&chassisSubsystem, drivers());
    drivers->commandScheduler.registerSubsystems(&chassisTankDrive)
>>>>>>> d951315c07b73160f91b6017d936fa6f970af5f6
}

/* initialize subsystems ----------------------------------------------------*/
void initializeSubsystems() {}

/* set any default commands to subsystems here ------------------------------*/
void setDefaultSoldierCommands(tap::Drivers *) {
    drivers->commandScheduler.setDefaultCommand(&chassisTankDrive);
}

/* add any starting commands to the scheduler here --------------------------*/
void startSoldierCommands(tap::Drivers *) {}
    chassisSubsystem.setDefaultCommand(&chassis)
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
