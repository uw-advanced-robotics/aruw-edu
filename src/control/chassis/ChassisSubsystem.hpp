#ifndef CHASSIS_SUBSYSTEM_HPP_
#define CHASSIS_SUBSYSTEM_HPP_

#include <aruwlib/control/subsystem.hpp>
#include <aruwlib/motor/dji_motor.hpp>

using namespace aruwlib::control;

namespace aruwsrc {

namespace chassis {

/**
 * A bare bones Subsystem for interacting with a 4 wheeled chassis.
 */
class ChassisSubsystem : public Subsystem {
 public:
    /**
     * Constructs a new ChassisSubsystem with default parameters specified in
     * the private section of this class.
     */
    ChassisSubsystem():
        left_front_motor_(LEFT_FRONT_MOTOR_ID, CAN_BUS_MOTORS, false, "left front drive motor"),
        left_back_motor_(LEFT_BACK_MOTOR_ID, CAN_BUS_MOTORS, false, "left back drive motor"),
        right_front_motor_(RIGHT_FRONT_MOTOR_ID, CAN_BUS_MOTORS, false, "right front drive motor"),
        right_back_motor_(RIGHT_BACK_MOTOR_ID, CAN_BUS_MOTORS, false, "right back drive motor"),
        left_front_output_(0),
        left_back_output_(0),
        right_front_output_(0),
        right_back_output_(0) {}

    ChassisSubsystem(const ChassisSubsystem &other) = delete;

    ChassisSubsystem &operator=(const ChassisSubsystem &other) = delete;

    /**
     * \todo implement this function
     *
     * Handles input for controlling the chassis.  Any input specified here will be
     * relayed directly to the motor.
     *
     * @param[in] left_front_output the current output for the left front motor.  The
     *      current's sign is relative to the direction of movement of the chassis.  So,
     *      positive current to all motors should move the chassis forward, and negative
     *      to all motors should move the chassis backward.
     * @param[in] left_back_output the current output for the  left back motor.  See
     *      left_front_output for more information.
     * @param[in] right_front_output current output for the right front motor.  See 
     *      left_front_output for more information.
     * @param[in] right_back_output current output for the right back motor.  See 
     *      left_front_output for more information.
     */
    void setDesiredOutput(int16_t left_front_output, int16_t left_back_output,
                          int16_t right_front_output, int16_t right_back_output);

    /**
     * No-op function that is a placeholder because all interactions with motors are done
     * in setDesiredOutput
     */
    void refresh() override;

 private:
    /**
     * This max output is measured in the c620 robomaster translated current.
     * Per the datasheet, the controllable current range is -16384 ~ 0 ~ 16384.
     * The corresponding speed controller output torque current range is 
     * -20 ~ 0 ~ 20 A.
     * 
     * For this demo, we have capped the output at 8000. This should be more
     * than enough for what you are doing.
     */
    static constexpr float MAX_CURRENT_OUTPUT = 8000.0f;

    /// Hardware constants, not specific to any particular chassis.
    static constexpr aruwlib::motor::MotorId RIGHT_FRONT_MOTOR_ID = aruwlib::motor::MOTOR1;
    static constexpr aruwlib::motor::MotorId LEFT_FRONT_MOTOR_ID  = aruwlib::motor::MOTOR2;
    static constexpr aruwlib::motor::MotorId LEFT_BACK_MOTOR_ID   = aruwlib::motor::MOTOR3;
    static constexpr aruwlib::motor::MotorId RIGHT_BACK_MOTOR_ID  = aruwlib::motor::MOTOR4;
    static constexpr aruwlib::can::CanBus CAN_BUS_MOTORS = aruwlib::can::CanBus::CAN_BUS2;

    /// Motors.  Use these to interact with any dji style motors.
    aruwlib::motor::DjiMotor left_front_motor_;
    aruwlib::motor::DjiMotor left_back_motor_;
    aruwlib::motor::DjiMotor right_front_motor_;
    aruwlib::motor::DjiMotor right_back_motor_;

    /// Any user input is translated into desired current for each motor.
    uint16_t left_front_output_;
    uint16_t left_back_output_;
    uint16_t right_front_output_;
    uint16_t right_back_output_;
};

}  // namespace chassis

}  // namespace aruwsrc

#endif  // CHASSIS_SUBSYSTEM_HPP_
