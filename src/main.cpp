#include <modm/processing/timer.hpp>

#include <aruwlib/rm-dev-board-a/board.hpp>
#include <aruwlib/communication/remote.hpp>
#include <aruwlib/communication/can/can_rx_handler.hpp>
#include <aruwlib/motor/dji_motor_tx_handler.hpp>
#include <aruwlib/control/command_scheduler.hpp>

#include "control/chassis/ChassisTankDriveCommand.hpp"
#include "control/chassis/ChassisSubsystem.hpp"

/// \todo declare a new chassis drive subsystem
aruwsrc::chassis::ChassisSubsystem soldierChassis;

/// \todo declare a new chassis tank drive command
aruwsrc::chassis::ChassisTankDriveCommand tankDriveCommand(&soldierChassis);

modm::ShortPeriodicTimer sendMotorTimeout(2);
modm::ShortPeriodicTimer blinkLedTimer(500);

int main() {
    Board::initialize();
    aruwlib::Remote::initialize();

    /// \todo register the chassis subsystem here

    /// \todo add the chassis tank drive command as a default command for the chassis subsystem.

    while (true) {
        aruwlib::can::CanRxHandler::pollCanData();
        aruwlib::Remote::read();

        if (blinkLedTimer.execute()) {
            Board::Leds::toggle();
        }

        if (sendMotorTimeout.execute()) {
            aruwlib::control::CommandScheduler::getMainScheduler().run();
            aruwlib::motor::DjiMotorTxHandler::processCanSendData();
        }
        modm::delayMicroseconds(10);
    }
    return 0;
}
