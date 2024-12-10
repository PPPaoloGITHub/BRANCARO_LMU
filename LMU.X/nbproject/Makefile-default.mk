#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/LMU.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/LMU.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Application/AppSpecific/System/CAN/CANFeedback.c Application/AppSpecific/System/Version/Version.c Application/ProductLibrary/Application/Main/AppMain.c Application/ProductLibrary/Application/ResetTest/ResetTest.c Application/ProductLibrary/Driver/ADC/ADCManager.c Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.c Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.c Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.c Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.c Application/ProductLibrary/Driver/SwPWM/SwPWM.c Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.c Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.c Application/ProductLibrary/System/CAN/CANRecvdMsgParser.c Application/ProductLibrary/System/Timers/Timers.c mcc_generated_files/adc/src/adc1.c mcc_generated_files/boot/memory_partition.S mcc_generated_files/boot/hardware_interrupt_table.S mcc_generated_files/boot/user_interrupt_table.S mcc_generated_files/boot/application_header_crc32.S mcc_generated_files/boot/interrupts.S mcc_generated_files/can/src/can1.c mcc_generated_files/i2c_host/src/i2c1.c mcc_generated_files/system/src/interrupt.c mcc_generated_files/system/src/traps.c mcc_generated_files/system/src/pins.c mcc_generated_files/system/src/dmt_asm.s mcc_generated_files/system/src/dmt.c mcc_generated_files/system/src/reset.c mcc_generated_files/system/src/config_bits.c mcc_generated_files/system/src/clock.c mcc_generated_files/system/src/system.c mcc_generated_files/timer/src/tmr1.c mcc_generated_files/uart/src/uart1.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Application/AppSpecific/System/CAN/CANFeedback.o ${OBJECTDIR}/Application/AppSpecific/System/Version/Version.o ${OBJECTDIR}/Application/ProductLibrary/Application/Main/AppMain.o ${OBJECTDIR}/Application/ProductLibrary/Application/ResetTest/ResetTest.o ${OBJECTDIR}/Application/ProductLibrary/Driver/ADC/ADCManager.o ${OBJECTDIR}/Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.o ${OBJECTDIR}/Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.o ${OBJECTDIR}/Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.o ${OBJECTDIR}/Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.o ${OBJECTDIR}/Application/ProductLibrary/Driver/SwPWM/SwPWM.o ${OBJECTDIR}/Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.o ${OBJECTDIR}/Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.o ${OBJECTDIR}/Application/ProductLibrary/System/CAN/CANRecvdMsgParser.o ${OBJECTDIR}/Application/ProductLibrary/System/Timers/Timers.o ${OBJECTDIR}/mcc_generated_files/adc/src/adc1.o ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o ${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o ${OBJECTDIR}/mcc_generated_files/boot/application_header_crc32.o ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o ${OBJECTDIR}/mcc_generated_files/can/src/can1.o ${OBJECTDIR}/mcc_generated_files/i2c_host/src/i2c1.o ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o ${OBJECTDIR}/mcc_generated_files/system/src/traps.o ${OBJECTDIR}/mcc_generated_files/system/src/pins.o ${OBJECTDIR}/mcc_generated_files/system/src/dmt_asm.o ${OBJECTDIR}/mcc_generated_files/system/src/dmt.o ${OBJECTDIR}/mcc_generated_files/system/src/reset.o ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o ${OBJECTDIR}/mcc_generated_files/system/src/clock.o ${OBJECTDIR}/mcc_generated_files/system/src/system.o ${OBJECTDIR}/mcc_generated_files/timer/src/tmr1.o ${OBJECTDIR}/mcc_generated_files/uart/src/uart1.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Application/AppSpecific/System/CAN/CANFeedback.o.d ${OBJECTDIR}/Application/AppSpecific/System/Version/Version.o.d ${OBJECTDIR}/Application/ProductLibrary/Application/Main/AppMain.o.d ${OBJECTDIR}/Application/ProductLibrary/Application/ResetTest/ResetTest.o.d ${OBJECTDIR}/Application/ProductLibrary/Driver/ADC/ADCManager.o.d ${OBJECTDIR}/Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.o.d ${OBJECTDIR}/Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.o.d ${OBJECTDIR}/Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.o.d ${OBJECTDIR}/Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.o.d ${OBJECTDIR}/Application/ProductLibrary/Driver/SwPWM/SwPWM.o.d ${OBJECTDIR}/Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.o.d ${OBJECTDIR}/Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.o.d ${OBJECTDIR}/Application/ProductLibrary/System/CAN/CANRecvdMsgParser.o.d ${OBJECTDIR}/Application/ProductLibrary/System/Timers/Timers.o.d ${OBJECTDIR}/mcc_generated_files/adc/src/adc1.o.d ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o.d ${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o.d ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o.d ${OBJECTDIR}/mcc_generated_files/boot/application_header_crc32.o.d ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o.d ${OBJECTDIR}/mcc_generated_files/can/src/can1.o.d ${OBJECTDIR}/mcc_generated_files/i2c_host/src/i2c1.o.d ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d ${OBJECTDIR}/mcc_generated_files/system/src/traps.o.d ${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d ${OBJECTDIR}/mcc_generated_files/system/src/dmt_asm.o.d ${OBJECTDIR}/mcc_generated_files/system/src/dmt.o.d ${OBJECTDIR}/mcc_generated_files/system/src/reset.o.d ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o.d ${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d ${OBJECTDIR}/mcc_generated_files/system/src/system.o.d ${OBJECTDIR}/mcc_generated_files/timer/src/tmr1.o.d ${OBJECTDIR}/mcc_generated_files/uart/src/uart1.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Application/AppSpecific/System/CAN/CANFeedback.o ${OBJECTDIR}/Application/AppSpecific/System/Version/Version.o ${OBJECTDIR}/Application/ProductLibrary/Application/Main/AppMain.o ${OBJECTDIR}/Application/ProductLibrary/Application/ResetTest/ResetTest.o ${OBJECTDIR}/Application/ProductLibrary/Driver/ADC/ADCManager.o ${OBJECTDIR}/Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.o ${OBJECTDIR}/Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.o ${OBJECTDIR}/Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.o ${OBJECTDIR}/Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.o ${OBJECTDIR}/Application/ProductLibrary/Driver/SwPWM/SwPWM.o ${OBJECTDIR}/Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.o ${OBJECTDIR}/Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.o ${OBJECTDIR}/Application/ProductLibrary/System/CAN/CANRecvdMsgParser.o ${OBJECTDIR}/Application/ProductLibrary/System/Timers/Timers.o ${OBJECTDIR}/mcc_generated_files/adc/src/adc1.o ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o ${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o ${OBJECTDIR}/mcc_generated_files/boot/application_header_crc32.o ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o ${OBJECTDIR}/mcc_generated_files/can/src/can1.o ${OBJECTDIR}/mcc_generated_files/i2c_host/src/i2c1.o ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o ${OBJECTDIR}/mcc_generated_files/system/src/traps.o ${OBJECTDIR}/mcc_generated_files/system/src/pins.o ${OBJECTDIR}/mcc_generated_files/system/src/dmt_asm.o ${OBJECTDIR}/mcc_generated_files/system/src/dmt.o ${OBJECTDIR}/mcc_generated_files/system/src/reset.o ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o ${OBJECTDIR}/mcc_generated_files/system/src/clock.o ${OBJECTDIR}/mcc_generated_files/system/src/system.o ${OBJECTDIR}/mcc_generated_files/timer/src/tmr1.o ${OBJECTDIR}/mcc_generated_files/uart/src/uart1.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=Application/AppSpecific/System/CAN/CANFeedback.c Application/AppSpecific/System/Version/Version.c Application/ProductLibrary/Application/Main/AppMain.c Application/ProductLibrary/Application/ResetTest/ResetTest.c Application/ProductLibrary/Driver/ADC/ADCManager.c Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.c Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.c Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.c Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.c Application/ProductLibrary/Driver/SwPWM/SwPWM.c Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.c Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.c Application/ProductLibrary/System/CAN/CANRecvdMsgParser.c Application/ProductLibrary/System/Timers/Timers.c mcc_generated_files/adc/src/adc1.c mcc_generated_files/boot/memory_partition.S mcc_generated_files/boot/hardware_interrupt_table.S mcc_generated_files/boot/user_interrupt_table.S mcc_generated_files/boot/application_header_crc32.S mcc_generated_files/boot/interrupts.S mcc_generated_files/can/src/can1.c mcc_generated_files/i2c_host/src/i2c1.c mcc_generated_files/system/src/interrupt.c mcc_generated_files/system/src/traps.c mcc_generated_files/system/src/pins.c mcc_generated_files/system/src/dmt_asm.s mcc_generated_files/system/src/dmt.c mcc_generated_files/system/src/reset.c mcc_generated_files/system/src/config_bits.c mcc_generated_files/system/src/clock.c mcc_generated_files/system/src/system.c mcc_generated_files/timer/src/tmr1.c mcc_generated_files/uart/src/uart1.c main.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
_/_=\\
ShExtension=.bat
Device=dsPIC33CH512MP506
ProjectDir="C:\PAOLO\Progetti_GIT\LMU\LMU.X"
ProjectName=LMU
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\LMU.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="LMU.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/LMU.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [cd mcc_generated_files/boot && .${_/_}postBuild$(ShExtension) $(MP_CC_DIR) ${ProjectDir} ${ImageDir} ${ImageName} ${IsDebug} && cd ${ProjectDir}]"
	@cd mcc_generated_files/boot && .${_/_}postBuild$(ShExtension) $(MP_CC_DIR) ${ProjectDir} ${ImageDir} ${ImageName} ${IsDebug} && cd ${ProjectDir}
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=33CH512MP506
MP_LINKER_FILE_OPTION=,--script=p33CH512MP506.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Application/AppSpecific/System/CAN/CANFeedback.o: Application/AppSpecific/System/CAN/CANFeedback.c  .generated_files/flags/default/ec9b3bcf7ddb9e91faa28aa68f7bae7513b7fc48 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/AppSpecific/System/CAN" 
	@${RM} ${OBJECTDIR}/Application/AppSpecific/System/CAN/CANFeedback.o.d 
	@${RM} ${OBJECTDIR}/Application/AppSpecific/System/CAN/CANFeedback.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/AppSpecific/System/CAN/CANFeedback.c  -o ${OBJECTDIR}/Application/AppSpecific/System/CAN/CANFeedback.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/AppSpecific/System/CAN/CANFeedback.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/AppSpecific/System/Version/Version.o: Application/AppSpecific/System/Version/Version.c  .generated_files/flags/default/5623cc96ad49de4d3cd236c0a9a31d2cd3b1b61b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/AppSpecific/System/Version" 
	@${RM} ${OBJECTDIR}/Application/AppSpecific/System/Version/Version.o.d 
	@${RM} ${OBJECTDIR}/Application/AppSpecific/System/Version/Version.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/AppSpecific/System/Version/Version.c  -o ${OBJECTDIR}/Application/AppSpecific/System/Version/Version.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/AppSpecific/System/Version/Version.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Application/Main/AppMain.o: Application/ProductLibrary/Application/Main/AppMain.c  .generated_files/flags/default/c6da107f68a95d64c6c65da129b6c037d07ae6fc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Application/Main" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Application/Main/AppMain.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Application/Main/AppMain.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Application/Main/AppMain.c  -o ${OBJECTDIR}/Application/ProductLibrary/Application/Main/AppMain.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Application/Main/AppMain.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Application/ResetTest/ResetTest.o: Application/ProductLibrary/Application/ResetTest/ResetTest.c  .generated_files/flags/default/606b2fbb3f5f301ebbabe4599cad04e7e98c3643 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Application/ResetTest" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Application/ResetTest/ResetTest.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Application/ResetTest/ResetTest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Application/ResetTest/ResetTest.c  -o ${OBJECTDIR}/Application/ProductLibrary/Application/ResetTest/ResetTest.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Application/ResetTest/ResetTest.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Driver/ADC/ADCManager.o: Application/ProductLibrary/Driver/ADC/ADCManager.c  .generated_files/flags/default/bb4b2d7961d3954386fadf951e989bef07191a0b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Driver/ADC" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/ADC/ADCManager.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/ADC/ADCManager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Driver/ADC/ADCManager.c  -o ${OBJECTDIR}/Application/ProductLibrary/Driver/ADC/ADCManager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Driver/ADC/ADCManager.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.o: Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.c  .generated_files/flags/default/40f4e54b6b116ebb03e71f307c6bd8fd09892010 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Driver/ADS7128_ADC_EXP" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.c  -o ${OBJECTDIR}/Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.o: Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.c  .generated_files/flags/default/e81201759ad4db34734af87587a06ee62529e875 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Driver/EEPROM24LC512" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.c  -o ${OBJECTDIR}/Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.o: Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.c  .generated_files/flags/default/15b90f5e59f668a6f5c6d8e1d723d079446d9985 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Driver/MCP23017_IO_EXP" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.c  -o ${OBJECTDIR}/Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.o: Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.c  .generated_files/flags/default/3e69a0bee1178bda71c79192aa59b73600ad1608 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Driver/PCA9685_IO_PWM" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.c  -o ${OBJECTDIR}/Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Driver/SwPWM/SwPWM.o: Application/ProductLibrary/Driver/SwPWM/SwPWM.c  .generated_files/flags/default/78aec935b872fb1323a704293cf2b5c58ac09c4e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Driver/SwPWM" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/SwPWM/SwPWM.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/SwPWM/SwPWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Driver/SwPWM/SwPWM.c  -o ${OBJECTDIR}/Application/ProductLibrary/Driver/SwPWM/SwPWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Driver/SwPWM/SwPWM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.o: Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.c  .generated_files/flags/default/b46a7c7b5e3a7a42e4b8d24a2be83b4ffed806b5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Lsi/HW_HeartBeat" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.c  -o ${OBJECTDIR}/Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.o: Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.c  .generated_files/flags/default/2729b672082e3e4058b4d7589db6028f0783d892 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Lsi/LED_OnBoard" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.c  -o ${OBJECTDIR}/Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/System/CAN/CANRecvdMsgParser.o: Application/ProductLibrary/System/CAN/CANRecvdMsgParser.c  .generated_files/flags/default/f2fc65a4267cb99637cfc527270a0d419ea0fd99 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/System/CAN" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/System/CAN/CANRecvdMsgParser.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/System/CAN/CANRecvdMsgParser.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/System/CAN/CANRecvdMsgParser.c  -o ${OBJECTDIR}/Application/ProductLibrary/System/CAN/CANRecvdMsgParser.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/System/CAN/CANRecvdMsgParser.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/System/Timers/Timers.o: Application/ProductLibrary/System/Timers/Timers.c  .generated_files/flags/default/ec70c84438067f1485564fec7fd854be9ca35ec4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/System/Timers" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/System/Timers/Timers.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/System/Timers/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/System/Timers/Timers.c  -o ${OBJECTDIR}/Application/ProductLibrary/System/Timers/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/System/Timers/Timers.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/adc/src/adc1.o: mcc_generated_files/adc/src/adc1.c  .generated_files/flags/default/83367764b94c5290624c704a2e1dafda0a573200 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/adc/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc/src/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc/src/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/adc/src/adc1.c  -o ${OBJECTDIR}/mcc_generated_files/adc/src/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc/src/adc1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/can/src/can1.o: mcc_generated_files/can/src/can1.c  .generated_files/flags/default/e372b2f88baac96afe3829b3372f4c2dcd60f39a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/can/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/can/src/can1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/can/src/can1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/can/src/can1.c  -o ${OBJECTDIR}/mcc_generated_files/can/src/can1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/can/src/can1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/i2c_host/src/i2c1.o: mcc_generated_files/i2c_host/src/i2c1.c  .generated_files/flags/default/446d1494b9a8d8f30b926e6fa78522c5ae9de1dc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/i2c_host/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c_host/src/i2c1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c_host/src/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/i2c_host/src/i2c1.c  -o ${OBJECTDIR}/mcc_generated_files/i2c_host/src/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/i2c_host/src/i2c1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o: mcc_generated_files/system/src/interrupt.c  .generated_files/flags/default/c16436a4a7674e86ad5eab1236b29c3e530f1903 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system/src/interrupt.c  -o ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system/src/traps.o: mcc_generated_files/system/src/traps.c  .generated_files/flags/default/d01a6e128cb7812d6abbaa1ea8da8268baf99ce5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system/src/traps.c  -o ${OBJECTDIR}/mcc_generated_files/system/src/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system/src/traps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system/src/pins.o: mcc_generated_files/system/src/pins.c  .generated_files/flags/default/116a36763500a7c79b235be9f0c892c73404afcb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/pins.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system/src/pins.c  -o ${OBJECTDIR}/mcc_generated_files/system/src/pins.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system/src/dmt.o: mcc_generated_files/system/src/dmt.c  .generated_files/flags/default/892f72b3ee89b0a932d9f6e468a6cbb072fb8d23 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/dmt.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/dmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system/src/dmt.c  -o ${OBJECTDIR}/mcc_generated_files/system/src/dmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system/src/dmt.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system/src/reset.o: mcc_generated_files/system/src/reset.c  .generated_files/flags/default/7c6539c524668b7809a87d2c3a58b86888c66496 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/reset.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/reset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system/src/reset.c  -o ${OBJECTDIR}/mcc_generated_files/system/src/reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system/src/reset.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o: mcc_generated_files/system/src/config_bits.c  .generated_files/flags/default/c7151b81dd59ae3195c82839e04587ac7b894e8f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system/src/config_bits.c  -o ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system/src/clock.o: mcc_generated_files/system/src/clock.c  .generated_files/flags/default/b952ffd3e206ab4c2d4e02561aa72f03965eaf85 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system/src/clock.c  -o ${OBJECTDIR}/mcc_generated_files/system/src/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system/src/system.o: mcc_generated_files/system/src/system.c  .generated_files/flags/default/2b68de0d79fc1dbe7b4980a1f6a60d09c2c8de71 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system/src/system.c  -o ${OBJECTDIR}/mcc_generated_files/system/src/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system/src/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/timer/src/tmr1.o: mcc_generated_files/timer/src/tmr1.c  .generated_files/flags/default/944242a022f4af281b80ca80922987392d0c30ff .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/timer/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/timer/src/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/timer/src/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/timer/src/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/timer/src/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/timer/src/tmr1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart/src/uart1.o: mcc_generated_files/uart/src/uart1.c  .generated_files/flags/default/cb6d4e13ad0632594d3253b55b0b8309b5b650b6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/uart/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart/src/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart/src/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart/src/uart1.c  -o ${OBJECTDIR}/mcc_generated_files/uart/src/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart/src/uart1.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/7cb8b939e8c67dd3c5eed8e11f64f1118e24c8ba .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/Application/AppSpecific/System/CAN/CANFeedback.o: Application/AppSpecific/System/CAN/CANFeedback.c  .generated_files/flags/default/efe77e5499e999c11e63476e92b30d9b7897b833 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/AppSpecific/System/CAN" 
	@${RM} ${OBJECTDIR}/Application/AppSpecific/System/CAN/CANFeedback.o.d 
	@${RM} ${OBJECTDIR}/Application/AppSpecific/System/CAN/CANFeedback.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/AppSpecific/System/CAN/CANFeedback.c  -o ${OBJECTDIR}/Application/AppSpecific/System/CAN/CANFeedback.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/AppSpecific/System/CAN/CANFeedback.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/AppSpecific/System/Version/Version.o: Application/AppSpecific/System/Version/Version.c  .generated_files/flags/default/d9cc123d6c7d6edfc459fd180c86e74176be51d0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/AppSpecific/System/Version" 
	@${RM} ${OBJECTDIR}/Application/AppSpecific/System/Version/Version.o.d 
	@${RM} ${OBJECTDIR}/Application/AppSpecific/System/Version/Version.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/AppSpecific/System/Version/Version.c  -o ${OBJECTDIR}/Application/AppSpecific/System/Version/Version.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/AppSpecific/System/Version/Version.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Application/Main/AppMain.o: Application/ProductLibrary/Application/Main/AppMain.c  .generated_files/flags/default/5ef90ac412b5467af1b100c25397068bd658253c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Application/Main" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Application/Main/AppMain.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Application/Main/AppMain.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Application/Main/AppMain.c  -o ${OBJECTDIR}/Application/ProductLibrary/Application/Main/AppMain.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Application/Main/AppMain.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Application/ResetTest/ResetTest.o: Application/ProductLibrary/Application/ResetTest/ResetTest.c  .generated_files/flags/default/41c4c283d8fbd80de6809b4ac8756df41161853a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Application/ResetTest" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Application/ResetTest/ResetTest.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Application/ResetTest/ResetTest.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Application/ResetTest/ResetTest.c  -o ${OBJECTDIR}/Application/ProductLibrary/Application/ResetTest/ResetTest.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Application/ResetTest/ResetTest.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Driver/ADC/ADCManager.o: Application/ProductLibrary/Driver/ADC/ADCManager.c  .generated_files/flags/default/f6f7d9b589331d61317a3968a568f94289c84ca .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Driver/ADC" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/ADC/ADCManager.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/ADC/ADCManager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Driver/ADC/ADCManager.c  -o ${OBJECTDIR}/Application/ProductLibrary/Driver/ADC/ADCManager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Driver/ADC/ADCManager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.o: Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.c  .generated_files/flags/default/b9786f1fa32d7a111aa9540058fd7635dc33415 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Driver/ADS7128_ADC_EXP" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.c  -o ${OBJECTDIR}/Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Driver/ADS7128_ADC_EXP/ADS7128.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.o: Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.c  .generated_files/flags/default/db95daa6cc5cfec136d6a165c087941674ef427b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Driver/EEPROM24LC512" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.c  -o ${OBJECTDIR}/Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Driver/EEPROM24LC512/EEPROM24LC512.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.o: Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.c  .generated_files/flags/default/e72ba791f9feb0ef780f43e6f44ac5a1005b1cb2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Driver/MCP23017_IO_EXP" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.c  -o ${OBJECTDIR}/Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Driver/MCP23017_IO_EXP/MCP23017.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.o: Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.c  .generated_files/flags/default/2952aed139150a6514002f77a1c6837e9ebddce7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Driver/PCA9685_IO_PWM" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.c  -o ${OBJECTDIR}/Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Driver/PCA9685_IO_PWM/PCA9685.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Driver/SwPWM/SwPWM.o: Application/ProductLibrary/Driver/SwPWM/SwPWM.c  .generated_files/flags/default/fdf7bf9c1669e2566025a606b466fe70bbc05357 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Driver/SwPWM" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/SwPWM/SwPWM.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Driver/SwPWM/SwPWM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Driver/SwPWM/SwPWM.c  -o ${OBJECTDIR}/Application/ProductLibrary/Driver/SwPWM/SwPWM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Driver/SwPWM/SwPWM.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.o: Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.c  .generated_files/flags/default/b941bd2081b1286eed55650288d75b6954ebb011 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Lsi/HW_HeartBeat" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.c  -o ${OBJECTDIR}/Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Lsi/HW_HeartBeat/HW_HeartBeat.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.o: Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.c  .generated_files/flags/default/808dc82507c51416b4badc07264e691c3f491b41 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/Lsi/LED_OnBoard" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.c  -o ${OBJECTDIR}/Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/Lsi/LED_OnBoard/LED_OnBoard.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/System/CAN/CANRecvdMsgParser.o: Application/ProductLibrary/System/CAN/CANRecvdMsgParser.c  .generated_files/flags/default/7db8e2912dc6aa8c04ffefb09d9452b253fced59 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/System/CAN" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/System/CAN/CANRecvdMsgParser.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/System/CAN/CANRecvdMsgParser.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/System/CAN/CANRecvdMsgParser.c  -o ${OBJECTDIR}/Application/ProductLibrary/System/CAN/CANRecvdMsgParser.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/System/CAN/CANRecvdMsgParser.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Application/ProductLibrary/System/Timers/Timers.o: Application/ProductLibrary/System/Timers/Timers.c  .generated_files/flags/default/8b1bb54c15a93d922711dbbe92e174c8929b6d57 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Application/ProductLibrary/System/Timers" 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/System/Timers/Timers.o.d 
	@${RM} ${OBJECTDIR}/Application/ProductLibrary/System/Timers/Timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Application/ProductLibrary/System/Timers/Timers.c  -o ${OBJECTDIR}/Application/ProductLibrary/System/Timers/Timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Application/ProductLibrary/System/Timers/Timers.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/adc/src/adc1.o: mcc_generated_files/adc/src/adc1.c  .generated_files/flags/default/cb32607509ff2bbe61e59380b8f78931f341041c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/adc/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc/src/adc1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adc/src/adc1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/adc/src/adc1.c  -o ${OBJECTDIR}/mcc_generated_files/adc/src/adc1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/adc/src/adc1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/can/src/can1.o: mcc_generated_files/can/src/can1.c  .generated_files/flags/default/5bdf18e7c8de2262ff403e3465c8daefb49395d4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/can/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/can/src/can1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/can/src/can1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/can/src/can1.c  -o ${OBJECTDIR}/mcc_generated_files/can/src/can1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/can/src/can1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/i2c_host/src/i2c1.o: mcc_generated_files/i2c_host/src/i2c1.c  .generated_files/flags/default/9cda3ecb400cf3e9c28678bd9faf52e0ac39afe0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/i2c_host/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c_host/src/i2c1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c_host/src/i2c1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/i2c_host/src/i2c1.c  -o ${OBJECTDIR}/mcc_generated_files/i2c_host/src/i2c1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/i2c_host/src/i2c1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o: mcc_generated_files/system/src/interrupt.c  .generated_files/flags/default/e1aa5bb8f7981101ef2087cc6ea995cad09dac61 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system/src/interrupt.c  -o ${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system/src/interrupt.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system/src/traps.o: mcc_generated_files/system/src/traps.c  .generated_files/flags/default/7021e456e9bbcb56b017acb1f1aebc4762e6a289 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/traps.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system/src/traps.c  -o ${OBJECTDIR}/mcc_generated_files/system/src/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system/src/traps.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system/src/pins.o: mcc_generated_files/system/src/pins.c  .generated_files/flags/default/a2be6827ce09a3ad55a21b6f950aa4204fa04eca .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/pins.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system/src/pins.c  -o ${OBJECTDIR}/mcc_generated_files/system/src/pins.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system/src/pins.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system/src/dmt.o: mcc_generated_files/system/src/dmt.c  .generated_files/flags/default/2aa6dc062851e5766c5f22148be502af2729ef8d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/dmt.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/dmt.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system/src/dmt.c  -o ${OBJECTDIR}/mcc_generated_files/system/src/dmt.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system/src/dmt.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system/src/reset.o: mcc_generated_files/system/src/reset.c  .generated_files/flags/default/26972818b0953c48697f40429398e21f05e6f746 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/reset.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/reset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system/src/reset.c  -o ${OBJECTDIR}/mcc_generated_files/system/src/reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system/src/reset.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o: mcc_generated_files/system/src/config_bits.c  .generated_files/flags/default/942d62d25311b39739747eb5de4e46956b45981 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system/src/config_bits.c  -o ${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system/src/config_bits.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system/src/clock.o: mcc_generated_files/system/src/clock.c  .generated_files/flags/default/a2ac8bcef2bafa6da7b21dcafc82bad4a9f92df4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system/src/clock.c  -o ${OBJECTDIR}/mcc_generated_files/system/src/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system/src/clock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/system/src/system.o: mcc_generated_files/system/src/system.c  .generated_files/flags/default/1215d38ee69cc63781e3224d4b89abd468371783 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/system.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/system/src/system.c  -o ${OBJECTDIR}/mcc_generated_files/system/src/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/system/src/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/timer/src/tmr1.o: mcc_generated_files/timer/src/tmr1.c  .generated_files/flags/default/9a3b659de41731283f70fb5c920737f301249884 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/timer/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/timer/src/tmr1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/timer/src/tmr1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/timer/src/tmr1.c  -o ${OBJECTDIR}/mcc_generated_files/timer/src/tmr1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/timer/src/tmr1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/uart/src/uart1.o: mcc_generated_files/uart/src/uart1.c  .generated_files/flags/default/9f9e1ecd43998456b02776956393c191b260c98c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/uart/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart/src/uart1.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/uart/src/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mcc_generated_files/uart/src/uart1.c  -o ${OBJECTDIR}/mcc_generated_files/uart/src/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/uart/src/uart1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/f06318ced6f4f107b8a30f7837795722a33a99ef .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mlarge-code -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/system/src/dmt_asm.o: mcc_generated_files/system/src/dmt_asm.s  .generated_files/flags/default/a1833f037ffab4292fc3759ae7e34a032bde0db5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/dmt_asm.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/dmt_asm.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/system/src/dmt_asm.s  -o ${OBJECTDIR}/mcc_generated_files/system/src/dmt_asm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/system/src/dmt_asm.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/mcc_generated_files/system/src/dmt_asm.o: mcc_generated_files/system/src/dmt_asm.s  .generated_files/flags/default/fb6740c2c6ff1311ebf094512a6b2f50d41d2f10 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/system/src" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/dmt_asm.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/system/src/dmt_asm.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/system/src/dmt_asm.s  -o ${OBJECTDIR}/mcc_generated_files/system/src/dmt_asm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/system/src/dmt_asm.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o: mcc_generated_files/boot/memory_partition.S  .generated_files/flags/default/e6fc5b55de61d6cdaa726e9007dbb06af94b0d04 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/memory_partition.S  -o ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o.d"  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o.asm.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o: mcc_generated_files/boot/hardware_interrupt_table.S  .generated_files/flags/default/50f0506603104c1637f68dedf16237feb2512ea6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/hardware_interrupt_table.S  -o ${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o.d"  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o.asm.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o: mcc_generated_files/boot/user_interrupt_table.S  .generated_files/flags/default/b9352f12392fbe68fd9f8c2469f6889ee683a8f6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/user_interrupt_table.S  -o ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o.d"  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o.asm.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/boot/application_header_crc32.o: mcc_generated_files/boot/application_header_crc32.S  .generated_files/flags/default/f4628f5a9b9e1fdd338def2272b6c533d7e6dab6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/application_header_crc32.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/application_header_crc32.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/application_header_crc32.S  -o ${OBJECTDIR}/mcc_generated_files/boot/application_header_crc32.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/application_header_crc32.o.d"  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/application_header_crc32.o.asm.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/boot/interrupts.o: mcc_generated_files/boot/interrupts.S  .generated_files/flags/default/ff8b31d3b41c5a25773c427f53825d53d5862cc6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/interrupts.S  -o ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/interrupts.o.d"  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/interrupts.o.asm.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o: mcc_generated_files/boot/memory_partition.S  .generated_files/flags/default/f54a2bbacc9ef4321f1f8e32d947b9c348a21f1a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/memory_partition.S  -o ${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o.d"  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/memory_partition.o.asm.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o: mcc_generated_files/boot/hardware_interrupt_table.S  .generated_files/flags/default/26e03b85c3dc0c84421636fa0a5b27e7bf75205a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/hardware_interrupt_table.S  -o ${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o.d"  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/hardware_interrupt_table.o.asm.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o: mcc_generated_files/boot/user_interrupt_table.S  .generated_files/flags/default/a17b44b69530a36a0cfb11050411e5e2ddbd89bf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/user_interrupt_table.S  -o ${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o.d"  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/user_interrupt_table.o.asm.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/boot/application_header_crc32.o: mcc_generated_files/boot/application_header_crc32.S  .generated_files/flags/default/cee444710307d16bb1bafcdd692dd1a02d62d41a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/application_header_crc32.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/application_header_crc32.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/application_header_crc32.S  -o ${OBJECTDIR}/mcc_generated_files/boot/application_header_crc32.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/application_header_crc32.o.d"  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/application_header_crc32.o.asm.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/mcc_generated_files/boot/interrupts.o: mcc_generated_files/boot/interrupts.S  .generated_files/flags/default/8efa34002d96fdb80586491db12bfdef68f84fc1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/boot" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  mcc_generated_files/boot/interrupts.S  -o ${OBJECTDIR}/mcc_generated_files/boot/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/mcc_generated_files/boot/interrupts.o.d"  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/mcc_generated_files/boot/interrupts.o.asm.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/LMU.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/LMU.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/LMU.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/LMU.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/LMU.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
