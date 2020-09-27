#include <aruwlib/Drivers.hpp>
#include <gtest/gtest.h>

#include "control/ControlOperatorInterfaceEdu.hpp"

using namespace control;

TEST(ControlOperatorInterfaceEdu, getChassisXLeftTankInput_zero_if_zero_remote_input)
{
    aruwlib::Drivers drivers;
    ControlOperatorInterfaceEdu operatorInterface(&drivers);
    EXPECT_CALL(drivers.remote, getChannel).Times(1);

    EXPECT_EQ(0, operatorInterface.getChassisXLeftTankInput());
}

TEST(
    ControlOperatorInterfaceEdu,
    getChassisXLeftTankInput_positive_if_positive_left_vertical_remote_input)
{
    aruwlib::Drivers drivers;
    ControlOperatorInterfaceEdu operatorInterface(&drivers);
    EXPECT_CALL(drivers.remote, getChannel).Times(1);
    ON_CALL(drivers.remote, getChannel(aruwlib::Remote::Channel::LEFT_VERTICAL))
        .WillByDefault([](aruwlib::Remote::Channel) { return 1; });

    EXPECT_EQ(1, operatorInterface.getChassisXLeftTankInput());
}

TEST(
    ControlOperatorInterfaceEdu,
    getChassisXLeftTankInput_negative_if_negative_left_vertical_remote_input)
{
    aruwlib::Drivers drivers;
    ControlOperatorInterfaceEdu operatorInterface(&drivers);
    EXPECT_CALL(drivers.remote, getChannel).Times(1);
    ON_CALL(drivers.remote, getChannel(aruwlib::Remote::Channel::LEFT_VERTICAL))
        .WillByDefault([](aruwlib::Remote::Channel) { return -1; });

    EXPECT_EQ(-1, operatorInterface.getChassisXLeftTankInput());
}

TEST(ControlOperatorInterfaceEdu, getChassisYLeftTankInput_zero_if_zero_remote_input)
{
    aruwlib::Drivers drivers;
    ControlOperatorInterfaceEdu operatorInterface(&drivers);
    EXPECT_CALL(drivers.remote, getChannel).Times(1);

    EXPECT_EQ(0, operatorInterface.getChassisXLeftTankInput());
}

TEST(
    ControlOperatorInterfaceEdu,
    getChassisYLeftTankInput_positive_if_positive_right_vertical_remote_input)
{
    aruwlib::Drivers drivers;
    ControlOperatorInterfaceEdu operatorInterface(&drivers);
    EXPECT_CALL(drivers.remote, getChannel).Times(1);
    ON_CALL(drivers.remote, getChannel(aruwlib::Remote::Channel::RIGHT_VERTICAL))
        .WillByDefault([](aruwlib::Remote::Channel) { return 1; });

    EXPECT_EQ(1, operatorInterface.getChassisYLeftTankInput());
}

TEST(
    ControlOperatorInterfaceEdu,
    getChassisYLeftTankInput_negative_if_negative_right_vertical_remote_input)
{
    aruwlib::Drivers drivers;
    ControlOperatorInterfaceEdu operatorInterface(&drivers);
    EXPECT_CALL(drivers.remote, getChannel).Times(1);
    ON_CALL(drivers.remote, getChannel(aruwlib::Remote::Channel::RIGHT_VERTICAL))
        .WillByDefault([](aruwlib::Remote::Channel) { return -1; });

    EXPECT_EQ(-1, operatorInterface.getChassisYLeftTankInput());
}
