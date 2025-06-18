cmake_minimum_required(VERSION 3.10)
project(Chess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add SFML info
set(SFML_INCLUDE_DIRS "C:/Program Files/SFML-2.6.2/include")
set(SFML_LIB_DIR "C:/Program Files/SFML-2.6.2/lib")
file(GLOB SFML_LIBS "C:/Program Files/SFML-2.6.2/lib/lib*.a")
file(GLOB SFML_DLLS "C:/Program Files/SFML-2.6.2/bin/*.dll")


# Show SFML info
message(STATUS "SFML include dirs: ${SFML_INCLUDE_DIRS}")
message(STATUS "SFML libraries: ${SFML_LIBS}")

# Add libraries
link_directories(${SFML_LIB_DIR})

# Main executable and sources
add_executable(Chess
    src/menu.cpp 
    src/board.cpp
    src/player.cpp
    src/piece.cpp
    src/chessGUI.cpp
)

# Include directories
target_include_directories(Chess PRIVATE
    ${SFML_INCLUDE_DIRS}
    include
)

# Link libraries
target_link_libraries(Chess PRIVATE ${SFML_LIBS} )

# Copy SFML DLLs after build
foreach(dll ${SFML_DLLS})
    add_custom_command(TARGET Chess POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${dll}" $<TARGET_FILE_DIR:Chess>)
endforeach()









