cmake_minimum_required(VERSION 3.6)

set(TOOLCHAIN_PREFIX "C:/Tools/gcc-arm-none-eabi")
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/lib/scripts/STM32F103ZETx_FLASH.ld")

include(lib/cmake/toolchain-arm-none-eabi.cmake)
include(lib/cmake/binutils-arm-none-eabi.cmake)
include(lib/cmake/target.cmake)

project(executable C ASM)

file(GLOB_RECURSE SOURCES
    src/*.c
    src/app/*.c
    src/bsp/*.c
    lib/startup/*.[sc]
    lib/Drivers/STM32F1xx_HAL_Driver/Src/*.c
    lib/uC-OS3/Source/*.c
    lib/uC-OS3/uC-LIB/*.c
    lib/uC-OS3/uC-CPU/cpu_core.c
    lib/uC-OS3/uC-CPU/ARM-Cortex-M/ARMv7-M/cpu_c.c
    lib/uC-OS3/uC-CPU/ARM-Cortex-M/ARMv7-M/GNU/cpu_a.s
    lib/uC-OS3/Ports/ARM-Cortex-M/ARMv7-M/os_cpu_c.c
    lib/uC-OS3/Ports/ARM-Cortex-M/ARMv7-M/GNU/os_cpu_a.S
    lib/uC-OS3/Cfg/os_app_hooks.c
)

include_directories(
    inc
    src/bsp
    lib/Drivers/CMSIS/Include
    lib/Drivers/CMSIS/Device/ST/STM32F1xx/Include
    lib/Drivers/STM32F1xx_HAL_Driver/Inc
    lib/uC-OS3/Source
    lib/uC-OS3/uC-LIB
    lib/uC-OS3/uC-CPU
    lib/uC-OS3/uC-CPU/ARM-Cortex-M/ARMv7-M/GNU
    lib/uC-OS3/Ports/ARM-Cortex-M/ARMv7-M/GNU
    lib/uC-OS3/Cfg
)

add_executable(${PROJECT_NAME}.elf ${SOURCES})

target_link_libraries(${PROJECT_NAME}.elf
    gcc
    m
    nosys
    c
)

target_compile_definitions(${PROJECT_NAME}.elf PUBLIC
    -DSTM32F103xE
    -DUSE_FULL_LL_DRIVER
)

create_bin_output(${PROJECT_NAME})
