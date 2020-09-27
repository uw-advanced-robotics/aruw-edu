import os
import sys
from os.path import join, abspath

# path constants
PROJECT_NAME                = 'aruw-edu'
BUILD_PATH                  = 'build'
SOURCE_PATH                 = 'src'
TEST_PATH                   = 'test'
SOLUTIONS_PATH              = 'solutions'
ARUW_MCB_PATH               = 'aruw-mcb'
ARUW_MCB_PROJECT_PATH       = join(ARUW_MCB_PATH, 'aruw-mcb-project')
ARUW_MCB_SOURCE_PATH        = join(ARUW_MCB_PROJECT_PATH, 'src')
ARUW_MCB_TEST_PATH          = join(ARUW_MCB_PROJECT_PATH, 'test')
ARUW_MCB_HARDWARE_MODM_PATH = join(ARUW_MCB_PROJECT_PATH, 'modm')
ARUW_MCB_SIM_MODM_PATH      = join(ARUW_MCB_PROJECT_PATH, 'sim-modm/modm')
ARUW_MCB_ARUWLIB_PATH       = join(ARUW_MCB_PROJECT_PATH, 'src/aruwlib')
ARUW_MCB_ROBOT_TYPE_FILE    = join(ARUW_MCB_PROJECT_PATH, 'robot-type/robot_type.hpp')
ARUW_MCB_LINKERSCRIPT_FILE  = join(ARUW_MCB_HARDWARE_MODM_PATH, 'link/linkerscript.ld')

# External libs
GTEST_LIBS = ["gtest", "gtest_main", "gmock", "gmock_main", "pthread"]

VALID_ROBOT_TYPES       = ['TARGET_SOLDIER', 'TARGET_OLD_SOLDIER', 'TARGET_DRONE', 'TARGET_ENGINEER', 'TARGET_SENTINEL', 'TARGET_HERO']

USAGE = 'Usage: scons <target> [profile=<debug|release>] [robot=TARGET_<ROBOT_TYPE>] [use-solutions=[true|false]]\n\
    \"<target>\" is one of:\n\
        - \"build\": build all code for the hardware platform.\n\
        - \"run\": build all code for the hardware platform, and deploy it to the board via a connected ST-Link.\n\
        - \"build-tests\": build core code and tests for the current host platform.\n\
        - \"run-tests\": build core code and tests for the current host platform, and execute them locally with the test runner.\n\
    \"TARGET_<ROBOT_TYPE>\" is an optional argument that can override whatever robot type has been specified in robot_type.hpp.\n\
        - <ROBOT_TYPE> must be one of the following:\n\
            - SOLDIER, OLD_SOLDIER, DRONE, ENGINEER, SENTINEL, HERO\n\
    \"use-solutions\" indicates that files from the solutions directory should be used instead of files in /src'


# Don't compile this stuff
ignored_dirs = [ '.lbuild_cache', BUILD_PATH, ARUW_MCB_PATH, SOLUTIONS_PATH ]
ignored_files = []


if len(COMMAND_LINE_TARGETS) not in [1, 2, 3, 4]:
    raise Exception('This build script currently supports exactly one target per invocation.\n' + USAGE)


# Extract biuld environment, either test or hardware
build_target = COMMAND_LINE_TARGETS[0]
if build_target in ['build-tests', 'run-tests']:
    target_env = 'tests'
else:
    target_env = 'hardware'


# SCons environment with all tools
env = DefaultEnvironment(tools=[], ENV=os.environ)
env['CONFIG_BUILD_BASE'] = abspath(join(BUILD_PATH, target_env))
env['CONFIG_PROJECT_NAME'] = PROJECT_NAME


# Configure build jobs
if GetOption('num_jobs') == 1:
    SetOption('num_jobs', 8)


# Configure robot type and check against valid robot type
robot_type = ARGUMENTS.get('robot')
# If there is no optional argument, revert back to the macro in robot_type.hpp
if robot_type == None:
    with open(ARUW_MCB_ROBOT_TYPE_FILE, 'r') as robot_type_file_reader:
        for word in robot_type_file_reader.read().splitlines():
            if '#' in word and 'define' in word and 'TARGET_' in word:
                robot_type = word.split()[-1]
                break
