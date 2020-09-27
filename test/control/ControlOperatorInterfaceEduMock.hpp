#ifndef CONTROL_OPERATOR_INTERFACE_EDU_MOCK_HPP_
#define CONTROL_OPERATOR_INTERFACE_EDU_MOCK_HPP_

#include <gmock/gmock.h>

#include "control/ControlOperatorInterfaceEdu.hpp"

namespace control
{
class ControlOperatorInterfaceEduMock : public ControlOperatorInterfaceEdu
{
public:
    ControlOperatorInterfaceEduMock(aruwlib::Drivers *drivers)
        : ControlOperatorInterfaceEdu(drivers)
    {
    }
    MOCK_METHOD(float, getChassisXLeftTankInput, (), (override));
    MOCK_METHOD(float, getChassisYLeftTankInput, (), (override));
};
}  // namespace control

#endif  // CONTROL_OPERATOR_INTERFACE_EDU_MOCK_HPP_
