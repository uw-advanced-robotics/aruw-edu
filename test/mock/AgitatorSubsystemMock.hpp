#ifndef AGITATOR_SUBSYSTEM_MOCK_HPP_
#define AGITATOR_SUBSYSTEM_MOCK_HPP_

#include <gmock/gmock.h>

#include "control/agitator/AgitatorSubsystem.hpp"

namespace mock
{
class AgitatorSubsystemMock : public control::agitator::AgitatorSubsystem
{
public:
    AgitatorSubsystemMock(aruwlib::Drivers *drivers) : control::agitator::AgitatorSubsystem(drivers)
    {
    }
    MOCK_METHOD(void, refresh, (), (override));
    MOCK_METHOD(void, setDesiredAngle, (float newAngle), (override));
    MOCK_METHOD(float, getAngle, (), (const override));
    MOCK_METHOD(bool, calibrated, (), (const override));
    MOCK_METHOD(float, getDesiredAngle, (), (const override));
    MOCK_METHOD(const aruwlib::motor::DjiMotor &, getMotor, (), (const override));
};  // class AgitatorSubsystemMock
}  // namespace mock

#endif  // AGITATOR_SUBSYSTEM_MOCK_HPP_
