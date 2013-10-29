# define minimum cmake version
cmake_minimum_required(VERSION 2.6.2)
 
# Our project is called 'codelite' this is how it will be called in
# visual studio, and in our makefiles. 
project(codelite-terminal)

# It was noticed that when using MinGW gcc it is essential that 'core' is mentioned before 'base'.
find_package(wxWidgets COMPONENTS std stc REQUIRED)

# Add RPATH
set (LINKER_OPTIONS -Wl,-rpath,"${PLUGINS_DIR}")

# we need wxWidgets flags to be set only for the c++ files, so we do it like this
# by setting the CMAKE_CXX_FLAGS
execute_process(COMMAND ${CL_WX_CONFIG} --cxxflags OUTPUT_VARIABLE WX_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
set (CMAKE_CXX_FLAGS ${WX_CXX_FLAGS})

# prepare list of files
FILE(GLOB SRCS "*.cpp")

# Define the output
add_executable(codelite-terminal ${SRCS})
set ( UTIL_LIB "" )
if ( UNIX )
    set( UTIL_LIB "-lutil")
endif ( UNIX )

target_link_libraries(codelite-terminal ${LINKER_OPTIONS} ${wxWidgets_LIBRARIES} ${UTIL_LIB} )

install(TARGETS codelite-terminal DESTINATION ${CL_PREFIX}/bin)
add_dependencies(codelite-terminal plugin)