if robot_type not in VALID_ROBOT_TYPES:
    raise Exception(USAGE)


print('Configured {0} parallel build jobs (-j{0}), {1}'.format(GetOption('num_jobs'), robot_type))


# Configure modm path based on build environment
modm_path = None
if target_env == 'hardware':
    modm_path = ARUW_MCB_HARDWARE_MODM_PATH
    ignored_dirs.append('test')
else:
    modm_path = ARUW_MCB_SIM_MODM_PATH
    ignored_files.append(join(SOURCE_PATH, 'main.cpp'))
    ignored_files.append(join(SOURCE_PATH, 'control/soldier_control.cpp'))


# Building all libraries (read from SConscript files located in provided dirs)
# Ensure that modm is first, otherwise aruwlib won't have the needed build config
EXTERNAL_SCONS_LIBRARIES = [ modm_path, ARUW_MCB_ARUWLIB_PATH ]
env.SConscript(dirs=EXTERNAL_SCONS_LIBRARIES, exports='env')


# Configure build flags that are unique to debug or release profile
profile = ARGUMENTS.get('profile', 'release')

if profile == 'debug':
    env.Append(CCFLAGS = ['-fno-inline'])

env.Append(CPPFLAGS = [
    '-DENV_' + {'hardware': 'HARDWARE', 'tests': 'SIMULATOR'}[target_env]
])

if 'additional-ccflags' in ARGUMENTS:
    env.Append(CCFLAGS = [
       *ARGUMENTS['additional-ccflags'].split(','),
    ])

env.AppendUnique(CPPPATH=[
    abspath(SOURCE_PATH),
    abspath(ARUW_MCB_SOURCE_PATH)
])

# append on the global robot target build flag instead of including the file manually
env.Append(CCFLAGS=['-D ' + robot_type])

if target_env == 'tests':
    env.AppendUnique(CPPPATH=[
        abspath(r'./test'),
        abspath(ARUW_MCB_TEST_PATH)
    ])
    
    env.AppendUnique(LIBS=GTEST_LIBS)


sources = env.FindSourceFiles('.', ignorePaths=ignored_dirs, ignoreFiles=ignored_files)


# Substitute actual files if use solutions is specified
if ARGUMENTS.get('use-solutions', 'false') == 'true':
    solution_sources = env.FindSourceFiles(SOLUTIONS_PATH)
    # find and replace each file from solution_sources
    for file in solution_sources:
        try:
            source_file_index = sources.index(file.replace(SOLUTIONS_PATH, SOURCE_PATH))
            sources[source_file_index] = file
        except ValueError:
            raise Exception('{0} is in the solution directory but does not exist in the source files'.format(file))
    env.AppendUnique(CPPPATH=[abspath(SOLUTIONS_PATH)])


if target_env == 'hardware':
    program = env.Program(target=env['CONFIG_PROJECT_NAME']+'.elf', source=sources)

    # SCons functions
    env.Alias('build', program)
    # The executable depends on the linkerscript

    # This is a copy of the BuildTarget SCons functions from build_target.py, but the linker
    # path dependency is changed.
    env.Alias('qtcreator', env.QtCreatorProject(sources))
    env.Alias('symbols', env.Symbols(program))
    env.Alias('listing', env.Listing(program))
    env.Alias('bin', env.Bin(program))
    env.Alias('build', program)
    # The executable depends on the linkerscript
    env.Depends(target=program,
                dependency=abspath(ARUW_MCB_LINKERSCRIPT_FILE))
    env.Alias('size', env.Size(program))
    env.Alias('itm', env.OpenOcdItm())
    env.Alias('gdb', env.OpenOcdGdb(program))
    env.Alias('postmortem', env.PostMortemGdb(program))
    env.Alias('artifact', env.CacheArtifact(program))

    env.Alias('program', env.OpenOcd(program, commands=['modm_program {$SOURCE}']))
    env.Alias('bmp', env.BlackMagicProbe(program))
    env.Alias('all', ['build', 'size'])
    env.Default('all')
else:
    program = env.Program(target=env['CONFIG_PROJECT_NAME']+'-tests.exe', source=sources)
    # WARNING: all test targets must be included in the target_env check earlier in the file
    env.Alias('build-tests', program)
    env.Alias('run-tests', env.Run(program))
