/*
 * Copyright (c) 2020-2021 Advanced Robotics at the University of Washington <robomstr@uw.edu>
 *
 * This file is part of aruwlib.
 *
 * aruwlib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * aruwlib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with aruwlib.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef HOLD_REPEAT_MAPPING_HPP_
#define HOLD_REPEAT_MAPPING_HPP_

#include "command_mapping.hpp"

namespace aruwlib
{
namespace control
{
class Command;
class RemoteMapState;

/**
 * A CommandMapping that adds `Command`s when the contained
 * mapping is a subset of the remote mapping. If a Command finishes and the
 * contained mapping is still a subset of the remote mapping, it is added again.
 * It then removes the `Command`s when the mapping is no longer a subset.
 *
 * Additionally, When neg keys are being used and the mapping's neg keys
 * are a subset of the remote map state, the `Command`s are removed.
 */
class HoldRepeatCommandMapping : public CommandMapping
{
public:
    /**
     * Constructor must take the set of `Command`s and the RemoteMapState.
     */
    HoldRepeatCommandMapping(
        Drivers *drivers,
        const std::vector<Command *> cmds,
        const RemoteMapState &rms)
        : CommandMapping(drivers, cmds, rms),
          commandsScheduled(false)
    {
    }

    /**
     * Default destructor.
     */
    ~HoldRepeatCommandMapping() override = default;

    void executeCommandMapping(const RemoteMapState &currState) override;

private:
    bool commandsScheduled;
};  // class HoldRepeatCommandMapping
}  // namespace control
}  // namespace aruwlib

#endif  // HOLD_REPEAT_COMMAND_MAPPING_HPP_
