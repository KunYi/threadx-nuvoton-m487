# ThreadX v6.4.2 Porting for Nuvoton M487

This project provides a port of [Eclipse ThreadX RTOS](https://github.com/eclipse-threadx/threadx) version 6.4.2 to the Nuvoton M487 microcontroller.
The target board used for testing is [NuMaker-PFM-M487](https://www.nuvoton.com/products/microcontrollers/arm-cortex-m4-mcus/m487-ethernet-series/).

## 📌 Project Purpose

The goal of this project is to provide a working ThreadX RTOS environment on the Nuvoton M487 MCU, enabling developers to:

- Evaluate the performance and behavior of ThreadX on Nuvoton's Cortex-M4 platform.
- Use this as a reference or base for further embedded development with ThreadX on the M480 series.

## ✅ Features

- Ported ThreadX v6.4.2 kernel
- Startup code and context switch implemented for ARM Cortex-M4
- Demo project for NuMaker-PFM-M487 board
- GCC (Arm GNU Toolchain)

## 🔧 Requirements

- NuMaker-PFM-M487 development board
- CMake
- Arm GNU Toolchain (e.g., arm-none-eabi-gcc)
- Nuvoton-OpenOCD
- On board debugger: Nuvoton Nu-Link

## 🚀 Getting Started

1. Clone the repository:
    ```bash
    git clone https://github.com/KunYi/threadx-nuvoton-m487.git
    ```

2. Build the demo project using CMake
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   # output
   [  1%] Building ASM object thirdparty/threadx/CMakeFiles/threadx.dir/ports/cortex_m4/gnu/src/tx_thread_context_restore.S.obj
   [  1%] Building ASM object thirdparty/threadx/CMakeFiles/threadx.dir/ports/cortex_m4/gnu/src/tx_thread_context_save.S.obj
   [  2%] Building ASM object thirdparty/threadx/CMakeFiles/threadx.dir/ports/cortex_m4/gnu/src/tx_thread_interrupt_control.S.obj
   [  2%] Building ASM object thirdparty/threadx/CMakeFiles/threadx.dir/ports/cortex_m4/gnu/src/tx_thread_schedule.S.obj
   [  2%] Building ASM object thirdparty/threadx/CMakeFiles/threadx.dir/ports/cortex_m4/gnu/src/tx_thread_stack_build.S.obj
   [  3%] Building ASM object thirdparty/threadx/CMakeFiles/threadx.dir/ports/cortex_m4/gnu/src/tx_thread_system_return.S.obj
   [  3%] Building ASM object thirdparty/threadx/CMakeFiles/threadx.dir/ports/cortex_m4/gnu/src/tx_timer_interrupt.S.obj
   ...
   ...
   [ 99%] Building C object CMakeFiles/M480_ThreadX.elf.dir/M480BSP/Library/StdDriver/src/wdt.c.obj
   [ 99%] Building C object CMakeFiles/M480_ThreadX.elf.dir/M480BSP/Library/StdDriver/src/wwdt.c.obj
   [100%] Linking C executable M480_ThreadX.elf
   Memory region         Used Size  Region Size  %age Used
           FLASH:       32176 B       512 KB      6.14%
             RAM:       12844 B       128 KB      9.80%
       text	   data	    bss	    dec	    hex	filename
       32176	    156	  12688	  45020	   afdc	M480_ThreadX.elf
   [100%] Built target M480_ThreadX.elf
   ```

3. Flash the firmware to the NuMaker-PFM-M487 board.
   ```bash
   # use Nuvoton OpenOCD to flash
   openocd -f "interface/nulink.cfg" -f "target/numicroM4.cfg"  -c "program build/M480_ThreadX.elf verify reset exit"
   # output
   Open On-Chip Debugger 0.10.022.0-dev-00501-g66be6bee (2025-03-04-06:10)
   Licensed under GNU GPL v2
   For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
   Info : auto-selecting first available session transport "hla_swd". To override use 'transport select <transport>'.
   Info : The selected transport took over low-level target control. The results might differ compared to plain JTAG/SWD
   Info : clock speed 4000 kHz
   Info : NULINK is Nu-Link1
   Info : NULINK firmware_version(7313), product_id(0x40012009)
   Info : IDCODE: 0x2BA01477
   Info : NuMicro.cpu: hardware has 6 breakpoints, 4 watchpoints
   NuMicro.cpu: target state: halted
   target halted due to debug-request, current mode: Thread
   xPSR: 0x01000000 pc: 0x00000e00 msp: 0x20020000
   ** Programming Started **
   auto erase enabled
   Info : Device ID: 0x00d48750
   Info : Device Name: M487JIDAE
   Info : bank base = 0x00000000, size = 0x10080000
   Info : Nuvoton NuMicro: Sector Erase ... (0 to 7)
   Info : Nuvoton NuMicro: Flash Write ...
   Info : Program at 0x00000000 to 0x00002fff
   Info : Program at 0x00003000 to 0x00005fff
   Info : Program at 0x00006000 to 0x00007fff
   Warn : Adding extra erase range, 0x00007000 to 0x00007daf
   Info : Nuvoton NuMicro: Sector Erase ... (7 to 7)
   Info : Nuvoton NuMicro: Flash Write ...
   Info : Program at 0x00007db0 to 0x00007fff
   wrote 33360 bytes from file M480_ThreadX.elf in 3.623043s (8.992 KiB/s)
   ** Programming Finished **
   ** Verify Started **
   verified 32332 bytes in 0.742000s (42.553 KiB/s)
   ** Verified OK **
   ** Resetting Target **
   shutdown command invoked
   ```

4. Connect to a serial terminal to observe output (if demo includes UART debug).

## 🧩 Project Structure

The directory layout is as follows:

```
.
├── cmake			# cmake helper
│   ├── arm-none-eabi-gcc.cmake
│   └── m480bsp.cmake
├── CMakeLists.txt
├── CMakePresets.json
├── Core			# porting and demo code
│   ├── gcc_arm.ld
│   └── Src
│       ├── demo_threadx.c
│       ├── hal_clock.c
│       ├── main.c
│       └── tx_initialize_low_level.S
├── LICENSE			# License
├── M480BSP			# Nuvoton M480 BSP
│   └── Library
│       ├── CMSIS
│       ├── Device
│       ├── FWUpdate
│       ├── SmartcardLib
│       ├── StdDriver
│       └── UsbHostLib
├── README.md			# This file
└── thirdparty
    └── threadx  		# ThreadX core (v6.4.2)
        ├── cmake
        ├── CMakeLists.txt
        ├── common
        ├── common_modules
        ├── CONTRIBUTING.md
        ├── docs
        ├── LICENSE.txt
        ├── ports
        ├── ports_arch
        ├── ports_module
        ├── README.md
        ├── samples
        ├── scripts
        ├── SECURITY.md
        ├── test
        └── utility
```

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for details.

## 📬 Contact

KUN YI CHEN <kunyi.chen@gmail.com>

Feel free to reach out with any questions, feedback, or if you're interested in contributing to this project.
