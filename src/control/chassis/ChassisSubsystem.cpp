#include "ChassisSubsystem.hpp"

#include <aruwlib/algorithms/math_user_utils.hpp>
#include <aruwlib/communication/remote.hpp>

using namespace aruwlib;
using namespace aruwlib::algorithms;

namespace aruwsrc {

namespace chassis {

void ChassisSubsystem::refresh() {}

void ChassisSubsystem::setDesiredOutput(int16_t leftFrontOutput,
                                        int16_t leftBackOutput,
                                        int16_t rightFrontOutput,
                                        int16_t rightBackOutput) {
    /// \todo
}

}  // namespace chassis

}  // namespace aruwsrc
