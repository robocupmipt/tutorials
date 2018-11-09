cmake_minimum_required(VERSION 2.8)

# Give a name to the project.
project(mymodule)

# You need this to find the qiBuild CMake framework
find_package(qibuild)

# Create an option to make is possible compiling the module
# as a remote executable, or as a local shared library
option(MYMODULE_IS_REMOTE
  "module is compiled as a remote module (ON or OFF)"
  ON)

# Create a list of source files
set(_srcs
    mymodule.cpp
    mymodule.h
    main.cpp)

if(MYMODULE_IS_REMOTE)
  # Add a compile flag because code changes a little bit
  # when we are compiling an executable
  # This will let you use #ifdef HELLOWORLD_IS_REMOTE
  # in the C++ code
  add_definitions( " -DMYMODULE_IS_REMOTE ")

  # Create an executable
  qi_create_bin(mymodule ${_srcs})
else()
  # Create a plugin, that is a shared library, and make
  # sure it is built in lib/naoqi, so that the naoqi executable
  # can find it later
  qi_create_lib(mymodule SHARED ${_srcs} SUBFOLDER naoqi)
endif()

# Tell CMake that mymodule depends on ALCOMMON and ALPROXIES.
# This will set the libraries to link mymodule with,
# the include paths, and so on
qi_use_lib(mymodule ALCOMMON ALPROXIES BOOST)
