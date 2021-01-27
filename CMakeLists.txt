cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(polyphonic_vocoder)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

find_package(FFTW3)
find_package(JACK)

include_directories(include ${FFTW3_INCLUDE_DIR} ${JACK_INCLUDE_DIR})

file(GLOB SOURCES 
    src/main.cpp    
)

add_executable(polyphonic_vocoder ${SOURCES})

target_link_libraries(polyphonic_vocoder ${FFTW3_LIBRARY} ${JACK_LIBRARY})

install(TARGETS polyphonic_vocoder DESTINATION bin)