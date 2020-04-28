#include "ChassisSubsystem.hpp"

#include <aruwlib/algorithms/math_user_utils.hpp>
#include <aruwlib/communication/remote.hpp>

using namespace aruwlib;
using namespace aruwlib::algorithms;

namespace aruwsrc {

namespace chassis {

void ChassisSubsystem::refresh() {}

void ChassisSubsystem::setDesiredOutput(int16_t left_front_output,
                                        int16_t left_back_output,
                                        int16_t right_front_output,
                                        int16_t right_back_output) {
    /// \todo
}

}  // namespace chassis

}  // namespace aruwsrc
