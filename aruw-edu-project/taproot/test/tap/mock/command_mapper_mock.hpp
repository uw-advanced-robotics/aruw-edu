/*
 * Copyright (c) 2020-2021 Advanced Robotics at the University of Washington <robomstr@uw.edu>
 *
 * This file is part of Taproot.
 *
 * Taproot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Taproot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Taproot.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef COMMAND_MAPPER_MOCK_HPP_
#define COMMAND_MAPPER_MOCK_HPP_

#include <gmock/gmock.h>

#include "tap/control/command.hpp"
#include "tap/control/command_mapper.hpp"

namespace tap
{
namespace mock
{
class CommandMapperMock : public tap::control::CommandMapper
{
public:
    CommandMapperMock(tap::Drivers *drivers);
    virtual ~CommandMapperMock();

    MOCK_METHOD(
        void,
        handleKeyStateChange,
        (uint16_t, Remote::SwitchState, Remote::SwitchState, bool, bool),
        (override));
    MOCK_METHOD(void, addMap, (tap::control::CommandMapping *), (override));
    MOCK_METHOD(std::size_t, getSize, (), (const override));
};  // class CommandMapperMock
}  // namespace mock
}  // namespace tap

#endif  // COMMAND_MAPPER_MOCK_HPP_
