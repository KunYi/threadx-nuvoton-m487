add_library(m480bsp INTERFACE)
set(M480LIB_DIR ${CMAKE_SOURCE_DIR}/M480BSP/Library)
set(M480BSP_STDDRIVE_DIR ${M480LIB_DIR}/StdDriver)
set(M480BSP_CMSIS_DIR ${M480LIB_DIR}/CMSIS)

target_sources(m480bsp INTERFACE
	${M480LIB_DIR}/Device/Nuvoton/M480/Source/system_M480.c
	${M480LIB_DIR}/Device/Nuvoton/M480/Source/GCC/startup_M480.S
	${M480BSP_STDDRIVE_DIR}/src/acmp.c
	${M480BSP_STDDRIVE_DIR}/src/bpwm.c
	${M480BSP_STDDRIVE_DIR}/src/can.c
	${M480BSP_STDDRIVE_DIR}/src/ccap.c
	${M480BSP_STDDRIVE_DIR}/src/clk.c
	${M480BSP_STDDRIVE_DIR}/src/crc.c
	${M480BSP_STDDRIVE_DIR}/src/crypto.c
	${M480BSP_STDDRIVE_DIR}/src/dac.c
	${M480BSP_STDDRIVE_DIR}/src/eadc.c
	${M480BSP_STDDRIVE_DIR}/src/ebi.c
	${M480BSP_STDDRIVE_DIR}/src/ecap.c
	${M480BSP_STDDRIVE_DIR}/src/emac.c
	${M480BSP_STDDRIVE_DIR}/src/epwm.c
	${M480BSP_STDDRIVE_DIR}/src/fmc.c
	${M480BSP_STDDRIVE_DIR}/src/gpio.c
	${M480BSP_STDDRIVE_DIR}/src/hsusbd.c
	${M480BSP_STDDRIVE_DIR}/src/i2c.c
	${M480BSP_STDDRIVE_DIR}/src/i2s.c
	${M480BSP_STDDRIVE_DIR}/src/pdma.c
	${M480BSP_STDDRIVE_DIR}/src/qei.c
	${M480BSP_STDDRIVE_DIR}/src/qspi.c
	${M480BSP_STDDRIVE_DIR}/src/retarget.c
	${M480BSP_STDDRIVE_DIR}/src/rtc.c
	${M480BSP_STDDRIVE_DIR}/src/sc.c
	${M480BSP_STDDRIVE_DIR}/src/scuart.c
	${M480BSP_STDDRIVE_DIR}/src/sdh.c
	${M480BSP_STDDRIVE_DIR}/src/spi.c
	${M480BSP_STDDRIVE_DIR}/src/spim.c
	${M480BSP_STDDRIVE_DIR}/src/sys.c
	${M480BSP_STDDRIVE_DIR}/src/timer.c
	${M480BSP_STDDRIVE_DIR}/src/timer_pwm.c
	${M480BSP_STDDRIVE_DIR}/src/trng.c
	${M480BSP_STDDRIVE_DIR}/src/uart.c
	${M480BSP_STDDRIVE_DIR}/src/usbd.c
	${M480BSP_STDDRIVE_DIR}/src/usci_i2c.c
	${M480BSP_STDDRIVE_DIR}/src/usci_spi.c
	${M480BSP_STDDRIVE_DIR}/src/usci_uart.c
	${M480BSP_STDDRIVE_DIR}/src/wdt.c
	${M480BSP_STDDRIVE_DIR}/src/wwdt.c
)

target_include_directories(m480bsp INTERFACE
	${M480LIB_DIR}/Device/Nuvoton/M480/Include
	${M480BSP_STDDRIVE_DIR}/inc
	${M480BSP_CMSIS_DIR}/Include
)
