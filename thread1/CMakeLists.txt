MESSAGE(STATUS "===============================")
MESSAGE(STATUS "Thread1 Configuration")
MESSAGE(STATUS "===============================")
project(thread1)

add_library(${PROJECT_NAME} STATIC ${BACKWARD_ENABLE})
add_backward(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC 
    fmt::fmt
)
target_include_directories(${PROJECT_NAME} PUBLIC 
    src
)

file(GLOB SOURCE CONFIGURE_DEPENDS "src/*")
add_executable(${PROJECT_NAME}_exe ${SOURCE})
target_link_libraries(${PROJECT_NAME}_exe PUBLIC ${PROJECT_NAME})