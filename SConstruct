# Copyright (c) 2017-2018, Niklas Hauser
#
# This file is part of the modm project.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

#!/usr/bin/env python3

import os
from os.path import join, abspath

# User Configurable Options
project_name = "aruw-edu"
build_path = "build"

# SCons environment with all tools
env = DefaultEnvironment(tools=[], ENV=os.environ)
env["CONFIG_BUILD_BASE"] = abspath(build_path)
env["CONFIG_PROJECT_NAME"] = project_name

# Configure build jobs
if GetOption('num_jobs') == 1:
    SetOption('num_jobs', 8)

print("Configured {0} parallel build jobs (-j{0})".format(GetOption('num_jobs')))

# Building all libraries (read from sconscript files located in generated_paths)
generated_paths = ["mcb-2019-2020/mcb-2019-2020-project/modm",
                   "mcb-2019-2020/mcb-2019-2020-project/src/aruwlib"]
env.SConscript(dirs=generated_paths, exports="env")

# References:
#   GCC flags: https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html
#   Scons API: https://www.scons.org/doc/latest/HTML/scons-user/apa.html
# 
# You can append one or multiple options like this
#     env.Append(CCFLAGS="-pedantic")
#     env.Append(CCFLAGS=["-pedantic", "-pedantic-errors"])
# If you need to remove options, you need to do this:
#     env["CCFLAGS"].remove("-pedantic")
# Note that a lot of options also have a "-no-{option}" option
# that may overwrite previous options.

# Configure build flags that are unique to debug or release profile

profile = ARGUMENTS.get("profile", "release")

if profile == "debug":
    env.Append(CCFLAGS = [
        "-fno-inline",
    ])

if 'additional-ccflags' in ARGUMENTS:
    env.Append(CCFLAGS = [
       ARGUMENTS['additional-ccflags'],
    ])

# add this path so you don't have to write #include "src/..."
env.AppendUnique(CPPPATH=[abspath(r"./src"),
                          abspath(r"./mcb-2019-2020/mcb-2019-2020-project/robot-type"),
                          abspath(r"./mcb-2019-2020/mcb-2019-2020-project/src")])

# don't compile this stuff
ignored = [".lbuild_cache", build_path, "robot-type", "mcb-2019-2020"] + generated_paths
sources = env.FindSourceFiles(".", ignorePaths=ignored)

program = env.Program(target=env["CONFIG_PROJECT_NAME"]+".elf", source=sources)
env.Depends(target=program, dependency=abspath("mcb-2019-2020/mcb-2019-2020-project/modm/link/linkerscript.ld"))

env.BuildTarget(sources)
