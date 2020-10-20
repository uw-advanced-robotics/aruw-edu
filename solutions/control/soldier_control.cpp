#include <aruwlib/DriversSingleton.hpp>
#include <aruwlib/control/command_mapper.hpp>

#include "control/agitator/AgitatorRotateCommand.hpp"
#include "control/agitator/AgitatorSubsystem.hpp"
#include "control/chassis/ChassisSubsystem.hpp"
#include "control/chassis/ChassisTankDriveCommand.hpp"

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
control::agitator::AgitatorSubsystem theAgitator(drivers());

/* define commands ----------------------------------------------------------*/
chassis::ChassisTankDriveCommand tankDrive(&theChassis, drivers(), &controlOperatorInterfaceEdu);
control::agitator::AgitatorRotateCommand rotateCommand(&theAgitator, aruwlib::algorithms::PI / 6);

/* register subsystems here -------------------------------------------------*/
void registerSoldierSubsystems(aruwlib::Drivers *drivers)
{
    drivers->commandScheduler.registerSubsystem(&theChassis);
    drivers->commandScheduler.registerSubsystem(&theAgitator);
}

/* initialize subsystems ----------------------------------------------------*/
void initializeSubsystems() { theChassis.initialize(); }

/* set any default commands to subsystems here ------------------------------*/
void setDefaultSoldierCommands(aruwlib::Drivers *) { theChassis.setDefaultCommand(&tankDrive); }

/* add any starting commands to the scheduler here --------------------------*/
void startSoldierCommands(aruwlib::Drivers *) {}

/* register io mappings here ------------------------------------------------*/
void registerSoldierIoMappings(aruwlib::Drivers *drivers)
{
    drivers->commandMapper.addHoldRepeatMapping(
        drivers->commandMapper.newKeyMap(
            aruwlib::Remote::Switch::RIGHT_SWITCH,
            aruwlib::Remote::SwitchState::UP),
        &rotateCommand);
}

void initSubsystemCommands(aruwlib::Drivers *drivers)
{
    initializeSubsystems();
    registerSoldierSubsystems(drivers);
    setDefaultSoldierCommands(drivers);
    startSoldierCommands(drivers);
    registerSoldierIoMappings(drivers);
}

}  // namespace control
