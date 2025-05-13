
cmake_minimum_required(VERSION 3.16)

# Path to toolchain file. This one has to be before 'project()' below
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/arm-none-eabi-gcc.cmake)

project(M480_ThreadX)

set(EXECUTABLE ${PROJECT_NAME}.elf)
# set(LINKER_FILE ${M480_DEVICE_DIR}/Source/GCC/gcc_arm.ld)
set(LINKER_FILE ${CMAKE_SOURCE_DIR}/Core/gcc_arm.ld)

set(CMAKE_C_FLAGS_DEBUG
  "-O0 -ggdb"
  CACHE INTERNAL " C compiler flags")
set(CMAKE_C_FLAGS_RELEASE
  "-O3"
  CACHE INTERNAL " C compiler flags")
set(CMAKE_C_FLAGS_RELWITHDEBINFO
  "-O3 -ggdb"
  CACHE INTERNAL " C compiler flags")
set(CMAKE_C_FLAGS_MINSIZEREL
  "-O3"
  CACHE INTERNAL " C compiler flags")


add_compile_options(
  -mcpu=cortex-m4
  -mthumb
  -mfpu=fpv4-sp-d16
  -mfloat-abi=hard

  -fdata-sections
  -ffunction-sections

  -DUSE_HAL_DRIVER
  -DSTM32F429xx

  -DTX_ENABLE_FPU_SUPPORT
  -Wall
)

enable_language(C ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(THREADX_ARCH cortex_m4)
set(THREADX_TOOLCHAIN gnu)
add_subdirectory(thirdparty/threadx)

set(THREADX_DIR
  ${CMAKE_SOURCE_DIR}/thirdparty/threadx/inc
)

include(cmake/m480bsp.cmake)

set(SRC_FILES
  Core/Src/tx_initialize_low_level.S
  Core/Src/hal_clock.c
  Core/Src/main.c
  Core/Src/demo_threadx.c
)

# Build the executable based on the source files
add_executable(${EXECUTABLE} ${SRC_FILES})

target_link_libraries(${EXECUTABLE}
  threadx
  m480bsp
)

# List of includ directories
target_include_directories(${EXECUTABLE} PRIVATE
  ${CMAKE_SOURCE_DIR}
  ${THREADX_DIR}
  m480bsp
)

# Compiler options
# target_compile_options(${EXECUTABLE} PRIVATE
#         )

# Linker options
target_link_options(${EXECUTABLE} PRIVATE
  -T${LINKER_FILE}
  -mcpu=cortex-m4
  -mthumb
  -mfpu=fpv4-sp-d16
  -mfloat-abi=hard
  -specs=nano.specs
  -specs=nosys.specs
  -lc
  -lm
  -Wl,-Map=${PROJECT_NAME}.map,--cref
  -Wl,--gc-sections
  -Xlinker -print-memory-usage -Xlinker
)

# Optional: Print executable size as part of the post build process
add_custom_command(TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND ${CMAKE_SIZE_UTIL} ${EXECUTABLE})

# Optional: Create hex, bin and S-Record files after the build
add_custom_command(TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
  COMMAND ${CMAKE_OBJCOPY} -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)
