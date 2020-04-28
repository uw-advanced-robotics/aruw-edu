#ifndef CHASSIS_TANK_DRIVE_COMMAND_HPP_
#define CHASSIS_TANK_DRIVE_COMMAND_HPP_

#include <aruwlib/control/command.hpp>

#include "ChassisSubsystem.hpp"

using namespace aruwlib::control;

namespace aruwsrc {

namespace chassis {

class ChassisTankDriveCommand : public Command {
 public:
    /**
     * Initializes the command with the passed in ChassisSubsystem.  Must not
     * be nullptr.
     *
     * @param[in] chassis a pointer to the chassis to be passed in that this
     *      Command will interact with.
     */
    explicit ChassisTankDriveCommand(ChassisSubsystem *const chassis);

    ChassisTankDriveCommand(const ChassisTankDriveCommand &other) = delete;

    ChassisTankDriveCommand &operator=(const ChassisTankDriveCommand &other) = delete;

    void initialize() override;

    /**
     * \todo
     * Your job, to implement this function
     */
    void execute() override;

    void end(bool) override;

    bool isFinished() const override;

 private:
    ChassisSubsystem *const chassis_;
};

}  // namespace chassis

}  // namespace aruwsrc

#endif  // CHASSIS_TANK_DRIVE_COMMAND_HPP_
