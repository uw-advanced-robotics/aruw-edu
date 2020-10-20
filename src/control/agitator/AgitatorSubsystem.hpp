#ifndef AGITATOR_SUBSYSTEM_HPP_
#define AGITATOR_SUBSYSTEM_HPP_

#include <aruwlib/communication/can/can.hpp>
#include <aruwlib/control/subsystem.hpp>
#include <aruwlib/motor/dji_motor.hpp>

#include "algorithms/EduPid.hpp"

#include "mock_macros.hpp"

namespace control
{
namespace agitator
{
class AgitatorSubsystem : public aruwlib::control::Subsystem
{
public:
    AgitatorSubsystem(aruwlib::Drivers *drivers)
        : aruwlib::control::Subsystem(drivers),
          pid(K_P, K_I, K_D, PID_MAX_I, PID_MAX_OUT),
          motor(drivers, aruwlib::motor::MOTOR7, aruwlib::can::CanBus::CAN_BUS1, false, "agitator")
    {
    }

    virtual ~AgitatorSubsystem() = default;

    void refresh() override;

    mockable void setDesiredAngle(float newAngle);

    mockable float getAngle() const;

    mockable bool calibrated() const { return isCalibrated; }

    mockable float getDesiredAngle() const { return desiredAngle; }

private:
    static constexpr float K_P = 170000.0f;
    static constexpr float K_I = 0.0f;
    static constexpr float K_D = 80.0f;
    static constexpr float PID_MAX_I = 0.0f;
    static constexpr float PID_MAX_OUT = 16000.0f;
    static constexpr float GEAR_RATIO = 19.0f;

    float desiredAngle = 0.0f;
    float actualAngle = 0.0f;
    bool isCalibrated = false;
    float agitatorCalibratedZeroAngle = 0.0f;
    int64_t prevTime = 0;
    int64_t prevDt = 0;  // todo this is my implementation, remove.

    algorithms::EduPid pid;

    aruwlib::motor::DjiMotor motor;

    bool calibrateHere();

    float getUncalibratedAngle() const;
};  // AgitatorSubsystem
}  // namespace agitator
}  // namespace control

#endif  // AGITATOR_SUBSYSTEM_HPP_
