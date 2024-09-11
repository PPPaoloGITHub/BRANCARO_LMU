/**
 *    @file		Compiler_defs.h
 *    @brief    Compiler definitions
 *
 *    $Header: ver 1.0 Paolo Parrino
 *
 *    @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 */
#ifndef __COMPILER_DEFS_H__
#define __COMPILER_DEFS_H__


    #define LITTLE_ENDIAN
    #ifdef BIG_ENDIAN
        #undef BIG_ENDIAN
    #endif
    //#define INTERRUPT_DIRECTIVE

    //#define  STACK_NUMBER     110

    //!Macro that enables interrupts by using the assembly instruction
    #define ENABLE_INTERRUPTS()     {;}

    //!Macro that disables interrupts by using the assembly instruction
    #define DISABLE_INTERRUPTS()    {;}

    //!Macro to reset the system by executing an illegal instruction.
    //The nop that follows the illegal instruction is to prevent the optimizing
    //compiler from accidentally doing a SYSTEM_RESET() because it gets grouped
    //with other code.
    #define SYSTEM_RESET()          {;}

    //! Macro to spend CPU cycles by using the NOP assembly instruction
    #define NOP()                   {__NOP();}  //asm("nop");

    //! Macro to reset the watchdog timer.
    #define SERVICE_WATCHDOG()      {;}

//    #define FAR
//    #define NEAR
//    #define TINY
    #define RESET_STACK_POINTER()	{;}



//------------------------------------------------------------------------------
//  --- Macro Definitions


#endif // __COMPILER_DEFS_H__


