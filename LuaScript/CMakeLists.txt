# define minimum cmake version
cmake_minimum_required(VERSION 2.6.2)

# set the plugin name here
set( PLUGIN_NAME "LuaScript")

# Our project is called 'plugin' this is how it will be called in
# visual studio, and in our makefiles. 
project( ${PLUGIN_NAME} )

# Build lua lib
set (LUA_DIR ../sdk/lua)
if (UNIX AND NOT APPLE )
	set(LUA_TARGET linux)
else ( UNIX AND NOT APPLE )
	set(LUA_TARGET macosx)
endif ( UNIX AND NOT APPLE )
execute_process(COMMAND make ${LUA_TARGET} WORKING_DIRECTORY ${LUA_DIR})
execute_process(COMMAND mv ${LUA_DIR}/src/liblua.a ${CL_LIBPATH}/liblualib.a)


# It was noticed that when using MinGW gcc it is essential that 'core' is mentioned before 'base'.
find_package(wxWidgets COMPONENTS ${WX_COMPONENTS} REQUIRED)

# wxWidgets include (this will do all the magic to configure everything)
include( "${wxWidgets_USE_FILE}" )

# Include paths
include_directories("${CL_SRC_ROOT}/Plugin" "${CL_SRC_ROOT}/sdk/wxsqlite3/include" "${CL_SRC_ROOT}/CodeLite" "${CL_SRC_ROOT}/PCH" "${CL_SRC_ROOT}/Interfaces" "${LUA_DIR}/src", )

add_definitions(-DWXUSINGDLL_WXSQLITE3)
add_definitions(-DWXUSINGDLL_CL)
add_definitions(-DWXUSINGDLL_SDK)

if ( USE_PCH )
    add_definitions(-include "${CL_PCH_FILE}")
    add_definitions(-Winvalid-pch)
endif ( USE_PCH )

# Add RPATH
set (LINKER_OPTIONS -Wl,-rpath,"${PLUGINS_DIR}")

FILE(GLOB SRCS "*.cpp")

# Define the output
add_library(${PLUGIN_NAME} SHARED ${SRCS})

# Remove the "lib" prefix from the plugin name
set_target_properties(${PLUGIN_NAME} PROPERTIES PREFIX "")
target_link_libraries(${PLUGIN_NAME} ${LINKER_OPTIONS} ${wxWidgets_LIBRARIES} -L"${CL_LIBPATH}" -lwxsqlite3 -lsqlite3lib -llibcodelite -lplugin -llualib)

# Make sure that the plugin will not start build before 'plugin.so' is ready
add_dependencies(${PLUGIN_NAME} plugin)
install(TARGETS ${PLUGIN_NAME} DESTINATION ${PLUGINS_DIR})
