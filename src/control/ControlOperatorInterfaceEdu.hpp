#ifndef CONTROL_OPERATOR_INTERFACE_EDU_HPP_
#define CONTROL_OPERATOR_INTERFACE_EDU_HPP_

#include <aruwlib/algorithms/linear_interpolation.hpp>

namespace aruwlib {

namespace control {

/**
 * When you want to receive use interface inside of commands, we put
 * a layer of abstraction here. This class allows for one to easily know
 * what sort of controls are being used for all commands.
 */
class ControlOperatorInterfaceEdu {
 public:
    /**
     * Returns the value used for chassis tank drive movement forward and backward,
     * left side, between -1 and 1.
     */
    static float getChassisXLeftTankInput();

    /**
     * Returns the value used for chassis tank drive movement forward and backward,
     * right side, between -1 and 1.
     */
    static float getChassisYLeftTankInput();
};  // ControlOperatorInterfaceEdu

}  // namespace control

}  // namespace aruwlib

#endif  // CONTROL_OPERATOR_INTERFACE_EDU_HPP_
