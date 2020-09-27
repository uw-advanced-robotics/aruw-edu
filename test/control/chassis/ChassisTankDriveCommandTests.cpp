#include <aruwlib/Drivers.hpp>
#include <gtest/gtest.h>

#include "control/ControlOperatorInterfaceEduMock.hpp"
#include "control/chassis/ChassisTankDriveCommand.hpp"

#include "ChassisSubsystemMock.hpp"

using namespace control::chassis;
using control::ControlOperatorInterfaceEduMock;

constexpr float DEFAULT_DESIRED_OUTPUT = 1;

static void defaultExpectations(aruwlib::Drivers *drivers)
{
    EXPECT_CALL(drivers->canRxHandler, removeReceiveHandler).Times(4);
    EXPECT_CALL(drivers->djiMotorTxHandler, removeFromMotorManager).Times(4);
}

TEST(ChassisTankDriveCommand, execute_zero_remote_input_zero_desired_output)
{
    aruwlib::Drivers drivers;
    defaultExpectations(&drivers);
    ChassisSubsystemMock cs(&drivers);
    ControlOperatorInterfaceEduMock operatorInterface(&drivers);
    ChassisTankDriveCommand ctd(&cs, &drivers, &operatorInterface);
    ON_CALL(operatorInterface, getChassisXLeftTankInput).WillByDefault([]() { return 0; });
    ON_CALL(operatorInterface, getChassisYLeftTankInput).WillByDefault([]() { return 0; });
    EXPECT_CALL(operatorInterface, getChassisXLeftTankInput).Times(1);
    EXPECT_CALL(operatorInterface, getChassisYLeftTankInput).Times(1);
    EXPECT_CALL(cs, setDesiredOutput(0, 0));

    ctd.execute();
}

TEST(ChassisTankDriveCommand, execute_positive_remote_input_positive_desired_output)
{
    aruwlib::Drivers drivers;
    defaultExpectations(&drivers);
    ChassisSubsystemMock cs(&drivers);
    ControlOperatorInterfaceEduMock operatorInterface(&drivers);
    ChassisTankDriveCommand ctd(&cs, &drivers, &operatorInterface);
    ON_CALL(operatorInterface, getChassisXLeftTankInput).WillByDefault([]() {
        return DEFAULT_DESIRED_OUTPUT;
    });
    ON_CALL(operatorInterface, getChassisYLeftTankInput).WillByDefault([]() {
        return DEFAULT_DESIRED_OUTPUT;
    });
    EXPECT_CALL(operatorInterface, getChassisXLeftTankInput).Times(1);
    EXPECT_CALL(operatorInterface, getChassisYLeftTankInput).Times(1);
    EXPECT_CALL(
        cs,
        setDesiredOutput(
            DEFAULT_DESIRED_OUTPUT * ChassisSubsystem::MAX_CURRENT_OUTPUT,
            DEFAULT_DESIRED_OUTPUT * ChassisSubsystem::MAX_CURRENT_OUTPUT));

    ctd.execute();
}

TEST(ChassisTankDriveCommand, execute_negative_remote_input_positive_desired_output)
{
    aruwlib::Drivers drivers;
    defaultExpectations(&drivers);
    ChassisSubsystemMock cs(&drivers);
    ControlOperatorInterfaceEduMock operatorInterface(&drivers);
    ChassisTankDriveCommand ctd(&cs, &drivers, &operatorInterface);
    ON_CALL(operatorInterface, getChassisXLeftTankInput).WillByDefault([]() {
        return -DEFAULT_DESIRED_OUTPUT;
    });
    ON_CALL(operatorInterface, getChassisYLeftTankInput).WillByDefault([]() {
        return -DEFAULT_DESIRED_OUTPUT;
    });
    EXPECT_CALL(operatorInterface, getChassisXLeftTankInput).Times(1);
    EXPECT_CALL(operatorInterface, getChassisYLeftTankInput).Times(1);
    EXPECT_CALL(
        cs,
        setDesiredOutput(
            -DEFAULT_DESIRED_OUTPUT * ChassisSubsystem::MAX_CURRENT_OUTPUT,
            -DEFAULT_DESIRED_OUTPUT * ChassisSubsystem::MAX_CURRENT_OUTPUT));

    ctd.execute();
}
