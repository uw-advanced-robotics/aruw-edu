#include <aruwlib/Drivers.hpp>
#include <gmock/gmock.h>

#include "control/agitator/AgitatorRotateCommand.hpp"
#include "mock/AgitatorSubsystemMock.hpp"

using control::agitator::AgitatorRotateCommand;

TEST(AgitatorRotateCommand, initialize_sets_desired_angle_when_agitator_calibrated)
{
    aruwlib::Drivers d;
    mock::AgitatorSubsystemMock subMock(&d);
    AgitatorRotateCommand cmd(&subMock, 10.0f);
    EXPECT_CALL(d.canRxHandler, removeReceiveHandler);
    EXPECT_CALL(d.djiMotorTxHandler, removeFromMotorManager);
    EXPECT_CALL(subMock, calibrated).WillOnce([]() { return true; });
    EXPECT_CALL(subMock, setDesiredAngle(10.0f));
    EXPECT_CALL(subMock, getAngle).WillOnce([]() { return 0.0f; });

    cmd.initialize();
}

TEST(AgitatorRotateCommand, initialize_does_not_set_desired_angle_when_agitator_not_calibrated)
{
    aruwlib::Drivers d;
    mock::AgitatorSubsystemMock subMock(&d);
    AgitatorRotateCommand cmd(&subMock, 10.0f);
    EXPECT_CALL(d.canRxHandler, removeReceiveHandler);
    EXPECT_CALL(d.djiMotorTxHandler, removeFromMotorManager);
    EXPECT_CALL(subMock, calibrated).WillOnce([]() { return false; });
    EXPECT_CALL(subMock, getAngle).Times(0);

    cmd.initialize();
}

TEST(
    AgitatorRotateCommand,
    isFinished_returns_false_if_desired_and_current_angle_not_within_tolerance)
{
    aruwlib::Drivers d;
    mock::AgitatorSubsystemMock subMock(&d);
    AgitatorRotateCommand cmd(&subMock, 10.0f);
    EXPECT_CALL(d.canRxHandler, removeReceiveHandler);
    EXPECT_CALL(d.djiMotorTxHandler, removeFromMotorManager);
    EXPECT_CALL(subMock, getAngle).WillRepeatedly([]() { return 10.0f; });
    EXPECT_CALL(subMock, getDesiredAngle).WillOnce([]() { return 0.0f; });

    EXPECT_FALSE(cmd.isFinished());
}

TEST(AgitatorRotateCommand, isFinished_returns_true_if_desired_and_current_angle_within_tolerance)
{
    aruwlib::Drivers d;
    mock::AgitatorSubsystemMock subMock(&d);
    AgitatorRotateCommand cmd(&subMock, 10.0f);
    EXPECT_CALL(d.canRxHandler, removeReceiveHandler);
    EXPECT_CALL(d.djiMotorTxHandler, removeFromMotorManager);
    EXPECT_CALL(subMock, getAngle).WillRepeatedly([]() { return 10.0f; });
    EXPECT_CALL(subMock, getDesiredAngle).WillOnce([]() { return 10.0000001f; });

    EXPECT_TRUE(cmd.isFinished());
}

TEST(AgitatorRotateCommand, end_sets_desired_angle_to_current_angle)
{
    aruwlib::Drivers d;
    mock::AgitatorSubsystemMock subMock(&d);
    AgitatorRotateCommand cmd(&subMock, 10.0f);
    EXPECT_CALL(d.canRxHandler, removeReceiveHandler);
    EXPECT_CALL(d.djiMotorTxHandler, removeFromMotorManager);
    EXPECT_CALL(subMock, getAngle).Times(2).WillRepeatedly([]() { return 10.0f; });
    EXPECT_CALL(subMock, setDesiredAngle(10.0f)).Times(2);

    cmd.end(false);
    cmd.end(true);
}
