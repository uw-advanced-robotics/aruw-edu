#include "aruwlib/control/command_mapper.hpp"
#include "aruwlib/control/hold_repeat_command_mapping.hpp"
#include "aruwlib/drivers_singleton.hpp"

#include "control/agitator/agitator_rotate_command.hpp"
#include "control/agitator/agitator_subsystem.hpp"
#include "control/chassis/chassis_subsystem.hpp"
#include "control/chassis/chassis_tank_drive_command.hpp"

using aruwlib::Remote;
using aruwlib::control::CommandMapper;
using namespace aruwlib::control;

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
chassis::ChassisTankDriveCommand tankDrive(&theChassis, drivers());
control::agitator::AgitatorRotateCommand rotateCommand(&theAgitator, aruwlib::algorithms::PI / 6);

/* define command mappings --------------------------------------------------*/
aruwlib::control::HoldRepeatCommandMapping rightSwitchUp(
    drivers(),
    {&rotateCommand},
    RemoteMapState(Remote::Switch::RIGHT_SWITCH, Remote::SwitchState::UP));

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
    drivers->commandMapper.addMap(&rightSwitchUp);
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
