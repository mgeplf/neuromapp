include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})

add_executable (app driver.cpp main.cpp)
target_link_libraries (app
                       hello
                       keyvalue
                       coreneuron10_kernel
                       coreneuron10_solver
                       coreneuron10_cstep
                       coreneuron10_event
                       synapse
                       replib
                       storage
                       ${READLINE_LIBRARY}
                       ${CURSES_CURSES_LIBRARY}
                       ${Boost_PROGRAM_OPTIONS_LIBRARIES}
                       ${Boost_CHRONO_LIBRARIES}
                       ${Boost_SYSTEM_LIBRARIES}
                       ${Boost_ATOMIC_LIBRARIES})
install (TARGETS app DESTINATION bin)
