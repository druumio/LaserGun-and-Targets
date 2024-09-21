add_library(pico_servo
        pico_servo.cpp)

target_link_libraries(pico_servo
        hardware_pwm        
        pico_stdlib)
        
target_include_directories(pico_servo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})