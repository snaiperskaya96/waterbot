cmake_minimum_required(VERSION 3.0)
project(WaterBot)

set(CMAKE_CXX_STANDARD 11)

option(DEBUG "Prints debugging information." OFF)
option(RASPI "If OFF do not compile raspi's specific libraries (WiringPi) and use random values instead." ON)

set(WATERBOT_BIN_DIR "/usr/local/bin")
set(WATERBOT_CONF_DIR "/etc/WaterBot")
set(SYSTEMD_UNIT_DIR "/usr/lib/systemd/system")
set(ADDITIONAL_LIBRARIES)
set(ADDITIONAL_INCLUDES)

if(RASPI)
    message("Compiling using Raspberry configuration (Use -DRASPI=OFF to disable)")
    set(ADDITIONAL_LIBRARIES ${ADDITIONAL_LIBRARIES} wiringPi)
    add_definitions(-DWATERBOT_RASPI)
endif()

if(DEBUG)
    message("Compiling using Debug configuration")
    add_definitions(-DWATERBOT_DEBUG)
endif()

find_package(CURL REQUIRED)

include_directories(Source Source/Utils)

set(SOURCE_FILES
        Source/WaterBot.cpp Source/Config/Config.cpp Source/Config/Config.h Source/Utils/Ini/ini.h
        Source/Utils/Ini/ini.c Source/Utils/Ini/INIReader.cpp Source/Utils/Ini/INIReader.h
        Source/Plant/Plant.h Source/Plant/Plant.cpp Source/Http/Http.cpp Source/Http/Http.h
        Source/Utils/restclient-cpp/connection.cc Source/Utils/restclient-cpp/connection.h
        Source/Utils/restclient-cpp/helpers.cc Source/Utils/restclient-cpp/helpers.h
        Source/Utils/restclient-cpp/restclient.cc Source/Utils/restclient-cpp/restclient.h Source/WaterBot.h Source/Utils/Input/InputParser.h)

add_executable(WaterBot ${SOURCE_FILES})
target_link_libraries(WaterBot ${CURL_LIBRARIES} ${ADDITIONAL_LIBRARIES})
target_include_directories(WaterBot PUBLIC ${CURL_INCLUDE_DIRS} ${ADDITIONAL_INCLUDES})

# Macro for installing configuration files
# https://github.com/jirihnidek/daemon/blob/master/CMakeLists.txt
function(install_conf src dest)
    if(NOT IS_ABSOLUTE "${src}")
        set(src "${CMAKE_CURRENT_SOURCE_DIR}/${src}")
    endif()
    get_filename_component(src_name "${src}" NAME)
    if (NOT IS_ABSOLUTE "${dest}")
        set(dest "${CMAKE_INSTALL_PREFIX}/${dest}")
    endif()
    install(CODE "
    if(NOT EXISTS \"\$ENV{DESTDIR}${dest}/${src_name}\")
      #file(INSTALL \"${src}\" DESTINATION \"${dest}\")
      message(STATUS \"Installing: \$ENV{DESTDIR}${dest}/${src_name}\")
      execute_process(COMMAND \${CMAKE_COMMAND} -E copy \"${src}\"
                      \"\$ENV{DESTDIR}${dest}/${src_name}\"
                      RESULT_VARIABLE copy_result
                      ERROR_VARIABLE error_output)
      if(copy_result)
        message(FATAL_ERROR \${error_output})
      endif()
    else()
      message(STATUS \"Skipping  : \$ENV{DESTDIR}${dest}/${src_name}\")
    endif()
  ")
endfunction(install_conf)


install(DIRECTORY DESTINATION /etc/WaterBot)
install(TARGETS WaterBot DESTINATION /usr/local/bin)
install_conf(./WaterBot.ini ${WATERBOT_CONF_DIR})
install_conf(./Service/waterbot.service ${SYSTEMD_UNIT_DIR})