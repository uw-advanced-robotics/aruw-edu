#ifndef AGITATOR_ROTATE_COMMAND_HPP_
#define AGITATOR_ROTATE_COMMAND_HPP_

#include <aruwlib/algorithms/math_user_utils.hpp>
#include <aruwlib/control/command.hpp>

namespace control
{
namespace agitator
{
class AgitatorSubsystem;
class AgitatorRotateCommand : public aruwlib::control::Command
{
public:
    AgitatorRotateCommand(AgitatorSubsystem *sub, float rotateAngle)
        : agitator(sub),
          rotateAngle(rotateAngle)
    {
    }

    void initialize() override;

    void execute() override {}

    void end(bool interrupted) override;

    bool isFinished() const override;

    const char *getName() const override { return "agitator rotate command"; }

private:
    static constexpr float FINISHED_EPSILON = aruwlib::algorithms::PI / 100;

    AgitatorSubsystem *agitator;

    float rotateAngle;
};  // class AgitatorRotateCommand
}  // namespace agitator
}  // namespace control

#endif  // AGITATOR_ROTATE_COMMAND_HPP_
