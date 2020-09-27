#ifndef CHASSIS_TANK_DRIVE_COMMAND_HPP_
#define CHASSIS_TANK_DRIVE_COMMAND_HPP_

#include <aruwlib/control/command.hpp>

#include "ChassisSubsystem.hpp"

namespace control
{
namespace chassis
{
class ChassisTankDriveCommand : public aruwlib::control::Command
{
public:
    /**
     * Initializes the command with the passed in ChassisSubsystem.  Must not
     * be nullptr.
     *
     * @param[in] chassis a pointer to the chassis to be passed in that this
     *      Command will interact with.
     */
    ChassisTankDriveCommand(
        ChassisSubsystem *const chassis,
        aruwlib::Drivers *drivers,
        ControlOperatorInterfaceEdu *controlOperatorInterfaceEdu);

    ChassisTankDriveCommand(const ChassisTankDriveCommand &other) = delete;

    ChassisTankDriveCommand &operator=(const ChassisTankDriveCommand &other) = delete;

    void initialize() override;

    const char *getName() const { return "chassis tank drive command"; }

    /**
     * \todo
     * Your job, to implement this function
     */
    void execute() override;

    void end(bool) override;

    bool isFinished() const override;

private:
    ChassisSubsystem *const chassis;

    aruwlib::Drivers *drivers;

    ControlOperatorInterfaceEdu *controlOperatorInterfaceEdu;
};  // ChassisTankDriveCommand

}  // namespace chassis

}  // namespace control

#endif  // CHASSIS_TANK_DRIVE_COMMAND_HPP_
