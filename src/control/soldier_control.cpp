#include <aruwlib/DriversSingleton.hpp>
#include <aruwlib/control/command_mapper.hpp>

#include "chassis/ChassisSubsystem.hpp"
#include "chassis/ChassisTankDriveCommand.hpp"

using aruwlib::DoNotUse_getDrivers;
using aruwlib::Remote;
using aruwlib::control::CommandMapper;

/*
 * NOTE: We are using the DoNotUse_getDrivers() function here
 *      because this file defines all subsystems and command
 *      and thus we must pass in the single statically allocated
 *      Drivers class to all of these objects.
 */
static aruwlib::driversFunc drivers = aruwlib::DoNotUse_getDrivers;

namespace control
{
ControlOperatorInterfaceEdu controlOperatorInterfaceEdu(drivers());

/* define subsystems --------------------------------------------------------*/
chassis::ChassisSubsystem theChassis(drivers());

/* define commands ----------------------------------------------------------*/
chassis::ChassisTankDriveCommand tankDrive(&theChassis, drivers(), &controlOperatorInterfaceEdu);

/* register subsystems here -------------------------------------------------*/
void registerSoldierSubsystems(aruwlib::Drivers *drivers)
{
    drivers->commandScheduler.registerSubsystem(&theChassis);
}

/* initialize subsystems ----------------------------------------------------*/
void initializeSubsystems() { theChassis.initialize(); }

/* set any default commands to subsystems here ------------------------------*/
void setDefaultSoldierCommands(aruwlib::Drivers *) { theChassis.setDefaultCommand(&tankDrive); }

/* add any starting commands to the scheduler here --------------------------*/
void startSoldierCommands(aruwlib::Drivers *) {}

/* register io mappings here ------------------------------------------------*/
void registerSoldierIoMappings(aruwlib::Drivers *) {}

void initSubsystemCommands(aruwlib::Drivers *drivers)
{
    initializeSubsystems();
    registerSoldierSubsystems(drivers);
    setDefaultSoldierCommands(drivers);
    startSoldierCommands(drivers);
    registerSoldierIoMappings(drivers);
}

}  // namespace control
