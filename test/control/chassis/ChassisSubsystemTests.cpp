#include <aruwlib/Drivers.hpp>
#include <gtest/gtest.h>

#include "control/chassis/ChassisSubsystem.hpp"

using namespace control::chassis;

constexpr int16_t DEFAULT_DESIRED_OUTPUT = 1000;
constexpr int16_t DEFAULT_SMALL_DESIRED_OUTPUT = 100;
constexpr int16_t DEFAULT_LARGE_DESIRED_OUTPUT = 20000;

static void defaultExpectations(aruwlib::Drivers *drivers)
{
    EXPECT_CALL(drivers->canRxHandler, removeReceiveHandler).Times(4);
    EXPECT_CALL(drivers->djiMotorTxHandler, removeFromMotorManager).Times(4);
}

TEST(ChassisSubsystem, setDesiredOutput_zero_translates_to_zero_motor_output)
{
    aruwlib::Drivers drivers;
    ChassisSubsystem cs(&drivers);
    defaultExpectations(&drivers);

    cs.setDesiredOutput(0, 0);
    EXPECT_EQ(0, cs.getLeftFrontMotor().getOutputDesired());
    EXPECT_EQ(0, cs.getLeftBackMotor().getOutputDesired());
    EXPECT_EQ(0, cs.getRightFrontMotor().getOutputDesired());
    EXPECT_EQ(0, cs.getRightBackMotor().getOutputDesired());
}

TEST(ChassisSubsystem, setDesiredOutput_left_positive_translates_to_left_wheels_positive)
{
    aruwlib::Drivers drivers;
    ChassisSubsystem cs(&drivers);
    defaultExpectations(&drivers);

    cs.setDesiredOutput(DEFAULT_DESIRED_OUTPUT, 0);
    EXPECT_EQ(DEFAULT_DESIRED_OUTPUT, cs.getLeftFrontMotor().getOutputDesired());
    EXPECT_EQ(DEFAULT_DESIRED_OUTPUT, cs.getLeftBackMotor().getOutputDesired());
    EXPECT_EQ(0, cs.getRightFrontMotor().getOutputDesired());
    EXPECT_EQ(0, cs.getRightBackMotor().getOutputDesired());
}

TEST(ChassisSubsystem, setDesiredOutput_left_negative_translates_to_left_wheels_negative)
{
    aruwlib::Drivers drivers;
    ChassisSubsystem cs(&drivers);
    defaultExpectations(&drivers);

    cs.setDesiredOutput(-DEFAULT_DESIRED_OUTPUT, 0);
    EXPECT_EQ(-DEFAULT_DESIRED_OUTPUT, cs.getLeftFrontMotor().getOutputDesired());
    EXPECT_EQ(-DEFAULT_DESIRED_OUTPUT, cs.getLeftBackMotor().getOutputDesired());
    EXPECT_EQ(0, cs.getRightFrontMotor().getOutputDesired());
    EXPECT_EQ(0, cs.getRightBackMotor().getOutputDesired());
}

TEST(ChassisSubsystem, setDesiredOutput_right_positive_translates_to_right_wheels_negative)
{
    aruwlib::Drivers drivers;
    ChassisSubsystem cs(&drivers);
    defaultExpectations(&drivers);

    cs.setDesiredOutput(0, DEFAULT_DESIRED_OUTPUT);
    EXPECT_EQ(0, cs.getLeftFrontMotor().getOutputDesired());
    EXPECT_EQ(0, cs.getLeftBackMotor().getOutputDesired());
    EXPECT_EQ(-DEFAULT_DESIRED_OUTPUT, cs.getRightFrontMotor().getOutputDesired());
    EXPECT_EQ(-DEFAULT_DESIRED_OUTPUT, cs.getRightBackMotor().getOutputDesired());
}

TEST(ChassisSubsystem, setDesiredOutput_right_negative_translates_to_right_wheels_positive)
{
    aruwlib::Drivers drivers;
    ChassisSubsystem cs(&drivers);
    defaultExpectations(&drivers);

    cs.setDesiredOutput(0, -DEFAULT_DESIRED_OUTPUT);
    EXPECT_EQ(0, cs.getLeftFrontMotor().getOutputDesired());
    EXPECT_EQ(0, cs.getLeftBackMotor().getOutputDesired());
    EXPECT_EQ(DEFAULT_DESIRED_OUTPUT, cs.getRightFrontMotor().getOutputDesired());
    EXPECT_EQ(DEFAULT_DESIRED_OUTPUT, cs.getRightBackMotor().getOutputDesired());
}

TEST(ChassisSubsystem, setDesiredOutput_left_right_simultaneously_independent_of_each_other)
{
    aruwlib::Drivers drivers;
    ChassisSubsystem cs(&drivers);
    defaultExpectations(&drivers);

    cs.setDesiredOutput(DEFAULT_SMALL_DESIRED_OUTPUT, DEFAULT_DESIRED_OUTPUT);
    EXPECT_EQ(DEFAULT_SMALL_DESIRED_OUTPUT, cs.getLeftFrontMotor().getOutputDesired());
    EXPECT_EQ(DEFAULT_SMALL_DESIRED_OUTPUT, cs.getLeftBackMotor().getOutputDesired());
    EXPECT_EQ(-DEFAULT_DESIRED_OUTPUT, cs.getRightFrontMotor().getOutputDesired());
    EXPECT_EQ(-DEFAULT_DESIRED_OUTPUT, cs.getRightBackMotor().getOutputDesired());
}

TEST(ChassisSubsystem, setDesiredOutput_positive_limited_to_max_output)
{
    aruwlib::Drivers drivers;
    ChassisSubsystem cs(&drivers);
    defaultExpectations(&drivers);

    cs.setDesiredOutput(DEFAULT_LARGE_DESIRED_OUTPUT, DEFAULT_LARGE_DESIRED_OUTPUT);
    EXPECT_EQ(ChassisSubsystem::MAX_CURRENT_OUTPUT, cs.getLeftFrontMotor().getOutputDesired());
    EXPECT_EQ(ChassisSubsystem::MAX_CURRENT_OUTPUT, cs.getLeftBackMotor().getOutputDesired());
    EXPECT_EQ(-ChassisSubsystem::MAX_CURRENT_OUTPUT, cs.getRightFrontMotor().getOutputDesired());
    EXPECT_EQ(-ChassisSubsystem::MAX_CURRENT_OUTPUT, cs.getRightBackMotor().getOutputDesired());
}

TEST(ChassisSubsystem, setDesiredOutput_negative_limited_to_max_output)
{
    aruwlib::Drivers drivers;
    ChassisSubsystem cs(&drivers);
    defaultExpectations(&drivers);

    cs.setDesiredOutput(-DEFAULT_LARGE_DESIRED_OUTPUT, -DEFAULT_LARGE_DESIRED_OUTPUT);
    EXPECT_EQ(-ChassisSubsystem::MAX_CURRENT_OUTPUT, cs.getLeftFrontMotor().getOutputDesired());
    EXPECT_EQ(-ChassisSubsystem::MAX_CURRENT_OUTPUT, cs.getLeftBackMotor().getOutputDesired());
    EXPECT_EQ(ChassisSubsystem::MAX_CURRENT_OUTPUT, cs.getRightFrontMotor().getOutputDesired());
    EXPECT_EQ(ChassisSubsystem::MAX_CURRENT_OUTPUT, cs.getRightBackMotor().getOutputDesired());
}
