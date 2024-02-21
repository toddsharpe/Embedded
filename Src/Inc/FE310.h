
/****************************************************************************************************//**
 * @file     FE310.h
 *
 * @brief    CMSIS Cortex-M3 Peripheral Access Layer Header File for
 *           FE310 from SiFive.
 *
 * @version  V(null)
 * @date     6. January 2023
 *
 * @note     Generated with SVDConv V2.87l 
 *           from CMSIS SVD File 'e310x.svd' Version (null),
 *******************************************************************************************************/



/** @addtogroup SiFive
  * @{
  */

/** @addtogroup FE310
  * @{
  */

#ifndef FE310_H
#define FE310_H

#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum {
/* -------------------  Cortex-M3 Processor Exceptions Numbers  ------------------- */
  Reset_IRQn                    = -15,              /*!<   1  Reset Vector, invoked on Power up and warm reset                 */
  NonMaskableInt_IRQn           = -14,              /*!<   2  Non maskable Interrupt, cannot be stopped or preempted           */
  HardFault_IRQn                = -13,              /*!<   3  Hard Fault, all classes of Fault                                 */
  MemoryManagement_IRQn         = -12,              /*!<   4  Memory Management, MPU mismatch, including Access Violation
                                                         and No Match                                                          */
  BusFault_IRQn                 = -11,              /*!<   5  Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory
                                                         related Fault                                                         */
  UsageFault_IRQn               = -10,              /*!<   6  Usage Fault, i.e. Undef Instruction, Illegal State Transition    */
  SVCall_IRQn                   =  -5,              /*!<  11  System Service Call via SVC instruction                          */
  DebugMonitor_IRQn             =  -4,              /*!<  12  Debug Monitor                                                    */
  PendSV_IRQn                   =  -2,              /*!<  14  Pendable request for system service                              */
  SysTick_IRQn                  =  -1,              /*!<  15  System Tick Timer                                                */
/* ----------------------  FE310 Specific Interrupt Numbers  ---------------------- */
  WATCHDOG_IRQn                 =   1,              /*!<   1  WATCHDOG                                                         */
  RTC_IRQn                      =   2,              /*!<   2  RTC                                                              */
  UART0_IRQn                    =   3,              /*!<   3  UART0                                                            */
  UART1_IRQn                    =   4,              /*!<   4  UART1                                                            */
  QSPI0_IRQn                    =   5,              /*!<   5  QSPI0                                                            */
  QSPI1_IRQn                    =   6,              /*!<   6  QSPI1                                                            */
  QSPI2_IRQn                    =   7,              /*!<   7  QSPI2                                                            */
  GPIO0_IRQn                    =   8,              /*!<   8  GPIO0                                                            */
  GPIO1_IRQn                    =   9,              /*!<   9  GPIO1                                                            */
  GPIO2_IRQn                    =  10,              /*!<  10  GPIO2                                                            */
  GPIO3_IRQn                    =  11,              /*!<  11  GPIO3                                                            */
  GPIO4_IRQn                    =  12,              /*!<  12  GPIO4                                                            */
  GPIO5_IRQn                    =  13,              /*!<  13  GPIO5                                                            */
  GPIO6_IRQn                    =  14,              /*!<  14  GPIO6                                                            */
  GPIO7_IRQn                    =  15,              /*!<  15  GPIO7                                                            */
  GPIO8_IRQn                    =  16,              /*!<  16  GPIO8                                                            */
  GPIO9_IRQn                    =  17,              /*!<  17  GPIO9                                                            */
  GPIO10_IRQn                   =  18,              /*!<  18  GPIO10                                                           */
  GPIO11_IRQn                   =  19,              /*!<  19  GPIO11                                                           */
  GPIO12_IRQn                   =  20,              /*!<  20  GPIO12                                                           */
  GPIO13_IRQn                   =  21,              /*!<  21  GPIO13                                                           */
  GPIO14_IRQn                   =  22,              /*!<  22  GPIO14                                                           */
  GPIO15_IRQn                   =  23,              /*!<  23  GPIO15                                                           */
  GPIO16_IRQn                   =  24,              /*!<  24  GPIO16                                                           */
  GPIO17_IRQn                   =  25,              /*!<  25  GPIO17                                                           */
  GPIO18_IRQn                   =  26,              /*!<  26  GPIO18                                                           */
  GPIO19_IRQn                   =  27,              /*!<  27  GPIO19                                                           */
  GPIO20_IRQn                   =  28,              /*!<  28  GPIO20                                                           */
  GPIO21_IRQn                   =  29,              /*!<  29  GPIO21                                                           */
  GPIO22_IRQn                   =  30,              /*!<  30  GPIO22                                                           */
  GPIO23_IRQn                   =  31,              /*!<  31  GPIO23                                                           */
  GPIO24_IRQn                   =  32,              /*!<  32  GPIO24                                                           */
  GPIO25_IRQn                   =  33,              /*!<  33  GPIO25                                                           */
  GPIO26_IRQn                   =  34,              /*!<  34  GPIO26                                                           */
  GPIO27_IRQn                   =  35,              /*!<  35  GPIO27                                                           */
  GPIO28_IRQn                   =  36,              /*!<  36  GPIO28                                                           */
  GPIO29_IRQn                   =  37,              /*!<  37  GPIO29                                                           */
  GPIO30_IRQn                   =  38,              /*!<  38  GPIO30                                                           */
  GPIO31_IRQn                   =  39,              /*!<  39  GPIO31                                                           */
  PWM0CMP0_IRQn                 =  40,              /*!<  40  PWM0CMP0                                                         */
  PWM0CMP1_IRQn                 =  41,              /*!<  41  PWM0CMP1                                                         */
  PWM0CMP2_IRQn                 =  42,              /*!<  42  PWM0CMP2                                                         */
  PWM0CMP3_IRQn                 =  43,              /*!<  43  PWM0CMP3                                                         */
  PWM1CMP0_IRQn                 =  44,              /*!<  44  PWM1CMP0                                                         */
  PWM1CMP1_IRQn                 =  45,              /*!<  45  PWM1CMP1                                                         */
  PWM1CMP2_IRQn                 =  46,              /*!<  46  PWM1CMP2                                                         */
  PWM1CMP3_IRQn                 =  47,              /*!<  47  PWM1CMP3                                                         */
  PWM2CMP0_IRQn                 =  48,              /*!<  48  PWM2CMP0                                                         */
  PWM2CMP1_IRQn                 =  49,              /*!<  49  PWM2CMP1                                                         */
  PWM2CMP2_IRQn                 =  50,              /*!<  50  PWM2CMP2                                                         */
  PWM2CMP3_IRQn                 =  51,              /*!<  51  PWM2CMP3                                                         */
  I2C0_IRQn                     =  52               /*!<  52  I2C0                                                             */
} IRQn_Type;


/** @addtogroup Configuration_of_CMSIS
  * @{
  */


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* ----------------Configuration of the Cortex-M3 Processor and Core Peripherals---------------- */
#define __CM3_REV                 0xffffffff        /*!< Cortex-M3 Core Revision                                               */
#define __MPU_PRESENT                  -1           /*!< MPU present or not                                                    */
#define __NVIC_PRIO_BITS               -1           /*!< Number of Bits used for Priority Levels                               */
#define __Vendor_SysTickConfig         -1           /*!< Set to 1 if different SysTick Config is used                          */
/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_cm3.h"                               /*!< Cortex-M3 processor and core peripherals                              */
//#include "system_FE310.h"                           /*!< FE310 System                                                          */


/* ================================================================================ */
/* ================       Device Specific Peripheral Section       ================ */
/* ================================================================================ */


/** @addtogroup Device_Peripheral_Registers
  * @{
  */


/* -------------------  Start of section using anonymous unions  ------------------ */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
/* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler type
#endif



/* ================================================================================ */
/* ================                      CLINT                     ================ */
/* ================================================================================ */


/**
  * @brief Coreplex Local Interrupts (CLINT)
  */

typedef struct {                                    /*!< CLINT Structure                                                       */
  __IO uint32_t  msip;                              /*!< Hart 0 software interrupt register                                    */
  __I  uint32_t  RESERVED[4095];
  __IO uint32_t  mtimecmp;                          /*!< Hart 0 time comparator register                                       */
  __IO uint32_t  mtimecmph;                         /*!< Hart 0 time comparator register                                       */
  __I  uint32_t  RESERVED1[8188];
  __IO uint32_t  mtime;                             /*!< Timer register                                                        */
  __IO uint32_t  mtimeh;                            /*!< Timer register                                                        */
} CLINT_Type;


/* ================================================================================ */
/* ================                      PLIC                      ================ */
/* ================================================================================ */


/**
  * @brief Platform Level Interrupt Control (PLIC)
  */

typedef struct {                                    /*!< PLIC Structure                                                        */
  
  union {
    __IO uint32_t  priority[53];                    /*!< Interrupt Priority Register                                           */
    
    struct {
      __IO uint32_t  priority   :  3;               /*!< (null)                                                                */
    } priority_b[53];                               /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED[971];
  __IO uint32_t  pending[2];                        /*!< Interrupt Pending Register                                            */
  __I  uint32_t  RESERVED1[1022];
  __IO uint32_t  enable[2];                         /*!< Interrupt Enable Register                                             */
  __I  uint32_t  RESERVED2[522238];
  
  union {
    __IO uint32_t  threshold;                       /*!< Priority Threshold Register                                           */
    
    struct {
      __IO uint32_t  priority   :  3;               /*!< (null)                                                                */
    } threshold_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  claim;                             /*!< Claim/Complete Register                                               */
} PLIC_Type;


/* ================================================================================ */
/* ================                      WDOG                      ================ */
/* ================================================================================ */


/**
  * @brief Watchdog (WDOG)
  */

typedef struct {                                    /*!< WDOG Structure                                                        */
  
  union {
    __IO uint32_t  wdogcfg;                         /*!< Watchdog Configuration Register                                       */
    
    struct {
      __IO uint32_t  scale      :  4;               /*!< (null)                                                                */
           uint32_t             :  4;
      __IO uint32_t  rsten      :  1;               /*!< (null)                                                                */
      __IO uint32_t  zerocmp    :  1;               /*!< (null)                                                                */
           uint32_t             :  2;
      __IO uint32_t  enalways   :  1;               /*!< (null)                                                                */
      __IO uint32_t  encoreawake:  1;               /*!< (null)                                                                */
           uint32_t             : 14;
      __IO uint32_t  cmpip      :  1;               /*!< (null)                                                                */
    } wdogcfg_b;                                    /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED;
  __IO uint32_t  wdogcount;                         /*!< Watchdog Counter Register                                             */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  wdogs;                             /*!< Watchdog Scaled Counter Register                                      */
  __I  uint32_t  RESERVED2;
  __IO uint32_t  wdogfeed;                          /*!< Watchdog Feed Register                                                */
  __O  uint32_t  wdogkey;                           /*!< Watchdog Key Register                                                 */
  
  union {
    __IO uint32_t  wdogcmp;                         /*!< Watchdog Compare Register                                             */
    
    struct {
      __IO uint32_t  value      : 16;               /*!< (null)                                                                */
    } wdogcmp_b;                                    /*!< BitSize                                                               */
  };
} WDOG_Type;


/* ================================================================================ */
/* ================                       RTC                      ================ */
/* ================================================================================ */


/**
  * @brief Watchdog (RTC)
  */

typedef struct {                                    /*!< RTC Structure                                                         */
  __I  uint32_t  RESERVED[16];
  
  union {
    __IO uint32_t  rtccfg;                          /*!< RTC Configuration Register                                            */
    
    struct {
      __IO uint32_t  scale      :  4;               /*!< (null)                                                                */
           uint32_t             :  8;
      __IO uint32_t  enalways   :  1;               /*!< (null)                                                                */
           uint32_t             : 15;
      __IO uint32_t  cmpip      :  1;               /*!< (null)                                                                */
    } rtccfg_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED1;
  __IO uint32_t  rtclo;                             /*!< RTC Counter Low Register                                              */
  
  union {
    __IO uint32_t  rtchi;                           /*!< RTC Counter High Register                                             */
    
    struct {
      __IO uint32_t  value      : 16;               /*!< (null)                                                                */
    } rtchi_b;                                      /*!< BitSize                                                               */
  };
  __IO uint32_t  rtcs;                              /*!< RTC Scaled Counter Register                                           */
  __I  uint32_t  RESERVED2[3];
  __IO uint32_t  rtccmp;                            /*!< RTC Compare Register                                                  */
} RTC_Type;


/* ================================================================================ */
/* ================                     AONCLK                     ================ */
/* ================================================================================ */


/**
  * @brief Always-On Clock Configuration (AONCLK)
  */

typedef struct {                                    /*!< AONCLK Structure                                                      */
  __I  uint32_t  RESERVED[28];
  
  union {
    __IO uint32_t  lfrosccfg;                       /*!< AON Clock Configuration Register                                      */
    
    struct {
      __IO uint32_t  div        :  6;               /*!< (null)                                                                */
           uint32_t             : 10;
      __IO uint32_t  trim       :  5;               /*!< (null)                                                                */
           uint32_t             :  9;
      __IO uint32_t  enable     :  1;               /*!< (null)                                                                */
      __IO uint32_t  ready      :  1;               /*!< (null)                                                                */
    } lfrosccfg_b;                                  /*!< BitSize                                                               */
  };
} AONCLK_Type;


/* ================================================================================ */
/* ================                     BACKUP                     ================ */
/* ================================================================================ */


/**
  * @brief Backup Registers (BACKUP)
  */

typedef struct {                                    /*!< BACKUP Structure                                                      */
  __I  uint32_t  RESERVED[32];
  __IO uint32_t  backup[16];                        /*!< Backup Register                                                       */
} BACKUP_Type;


/* ================================================================================ */
/* ================                       PMU                      ================ */
/* ================================================================================ */


/**
  * @brief PMU (PMU)
  */

typedef struct {                                    /*!< PMU Structure                                                         */
  __I  uint32_t  RESERVED[64];
  
  union {
    __IO uint32_t  pmuwakepm[8];                    /*!< PMU Wake Program Memory                                               */
    
    struct {
      __IO uint32_t  delay      :  4;               /*!< (null)                                                                */
      __IO uint32_t  pmu_out_0_en:  1;              /*!< (null)                                                                */
      __IO uint32_t  pmu_out_1_en:  1;              /*!< (null)                                                                */
           uint32_t             :  1;
      __IO uint32_t  corerst    :  1;               /*!< (null)                                                                */
      __IO uint32_t  hfclkrst   :  1;               /*!< (null)                                                                */
      __IO uint32_t  isolate    :  1;               /*!< (null)                                                                */
    } pmuwakepm_b[8];                               /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  pmusleeppm[8];                   /*!< PMU Sleep Program Memory                                              */
    
    struct {
      __IO uint32_t  delay      :  4;               /*!< (null)                                                                */
      __IO uint32_t  pmu_out_0_en:  1;              /*!< (null)                                                                */
      __IO uint32_t  pmu_out_1_en:  1;              /*!< (null)                                                                */
           uint32_t             :  1;
      __IO uint32_t  corerst    :  1;               /*!< (null)                                                                */
      __IO uint32_t  hfclkrst   :  1;               /*!< (null)                                                                */
      __IO uint32_t  isolate    :  1;               /*!< (null)                                                                */
    } pmusleeppm_b[8];                              /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  pmuie;                           /*!< PMU Interrupt Enable Register                                         */
    
    struct {
           uint32_t             :  1;
      __IO uint32_t  rtc        :  1;               /*!< (null)                                                                */
      __IO uint32_t  dwakeup    :  1;               /*!< (null)                                                                */
      __IO uint32_t  awakeup    :  1;               /*!< (null)                                                                */
    } pmuie_b;                                      /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  pmucause;                        /*!< PMU Cause Register                                                    */
    
    struct {
      __IO uint32_t  wakeupcause:  2;               /*!< (null)                                                                */
           uint32_t             :  6;
      __IO uint32_t  resetcause :  2;               /*!< (null)                                                                */
    } pmucause_b;                                   /*!< BitSize                                                               */
  };
  
  union {
    __O  uint32_t  pmusleep;                        /*!< PMU Sleep Register                                                    */
    
    struct {
      __O  uint32_t  sleep      :  1;               /*!< (null)                                                                */
    } pmusleep_b;                                   /*!< BitSize                                                               */
  };
  __IO uint32_t  pmukey;                            /*!< PMU Key Register                                                      */
} PMU_Type;


/* ================================================================================ */
/* ================                      PRCI                      ================ */
/* ================================================================================ */


/**
  * @brief Power Reset Clock Interrupts (PRCI)
  */

typedef struct {                                    /*!< PRCI Structure                                                        */
  
  union {
    __IO uint32_t  hfrosccfg;                       /*!< Clock Configuration Register                                          */
    
    struct {
      __IO uint32_t  div        :  6;               /*!< (null)                                                                */
           uint32_t             : 10;
      __IO uint32_t  trim       :  5;               /*!< (null)                                                                */
           uint32_t             :  9;
      __IO uint32_t  enable     :  1;               /*!< (null)                                                                */
      __IO uint32_t  ready      :  1;               /*!< (null)                                                                */
    } hfrosccfg_b;                                  /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  hfxosccfg;                       /*!< Clock Configuration Register                                          */
    
    struct {
           uint32_t             : 30;
      __IO uint32_t  enable     :  1;               /*!< (null)                                                                */
      __IO uint32_t  ready      :  1;               /*!< (null)                                                                */
    } hfxosccfg_b;                                  /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  pllcfg;                          /*!< PLL Configuration Register                                            */
    
    struct {
      __IO uint32_t  pllr       :  3;               /*!< (null)                                                                */
           uint32_t             :  1;
      __IO uint32_t  pllf       :  6;               /*!< (null)                                                                */
      __IO uint32_t  pllq       :  2;               /*!< (null)                                                                */
           uint32_t             :  4;
      __IO uint32_t  sel        :  1;               /*!< (null)                                                                */
      __IO uint32_t  refsel     :  1;               /*!< (null)                                                                */
      __IO uint32_t  bypass     :  1;               /*!< (null)                                                                */
           uint32_t             : 12;
      __IO uint32_t  lock       :  1;               /*!< (null)                                                                */
    } pllcfg_b;                                     /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  plloutdiv;                       /*!< PLL Divider Register                                                  */
    
    struct {
      __IO uint32_t  div        :  6;               /*!< (null)                                                                */
           uint32_t             :  2;
      __IO uint32_t  divby1     :  1;               /*!< (null)                                                                */
    } plloutdiv_b;                                  /*!< BitSize                                                               */
  };
  __IO uint32_t  coreclkcfg;                        /*!< Clock Configuration Register                                          */
} PRCI_Type;


/* ================================================================================ */
/* ================                       OTP                      ================ */
/* ================================================================================ */


/**
  * @brief One Time Programmable Memory (OTP)
  */

typedef struct {                                    /*!< OTP Structure                                                         */
  __IO uint32_t  lock;                              /*!< Programmed-I/O lock register                                          */
  __IO uint32_t  clock;                             /*!< OTP device clock signal                                               */
  __IO uint32_t  output_en;                         /*!< OTP device output-enable signal                                       */
  __IO uint32_t  select;                            /*!< OTP device chip-select signal                                         */
  __IO uint32_t  write_en;                          /*!< OTP device write-enable signal                                        */
  __IO uint32_t  mode;                              /*!< OTP device mode register                                              */
  __IO uint32_t  mrr;                               /*!< OTP read-voltage regulator control                                    */
  __IO uint32_t  mpp;                               /*!< OTP write-voltage charge pump control                                 */
  __IO uint32_t  vrren;                             /*!< OTP read-voltage enable                                               */
  __IO uint32_t  vppen;                             /*!< OTP write-voltage enable                                              */
  __IO uint32_t  addr;                              /*!< OTP device address                                                    */
  __IO uint32_t  data_in;                           /*!< OTP device data input                                                 */
  __IO uint32_t  data_out;                          /*!< OTP device data output                                                */
  __IO uint32_t  rsctrl;                            /*!< OTP read sequencer control                                            */
} OTP_Type;


/* ================================================================================ */
/* ================                      GPIO0                     ================ */
/* ================================================================================ */


/**
  * @brief General Purpose Input Output (GPIO0)
  */

typedef struct {                                    /*!< GPIO0 Structure                                                       */
  
  union {
    __IO uint32_t  input_val;                       /*!< Pin value.                                                            */
    
    struct {
      __IO uint32_t  pin0       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin1       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin2       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin3       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin4       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin5       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin6       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin7       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin8       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin9       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin10      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin11      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin12      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin13      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin14      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin15      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin16      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin17      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin18      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin19      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin20      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin21      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin22      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin23      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin24      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin25      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin26      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin27      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin28      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin29      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin30      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin31      :  1;               /*!< (null)                                                                */
    } input_val_b;                                  /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  input_en;                        /*!< Pin Input Enable Register                                             */
    
    struct {
      __IO uint32_t  pin0       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin1       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin2       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin3       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin4       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin5       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin6       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin7       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin8       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin9       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin10      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin11      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin12      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin13      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin14      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin15      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin16      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin17      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin18      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin19      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin20      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin21      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin22      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin23      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin24      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin25      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin26      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin27      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin28      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin29      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin30      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin31      :  1;               /*!< (null)                                                                */
    } input_en_b;                                   /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  output_en;                       /*!< Pin Output Enable Register                                            */
    
    struct {
      __IO uint32_t  pin0       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin1       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin2       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin3       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin4       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin5       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin6       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin7       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin8       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin9       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin10      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin11      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin12      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin13      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin14      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin15      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin16      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin17      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin18      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin19      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin20      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin21      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin22      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin23      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin24      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin25      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin26      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin27      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin28      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin29      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin30      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin31      :  1;               /*!< (null)                                                                */
    } output_en_b;                                  /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  output_val;                      /*!< Output Port Value Register                                            */
    
    struct {
      __IO uint32_t  pin0       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin1       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin2       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin3       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin4       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin5       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin6       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin7       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin8       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin9       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin10      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin11      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin12      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin13      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin14      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin15      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin16      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin17      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin18      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin19      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin20      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin21      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin22      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin23      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin24      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin25      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin26      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin27      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin28      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin29      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin30      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin31      :  1;               /*!< (null)                                                                */
    } output_val_b;                                 /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  pullup;                          /*!< Internal Pull-Up Enable Register                                      */
    
    struct {
      __IO uint32_t  pin0       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin1       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin2       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin3       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin4       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin5       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin6       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin7       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin8       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin9       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin10      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin11      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin12      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin13      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin14      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin15      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin16      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin17      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin18      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin19      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin20      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin21      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin22      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin23      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin24      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin25      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin26      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin27      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin28      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin29      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin30      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin31      :  1;               /*!< (null)                                                                */
    } pullup_b;                                     /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  drive;                           /*!< Drive Strength Register                                               */
    
    struct {
      __IO uint32_t  pin0       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin1       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin2       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin3       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin4       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin5       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin6       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin7       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin8       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin9       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin10      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin11      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin12      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin13      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin14      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin15      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin16      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin17      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin18      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin19      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin20      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin21      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin22      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin23      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin24      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin25      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin26      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin27      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin28      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin29      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin30      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin31      :  1;               /*!< (null)                                                                */
    } drive_b;                                      /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  rise_ie;                         /*!< Rise Interrupt Enable Register                                        */
    
    struct {
      __IO uint32_t  pin0       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin1       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin2       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin3       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin4       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin5       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin6       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin7       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin8       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin9       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin10      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin11      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin12      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin13      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin14      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin15      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin16      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin17      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin18      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin19      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin20      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin21      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin22      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin23      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin24      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin25      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin26      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin27      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin28      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin29      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin30      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin31      :  1;               /*!< (null)                                                                */
    } rise_ie_b;                                    /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  rise_ip;                         /*!< Rise Interrupt Pending Register                                       */
    
    struct {
      __IO uint32_t  pin0       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin1       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin2       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin3       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin4       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin5       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin6       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin7       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin8       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin9       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin10      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin11      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin12      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin13      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin14      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin15      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin16      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin17      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin18      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin19      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin20      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin21      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin22      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin23      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin24      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin25      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin26      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin27      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin28      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin29      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin30      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin31      :  1;               /*!< (null)                                                                */
    } rise_ip_b;                                    /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  fall_ie;                         /*!< Fall Interrupt Enable Register                                        */
    
    struct {
      __IO uint32_t  pin0       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin1       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin2       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin3       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin4       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin5       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin6       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin7       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin8       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin9       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin10      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin11      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin12      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin13      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin14      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin15      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin16      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin17      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin18      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin19      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin20      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin21      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin22      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin23      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin24      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin25      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin26      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin27      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin28      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin29      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin30      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin31      :  1;               /*!< (null)                                                                */
    } fall_ie_b;                                    /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  fall_ip;                         /*!< Fall Interrupt Pending Register                                       */
    
    struct {
      __IO uint32_t  pin0       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin1       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin2       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin3       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin4       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin5       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin6       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin7       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin8       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin9       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin10      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin11      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin12      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin13      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin14      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin15      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin16      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin17      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin18      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin19      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin20      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin21      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin22      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin23      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin24      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin25      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin26      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin27      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin28      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin29      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin30      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin31      :  1;               /*!< (null)                                                                */
    } fall_ip_b;                                    /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  high_ie;                         /*!< High Interrupt Enable Register                                        */
    
    struct {
      __IO uint32_t  pin0       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin1       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin2       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin3       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin4       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin5       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin6       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin7       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin8       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin9       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin10      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin11      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin12      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin13      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin14      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin15      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin16      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin17      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin18      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin19      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin20      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin21      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin22      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin23      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin24      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin25      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin26      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin27      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin28      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin29      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin30      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin31      :  1;               /*!< (null)                                                                */
    } high_ie_b;                                    /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  high_ip;                         /*!< High Interrupt Pending Register                                       */
    
    struct {
      __IO uint32_t  pin0       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin1       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin2       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin3       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin4       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin5       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin6       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin7       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin8       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin9       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin10      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin11      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin12      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin13      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin14      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin15      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin16      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin17      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin18      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin19      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin20      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin21      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin22      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin23      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin24      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin25      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin26      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin27      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin28      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin29      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin30      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin31      :  1;               /*!< (null)                                                                */
    } high_ip_b;                                    /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  low_ie;                          /*!< Low Interrupt Enable Register                                         */
    
    struct {
      __IO uint32_t  pin0       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin1       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin2       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin3       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin4       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin5       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin6       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin7       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin8       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin9       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin10      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin11      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin12      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin13      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin14      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin15      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin16      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin17      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin18      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin19      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin20      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin21      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin22      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin23      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin24      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin25      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin26      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin27      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin28      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin29      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin30      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin31      :  1;               /*!< (null)                                                                */
    } low_ie_b;                                     /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  low_ip;                          /*!< Low Interrupt Pending Register                                        */
    
    struct {
      __IO uint32_t  pin0       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin1       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin2       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin3       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin4       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin5       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin6       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin7       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin8       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin9       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin10      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin11      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin12      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin13      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin14      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin15      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin16      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin17      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin18      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin19      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin20      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin21      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin22      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin23      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin24      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin25      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin26      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin27      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin28      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin29      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin30      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin31      :  1;               /*!< (null)                                                                */
    } low_ip_b;                                     /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  iof_en;                          /*!< HW I/O Function Enable Register                                       */
    
    struct {
      __IO uint32_t  pin0       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin1       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin2       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin3       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin4       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin5       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin6       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin7       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin8       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin9       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin10      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin11      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin12      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin13      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin14      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin15      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin16      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin17      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin18      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin19      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin20      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin21      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin22      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin23      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin24      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin25      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin26      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin27      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin28      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin29      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin30      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin31      :  1;               /*!< (null)                                                                */
    } iof_en_b;                                     /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  iof_sel;                         /*!< HW I/O Function Select Register                                       */
    
    struct {
      __IO uint32_t  pin0       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin1       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin2       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin3       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin4       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin5       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin6       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin7       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin8       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin9       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin10      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin11      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin12      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin13      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin14      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin15      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin16      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin17      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin18      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin19      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin20      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin21      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin22      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin23      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin24      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin25      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin26      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin27      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin28      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin29      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin30      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin31      :  1;               /*!< (null)                                                                */
    } iof_sel_b;                                    /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  out_xor;                         /*!< Output XOR (invert) Register                                          */
    
    struct {
      __IO uint32_t  pin0       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin1       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin2       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin3       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin4       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin5       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin6       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin7       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin8       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin9       :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin10      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin11      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin12      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin13      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin14      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin15      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin16      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin17      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin18      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin19      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin20      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin21      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin22      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin23      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin24      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin25      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin26      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin27      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin28      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin29      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin30      :  1;               /*!< (null)                                                                */
      __IO uint32_t  pin31      :  1;               /*!< (null)                                                                */
    } out_xor_b;                                    /*!< BitSize                                                               */
  };
} GPIO0_Type;


/* ================================================================================ */
/* ================                      UART0                     ================ */
/* ================================================================================ */


/**
  * @brief Universal Asynchronous Receiver Transmitter (UART0)
  */

typedef struct {                                    /*!< UART0 Structure                                                       */
  
  union {
    __IO uint32_t  txdata;                          /*!< Transmit Data Register                                                */
    
    struct {
      __IO uint32_t  data       :  8;               /*!< (null)                                                                */
           uint32_t             : 23;
      __IO uint32_t  full       :  1;               /*!< (null)                                                                */
    } txdata_b;                                     /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  rxdata;                          /*!< Receive Data Register                                                 */
    
    struct {
      __IO uint32_t  data       :  8;               /*!< (null)                                                                */
           uint32_t             : 23;
      __IO uint32_t  empty      :  1;               /*!< (null)                                                                */
    } rxdata_b;                                     /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  txctrl;                          /*!< Transmit Control Register                                             */
    
    struct {
      __IO uint32_t  enable     :  1;               /*!< (null)                                                                */
      __IO uint32_t  nstop      :  1;               /*!< (null)                                                                */
           uint32_t             : 14;
      __IO uint32_t  counter    :  3;               /*!< (null)                                                                */
    } txctrl_b;                                     /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  rxctrl;                          /*!< Receive Control Register                                              */
    
    struct {
      __IO uint32_t  enable     :  1;               /*!< (null)                                                                */
           uint32_t             : 15;
      __IO uint32_t  counter    :  3;               /*!< (null)                                                                */
    } rxctrl_b;                                     /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  ie;                              /*!< Interrupt Enable Register                                             */
    
    struct {
      __IO uint32_t  txwm       :  1;               /*!< (null)                                                                */
      __IO uint32_t  rxwm       :  1;               /*!< (null)                                                                */
    } ie_b;                                         /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  ip;                              /*!< Interrupt Pending Register                                            */
    
    struct {
      __IO uint32_t  txwm       :  1;               /*!< (null)                                                                */
      __IO uint32_t  rxwm       :  1;               /*!< (null)                                                                */
    } ip_b;                                         /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  div;                             /*!< Baud Rate Divisor Register                                            */
    
    struct {
      __IO uint32_t  value      : 16;               /*!< (null)                                                                */
    } div_b;                                        /*!< BitSize                                                               */
  };
} UART0_Type;


/* ================================================================================ */
/* ================                      QSPI0                     ================ */
/* ================================================================================ */


/**
  * @brief Quad Serial Peripheral Interface (QSPI0)
  */

typedef struct {                                    /*!< QSPI0 Structure                                                       */
  
  union {
    __IO uint32_t  sckdiv;                          /*!< Serial Clock Divisor Register                                         */
    
    struct {
      __IO uint32_t  div        : 12;               /*!< Divisor for serial clock                                              */
    } sckdiv_b;                                     /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  sckmode;                         /*!< Serial Clock Mode Register                                            */
    
    struct {
      __IO uint32_t  pha        :  1;               /*!< Serial clock phase                                                    */
      __IO uint32_t  pol        :  1;               /*!< Serial clock polarity                                                 */
    } sckmode_b;                                    /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED[2];
  __IO uint32_t  csid;                              /*!< Chip Select ID Register                                               */
  __IO uint32_t  csdef;                             /*!< Chip Select Default Register                                          */
  
  union {
    __IO uint32_t  csmode;                          /*!< Chip Select Mode Register                                             */
    
    struct {
      __IO uint32_t  mode       :  2;               /*!< Chip select mode                                                      */
    } csmode_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED1[3];
  
  union {
    __IO uint32_t  delay0;                          /*!< Delay Control 0 Register                                              */
    
    struct {
      __IO uint32_t  cssck      :  8;               /*!< CS to SCK Delay                                                       */
           uint32_t             :  8;
      __IO uint32_t  sckcs      :  8;               /*!< SCK to CS Delay                                                       */
    } delay0_b;                                     /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  delay1;                          /*!< Delay Control 1 Register                                              */
    
    struct {
      __IO uint32_t  intercs    :  8;               /*!< Minimum CS inactive time                                              */
           uint32_t             :  8;
      __IO uint32_t  interxfr   :  8;               /*!< Maximum interframe delay                                              */
    } delay1_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED2[4];
  
  union {
    __IO uint32_t  fmt;                             /*!< Frame Format Register                                                 */
    
    struct {
      __IO uint32_t  proto      :  2;               /*!< SPI protocol                                                          */
      __IO uint32_t  endian     :  1;               /*!< SPI endianness                                                        */
      __IO uint32_t  dir        :  1;               /*!< SPI I/O direction                                                     */
           uint32_t             : 12;
      __IO uint32_t  len        :  4;               /*!< Number of bits per frame                                              */
    } fmt_b;                                        /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED3;
  
  union {
    __IO uint32_t  txdata;                          /*!< Transmit Data Register                                                */
    
    struct {
      __IO uint32_t  data       :  8;               /*!< Transmit data                                                         */
           uint32_t             : 23;
      __IO uint32_t  full       :  1;               /*!< FIFO full flag                                                        */
    } txdata_b;                                     /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  rxdata;                          /*!< Receive Data Register                                                 */
    
    struct {
      __IO uint32_t  data       :  8;               /*!< Received data                                                         */
           uint32_t             : 23;
      __IO uint32_t  empty      :  1;               /*!< FIFO empty flag                                                       */
    } rxdata_b;                                     /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  txmark;                          /*!< Transmit Watermark Register                                           */
    
    struct {
      __IO uint32_t  txmark     :  3;               /*!< Transmit watermark                                                    */
    } txmark_b;                                     /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  rxmark;                          /*!< Receive Watermark Register                                            */
    
    struct {
      __IO uint32_t  rxmark     :  3;               /*!< Receive watermark                                                     */
    } rxmark_b;                                     /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED4[2];
  
  union {
    __IO uint32_t  fctrl;                           /*!< SPI Flash Interface Control Register                                  */
    
    struct {
      __IO uint32_t  en         :  1;               /*!< SPI Flash Mode Select                                                 */
    } fctrl_b;                                      /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  ffmt;                            /*!< SPI Flash Instruction Format Register                                 */
    
    struct {
      __IO uint32_t  cmd_en     :  1;               /*!< Enable sending of command                                             */
      __IO uint32_t  addr_len   :  3;               /*!< Number of address bytes (0 to 4)                                      */
      __IO uint32_t  pad_cnt    :  4;               /*!< Number of dummy cycles                                                */
      __IO uint32_t  cmd_proto  :  2;               /*!< Protocol for transmitting command                                     */
      __IO uint32_t  addr_proto :  2;               /*!< Protocol for transmitting address and padding                         */
      __IO uint32_t  data_proto :  2;               /*!< Protocol for receiving data bytes                                     */
           uint32_t             :  2;
      __IO uint32_t  cmd_code   :  8;               /*!< Value of command byte                                                 */
      __IO uint32_t  pad_code   :  8;               /*!< First 8 bits to transmit during dummy cycles                          */
    } ffmt_b;                                       /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED5[2];
  
  union {
    __IO uint32_t  ie;                              /*!< SPI Interrupt Enable Register                                         */
    
    struct {
      __IO uint32_t  txwm       :  1;               /*!< Transmit watermark enable                                             */
      __IO uint32_t  rxwm       :  1;               /*!< Receive watermark enable                                              */
    } ie_b;                                         /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  ip;                              /*!< SPI Interrupt Pending Register                                        */
    
    struct {
      __IO uint32_t  txwm       :  1;               /*!< Transmit watermark enable                                             */
      __IO uint32_t  rxwm       :  1;               /*!< Receive watermark enable                                              */
    } ip_b;                                         /*!< BitSize                                                               */
  };
} QSPI0_Type;


/* ================================================================================ */
/* ================                      PWM0                      ================ */
/* ================================================================================ */


/**
  * @brief 8-bit timer with 4 cmp (PWM0)
  */

typedef struct {                                    /*!< PWM0 Structure                                                        */
  
  union {
    __IO uint32_t  cfg;                             /*!< PWM Configuration Register                                            */
    
    struct {
      __IO uint32_t  scale      :  4;               /*!< (null)                                                                */
           uint32_t             :  4;
      __IO uint32_t  sticky     :  1;               /*!< (null)                                                                */
      __IO uint32_t  zerocmp    :  1;               /*!< (null)                                                                */
      __IO uint32_t  deglitch   :  1;               /*!< (null)                                                                */
           uint32_t             :  1;
      __IO uint32_t  enalways   :  1;               /*!< (null)                                                                */
      __IO uint32_t  enoneshot  :  1;               /*!< (null)                                                                */
           uint32_t             :  2;
      __IO uint32_t  cmp0center :  1;               /*!< (null)                                                                */
      __IO uint32_t  cmp1center :  1;               /*!< (null)                                                                */
      __IO uint32_t  cmp2center :  1;               /*!< (null)                                                                */
      __IO uint32_t  cmp3center :  1;               /*!< (null)                                                                */
           uint32_t             :  4;
      __IO uint32_t  cmp0gang   :  1;               /*!< (null)                                                                */
      __IO uint32_t  cmp1gang   :  1;               /*!< (null)                                                                */
      __IO uint32_t  cmp2gang   :  6;               /*!< (null)                                                                */
      __IO uint32_t  cmp3gang   :  1;               /*!< (null)                                                                */
      //#error "Field not sorted, not increasing or multiple defined bits (alias) error! Field 'cmp3gang' should be on [32..27]"
      //#error "Field size error detected! Field 'cmp3gang' [33] should be [32]"
      __IO uint32_t  cmp0ip     :  1;               /*!< (null)                                                                */
      //#error "Field not sorted, not increasing or multiple defined bits (alias) error! Field 'cmp0ip' should be on [33..28]"
      //#error "Field size error detected! Field 'cmp0ip' [34] should be [32]"
      __IO uint32_t  cmp1ip     :  1;               /*!< (null)                                                                */
      //#error "Field not sorted, not increasing or multiple defined bits (alias) error! Field 'cmp1ip' should be on [34..29]"
      //#error "Field size error detected! Field 'cmp1ip' [35] should be [32]"
      __IO uint32_t  cmp2ip     :  1;               /*!< (null)                                                                */
      //#error "Field not sorted, not increasing or multiple defined bits (alias) error! Field 'cmp2ip' should be on [35..30]"
      //#error "Field size error detected! Field 'cmp2ip' [36] should be [32]"
      __IO uint32_t  cmp3ip     :  1;               /*!< (null)                                                                */
      //#error "Field not sorted, not increasing or multiple defined bits (alias) error! Field 'cmp3ip' should be on [36..31]"
      //#error "Field size error detected! Field 'cmp3ip' [37] should be [32]"
    } cfg_b;                                        /*!< BitSize                                                               */
  };
  __I  uint32_t  RESERVED;
  __IO uint32_t  count;                             /*!< Counter Register                                                      */
  __I  uint32_t  RESERVED1;
  __IO uint32_t  pwms;                              /*!< Scaled Halfword Counter Register                                      */
  __I  uint32_t  RESERVED2[3];
  
  union {
    __IO uint32_t  cmp0;                            /*!< Compare Register                                                      */
    
    struct {
      __IO uint32_t  value      : 16;               /*!< (null)                                                                */
    } cmp0_b;                                       /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  cmp1;                            /*!< Compare Register                                                      */
    
    struct {
      __IO uint32_t  value      : 16;               /*!< (null)                                                                */
    } cmp1_b;                                       /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  cmp2;                            /*!< Compare Register                                                      */
    
    struct {
      __IO uint32_t  value      : 16;               /*!< (null)                                                                */
    } cmp2_b;                                       /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  cmp3;                            /*!< Compare Register                                                      */
    
    struct {
      __IO uint32_t  value      : 16;               /*!< (null)                                                                */
    } cmp3_b;                                       /*!< BitSize                                                               */
  };
} PWM0_Type;


/* ================================================================================ */
/* ================                      I2C0                      ================ */
/* ================================================================================ */


/**
  * @brief Inter-Integrated Circuit Master Interface (FE310-G002 only) (I2C0)
  */

typedef struct {                                    /*!< I2C0 Structure                                                        */
  
  union {
    __IO uint32_t  prer_lo;                         /*!< Clock Prescale register lo-byte                                       */
    
    struct {
      __IO uint32_t  value      :  8;               /*!< (null)                                                                */
    } prer_lo_b;                                    /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  prer_hi;                         /*!< Clock Prescale register hi-byte                                       */
    
    struct {
      __IO uint32_t  value      :  8;               /*!< (null)                                                                */
    } prer_hi_b;                                    /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  ctr;                             /*!< Control register                                                      */
    
    struct {
           uint32_t             :  6;
      __IO uint32_t  ien        :  1;               /*!< I2C core interrupt enable bit                                         */
      __IO uint32_t  en         :  1;               /*!< I2C core enable bit                                                   */
    } ctr_b;                                        /*!< BitSize                                                               */
  };
  
  union {
    __IO uint32_t  txr_rxr;                         /*!< Transmit register / Receive register                                  */
    
    struct {
      __IO uint32_t  data       :  8;               /*!< (null)                                                                */
    } txr_rxr_b;                                    /*!< BitSize                                                               */
  };
  
  union {
    union {
      __I  uint32_t  sr;                            /*!< Status register                                                       */
      
      struct {
        __I  uint32_t  IF       :  1;               /*!< Interrupt Flag. This bit is set when an interrupt is pending,
                                                         which will cause a processor interrupt request if the IEN bit
                                                          is set.                                                              */
        __I  uint32_t  tip      :  1;               /*!< Transfer in progress                                                  */
             uint32_t           :  3;
        __I  uint32_t  al       :  1;               /*!< Arbitration lost                                                      */
        __I  uint32_t  busy     :  1;               /*!< I2C bus busy                                                          */
        __I  uint32_t  rx_ack   :  1;               /*!< Received acknowledge from slave. This flag represents acknowledge
                                                         from the addressed slave. '1' = No acknowledge received '0'
                                                          = Acknowledge received                                               */
      } sr_b;                                       /*!< BitSize                                                               */
    };
    
    union {
      __O  uint32_t  cr;                            /*!< Command register                                                      */
      
      struct {
        __O  uint32_t  iack     :  1;               /*!< Interrupt acknowledge. When set, clears a pending interrupt           */
             uint32_t           :  2;
        __O  uint32_t  ack      :  1;               /*!< When a receiver, sent ACK (0) or NACK (1)                             */
        __O  uint32_t  wr       :  1;               /*!< Write to slave                                                        */
        __O  uint32_t  rd       :  1;               /*!< Read from slave                                                       */
        __O  uint32_t  sto      :  1;               /*!< Generate stop condition                                               */
        __O  uint32_t  sta      :  1;               /*!< Generate (repeated) start condition                                   */
      } cr_b;                                       /*!< BitSize                                                               */
    };
    __IO uint32_t  cr_sr;                           /*!< Command register / Status register                                    */
  };
} I2C0_Type;


/* --------------------  End of section using anonymous unions  ------------------- */
#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler type
#endif



/* ================================================================================ */
/* ================          struct 'PLIC' Position & Mask         ================ */
/* ================================================================================ */


/* --------------------------------  PLIC_priority  ------------------------------- */
#define PLIC_priority_priority_Pos            (0UL)                     /*!< PLIC priority: priority (Bit 0)                             */
#define PLIC_priority_priority_Msk            (0x7UL)                   /*!< PLIC priority: priority (Bitfield-Mask: 0x07)               */

/* -------------------------------  PLIC_threshold  ------------------------------- */
#define PLIC_threshold_priority_Pos           (0UL)                     /*!< PLIC threshold: priority (Bit 0)                            */
#define PLIC_threshold_priority_Msk           (0x7UL)                   /*!< PLIC threshold: priority (Bitfield-Mask: 0x07)              */


/* ================================================================================ */
/* ================          struct 'WDOG' Position & Mask         ================ */
/* ================================================================================ */


/* --------------------------------  WDOG_wdogcfg  -------------------------------- */
#define WDOG_wdogcfg_scale_Pos                (0UL)                     /*!< WDOG wdogcfg: scale (Bit 0)                                 */
#define WDOG_wdogcfg_scale_Msk                (0xfUL)                   /*!< WDOG wdogcfg: scale (Bitfield-Mask: 0x0f)                   */
#define WDOG_wdogcfg_rsten_Pos                (8UL)                     /*!< WDOG wdogcfg: rsten (Bit 8)                                 */
#define WDOG_wdogcfg_rsten_Msk                (0x100UL)                 /*!< WDOG wdogcfg: rsten (Bitfield-Mask: 0x01)                   */
#define WDOG_wdogcfg_zerocmp_Pos              (9UL)                     /*!< WDOG wdogcfg: zerocmp (Bit 9)                               */
#define WDOG_wdogcfg_zerocmp_Msk              (0x200UL)                 /*!< WDOG wdogcfg: zerocmp (Bitfield-Mask: 0x01)                 */
#define WDOG_wdogcfg_enalways_Pos             (12UL)                    /*!< WDOG wdogcfg: enalways (Bit 12)                             */
#define WDOG_wdogcfg_enalways_Msk             (0x1000UL)                /*!< WDOG wdogcfg: enalways (Bitfield-Mask: 0x01)                */
#define WDOG_wdogcfg_encoreawake_Pos          (13UL)                    /*!< WDOG wdogcfg: encoreawake (Bit 13)                          */
#define WDOG_wdogcfg_encoreawake_Msk          (0x2000UL)                /*!< WDOG wdogcfg: encoreawake (Bitfield-Mask: 0x01)             */
#define WDOG_wdogcfg_cmpip_Pos                (28UL)                    /*!< WDOG wdogcfg: cmpip (Bit 28)                                */
#define WDOG_wdogcfg_cmpip_Msk                (0x10000000UL)            /*!< WDOG wdogcfg: cmpip (Bitfield-Mask: 0x01)                   */

/* --------------------------------  WDOG_wdogcmp  -------------------------------- */
#define WDOG_wdogcmp_value_Pos                (0UL)                     /*!< WDOG wdogcmp: value (Bit 0)                                 */
#define WDOG_wdogcmp_value_Msk                (0xffffUL)                /*!< WDOG wdogcmp: value (Bitfield-Mask: 0xffff)                 */


/* ================================================================================ */
/* ================          struct 'RTC' Position & Mask          ================ */
/* ================================================================================ */


/* ---------------------------------  RTC_rtccfg  --------------------------------- */
#define RTC_rtccfg_scale_Pos                  (0UL)                     /*!< RTC rtccfg: scale (Bit 0)                                   */
#define RTC_rtccfg_scale_Msk                  (0xfUL)                   /*!< RTC rtccfg: scale (Bitfield-Mask: 0x0f)                     */
#define RTC_rtccfg_enalways_Pos               (12UL)                    /*!< RTC rtccfg: enalways (Bit 12)                               */
#define RTC_rtccfg_enalways_Msk               (0x1000UL)                /*!< RTC rtccfg: enalways (Bitfield-Mask: 0x01)                  */
#define RTC_rtccfg_cmpip_Pos                  (28UL)                    /*!< RTC rtccfg: cmpip (Bit 28)                                  */
#define RTC_rtccfg_cmpip_Msk                  (0x10000000UL)            /*!< RTC rtccfg: cmpip (Bitfield-Mask: 0x01)                     */

/* ----------------------------------  RTC_rtchi  --------------------------------- */
#define RTC_rtchi_value_Pos                   (0UL)                     /*!< RTC rtchi: value (Bit 0)                                    */
#define RTC_rtchi_value_Msk                   (0xffffUL)                /*!< RTC rtchi: value (Bitfield-Mask: 0xffff)                    */


/* ================================================================================ */
/* ================         struct 'AONCLK' Position & Mask        ================ */
/* ================================================================================ */


/* ------------------------------  AONCLK_lfrosccfg  ------------------------------ */
#define AONCLK_lfrosccfg_div_Pos              (0UL)                     /*!< AONCLK lfrosccfg: div (Bit 0)                               */
#define AONCLK_lfrosccfg_div_Msk              (0x3fUL)                  /*!< AONCLK lfrosccfg: div (Bitfield-Mask: 0x3f)                 */
#define AONCLK_lfrosccfg_trim_Pos             (16UL)                    /*!< AONCLK lfrosccfg: trim (Bit 16)                             */
#define AONCLK_lfrosccfg_trim_Msk             (0x1f0000UL)              /*!< AONCLK lfrosccfg: trim (Bitfield-Mask: 0x1f)                */
#define AONCLK_lfrosccfg_enable_Pos           (30UL)                    /*!< AONCLK lfrosccfg: enable (Bit 30)                           */
#define AONCLK_lfrosccfg_enable_Msk           (0x40000000UL)            /*!< AONCLK lfrosccfg: enable (Bitfield-Mask: 0x01)              */
#define AONCLK_lfrosccfg_ready_Pos            (31UL)                    /*!< AONCLK lfrosccfg: ready (Bit 31)                            */
#define AONCLK_lfrosccfg_ready_Msk            (0x80000000UL)            /*!< AONCLK lfrosccfg: ready (Bitfield-Mask: 0x01)               */


/* ================================================================================ */
/* ================          struct 'PMU' Position & Mask          ================ */
/* ================================================================================ */


/* --------------------------------  PMU_pmuwakepm  ------------------------------- */
#define PMU_pmuwakepm_delay_Pos               (0UL)                     /*!< PMU pmuwakepm: delay (Bit 0)                                */
#define PMU_pmuwakepm_delay_Msk               (0xfUL)                   /*!< PMU pmuwakepm: delay (Bitfield-Mask: 0x0f)                  */
#define PMU_pmuwakepm_pmu_out_0_en_Pos        (4UL)                     /*!< PMU pmuwakepm: pmu_out_0_en (Bit 4)                         */
#define PMU_pmuwakepm_pmu_out_0_en_Msk        (0x10UL)                  /*!< PMU pmuwakepm: pmu_out_0_en (Bitfield-Mask: 0x01)           */
#define PMU_pmuwakepm_pmu_out_1_en_Pos        (5UL)                     /*!< PMU pmuwakepm: pmu_out_1_en (Bit 5)                         */
#define PMU_pmuwakepm_pmu_out_1_en_Msk        (0x20UL)                  /*!< PMU pmuwakepm: pmu_out_1_en (Bitfield-Mask: 0x01)           */
#define PMU_pmuwakepm_corerst_Pos             (7UL)                     /*!< PMU pmuwakepm: corerst (Bit 7)                              */
#define PMU_pmuwakepm_corerst_Msk             (0x80UL)                  /*!< PMU pmuwakepm: corerst (Bitfield-Mask: 0x01)                */
#define PMU_pmuwakepm_hfclkrst_Pos            (8UL)                     /*!< PMU pmuwakepm: hfclkrst (Bit 8)                             */
#define PMU_pmuwakepm_hfclkrst_Msk            (0x100UL)                 /*!< PMU pmuwakepm: hfclkrst (Bitfield-Mask: 0x01)               */
#define PMU_pmuwakepm_isolate_Pos             (9UL)                     /*!< PMU pmuwakepm: isolate (Bit 9)                              */
#define PMU_pmuwakepm_isolate_Msk             (0x200UL)                 /*!< PMU pmuwakepm: isolate (Bitfield-Mask: 0x01)                */

/* -------------------------------  PMU_pmusleeppm  ------------------------------- */
#define PMU_pmusleeppm_delay_Pos              (0UL)                     /*!< PMU pmusleeppm: delay (Bit 0)                               */
#define PMU_pmusleeppm_delay_Msk              (0xfUL)                   /*!< PMU pmusleeppm: delay (Bitfield-Mask: 0x0f)                 */
#define PMU_pmusleeppm_pmu_out_0_en_Pos       (4UL)                     /*!< PMU pmusleeppm: pmu_out_0_en (Bit 4)                        */
#define PMU_pmusleeppm_pmu_out_0_en_Msk       (0x10UL)                  /*!< PMU pmusleeppm: pmu_out_0_en (Bitfield-Mask: 0x01)          */
#define PMU_pmusleeppm_pmu_out_1_en_Pos       (5UL)                     /*!< PMU pmusleeppm: pmu_out_1_en (Bit 5)                        */
#define PMU_pmusleeppm_pmu_out_1_en_Msk       (0x20UL)                  /*!< PMU pmusleeppm: pmu_out_1_en (Bitfield-Mask: 0x01)          */
#define PMU_pmusleeppm_corerst_Pos            (7UL)                     /*!< PMU pmusleeppm: corerst (Bit 7)                             */
#define PMU_pmusleeppm_corerst_Msk            (0x80UL)                  /*!< PMU pmusleeppm: corerst (Bitfield-Mask: 0x01)               */
#define PMU_pmusleeppm_hfclkrst_Pos           (8UL)                     /*!< PMU pmusleeppm: hfclkrst (Bit 8)                            */
#define PMU_pmusleeppm_hfclkrst_Msk           (0x100UL)                 /*!< PMU pmusleeppm: hfclkrst (Bitfield-Mask: 0x01)              */
#define PMU_pmusleeppm_isolate_Pos            (9UL)                     /*!< PMU pmusleeppm: isolate (Bit 9)                             */
#define PMU_pmusleeppm_isolate_Msk            (0x200UL)                 /*!< PMU pmusleeppm: isolate (Bitfield-Mask: 0x01)               */

/* ----------------------------------  PMU_pmuie  --------------------------------- */
#define PMU_pmuie_rtc_Pos                     (1UL)                     /*!< PMU pmuie: rtc (Bit 1)                                      */
#define PMU_pmuie_rtc_Msk                     (0x2UL)                   /*!< PMU pmuie: rtc (Bitfield-Mask: 0x01)                        */
#define PMU_pmuie_dwakeup_Pos                 (2UL)                     /*!< PMU pmuie: dwakeup (Bit 2)                                  */
#define PMU_pmuie_dwakeup_Msk                 (0x4UL)                   /*!< PMU pmuie: dwakeup (Bitfield-Mask: 0x01)                    */
#define PMU_pmuie_awakeup_Pos                 (3UL)                     /*!< PMU pmuie: awakeup (Bit 3)                                  */
#define PMU_pmuie_awakeup_Msk                 (0x8UL)                   /*!< PMU pmuie: awakeup (Bitfield-Mask: 0x01)                    */

/* --------------------------------  PMU_pmucause  -------------------------------- */
#define PMU_pmucause_wakeupcause_Pos          (0UL)                     /*!< PMU pmucause: wakeupcause (Bit 0)                           */
#define PMU_pmucause_wakeupcause_Msk          (0x3UL)                   /*!< PMU pmucause: wakeupcause (Bitfield-Mask: 0x03)             */
#define PMU_pmucause_resetcause_Pos           (8UL)                     /*!< PMU pmucause: resetcause (Bit 8)                            */
#define PMU_pmucause_resetcause_Msk           (0x300UL)                 /*!< PMU pmucause: resetcause (Bitfield-Mask: 0x03)              */

/* --------------------------------  PMU_pmusleep  -------------------------------- */
#define PMU_pmusleep_sleep_Pos                (0UL)                     /*!< PMU pmusleep: sleep (Bit 0)                                 */
#define PMU_pmusleep_sleep_Msk                (0x1UL)                   /*!< PMU pmusleep: sleep (Bitfield-Mask: 0x01)                   */


/* ================================================================================ */
/* ================          struct 'PRCI' Position & Mask         ================ */
/* ================================================================================ */


/* -------------------------------  PRCI_hfrosccfg  ------------------------------- */
#define PRCI_hfrosccfg_div_Pos                (0UL)                     /*!< PRCI hfrosccfg: div (Bit 0)                                 */
#define PRCI_hfrosccfg_div_Msk                (0x3fUL)                  /*!< PRCI hfrosccfg: div (Bitfield-Mask: 0x3f)                   */
#define PRCI_hfrosccfg_trim_Pos               (16UL)                    /*!< PRCI hfrosccfg: trim (Bit 16)                               */
#define PRCI_hfrosccfg_trim_Msk               (0x1f0000UL)              /*!< PRCI hfrosccfg: trim (Bitfield-Mask: 0x1f)                  */
#define PRCI_hfrosccfg_enable_Pos             (30UL)                    /*!< PRCI hfrosccfg: enable (Bit 30)                             */
#define PRCI_hfrosccfg_enable_Msk             (0x40000000UL)            /*!< PRCI hfrosccfg: enable (Bitfield-Mask: 0x01)                */
#define PRCI_hfrosccfg_ready_Pos              (31UL)                    /*!< PRCI hfrosccfg: ready (Bit 31)                              */
#define PRCI_hfrosccfg_ready_Msk              (0x80000000UL)            /*!< PRCI hfrosccfg: ready (Bitfield-Mask: 0x01)                 */

/* -------------------------------  PRCI_hfxosccfg  ------------------------------- */
#define PRCI_hfxosccfg_enable_Pos             (30UL)                    /*!< PRCI hfxosccfg: enable (Bit 30)                             */
#define PRCI_hfxosccfg_enable_Msk             (0x40000000UL)            /*!< PRCI hfxosccfg: enable (Bitfield-Mask: 0x01)                */
#define PRCI_hfxosccfg_ready_Pos              (31UL)                    /*!< PRCI hfxosccfg: ready (Bit 31)                              */
#define PRCI_hfxosccfg_ready_Msk              (0x80000000UL)            /*!< PRCI hfxosccfg: ready (Bitfield-Mask: 0x01)                 */

/* ---------------------------------  PRCI_pllcfg  -------------------------------- */
#define PRCI_pllcfg_pllr_Pos                  (0UL)                     /*!< PRCI pllcfg: pllr (Bit 0)                                   */
#define PRCI_pllcfg_pllr_Msk                  (0x7UL)                   /*!< PRCI pllcfg: pllr (Bitfield-Mask: 0x07)                     */
#define PRCI_pllcfg_pllf_Pos                  (4UL)                     /*!< PRCI pllcfg: pllf (Bit 4)                                   */
#define PRCI_pllcfg_pllf_Msk                  (0x3f0UL)                 /*!< PRCI pllcfg: pllf (Bitfield-Mask: 0x3f)                     */
#define PRCI_pllcfg_pllq_Pos                  (10UL)                    /*!< PRCI pllcfg: pllq (Bit 10)                                  */
#define PRCI_pllcfg_pllq_Msk                  (0xc00UL)                 /*!< PRCI pllcfg: pllq (Bitfield-Mask: 0x03)                     */
#define PRCI_pllcfg_sel_Pos                   (16UL)                    /*!< PRCI pllcfg: sel (Bit 16)                                   */
#define PRCI_pllcfg_sel_Msk                   (0x10000UL)               /*!< PRCI pllcfg: sel (Bitfield-Mask: 0x01)                      */
#define PRCI_pllcfg_refsel_Pos                (17UL)                    /*!< PRCI pllcfg: refsel (Bit 17)                                */
#define PRCI_pllcfg_refsel_Msk                (0x20000UL)               /*!< PRCI pllcfg: refsel (Bitfield-Mask: 0x01)                   */
#define PRCI_pllcfg_bypass_Pos                (18UL)                    /*!< PRCI pllcfg: bypass (Bit 18)                                */
#define PRCI_pllcfg_bypass_Msk                (0x40000UL)               /*!< PRCI pllcfg: bypass (Bitfield-Mask: 0x01)                   */
#define PRCI_pllcfg_lock_Pos                  (31UL)                    /*!< PRCI pllcfg: lock (Bit 31)                                  */
#define PRCI_pllcfg_lock_Msk                  (0x80000000UL)            /*!< PRCI pllcfg: lock (Bitfield-Mask: 0x01)                     */

/* -------------------------------  PRCI_plloutdiv  ------------------------------- */
#define PRCI_plloutdiv_div_Pos                (0UL)                     /*!< PRCI plloutdiv: div (Bit 0)                                 */
#define PRCI_plloutdiv_div_Msk                (0x3fUL)                  /*!< PRCI plloutdiv: div (Bitfield-Mask: 0x3f)                   */
#define PRCI_plloutdiv_divby1_Pos             (8UL)                     /*!< PRCI plloutdiv: divby1 (Bit 8)                              */
#define PRCI_plloutdiv_divby1_Msk             (0x100UL)                 /*!< PRCI plloutdiv: divby1 (Bitfield-Mask: 0x01)                */


/* ================================================================================ */
/* ================         struct 'GPIO0' Position & Mask         ================ */
/* ================================================================================ */


/* -------------------------------  GPIO0_input_val  ------------------------------ */
#define GPIO0_input_val_pin0_Pos              (0UL)                     /*!< GPIO0 input_val: pin0 (Bit 0)                               */
#define GPIO0_input_val_pin0_Msk              (0x1UL)                   /*!< GPIO0 input_val: pin0 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_val_pin1_Pos              (1UL)                     /*!< GPIO0 input_val: pin1 (Bit 1)                               */
#define GPIO0_input_val_pin1_Msk              (0x2UL)                   /*!< GPIO0 input_val: pin1 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_val_pin2_Pos              (2UL)                     /*!< GPIO0 input_val: pin2 (Bit 2)                               */
#define GPIO0_input_val_pin2_Msk              (0x4UL)                   /*!< GPIO0 input_val: pin2 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_val_pin3_Pos              (3UL)                     /*!< GPIO0 input_val: pin3 (Bit 3)                               */
#define GPIO0_input_val_pin3_Msk              (0x8UL)                   /*!< GPIO0 input_val: pin3 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_val_pin4_Pos              (4UL)                     /*!< GPIO0 input_val: pin4 (Bit 4)                               */
#define GPIO0_input_val_pin4_Msk              (0x10UL)                  /*!< GPIO0 input_val: pin4 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_val_pin5_Pos              (5UL)                     /*!< GPIO0 input_val: pin5 (Bit 5)                               */
#define GPIO0_input_val_pin5_Msk              (0x20UL)                  /*!< GPIO0 input_val: pin5 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_val_pin6_Pos              (6UL)                     /*!< GPIO0 input_val: pin6 (Bit 6)                               */
#define GPIO0_input_val_pin6_Msk              (0x40UL)                  /*!< GPIO0 input_val: pin6 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_val_pin7_Pos              (7UL)                     /*!< GPIO0 input_val: pin7 (Bit 7)                               */
#define GPIO0_input_val_pin7_Msk              (0x80UL)                  /*!< GPIO0 input_val: pin7 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_val_pin8_Pos              (8UL)                     /*!< GPIO0 input_val: pin8 (Bit 8)                               */
#define GPIO0_input_val_pin8_Msk              (0x100UL)                 /*!< GPIO0 input_val: pin8 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_val_pin9_Pos              (9UL)                     /*!< GPIO0 input_val: pin9 (Bit 9)                               */
#define GPIO0_input_val_pin9_Msk              (0x200UL)                 /*!< GPIO0 input_val: pin9 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_val_pin10_Pos             (10UL)                    /*!< GPIO0 input_val: pin10 (Bit 10)                             */
#define GPIO0_input_val_pin10_Msk             (0x400UL)                 /*!< GPIO0 input_val: pin10 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin11_Pos             (11UL)                    /*!< GPIO0 input_val: pin11 (Bit 11)                             */
#define GPIO0_input_val_pin11_Msk             (0x800UL)                 /*!< GPIO0 input_val: pin11 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin12_Pos             (12UL)                    /*!< GPIO0 input_val: pin12 (Bit 12)                             */
#define GPIO0_input_val_pin12_Msk             (0x1000UL)                /*!< GPIO0 input_val: pin12 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin13_Pos             (13UL)                    /*!< GPIO0 input_val: pin13 (Bit 13)                             */
#define GPIO0_input_val_pin13_Msk             (0x2000UL)                /*!< GPIO0 input_val: pin13 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin14_Pos             (14UL)                    /*!< GPIO0 input_val: pin14 (Bit 14)                             */
#define GPIO0_input_val_pin14_Msk             (0x4000UL)                /*!< GPIO0 input_val: pin14 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin15_Pos             (15UL)                    /*!< GPIO0 input_val: pin15 (Bit 15)                             */
#define GPIO0_input_val_pin15_Msk             (0x8000UL)                /*!< GPIO0 input_val: pin15 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin16_Pos             (16UL)                    /*!< GPIO0 input_val: pin16 (Bit 16)                             */
#define GPIO0_input_val_pin16_Msk             (0x10000UL)               /*!< GPIO0 input_val: pin16 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin17_Pos             (17UL)                    /*!< GPIO0 input_val: pin17 (Bit 17)                             */
#define GPIO0_input_val_pin17_Msk             (0x20000UL)               /*!< GPIO0 input_val: pin17 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin18_Pos             (18UL)                    /*!< GPIO0 input_val: pin18 (Bit 18)                             */
#define GPIO0_input_val_pin18_Msk             (0x40000UL)               /*!< GPIO0 input_val: pin18 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin19_Pos             (19UL)                    /*!< GPIO0 input_val: pin19 (Bit 19)                             */
#define GPIO0_input_val_pin19_Msk             (0x80000UL)               /*!< GPIO0 input_val: pin19 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin20_Pos             (20UL)                    /*!< GPIO0 input_val: pin20 (Bit 20)                             */
#define GPIO0_input_val_pin20_Msk             (0x100000UL)              /*!< GPIO0 input_val: pin20 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin21_Pos             (21UL)                    /*!< GPIO0 input_val: pin21 (Bit 21)                             */
#define GPIO0_input_val_pin21_Msk             (0x200000UL)              /*!< GPIO0 input_val: pin21 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin22_Pos             (22UL)                    /*!< GPIO0 input_val: pin22 (Bit 22)                             */
#define GPIO0_input_val_pin22_Msk             (0x400000UL)              /*!< GPIO0 input_val: pin22 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin23_Pos             (23UL)                    /*!< GPIO0 input_val: pin23 (Bit 23)                             */
#define GPIO0_input_val_pin23_Msk             (0x800000UL)              /*!< GPIO0 input_val: pin23 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin24_Pos             (24UL)                    /*!< GPIO0 input_val: pin24 (Bit 24)                             */
#define GPIO0_input_val_pin24_Msk             (0x1000000UL)             /*!< GPIO0 input_val: pin24 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin25_Pos             (25UL)                    /*!< GPIO0 input_val: pin25 (Bit 25)                             */
#define GPIO0_input_val_pin25_Msk             (0x2000000UL)             /*!< GPIO0 input_val: pin25 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin26_Pos             (26UL)                    /*!< GPIO0 input_val: pin26 (Bit 26)                             */
#define GPIO0_input_val_pin26_Msk             (0x4000000UL)             /*!< GPIO0 input_val: pin26 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin27_Pos             (27UL)                    /*!< GPIO0 input_val: pin27 (Bit 27)                             */
#define GPIO0_input_val_pin27_Msk             (0x8000000UL)             /*!< GPIO0 input_val: pin27 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin28_Pos             (28UL)                    /*!< GPIO0 input_val: pin28 (Bit 28)                             */
#define GPIO0_input_val_pin28_Msk             (0x10000000UL)            /*!< GPIO0 input_val: pin28 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin29_Pos             (29UL)                    /*!< GPIO0 input_val: pin29 (Bit 29)                             */
#define GPIO0_input_val_pin29_Msk             (0x20000000UL)            /*!< GPIO0 input_val: pin29 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin30_Pos             (30UL)                    /*!< GPIO0 input_val: pin30 (Bit 30)                             */
#define GPIO0_input_val_pin30_Msk             (0x40000000UL)            /*!< GPIO0 input_val: pin30 (Bitfield-Mask: 0x01)                */
#define GPIO0_input_val_pin31_Pos             (31UL)                    /*!< GPIO0 input_val: pin31 (Bit 31)                             */
#define GPIO0_input_val_pin31_Msk             (0x80000000UL)            /*!< GPIO0 input_val: pin31 (Bitfield-Mask: 0x01)                */

/* -------------------------------  GPIO0_input_en  ------------------------------- */
#define GPIO0_input_en_pin0_Pos               (0UL)                     /*!< GPIO0 input_en: pin0 (Bit 0)                                */
#define GPIO0_input_en_pin0_Msk               (0x1UL)                   /*!< GPIO0 input_en: pin0 (Bitfield-Mask: 0x01)                  */
#define GPIO0_input_en_pin1_Pos               (1UL)                     /*!< GPIO0 input_en: pin1 (Bit 1)                                */
#define GPIO0_input_en_pin1_Msk               (0x2UL)                   /*!< GPIO0 input_en: pin1 (Bitfield-Mask: 0x01)                  */
#define GPIO0_input_en_pin2_Pos               (2UL)                     /*!< GPIO0 input_en: pin2 (Bit 2)                                */
#define GPIO0_input_en_pin2_Msk               (0x4UL)                   /*!< GPIO0 input_en: pin2 (Bitfield-Mask: 0x01)                  */
#define GPIO0_input_en_pin3_Pos               (3UL)                     /*!< GPIO0 input_en: pin3 (Bit 3)                                */
#define GPIO0_input_en_pin3_Msk               (0x8UL)                   /*!< GPIO0 input_en: pin3 (Bitfield-Mask: 0x01)                  */
#define GPIO0_input_en_pin4_Pos               (4UL)                     /*!< GPIO0 input_en: pin4 (Bit 4)                                */
#define GPIO0_input_en_pin4_Msk               (0x10UL)                  /*!< GPIO0 input_en: pin4 (Bitfield-Mask: 0x01)                  */
#define GPIO0_input_en_pin5_Pos               (5UL)                     /*!< GPIO0 input_en: pin5 (Bit 5)                                */
#define GPIO0_input_en_pin5_Msk               (0x20UL)                  /*!< GPIO0 input_en: pin5 (Bitfield-Mask: 0x01)                  */
#define GPIO0_input_en_pin6_Pos               (6UL)                     /*!< GPIO0 input_en: pin6 (Bit 6)                                */
#define GPIO0_input_en_pin6_Msk               (0x40UL)                  /*!< GPIO0 input_en: pin6 (Bitfield-Mask: 0x01)                  */
#define GPIO0_input_en_pin7_Pos               (7UL)                     /*!< GPIO0 input_en: pin7 (Bit 7)                                */
#define GPIO0_input_en_pin7_Msk               (0x80UL)                  /*!< GPIO0 input_en: pin7 (Bitfield-Mask: 0x01)                  */
#define GPIO0_input_en_pin8_Pos               (8UL)                     /*!< GPIO0 input_en: pin8 (Bit 8)                                */
#define GPIO0_input_en_pin8_Msk               (0x100UL)                 /*!< GPIO0 input_en: pin8 (Bitfield-Mask: 0x01)                  */
#define GPIO0_input_en_pin9_Pos               (9UL)                     /*!< GPIO0 input_en: pin9 (Bit 9)                                */
#define GPIO0_input_en_pin9_Msk               (0x200UL)                 /*!< GPIO0 input_en: pin9 (Bitfield-Mask: 0x01)                  */
#define GPIO0_input_en_pin10_Pos              (10UL)                    /*!< GPIO0 input_en: pin10 (Bit 10)                              */
#define GPIO0_input_en_pin10_Msk              (0x400UL)                 /*!< GPIO0 input_en: pin10 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin11_Pos              (11UL)                    /*!< GPIO0 input_en: pin11 (Bit 11)                              */
#define GPIO0_input_en_pin11_Msk              (0x800UL)                 /*!< GPIO0 input_en: pin11 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin12_Pos              (12UL)                    /*!< GPIO0 input_en: pin12 (Bit 12)                              */
#define GPIO0_input_en_pin12_Msk              (0x1000UL)                /*!< GPIO0 input_en: pin12 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin13_Pos              (13UL)                    /*!< GPIO0 input_en: pin13 (Bit 13)                              */
#define GPIO0_input_en_pin13_Msk              (0x2000UL)                /*!< GPIO0 input_en: pin13 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin14_Pos              (14UL)                    /*!< GPIO0 input_en: pin14 (Bit 14)                              */
#define GPIO0_input_en_pin14_Msk              (0x4000UL)                /*!< GPIO0 input_en: pin14 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin15_Pos              (15UL)                    /*!< GPIO0 input_en: pin15 (Bit 15)                              */
#define GPIO0_input_en_pin15_Msk              (0x8000UL)                /*!< GPIO0 input_en: pin15 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin16_Pos              (16UL)                    /*!< GPIO0 input_en: pin16 (Bit 16)                              */
#define GPIO0_input_en_pin16_Msk              (0x10000UL)               /*!< GPIO0 input_en: pin16 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin17_Pos              (17UL)                    /*!< GPIO0 input_en: pin17 (Bit 17)                              */
#define GPIO0_input_en_pin17_Msk              (0x20000UL)               /*!< GPIO0 input_en: pin17 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin18_Pos              (18UL)                    /*!< GPIO0 input_en: pin18 (Bit 18)                              */
#define GPIO0_input_en_pin18_Msk              (0x40000UL)               /*!< GPIO0 input_en: pin18 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin19_Pos              (19UL)                    /*!< GPIO0 input_en: pin19 (Bit 19)                              */
#define GPIO0_input_en_pin19_Msk              (0x80000UL)               /*!< GPIO0 input_en: pin19 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin20_Pos              (20UL)                    /*!< GPIO0 input_en: pin20 (Bit 20)                              */
#define GPIO0_input_en_pin20_Msk              (0x100000UL)              /*!< GPIO0 input_en: pin20 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin21_Pos              (21UL)                    /*!< GPIO0 input_en: pin21 (Bit 21)                              */
#define GPIO0_input_en_pin21_Msk              (0x200000UL)              /*!< GPIO0 input_en: pin21 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin22_Pos              (22UL)                    /*!< GPIO0 input_en: pin22 (Bit 22)                              */
#define GPIO0_input_en_pin22_Msk              (0x400000UL)              /*!< GPIO0 input_en: pin22 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin23_Pos              (23UL)                    /*!< GPIO0 input_en: pin23 (Bit 23)                              */
#define GPIO0_input_en_pin23_Msk              (0x800000UL)              /*!< GPIO0 input_en: pin23 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin24_Pos              (24UL)                    /*!< GPIO0 input_en: pin24 (Bit 24)                              */
#define GPIO0_input_en_pin24_Msk              (0x1000000UL)             /*!< GPIO0 input_en: pin24 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin25_Pos              (25UL)                    /*!< GPIO0 input_en: pin25 (Bit 25)                              */
#define GPIO0_input_en_pin25_Msk              (0x2000000UL)             /*!< GPIO0 input_en: pin25 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin26_Pos              (26UL)                    /*!< GPIO0 input_en: pin26 (Bit 26)                              */
#define GPIO0_input_en_pin26_Msk              (0x4000000UL)             /*!< GPIO0 input_en: pin26 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin27_Pos              (27UL)                    /*!< GPIO0 input_en: pin27 (Bit 27)                              */
#define GPIO0_input_en_pin27_Msk              (0x8000000UL)             /*!< GPIO0 input_en: pin27 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin28_Pos              (28UL)                    /*!< GPIO0 input_en: pin28 (Bit 28)                              */
#define GPIO0_input_en_pin28_Msk              (0x10000000UL)            /*!< GPIO0 input_en: pin28 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin29_Pos              (29UL)                    /*!< GPIO0 input_en: pin29 (Bit 29)                              */
#define GPIO0_input_en_pin29_Msk              (0x20000000UL)            /*!< GPIO0 input_en: pin29 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin30_Pos              (30UL)                    /*!< GPIO0 input_en: pin30 (Bit 30)                              */
#define GPIO0_input_en_pin30_Msk              (0x40000000UL)            /*!< GPIO0 input_en: pin30 (Bitfield-Mask: 0x01)                 */
#define GPIO0_input_en_pin31_Pos              (31UL)                    /*!< GPIO0 input_en: pin31 (Bit 31)                              */
#define GPIO0_input_en_pin31_Msk              (0x80000000UL)            /*!< GPIO0 input_en: pin31 (Bitfield-Mask: 0x01)                 */

/* -------------------------------  GPIO0_output_en  ------------------------------ */
#define GPIO0_output_en_pin0_Pos              (0UL)                     /*!< GPIO0 output_en: pin0 (Bit 0)                               */
#define GPIO0_output_en_pin0_Msk              (0x1UL)                   /*!< GPIO0 output_en: pin0 (Bitfield-Mask: 0x01)                 */
#define GPIO0_output_en_pin1_Pos              (1UL)                     /*!< GPIO0 output_en: pin1 (Bit 1)                               */
#define GPIO0_output_en_pin1_Msk              (0x2UL)                   /*!< GPIO0 output_en: pin1 (Bitfield-Mask: 0x01)                 */
#define GPIO0_output_en_pin2_Pos              (2UL)                     /*!< GPIO0 output_en: pin2 (Bit 2)                               */
#define GPIO0_output_en_pin2_Msk              (0x4UL)                   /*!< GPIO0 output_en: pin2 (Bitfield-Mask: 0x01)                 */
#define GPIO0_output_en_pin3_Pos              (3UL)                     /*!< GPIO0 output_en: pin3 (Bit 3)                               */
#define GPIO0_output_en_pin3_Msk              (0x8UL)                   /*!< GPIO0 output_en: pin3 (Bitfield-Mask: 0x01)                 */
#define GPIO0_output_en_pin4_Pos              (4UL)                     /*!< GPIO0 output_en: pin4 (Bit 4)                               */
#define GPIO0_output_en_pin4_Msk              (0x10UL)                  /*!< GPIO0 output_en: pin4 (Bitfield-Mask: 0x01)                 */
#define GPIO0_output_en_pin5_Pos              (5UL)                     /*!< GPIO0 output_en: pin5 (Bit 5)                               */
#define GPIO0_output_en_pin5_Msk              (0x20UL)                  /*!< GPIO0 output_en: pin5 (Bitfield-Mask: 0x01)                 */
#define GPIO0_output_en_pin6_Pos              (6UL)                     /*!< GPIO0 output_en: pin6 (Bit 6)                               */
#define GPIO0_output_en_pin6_Msk              (0x40UL)                  /*!< GPIO0 output_en: pin6 (Bitfield-Mask: 0x01)                 */
#define GPIO0_output_en_pin7_Pos              (7UL)                     /*!< GPIO0 output_en: pin7 (Bit 7)                               */
#define GPIO0_output_en_pin7_Msk              (0x80UL)                  /*!< GPIO0 output_en: pin7 (Bitfield-Mask: 0x01)                 */
#define GPIO0_output_en_pin8_Pos              (8UL)                     /*!< GPIO0 output_en: pin8 (Bit 8)                               */
#define GPIO0_output_en_pin8_Msk              (0x100UL)                 /*!< GPIO0 output_en: pin8 (Bitfield-Mask: 0x01)                 */
#define GPIO0_output_en_pin9_Pos              (9UL)                     /*!< GPIO0 output_en: pin9 (Bit 9)                               */
#define GPIO0_output_en_pin9_Msk              (0x200UL)                 /*!< GPIO0 output_en: pin9 (Bitfield-Mask: 0x01)                 */
#define GPIO0_output_en_pin10_Pos             (10UL)                    /*!< GPIO0 output_en: pin10 (Bit 10)                             */
#define GPIO0_output_en_pin10_Msk             (0x400UL)                 /*!< GPIO0 output_en: pin10 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin11_Pos             (11UL)                    /*!< GPIO0 output_en: pin11 (Bit 11)                             */
#define GPIO0_output_en_pin11_Msk             (0x800UL)                 /*!< GPIO0 output_en: pin11 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin12_Pos             (12UL)                    /*!< GPIO0 output_en: pin12 (Bit 12)                             */
#define GPIO0_output_en_pin12_Msk             (0x1000UL)                /*!< GPIO0 output_en: pin12 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin13_Pos             (13UL)                    /*!< GPIO0 output_en: pin13 (Bit 13)                             */
#define GPIO0_output_en_pin13_Msk             (0x2000UL)                /*!< GPIO0 output_en: pin13 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin14_Pos             (14UL)                    /*!< GPIO0 output_en: pin14 (Bit 14)                             */
#define GPIO0_output_en_pin14_Msk             (0x4000UL)                /*!< GPIO0 output_en: pin14 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin15_Pos             (15UL)                    /*!< GPIO0 output_en: pin15 (Bit 15)                             */
#define GPIO0_output_en_pin15_Msk             (0x8000UL)                /*!< GPIO0 output_en: pin15 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin16_Pos             (16UL)                    /*!< GPIO0 output_en: pin16 (Bit 16)                             */
#define GPIO0_output_en_pin16_Msk             (0x10000UL)               /*!< GPIO0 output_en: pin16 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin17_Pos             (17UL)                    /*!< GPIO0 output_en: pin17 (Bit 17)                             */
#define GPIO0_output_en_pin17_Msk             (0x20000UL)               /*!< GPIO0 output_en: pin17 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin18_Pos             (18UL)                    /*!< GPIO0 output_en: pin18 (Bit 18)                             */
#define GPIO0_output_en_pin18_Msk             (0x40000UL)               /*!< GPIO0 output_en: pin18 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin19_Pos             (19UL)                    /*!< GPIO0 output_en: pin19 (Bit 19)                             */
#define GPIO0_output_en_pin19_Msk             (0x80000UL)               /*!< GPIO0 output_en: pin19 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin20_Pos             (20UL)                    /*!< GPIO0 output_en: pin20 (Bit 20)                             */
#define GPIO0_output_en_pin20_Msk             (0x100000UL)              /*!< GPIO0 output_en: pin20 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin21_Pos             (21UL)                    /*!< GPIO0 output_en: pin21 (Bit 21)                             */
#define GPIO0_output_en_pin21_Msk             (0x200000UL)              /*!< GPIO0 output_en: pin21 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin22_Pos             (22UL)                    /*!< GPIO0 output_en: pin22 (Bit 22)                             */
#define GPIO0_output_en_pin22_Msk             (0x400000UL)              /*!< GPIO0 output_en: pin22 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin23_Pos             (23UL)                    /*!< GPIO0 output_en: pin23 (Bit 23)                             */
#define GPIO0_output_en_pin23_Msk             (0x800000UL)              /*!< GPIO0 output_en: pin23 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin24_Pos             (24UL)                    /*!< GPIO0 output_en: pin24 (Bit 24)                             */
#define GPIO0_output_en_pin24_Msk             (0x1000000UL)             /*!< GPIO0 output_en: pin24 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin25_Pos             (25UL)                    /*!< GPIO0 output_en: pin25 (Bit 25)                             */
#define GPIO0_output_en_pin25_Msk             (0x2000000UL)             /*!< GPIO0 output_en: pin25 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin26_Pos             (26UL)                    /*!< GPIO0 output_en: pin26 (Bit 26)                             */
#define GPIO0_output_en_pin26_Msk             (0x4000000UL)             /*!< GPIO0 output_en: pin26 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin27_Pos             (27UL)                    /*!< GPIO0 output_en: pin27 (Bit 27)                             */
#define GPIO0_output_en_pin27_Msk             (0x8000000UL)             /*!< GPIO0 output_en: pin27 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin28_Pos             (28UL)                    /*!< GPIO0 output_en: pin28 (Bit 28)                             */
#define GPIO0_output_en_pin28_Msk             (0x10000000UL)            /*!< GPIO0 output_en: pin28 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin29_Pos             (29UL)                    /*!< GPIO0 output_en: pin29 (Bit 29)                             */
#define GPIO0_output_en_pin29_Msk             (0x20000000UL)            /*!< GPIO0 output_en: pin29 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin30_Pos             (30UL)                    /*!< GPIO0 output_en: pin30 (Bit 30)                             */
#define GPIO0_output_en_pin30_Msk             (0x40000000UL)            /*!< GPIO0 output_en: pin30 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_en_pin31_Pos             (31UL)                    /*!< GPIO0 output_en: pin31 (Bit 31)                             */
#define GPIO0_output_en_pin31_Msk             (0x80000000UL)            /*!< GPIO0 output_en: pin31 (Bitfield-Mask: 0x01)                */

/* ------------------------------  GPIO0_output_val  ------------------------------ */
#define GPIO0_output_val_pin0_Pos             (0UL)                     /*!< GPIO0 output_val: pin0 (Bit 0)                              */
#define GPIO0_output_val_pin0_Msk             (0x1UL)                   /*!< GPIO0 output_val: pin0 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_val_pin1_Pos             (1UL)                     /*!< GPIO0 output_val: pin1 (Bit 1)                              */
#define GPIO0_output_val_pin1_Msk             (0x2UL)                   /*!< GPIO0 output_val: pin1 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_val_pin2_Pos             (2UL)                     /*!< GPIO0 output_val: pin2 (Bit 2)                              */
#define GPIO0_output_val_pin2_Msk             (0x4UL)                   /*!< GPIO0 output_val: pin2 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_val_pin3_Pos             (3UL)                     /*!< GPIO0 output_val: pin3 (Bit 3)                              */
#define GPIO0_output_val_pin3_Msk             (0x8UL)                   /*!< GPIO0 output_val: pin3 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_val_pin4_Pos             (4UL)                     /*!< GPIO0 output_val: pin4 (Bit 4)                              */
#define GPIO0_output_val_pin4_Msk             (0x10UL)                  /*!< GPIO0 output_val: pin4 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_val_pin5_Pos             (5UL)                     /*!< GPIO0 output_val: pin5 (Bit 5)                              */
#define GPIO0_output_val_pin5_Msk             (0x20UL)                  /*!< GPIO0 output_val: pin5 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_val_pin6_Pos             (6UL)                     /*!< GPIO0 output_val: pin6 (Bit 6)                              */
#define GPIO0_output_val_pin6_Msk             (0x40UL)                  /*!< GPIO0 output_val: pin6 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_val_pin7_Pos             (7UL)                     /*!< GPIO0 output_val: pin7 (Bit 7)                              */
#define GPIO0_output_val_pin7_Msk             (0x80UL)                  /*!< GPIO0 output_val: pin7 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_val_pin8_Pos             (8UL)                     /*!< GPIO0 output_val: pin8 (Bit 8)                              */
#define GPIO0_output_val_pin8_Msk             (0x100UL)                 /*!< GPIO0 output_val: pin8 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_val_pin9_Pos             (9UL)                     /*!< GPIO0 output_val: pin9 (Bit 9)                              */
#define GPIO0_output_val_pin9_Msk             (0x200UL)                 /*!< GPIO0 output_val: pin9 (Bitfield-Mask: 0x01)                */
#define GPIO0_output_val_pin10_Pos            (10UL)                    /*!< GPIO0 output_val: pin10 (Bit 10)                            */
#define GPIO0_output_val_pin10_Msk            (0x400UL)                 /*!< GPIO0 output_val: pin10 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin11_Pos            (11UL)                    /*!< GPIO0 output_val: pin11 (Bit 11)                            */
#define GPIO0_output_val_pin11_Msk            (0x800UL)                 /*!< GPIO0 output_val: pin11 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin12_Pos            (12UL)                    /*!< GPIO0 output_val: pin12 (Bit 12)                            */
#define GPIO0_output_val_pin12_Msk            (0x1000UL)                /*!< GPIO0 output_val: pin12 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin13_Pos            (13UL)                    /*!< GPIO0 output_val: pin13 (Bit 13)                            */
#define GPIO0_output_val_pin13_Msk            (0x2000UL)                /*!< GPIO0 output_val: pin13 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin14_Pos            (14UL)                    /*!< GPIO0 output_val: pin14 (Bit 14)                            */
#define GPIO0_output_val_pin14_Msk            (0x4000UL)                /*!< GPIO0 output_val: pin14 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin15_Pos            (15UL)                    /*!< GPIO0 output_val: pin15 (Bit 15)                            */
#define GPIO0_output_val_pin15_Msk            (0x8000UL)                /*!< GPIO0 output_val: pin15 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin16_Pos            (16UL)                    /*!< GPIO0 output_val: pin16 (Bit 16)                            */
#define GPIO0_output_val_pin16_Msk            (0x10000UL)               /*!< GPIO0 output_val: pin16 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin17_Pos            (17UL)                    /*!< GPIO0 output_val: pin17 (Bit 17)                            */
#define GPIO0_output_val_pin17_Msk            (0x20000UL)               /*!< GPIO0 output_val: pin17 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin18_Pos            (18UL)                    /*!< GPIO0 output_val: pin18 (Bit 18)                            */
#define GPIO0_output_val_pin18_Msk            (0x40000UL)               /*!< GPIO0 output_val: pin18 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin19_Pos            (19UL)                    /*!< GPIO0 output_val: pin19 (Bit 19)                            */
#define GPIO0_output_val_pin19_Msk            (0x80000UL)               /*!< GPIO0 output_val: pin19 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin20_Pos            (20UL)                    /*!< GPIO0 output_val: pin20 (Bit 20)                            */
#define GPIO0_output_val_pin20_Msk            (0x100000UL)              /*!< GPIO0 output_val: pin20 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin21_Pos            (21UL)                    /*!< GPIO0 output_val: pin21 (Bit 21)                            */
#define GPIO0_output_val_pin21_Msk            (0x200000UL)              /*!< GPIO0 output_val: pin21 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin22_Pos            (22UL)                    /*!< GPIO0 output_val: pin22 (Bit 22)                            */
#define GPIO0_output_val_pin22_Msk            (0x400000UL)              /*!< GPIO0 output_val: pin22 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin23_Pos            (23UL)                    /*!< GPIO0 output_val: pin23 (Bit 23)                            */
#define GPIO0_output_val_pin23_Msk            (0x800000UL)              /*!< GPIO0 output_val: pin23 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin24_Pos            (24UL)                    /*!< GPIO0 output_val: pin24 (Bit 24)                            */
#define GPIO0_output_val_pin24_Msk            (0x1000000UL)             /*!< GPIO0 output_val: pin24 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin25_Pos            (25UL)                    /*!< GPIO0 output_val: pin25 (Bit 25)                            */
#define GPIO0_output_val_pin25_Msk            (0x2000000UL)             /*!< GPIO0 output_val: pin25 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin26_Pos            (26UL)                    /*!< GPIO0 output_val: pin26 (Bit 26)                            */
#define GPIO0_output_val_pin26_Msk            (0x4000000UL)             /*!< GPIO0 output_val: pin26 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin27_Pos            (27UL)                    /*!< GPIO0 output_val: pin27 (Bit 27)                            */
#define GPIO0_output_val_pin27_Msk            (0x8000000UL)             /*!< GPIO0 output_val: pin27 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin28_Pos            (28UL)                    /*!< GPIO0 output_val: pin28 (Bit 28)                            */
#define GPIO0_output_val_pin28_Msk            (0x10000000UL)            /*!< GPIO0 output_val: pin28 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin29_Pos            (29UL)                    /*!< GPIO0 output_val: pin29 (Bit 29)                            */
#define GPIO0_output_val_pin29_Msk            (0x20000000UL)            /*!< GPIO0 output_val: pin29 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin30_Pos            (30UL)                    /*!< GPIO0 output_val: pin30 (Bit 30)                            */
#define GPIO0_output_val_pin30_Msk            (0x40000000UL)            /*!< GPIO0 output_val: pin30 (Bitfield-Mask: 0x01)               */
#define GPIO0_output_val_pin31_Pos            (31UL)                    /*!< GPIO0 output_val: pin31 (Bit 31)                            */
#define GPIO0_output_val_pin31_Msk            (0x80000000UL)            /*!< GPIO0 output_val: pin31 (Bitfield-Mask: 0x01)               */

/* --------------------------------  GPIO0_pullup  -------------------------------- */
#define GPIO0_pullup_pin0_Pos                 (0UL)                     /*!< GPIO0 pullup: pin0 (Bit 0)                                  */
#define GPIO0_pullup_pin0_Msk                 (0x1UL)                   /*!< GPIO0 pullup: pin0 (Bitfield-Mask: 0x01)                    */
#define GPIO0_pullup_pin1_Pos                 (1UL)                     /*!< GPIO0 pullup: pin1 (Bit 1)                                  */
#define GPIO0_pullup_pin1_Msk                 (0x2UL)                   /*!< GPIO0 pullup: pin1 (Bitfield-Mask: 0x01)                    */
#define GPIO0_pullup_pin2_Pos                 (2UL)                     /*!< GPIO0 pullup: pin2 (Bit 2)                                  */
#define GPIO0_pullup_pin2_Msk                 (0x4UL)                   /*!< GPIO0 pullup: pin2 (Bitfield-Mask: 0x01)                    */
#define GPIO0_pullup_pin3_Pos                 (3UL)                     /*!< GPIO0 pullup: pin3 (Bit 3)                                  */
#define GPIO0_pullup_pin3_Msk                 (0x8UL)                   /*!< GPIO0 pullup: pin3 (Bitfield-Mask: 0x01)                    */
#define GPIO0_pullup_pin4_Pos                 (4UL)                     /*!< GPIO0 pullup: pin4 (Bit 4)                                  */
#define GPIO0_pullup_pin4_Msk                 (0x10UL)                  /*!< GPIO0 pullup: pin4 (Bitfield-Mask: 0x01)                    */
#define GPIO0_pullup_pin5_Pos                 (5UL)                     /*!< GPIO0 pullup: pin5 (Bit 5)                                  */
#define GPIO0_pullup_pin5_Msk                 (0x20UL)                  /*!< GPIO0 pullup: pin5 (Bitfield-Mask: 0x01)                    */
#define GPIO0_pullup_pin6_Pos                 (6UL)                     /*!< GPIO0 pullup: pin6 (Bit 6)                                  */
#define GPIO0_pullup_pin6_Msk                 (0x40UL)                  /*!< GPIO0 pullup: pin6 (Bitfield-Mask: 0x01)                    */
#define GPIO0_pullup_pin7_Pos                 (7UL)                     /*!< GPIO0 pullup: pin7 (Bit 7)                                  */
#define GPIO0_pullup_pin7_Msk                 (0x80UL)                  /*!< GPIO0 pullup: pin7 (Bitfield-Mask: 0x01)                    */
#define GPIO0_pullup_pin8_Pos                 (8UL)                     /*!< GPIO0 pullup: pin8 (Bit 8)                                  */
#define GPIO0_pullup_pin8_Msk                 (0x100UL)                 /*!< GPIO0 pullup: pin8 (Bitfield-Mask: 0x01)                    */
#define GPIO0_pullup_pin9_Pos                 (9UL)                     /*!< GPIO0 pullup: pin9 (Bit 9)                                  */
#define GPIO0_pullup_pin9_Msk                 (0x200UL)                 /*!< GPIO0 pullup: pin9 (Bitfield-Mask: 0x01)                    */
#define GPIO0_pullup_pin10_Pos                (10UL)                    /*!< GPIO0 pullup: pin10 (Bit 10)                                */
#define GPIO0_pullup_pin10_Msk                (0x400UL)                 /*!< GPIO0 pullup: pin10 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin11_Pos                (11UL)                    /*!< GPIO0 pullup: pin11 (Bit 11)                                */
#define GPIO0_pullup_pin11_Msk                (0x800UL)                 /*!< GPIO0 pullup: pin11 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin12_Pos                (12UL)                    /*!< GPIO0 pullup: pin12 (Bit 12)                                */
#define GPIO0_pullup_pin12_Msk                (0x1000UL)                /*!< GPIO0 pullup: pin12 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin13_Pos                (13UL)                    /*!< GPIO0 pullup: pin13 (Bit 13)                                */
#define GPIO0_pullup_pin13_Msk                (0x2000UL)                /*!< GPIO0 pullup: pin13 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin14_Pos                (14UL)                    /*!< GPIO0 pullup: pin14 (Bit 14)                                */
#define GPIO0_pullup_pin14_Msk                (0x4000UL)                /*!< GPIO0 pullup: pin14 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin15_Pos                (15UL)                    /*!< GPIO0 pullup: pin15 (Bit 15)                                */
#define GPIO0_pullup_pin15_Msk                (0x8000UL)                /*!< GPIO0 pullup: pin15 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin16_Pos                (16UL)                    /*!< GPIO0 pullup: pin16 (Bit 16)                                */
#define GPIO0_pullup_pin16_Msk                (0x10000UL)               /*!< GPIO0 pullup: pin16 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin17_Pos                (17UL)                    /*!< GPIO0 pullup: pin17 (Bit 17)                                */
#define GPIO0_pullup_pin17_Msk                (0x20000UL)               /*!< GPIO0 pullup: pin17 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin18_Pos                (18UL)                    /*!< GPIO0 pullup: pin18 (Bit 18)                                */
#define GPIO0_pullup_pin18_Msk                (0x40000UL)               /*!< GPIO0 pullup: pin18 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin19_Pos                (19UL)                    /*!< GPIO0 pullup: pin19 (Bit 19)                                */
#define GPIO0_pullup_pin19_Msk                (0x80000UL)               /*!< GPIO0 pullup: pin19 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin20_Pos                (20UL)                    /*!< GPIO0 pullup: pin20 (Bit 20)                                */
#define GPIO0_pullup_pin20_Msk                (0x100000UL)              /*!< GPIO0 pullup: pin20 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin21_Pos                (21UL)                    /*!< GPIO0 pullup: pin21 (Bit 21)                                */
#define GPIO0_pullup_pin21_Msk                (0x200000UL)              /*!< GPIO0 pullup: pin21 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin22_Pos                (22UL)                    /*!< GPIO0 pullup: pin22 (Bit 22)                                */
#define GPIO0_pullup_pin22_Msk                (0x400000UL)              /*!< GPIO0 pullup: pin22 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin23_Pos                (23UL)                    /*!< GPIO0 pullup: pin23 (Bit 23)                                */
#define GPIO0_pullup_pin23_Msk                (0x800000UL)              /*!< GPIO0 pullup: pin23 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin24_Pos                (24UL)                    /*!< GPIO0 pullup: pin24 (Bit 24)                                */
#define GPIO0_pullup_pin24_Msk                (0x1000000UL)             /*!< GPIO0 pullup: pin24 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin25_Pos                (25UL)                    /*!< GPIO0 pullup: pin25 (Bit 25)                                */
#define GPIO0_pullup_pin25_Msk                (0x2000000UL)             /*!< GPIO0 pullup: pin25 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin26_Pos                (26UL)                    /*!< GPIO0 pullup: pin26 (Bit 26)                                */
#define GPIO0_pullup_pin26_Msk                (0x4000000UL)             /*!< GPIO0 pullup: pin26 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin27_Pos                (27UL)                    /*!< GPIO0 pullup: pin27 (Bit 27)                                */
#define GPIO0_pullup_pin27_Msk                (0x8000000UL)             /*!< GPIO0 pullup: pin27 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin28_Pos                (28UL)                    /*!< GPIO0 pullup: pin28 (Bit 28)                                */
#define GPIO0_pullup_pin28_Msk                (0x10000000UL)            /*!< GPIO0 pullup: pin28 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin29_Pos                (29UL)                    /*!< GPIO0 pullup: pin29 (Bit 29)                                */
#define GPIO0_pullup_pin29_Msk                (0x20000000UL)            /*!< GPIO0 pullup: pin29 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin30_Pos                (30UL)                    /*!< GPIO0 pullup: pin30 (Bit 30)                                */
#define GPIO0_pullup_pin30_Msk                (0x40000000UL)            /*!< GPIO0 pullup: pin30 (Bitfield-Mask: 0x01)                   */
#define GPIO0_pullup_pin31_Pos                (31UL)                    /*!< GPIO0 pullup: pin31 (Bit 31)                                */
#define GPIO0_pullup_pin31_Msk                (0x80000000UL)            /*!< GPIO0 pullup: pin31 (Bitfield-Mask: 0x01)                   */

/* ---------------------------------  GPIO0_drive  -------------------------------- */
#define GPIO0_drive_pin0_Pos                  (0UL)                     /*!< GPIO0 drive: pin0 (Bit 0)                                   */
#define GPIO0_drive_pin0_Msk                  (0x1UL)                   /*!< GPIO0 drive: pin0 (Bitfield-Mask: 0x01)                     */
#define GPIO0_drive_pin1_Pos                  (1UL)                     /*!< GPIO0 drive: pin1 (Bit 1)                                   */
#define GPIO0_drive_pin1_Msk                  (0x2UL)                   /*!< GPIO0 drive: pin1 (Bitfield-Mask: 0x01)                     */
#define GPIO0_drive_pin2_Pos                  (2UL)                     /*!< GPIO0 drive: pin2 (Bit 2)                                   */
#define GPIO0_drive_pin2_Msk                  (0x4UL)                   /*!< GPIO0 drive: pin2 (Bitfield-Mask: 0x01)                     */
#define GPIO0_drive_pin3_Pos                  (3UL)                     /*!< GPIO0 drive: pin3 (Bit 3)                                   */
#define GPIO0_drive_pin3_Msk                  (0x8UL)                   /*!< GPIO0 drive: pin3 (Bitfield-Mask: 0x01)                     */
#define GPIO0_drive_pin4_Pos                  (4UL)                     /*!< GPIO0 drive: pin4 (Bit 4)                                   */
#define GPIO0_drive_pin4_Msk                  (0x10UL)                  /*!< GPIO0 drive: pin4 (Bitfield-Mask: 0x01)                     */
#define GPIO0_drive_pin5_Pos                  (5UL)                     /*!< GPIO0 drive: pin5 (Bit 5)                                   */
#define GPIO0_drive_pin5_Msk                  (0x20UL)                  /*!< GPIO0 drive: pin5 (Bitfield-Mask: 0x01)                     */
#define GPIO0_drive_pin6_Pos                  (6UL)                     /*!< GPIO0 drive: pin6 (Bit 6)                                   */
#define GPIO0_drive_pin6_Msk                  (0x40UL)                  /*!< GPIO0 drive: pin6 (Bitfield-Mask: 0x01)                     */
#define GPIO0_drive_pin7_Pos                  (7UL)                     /*!< GPIO0 drive: pin7 (Bit 7)                                   */
#define GPIO0_drive_pin7_Msk                  (0x80UL)                  /*!< GPIO0 drive: pin7 (Bitfield-Mask: 0x01)                     */
#define GPIO0_drive_pin8_Pos                  (8UL)                     /*!< GPIO0 drive: pin8 (Bit 8)                                   */
#define GPIO0_drive_pin8_Msk                  (0x100UL)                 /*!< GPIO0 drive: pin8 (Bitfield-Mask: 0x01)                     */
#define GPIO0_drive_pin9_Pos                  (9UL)                     /*!< GPIO0 drive: pin9 (Bit 9)                                   */
#define GPIO0_drive_pin9_Msk                  (0x200UL)                 /*!< GPIO0 drive: pin9 (Bitfield-Mask: 0x01)                     */
#define GPIO0_drive_pin10_Pos                 (10UL)                    /*!< GPIO0 drive: pin10 (Bit 10)                                 */
#define GPIO0_drive_pin10_Msk                 (0x400UL)                 /*!< GPIO0 drive: pin10 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin11_Pos                 (11UL)                    /*!< GPIO0 drive: pin11 (Bit 11)                                 */
#define GPIO0_drive_pin11_Msk                 (0x800UL)                 /*!< GPIO0 drive: pin11 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin12_Pos                 (12UL)                    /*!< GPIO0 drive: pin12 (Bit 12)                                 */
#define GPIO0_drive_pin12_Msk                 (0x1000UL)                /*!< GPIO0 drive: pin12 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin13_Pos                 (13UL)                    /*!< GPIO0 drive: pin13 (Bit 13)                                 */
#define GPIO0_drive_pin13_Msk                 (0x2000UL)                /*!< GPIO0 drive: pin13 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin14_Pos                 (14UL)                    /*!< GPIO0 drive: pin14 (Bit 14)                                 */
#define GPIO0_drive_pin14_Msk                 (0x4000UL)                /*!< GPIO0 drive: pin14 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin15_Pos                 (15UL)                    /*!< GPIO0 drive: pin15 (Bit 15)                                 */
#define GPIO0_drive_pin15_Msk                 (0x8000UL)                /*!< GPIO0 drive: pin15 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin16_Pos                 (16UL)                    /*!< GPIO0 drive: pin16 (Bit 16)                                 */
#define GPIO0_drive_pin16_Msk                 (0x10000UL)               /*!< GPIO0 drive: pin16 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin17_Pos                 (17UL)                    /*!< GPIO0 drive: pin17 (Bit 17)                                 */
#define GPIO0_drive_pin17_Msk                 (0x20000UL)               /*!< GPIO0 drive: pin17 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin18_Pos                 (18UL)                    /*!< GPIO0 drive: pin18 (Bit 18)                                 */
#define GPIO0_drive_pin18_Msk                 (0x40000UL)               /*!< GPIO0 drive: pin18 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin19_Pos                 (19UL)                    /*!< GPIO0 drive: pin19 (Bit 19)                                 */
#define GPIO0_drive_pin19_Msk                 (0x80000UL)               /*!< GPIO0 drive: pin19 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin20_Pos                 (20UL)                    /*!< GPIO0 drive: pin20 (Bit 20)                                 */
#define GPIO0_drive_pin20_Msk                 (0x100000UL)              /*!< GPIO0 drive: pin20 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin21_Pos                 (21UL)                    /*!< GPIO0 drive: pin21 (Bit 21)                                 */
#define GPIO0_drive_pin21_Msk                 (0x200000UL)              /*!< GPIO0 drive: pin21 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin22_Pos                 (22UL)                    /*!< GPIO0 drive: pin22 (Bit 22)                                 */
#define GPIO0_drive_pin22_Msk                 (0x400000UL)              /*!< GPIO0 drive: pin22 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin23_Pos                 (23UL)                    /*!< GPIO0 drive: pin23 (Bit 23)                                 */
#define GPIO0_drive_pin23_Msk                 (0x800000UL)              /*!< GPIO0 drive: pin23 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin24_Pos                 (24UL)                    /*!< GPIO0 drive: pin24 (Bit 24)                                 */
#define GPIO0_drive_pin24_Msk                 (0x1000000UL)             /*!< GPIO0 drive: pin24 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin25_Pos                 (25UL)                    /*!< GPIO0 drive: pin25 (Bit 25)                                 */
#define GPIO0_drive_pin25_Msk                 (0x2000000UL)             /*!< GPIO0 drive: pin25 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin26_Pos                 (26UL)                    /*!< GPIO0 drive: pin26 (Bit 26)                                 */
#define GPIO0_drive_pin26_Msk                 (0x4000000UL)             /*!< GPIO0 drive: pin26 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin27_Pos                 (27UL)                    /*!< GPIO0 drive: pin27 (Bit 27)                                 */
#define GPIO0_drive_pin27_Msk                 (0x8000000UL)             /*!< GPIO0 drive: pin27 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin28_Pos                 (28UL)                    /*!< GPIO0 drive: pin28 (Bit 28)                                 */
#define GPIO0_drive_pin28_Msk                 (0x10000000UL)            /*!< GPIO0 drive: pin28 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin29_Pos                 (29UL)                    /*!< GPIO0 drive: pin29 (Bit 29)                                 */
#define GPIO0_drive_pin29_Msk                 (0x20000000UL)            /*!< GPIO0 drive: pin29 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin30_Pos                 (30UL)                    /*!< GPIO0 drive: pin30 (Bit 30)                                 */
#define GPIO0_drive_pin30_Msk                 (0x40000000UL)            /*!< GPIO0 drive: pin30 (Bitfield-Mask: 0x01)                    */
#define GPIO0_drive_pin31_Pos                 (31UL)                    /*!< GPIO0 drive: pin31 (Bit 31)                                 */
#define GPIO0_drive_pin31_Msk                 (0x80000000UL)            /*!< GPIO0 drive: pin31 (Bitfield-Mask: 0x01)                    */

/* --------------------------------  GPIO0_rise_ie  ------------------------------- */
#define GPIO0_rise_ie_pin0_Pos                (0UL)                     /*!< GPIO0 rise_ie: pin0 (Bit 0)                                 */
#define GPIO0_rise_ie_pin0_Msk                (0x1UL)                   /*!< GPIO0 rise_ie: pin0 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ie_pin1_Pos                (1UL)                     /*!< GPIO0 rise_ie: pin1 (Bit 1)                                 */
#define GPIO0_rise_ie_pin1_Msk                (0x2UL)                   /*!< GPIO0 rise_ie: pin1 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ie_pin2_Pos                (2UL)                     /*!< GPIO0 rise_ie: pin2 (Bit 2)                                 */
#define GPIO0_rise_ie_pin2_Msk                (0x4UL)                   /*!< GPIO0 rise_ie: pin2 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ie_pin3_Pos                (3UL)                     /*!< GPIO0 rise_ie: pin3 (Bit 3)                                 */
#define GPIO0_rise_ie_pin3_Msk                (0x8UL)                   /*!< GPIO0 rise_ie: pin3 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ie_pin4_Pos                (4UL)                     /*!< GPIO0 rise_ie: pin4 (Bit 4)                                 */
#define GPIO0_rise_ie_pin4_Msk                (0x10UL)                  /*!< GPIO0 rise_ie: pin4 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ie_pin5_Pos                (5UL)                     /*!< GPIO0 rise_ie: pin5 (Bit 5)                                 */
#define GPIO0_rise_ie_pin5_Msk                (0x20UL)                  /*!< GPIO0 rise_ie: pin5 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ie_pin6_Pos                (6UL)                     /*!< GPIO0 rise_ie: pin6 (Bit 6)                                 */
#define GPIO0_rise_ie_pin6_Msk                (0x40UL)                  /*!< GPIO0 rise_ie: pin6 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ie_pin7_Pos                (7UL)                     /*!< GPIO0 rise_ie: pin7 (Bit 7)                                 */
#define GPIO0_rise_ie_pin7_Msk                (0x80UL)                  /*!< GPIO0 rise_ie: pin7 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ie_pin8_Pos                (8UL)                     /*!< GPIO0 rise_ie: pin8 (Bit 8)                                 */
#define GPIO0_rise_ie_pin8_Msk                (0x100UL)                 /*!< GPIO0 rise_ie: pin8 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ie_pin9_Pos                (9UL)                     /*!< GPIO0 rise_ie: pin9 (Bit 9)                                 */
#define GPIO0_rise_ie_pin9_Msk                (0x200UL)                 /*!< GPIO0 rise_ie: pin9 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ie_pin10_Pos               (10UL)                    /*!< GPIO0 rise_ie: pin10 (Bit 10)                               */
#define GPIO0_rise_ie_pin10_Msk               (0x400UL)                 /*!< GPIO0 rise_ie: pin10 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin11_Pos               (11UL)                    /*!< GPIO0 rise_ie: pin11 (Bit 11)                               */
#define GPIO0_rise_ie_pin11_Msk               (0x800UL)                 /*!< GPIO0 rise_ie: pin11 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin12_Pos               (12UL)                    /*!< GPIO0 rise_ie: pin12 (Bit 12)                               */
#define GPIO0_rise_ie_pin12_Msk               (0x1000UL)                /*!< GPIO0 rise_ie: pin12 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin13_Pos               (13UL)                    /*!< GPIO0 rise_ie: pin13 (Bit 13)                               */
#define GPIO0_rise_ie_pin13_Msk               (0x2000UL)                /*!< GPIO0 rise_ie: pin13 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin14_Pos               (14UL)                    /*!< GPIO0 rise_ie: pin14 (Bit 14)                               */
#define GPIO0_rise_ie_pin14_Msk               (0x4000UL)                /*!< GPIO0 rise_ie: pin14 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin15_Pos               (15UL)                    /*!< GPIO0 rise_ie: pin15 (Bit 15)                               */
#define GPIO0_rise_ie_pin15_Msk               (0x8000UL)                /*!< GPIO0 rise_ie: pin15 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin16_Pos               (16UL)                    /*!< GPIO0 rise_ie: pin16 (Bit 16)                               */
#define GPIO0_rise_ie_pin16_Msk               (0x10000UL)               /*!< GPIO0 rise_ie: pin16 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin17_Pos               (17UL)                    /*!< GPIO0 rise_ie: pin17 (Bit 17)                               */
#define GPIO0_rise_ie_pin17_Msk               (0x20000UL)               /*!< GPIO0 rise_ie: pin17 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin18_Pos               (18UL)                    /*!< GPIO0 rise_ie: pin18 (Bit 18)                               */
#define GPIO0_rise_ie_pin18_Msk               (0x40000UL)               /*!< GPIO0 rise_ie: pin18 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin19_Pos               (19UL)                    /*!< GPIO0 rise_ie: pin19 (Bit 19)                               */
#define GPIO0_rise_ie_pin19_Msk               (0x80000UL)               /*!< GPIO0 rise_ie: pin19 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin20_Pos               (20UL)                    /*!< GPIO0 rise_ie: pin20 (Bit 20)                               */
#define GPIO0_rise_ie_pin20_Msk               (0x100000UL)              /*!< GPIO0 rise_ie: pin20 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin21_Pos               (21UL)                    /*!< GPIO0 rise_ie: pin21 (Bit 21)                               */
#define GPIO0_rise_ie_pin21_Msk               (0x200000UL)              /*!< GPIO0 rise_ie: pin21 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin22_Pos               (22UL)                    /*!< GPIO0 rise_ie: pin22 (Bit 22)                               */
#define GPIO0_rise_ie_pin22_Msk               (0x400000UL)              /*!< GPIO0 rise_ie: pin22 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin23_Pos               (23UL)                    /*!< GPIO0 rise_ie: pin23 (Bit 23)                               */
#define GPIO0_rise_ie_pin23_Msk               (0x800000UL)              /*!< GPIO0 rise_ie: pin23 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin24_Pos               (24UL)                    /*!< GPIO0 rise_ie: pin24 (Bit 24)                               */
#define GPIO0_rise_ie_pin24_Msk               (0x1000000UL)             /*!< GPIO0 rise_ie: pin24 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin25_Pos               (25UL)                    /*!< GPIO0 rise_ie: pin25 (Bit 25)                               */
#define GPIO0_rise_ie_pin25_Msk               (0x2000000UL)             /*!< GPIO0 rise_ie: pin25 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin26_Pos               (26UL)                    /*!< GPIO0 rise_ie: pin26 (Bit 26)                               */
#define GPIO0_rise_ie_pin26_Msk               (0x4000000UL)             /*!< GPIO0 rise_ie: pin26 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin27_Pos               (27UL)                    /*!< GPIO0 rise_ie: pin27 (Bit 27)                               */
#define GPIO0_rise_ie_pin27_Msk               (0x8000000UL)             /*!< GPIO0 rise_ie: pin27 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin28_Pos               (28UL)                    /*!< GPIO0 rise_ie: pin28 (Bit 28)                               */
#define GPIO0_rise_ie_pin28_Msk               (0x10000000UL)            /*!< GPIO0 rise_ie: pin28 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin29_Pos               (29UL)                    /*!< GPIO0 rise_ie: pin29 (Bit 29)                               */
#define GPIO0_rise_ie_pin29_Msk               (0x20000000UL)            /*!< GPIO0 rise_ie: pin29 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin30_Pos               (30UL)                    /*!< GPIO0 rise_ie: pin30 (Bit 30)                               */
#define GPIO0_rise_ie_pin30_Msk               (0x40000000UL)            /*!< GPIO0 rise_ie: pin30 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ie_pin31_Pos               (31UL)                    /*!< GPIO0 rise_ie: pin31 (Bit 31)                               */
#define GPIO0_rise_ie_pin31_Msk               (0x80000000UL)            /*!< GPIO0 rise_ie: pin31 (Bitfield-Mask: 0x01)                  */

/* --------------------------------  GPIO0_rise_ip  ------------------------------- */
#define GPIO0_rise_ip_pin0_Pos                (0UL)                     /*!< GPIO0 rise_ip: pin0 (Bit 0)                                 */
#define GPIO0_rise_ip_pin0_Msk                (0x1UL)                   /*!< GPIO0 rise_ip: pin0 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ip_pin1_Pos                (1UL)                     /*!< GPIO0 rise_ip: pin1 (Bit 1)                                 */
#define GPIO0_rise_ip_pin1_Msk                (0x2UL)                   /*!< GPIO0 rise_ip: pin1 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ip_pin2_Pos                (2UL)                     /*!< GPIO0 rise_ip: pin2 (Bit 2)                                 */
#define GPIO0_rise_ip_pin2_Msk                (0x4UL)                   /*!< GPIO0 rise_ip: pin2 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ip_pin3_Pos                (3UL)                     /*!< GPIO0 rise_ip: pin3 (Bit 3)                                 */
#define GPIO0_rise_ip_pin3_Msk                (0x8UL)                   /*!< GPIO0 rise_ip: pin3 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ip_pin4_Pos                (4UL)                     /*!< GPIO0 rise_ip: pin4 (Bit 4)                                 */
#define GPIO0_rise_ip_pin4_Msk                (0x10UL)                  /*!< GPIO0 rise_ip: pin4 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ip_pin5_Pos                (5UL)                     /*!< GPIO0 rise_ip: pin5 (Bit 5)                                 */
#define GPIO0_rise_ip_pin5_Msk                (0x20UL)                  /*!< GPIO0 rise_ip: pin5 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ip_pin6_Pos                (6UL)                     /*!< GPIO0 rise_ip: pin6 (Bit 6)                                 */
#define GPIO0_rise_ip_pin6_Msk                (0x40UL)                  /*!< GPIO0 rise_ip: pin6 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ip_pin7_Pos                (7UL)                     /*!< GPIO0 rise_ip: pin7 (Bit 7)                                 */
#define GPIO0_rise_ip_pin7_Msk                (0x80UL)                  /*!< GPIO0 rise_ip: pin7 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ip_pin8_Pos                (8UL)                     /*!< GPIO0 rise_ip: pin8 (Bit 8)                                 */
#define GPIO0_rise_ip_pin8_Msk                (0x100UL)                 /*!< GPIO0 rise_ip: pin8 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ip_pin9_Pos                (9UL)                     /*!< GPIO0 rise_ip: pin9 (Bit 9)                                 */
#define GPIO0_rise_ip_pin9_Msk                (0x200UL)                 /*!< GPIO0 rise_ip: pin9 (Bitfield-Mask: 0x01)                   */
#define GPIO0_rise_ip_pin10_Pos               (10UL)                    /*!< GPIO0 rise_ip: pin10 (Bit 10)                               */
#define GPIO0_rise_ip_pin10_Msk               (0x400UL)                 /*!< GPIO0 rise_ip: pin10 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin11_Pos               (11UL)                    /*!< GPIO0 rise_ip: pin11 (Bit 11)                               */
#define GPIO0_rise_ip_pin11_Msk               (0x800UL)                 /*!< GPIO0 rise_ip: pin11 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin12_Pos               (12UL)                    /*!< GPIO0 rise_ip: pin12 (Bit 12)                               */
#define GPIO0_rise_ip_pin12_Msk               (0x1000UL)                /*!< GPIO0 rise_ip: pin12 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin13_Pos               (13UL)                    /*!< GPIO0 rise_ip: pin13 (Bit 13)                               */
#define GPIO0_rise_ip_pin13_Msk               (0x2000UL)                /*!< GPIO0 rise_ip: pin13 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin14_Pos               (14UL)                    /*!< GPIO0 rise_ip: pin14 (Bit 14)                               */
#define GPIO0_rise_ip_pin14_Msk               (0x4000UL)                /*!< GPIO0 rise_ip: pin14 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin15_Pos               (15UL)                    /*!< GPIO0 rise_ip: pin15 (Bit 15)                               */
#define GPIO0_rise_ip_pin15_Msk               (0x8000UL)                /*!< GPIO0 rise_ip: pin15 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin16_Pos               (16UL)                    /*!< GPIO0 rise_ip: pin16 (Bit 16)                               */
#define GPIO0_rise_ip_pin16_Msk               (0x10000UL)               /*!< GPIO0 rise_ip: pin16 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin17_Pos               (17UL)                    /*!< GPIO0 rise_ip: pin17 (Bit 17)                               */
#define GPIO0_rise_ip_pin17_Msk               (0x20000UL)               /*!< GPIO0 rise_ip: pin17 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin18_Pos               (18UL)                    /*!< GPIO0 rise_ip: pin18 (Bit 18)                               */
#define GPIO0_rise_ip_pin18_Msk               (0x40000UL)               /*!< GPIO0 rise_ip: pin18 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin19_Pos               (19UL)                    /*!< GPIO0 rise_ip: pin19 (Bit 19)                               */
#define GPIO0_rise_ip_pin19_Msk               (0x80000UL)               /*!< GPIO0 rise_ip: pin19 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin20_Pos               (20UL)                    /*!< GPIO0 rise_ip: pin20 (Bit 20)                               */
#define GPIO0_rise_ip_pin20_Msk               (0x100000UL)              /*!< GPIO0 rise_ip: pin20 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin21_Pos               (21UL)                    /*!< GPIO0 rise_ip: pin21 (Bit 21)                               */
#define GPIO0_rise_ip_pin21_Msk               (0x200000UL)              /*!< GPIO0 rise_ip: pin21 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin22_Pos               (22UL)                    /*!< GPIO0 rise_ip: pin22 (Bit 22)                               */
#define GPIO0_rise_ip_pin22_Msk               (0x400000UL)              /*!< GPIO0 rise_ip: pin22 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin23_Pos               (23UL)                    /*!< GPIO0 rise_ip: pin23 (Bit 23)                               */
#define GPIO0_rise_ip_pin23_Msk               (0x800000UL)              /*!< GPIO0 rise_ip: pin23 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin24_Pos               (24UL)                    /*!< GPIO0 rise_ip: pin24 (Bit 24)                               */
#define GPIO0_rise_ip_pin24_Msk               (0x1000000UL)             /*!< GPIO0 rise_ip: pin24 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin25_Pos               (25UL)                    /*!< GPIO0 rise_ip: pin25 (Bit 25)                               */
#define GPIO0_rise_ip_pin25_Msk               (0x2000000UL)             /*!< GPIO0 rise_ip: pin25 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin26_Pos               (26UL)                    /*!< GPIO0 rise_ip: pin26 (Bit 26)                               */
#define GPIO0_rise_ip_pin26_Msk               (0x4000000UL)             /*!< GPIO0 rise_ip: pin26 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin27_Pos               (27UL)                    /*!< GPIO0 rise_ip: pin27 (Bit 27)                               */
#define GPIO0_rise_ip_pin27_Msk               (0x8000000UL)             /*!< GPIO0 rise_ip: pin27 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin28_Pos               (28UL)                    /*!< GPIO0 rise_ip: pin28 (Bit 28)                               */
#define GPIO0_rise_ip_pin28_Msk               (0x10000000UL)            /*!< GPIO0 rise_ip: pin28 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin29_Pos               (29UL)                    /*!< GPIO0 rise_ip: pin29 (Bit 29)                               */
#define GPIO0_rise_ip_pin29_Msk               (0x20000000UL)            /*!< GPIO0 rise_ip: pin29 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin30_Pos               (30UL)                    /*!< GPIO0 rise_ip: pin30 (Bit 30)                               */
#define GPIO0_rise_ip_pin30_Msk               (0x40000000UL)            /*!< GPIO0 rise_ip: pin30 (Bitfield-Mask: 0x01)                  */
#define GPIO0_rise_ip_pin31_Pos               (31UL)                    /*!< GPIO0 rise_ip: pin31 (Bit 31)                               */
#define GPIO0_rise_ip_pin31_Msk               (0x80000000UL)            /*!< GPIO0 rise_ip: pin31 (Bitfield-Mask: 0x01)                  */

/* --------------------------------  GPIO0_fall_ie  ------------------------------- */
#define GPIO0_fall_ie_pin0_Pos                (0UL)                     /*!< GPIO0 fall_ie: pin0 (Bit 0)                                 */
#define GPIO0_fall_ie_pin0_Msk                (0x1UL)                   /*!< GPIO0 fall_ie: pin0 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ie_pin1_Pos                (1UL)                     /*!< GPIO0 fall_ie: pin1 (Bit 1)                                 */
#define GPIO0_fall_ie_pin1_Msk                (0x2UL)                   /*!< GPIO0 fall_ie: pin1 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ie_pin2_Pos                (2UL)                     /*!< GPIO0 fall_ie: pin2 (Bit 2)                                 */
#define GPIO0_fall_ie_pin2_Msk                (0x4UL)                   /*!< GPIO0 fall_ie: pin2 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ie_pin3_Pos                (3UL)                     /*!< GPIO0 fall_ie: pin3 (Bit 3)                                 */
#define GPIO0_fall_ie_pin3_Msk                (0x8UL)                   /*!< GPIO0 fall_ie: pin3 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ie_pin4_Pos                (4UL)                     /*!< GPIO0 fall_ie: pin4 (Bit 4)                                 */
#define GPIO0_fall_ie_pin4_Msk                (0x10UL)                  /*!< GPIO0 fall_ie: pin4 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ie_pin5_Pos                (5UL)                     /*!< GPIO0 fall_ie: pin5 (Bit 5)                                 */
#define GPIO0_fall_ie_pin5_Msk                (0x20UL)                  /*!< GPIO0 fall_ie: pin5 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ie_pin6_Pos                (6UL)                     /*!< GPIO0 fall_ie: pin6 (Bit 6)                                 */
#define GPIO0_fall_ie_pin6_Msk                (0x40UL)                  /*!< GPIO0 fall_ie: pin6 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ie_pin7_Pos                (7UL)                     /*!< GPIO0 fall_ie: pin7 (Bit 7)                                 */
#define GPIO0_fall_ie_pin7_Msk                (0x80UL)                  /*!< GPIO0 fall_ie: pin7 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ie_pin8_Pos                (8UL)                     /*!< GPIO0 fall_ie: pin8 (Bit 8)                                 */
#define GPIO0_fall_ie_pin8_Msk                (0x100UL)                 /*!< GPIO0 fall_ie: pin8 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ie_pin9_Pos                (9UL)                     /*!< GPIO0 fall_ie: pin9 (Bit 9)                                 */
#define GPIO0_fall_ie_pin9_Msk                (0x200UL)                 /*!< GPIO0 fall_ie: pin9 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ie_pin10_Pos               (10UL)                    /*!< GPIO0 fall_ie: pin10 (Bit 10)                               */
#define GPIO0_fall_ie_pin10_Msk               (0x400UL)                 /*!< GPIO0 fall_ie: pin10 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin11_Pos               (11UL)                    /*!< GPIO0 fall_ie: pin11 (Bit 11)                               */
#define GPIO0_fall_ie_pin11_Msk               (0x800UL)                 /*!< GPIO0 fall_ie: pin11 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin12_Pos               (12UL)                    /*!< GPIO0 fall_ie: pin12 (Bit 12)                               */
#define GPIO0_fall_ie_pin12_Msk               (0x1000UL)                /*!< GPIO0 fall_ie: pin12 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin13_Pos               (13UL)                    /*!< GPIO0 fall_ie: pin13 (Bit 13)                               */
#define GPIO0_fall_ie_pin13_Msk               (0x2000UL)                /*!< GPIO0 fall_ie: pin13 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin14_Pos               (14UL)                    /*!< GPIO0 fall_ie: pin14 (Bit 14)                               */
#define GPIO0_fall_ie_pin14_Msk               (0x4000UL)                /*!< GPIO0 fall_ie: pin14 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin15_Pos               (15UL)                    /*!< GPIO0 fall_ie: pin15 (Bit 15)                               */
#define GPIO0_fall_ie_pin15_Msk               (0x8000UL)                /*!< GPIO0 fall_ie: pin15 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin16_Pos               (16UL)                    /*!< GPIO0 fall_ie: pin16 (Bit 16)                               */
#define GPIO0_fall_ie_pin16_Msk               (0x10000UL)               /*!< GPIO0 fall_ie: pin16 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin17_Pos               (17UL)                    /*!< GPIO0 fall_ie: pin17 (Bit 17)                               */
#define GPIO0_fall_ie_pin17_Msk               (0x20000UL)               /*!< GPIO0 fall_ie: pin17 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin18_Pos               (18UL)                    /*!< GPIO0 fall_ie: pin18 (Bit 18)                               */
#define GPIO0_fall_ie_pin18_Msk               (0x40000UL)               /*!< GPIO0 fall_ie: pin18 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin19_Pos               (19UL)                    /*!< GPIO0 fall_ie: pin19 (Bit 19)                               */
#define GPIO0_fall_ie_pin19_Msk               (0x80000UL)               /*!< GPIO0 fall_ie: pin19 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin20_Pos               (20UL)                    /*!< GPIO0 fall_ie: pin20 (Bit 20)                               */
#define GPIO0_fall_ie_pin20_Msk               (0x100000UL)              /*!< GPIO0 fall_ie: pin20 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin21_Pos               (21UL)                    /*!< GPIO0 fall_ie: pin21 (Bit 21)                               */
#define GPIO0_fall_ie_pin21_Msk               (0x200000UL)              /*!< GPIO0 fall_ie: pin21 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin22_Pos               (22UL)                    /*!< GPIO0 fall_ie: pin22 (Bit 22)                               */
#define GPIO0_fall_ie_pin22_Msk               (0x400000UL)              /*!< GPIO0 fall_ie: pin22 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin23_Pos               (23UL)                    /*!< GPIO0 fall_ie: pin23 (Bit 23)                               */
#define GPIO0_fall_ie_pin23_Msk               (0x800000UL)              /*!< GPIO0 fall_ie: pin23 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin24_Pos               (24UL)                    /*!< GPIO0 fall_ie: pin24 (Bit 24)                               */
#define GPIO0_fall_ie_pin24_Msk               (0x1000000UL)             /*!< GPIO0 fall_ie: pin24 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin25_Pos               (25UL)                    /*!< GPIO0 fall_ie: pin25 (Bit 25)                               */
#define GPIO0_fall_ie_pin25_Msk               (0x2000000UL)             /*!< GPIO0 fall_ie: pin25 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin26_Pos               (26UL)                    /*!< GPIO0 fall_ie: pin26 (Bit 26)                               */
#define GPIO0_fall_ie_pin26_Msk               (0x4000000UL)             /*!< GPIO0 fall_ie: pin26 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin27_Pos               (27UL)                    /*!< GPIO0 fall_ie: pin27 (Bit 27)                               */
#define GPIO0_fall_ie_pin27_Msk               (0x8000000UL)             /*!< GPIO0 fall_ie: pin27 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin28_Pos               (28UL)                    /*!< GPIO0 fall_ie: pin28 (Bit 28)                               */
#define GPIO0_fall_ie_pin28_Msk               (0x10000000UL)            /*!< GPIO0 fall_ie: pin28 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin29_Pos               (29UL)                    /*!< GPIO0 fall_ie: pin29 (Bit 29)                               */
#define GPIO0_fall_ie_pin29_Msk               (0x20000000UL)            /*!< GPIO0 fall_ie: pin29 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin30_Pos               (30UL)                    /*!< GPIO0 fall_ie: pin30 (Bit 30)                               */
#define GPIO0_fall_ie_pin30_Msk               (0x40000000UL)            /*!< GPIO0 fall_ie: pin30 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ie_pin31_Pos               (31UL)                    /*!< GPIO0 fall_ie: pin31 (Bit 31)                               */
#define GPIO0_fall_ie_pin31_Msk               (0x80000000UL)            /*!< GPIO0 fall_ie: pin31 (Bitfield-Mask: 0x01)                  */

/* --------------------------------  GPIO0_fall_ip  ------------------------------- */
#define GPIO0_fall_ip_pin0_Pos                (0UL)                     /*!< GPIO0 fall_ip: pin0 (Bit 0)                                 */
#define GPIO0_fall_ip_pin0_Msk                (0x1UL)                   /*!< GPIO0 fall_ip: pin0 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ip_pin1_Pos                (1UL)                     /*!< GPIO0 fall_ip: pin1 (Bit 1)                                 */
#define GPIO0_fall_ip_pin1_Msk                (0x2UL)                   /*!< GPIO0 fall_ip: pin1 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ip_pin2_Pos                (2UL)                     /*!< GPIO0 fall_ip: pin2 (Bit 2)                                 */
#define GPIO0_fall_ip_pin2_Msk                (0x4UL)                   /*!< GPIO0 fall_ip: pin2 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ip_pin3_Pos                (3UL)                     /*!< GPIO0 fall_ip: pin3 (Bit 3)                                 */
#define GPIO0_fall_ip_pin3_Msk                (0x8UL)                   /*!< GPIO0 fall_ip: pin3 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ip_pin4_Pos                (4UL)                     /*!< GPIO0 fall_ip: pin4 (Bit 4)                                 */
#define GPIO0_fall_ip_pin4_Msk                (0x10UL)                  /*!< GPIO0 fall_ip: pin4 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ip_pin5_Pos                (5UL)                     /*!< GPIO0 fall_ip: pin5 (Bit 5)                                 */
#define GPIO0_fall_ip_pin5_Msk                (0x20UL)                  /*!< GPIO0 fall_ip: pin5 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ip_pin6_Pos                (6UL)                     /*!< GPIO0 fall_ip: pin6 (Bit 6)                                 */
#define GPIO0_fall_ip_pin6_Msk                (0x40UL)                  /*!< GPIO0 fall_ip: pin6 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ip_pin7_Pos                (7UL)                     /*!< GPIO0 fall_ip: pin7 (Bit 7)                                 */
#define GPIO0_fall_ip_pin7_Msk                (0x80UL)                  /*!< GPIO0 fall_ip: pin7 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ip_pin8_Pos                (8UL)                     /*!< GPIO0 fall_ip: pin8 (Bit 8)                                 */
#define GPIO0_fall_ip_pin8_Msk                (0x100UL)                 /*!< GPIO0 fall_ip: pin8 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ip_pin9_Pos                (9UL)                     /*!< GPIO0 fall_ip: pin9 (Bit 9)                                 */
#define GPIO0_fall_ip_pin9_Msk                (0x200UL)                 /*!< GPIO0 fall_ip: pin9 (Bitfield-Mask: 0x01)                   */
#define GPIO0_fall_ip_pin10_Pos               (10UL)                    /*!< GPIO0 fall_ip: pin10 (Bit 10)                               */
#define GPIO0_fall_ip_pin10_Msk               (0x400UL)                 /*!< GPIO0 fall_ip: pin10 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin11_Pos               (11UL)                    /*!< GPIO0 fall_ip: pin11 (Bit 11)                               */
#define GPIO0_fall_ip_pin11_Msk               (0x800UL)                 /*!< GPIO0 fall_ip: pin11 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin12_Pos               (12UL)                    /*!< GPIO0 fall_ip: pin12 (Bit 12)                               */
#define GPIO0_fall_ip_pin12_Msk               (0x1000UL)                /*!< GPIO0 fall_ip: pin12 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin13_Pos               (13UL)                    /*!< GPIO0 fall_ip: pin13 (Bit 13)                               */
#define GPIO0_fall_ip_pin13_Msk               (0x2000UL)                /*!< GPIO0 fall_ip: pin13 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin14_Pos               (14UL)                    /*!< GPIO0 fall_ip: pin14 (Bit 14)                               */
#define GPIO0_fall_ip_pin14_Msk               (0x4000UL)                /*!< GPIO0 fall_ip: pin14 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin15_Pos               (15UL)                    /*!< GPIO0 fall_ip: pin15 (Bit 15)                               */
#define GPIO0_fall_ip_pin15_Msk               (0x8000UL)                /*!< GPIO0 fall_ip: pin15 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin16_Pos               (16UL)                    /*!< GPIO0 fall_ip: pin16 (Bit 16)                               */
#define GPIO0_fall_ip_pin16_Msk               (0x10000UL)               /*!< GPIO0 fall_ip: pin16 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin17_Pos               (17UL)                    /*!< GPIO0 fall_ip: pin17 (Bit 17)                               */
#define GPIO0_fall_ip_pin17_Msk               (0x20000UL)               /*!< GPIO0 fall_ip: pin17 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin18_Pos               (18UL)                    /*!< GPIO0 fall_ip: pin18 (Bit 18)                               */
#define GPIO0_fall_ip_pin18_Msk               (0x40000UL)               /*!< GPIO0 fall_ip: pin18 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin19_Pos               (19UL)                    /*!< GPIO0 fall_ip: pin19 (Bit 19)                               */
#define GPIO0_fall_ip_pin19_Msk               (0x80000UL)               /*!< GPIO0 fall_ip: pin19 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin20_Pos               (20UL)                    /*!< GPIO0 fall_ip: pin20 (Bit 20)                               */
#define GPIO0_fall_ip_pin20_Msk               (0x100000UL)              /*!< GPIO0 fall_ip: pin20 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin21_Pos               (21UL)                    /*!< GPIO0 fall_ip: pin21 (Bit 21)                               */
#define GPIO0_fall_ip_pin21_Msk               (0x200000UL)              /*!< GPIO0 fall_ip: pin21 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin22_Pos               (22UL)                    /*!< GPIO0 fall_ip: pin22 (Bit 22)                               */
#define GPIO0_fall_ip_pin22_Msk               (0x400000UL)              /*!< GPIO0 fall_ip: pin22 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin23_Pos               (23UL)                    /*!< GPIO0 fall_ip: pin23 (Bit 23)                               */
#define GPIO0_fall_ip_pin23_Msk               (0x800000UL)              /*!< GPIO0 fall_ip: pin23 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin24_Pos               (24UL)                    /*!< GPIO0 fall_ip: pin24 (Bit 24)                               */
#define GPIO0_fall_ip_pin24_Msk               (0x1000000UL)             /*!< GPIO0 fall_ip: pin24 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin25_Pos               (25UL)                    /*!< GPIO0 fall_ip: pin25 (Bit 25)                               */
#define GPIO0_fall_ip_pin25_Msk               (0x2000000UL)             /*!< GPIO0 fall_ip: pin25 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin26_Pos               (26UL)                    /*!< GPIO0 fall_ip: pin26 (Bit 26)                               */
#define GPIO0_fall_ip_pin26_Msk               (0x4000000UL)             /*!< GPIO0 fall_ip: pin26 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin27_Pos               (27UL)                    /*!< GPIO0 fall_ip: pin27 (Bit 27)                               */
#define GPIO0_fall_ip_pin27_Msk               (0x8000000UL)             /*!< GPIO0 fall_ip: pin27 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin28_Pos               (28UL)                    /*!< GPIO0 fall_ip: pin28 (Bit 28)                               */
#define GPIO0_fall_ip_pin28_Msk               (0x10000000UL)            /*!< GPIO0 fall_ip: pin28 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin29_Pos               (29UL)                    /*!< GPIO0 fall_ip: pin29 (Bit 29)                               */
#define GPIO0_fall_ip_pin29_Msk               (0x20000000UL)            /*!< GPIO0 fall_ip: pin29 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin30_Pos               (30UL)                    /*!< GPIO0 fall_ip: pin30 (Bit 30)                               */
#define GPIO0_fall_ip_pin30_Msk               (0x40000000UL)            /*!< GPIO0 fall_ip: pin30 (Bitfield-Mask: 0x01)                  */
#define GPIO0_fall_ip_pin31_Pos               (31UL)                    /*!< GPIO0 fall_ip: pin31 (Bit 31)                               */
#define GPIO0_fall_ip_pin31_Msk               (0x80000000UL)            /*!< GPIO0 fall_ip: pin31 (Bitfield-Mask: 0x01)                  */

/* --------------------------------  GPIO0_high_ie  ------------------------------- */
#define GPIO0_high_ie_pin0_Pos                (0UL)                     /*!< GPIO0 high_ie: pin0 (Bit 0)                                 */
#define GPIO0_high_ie_pin0_Msk                (0x1UL)                   /*!< GPIO0 high_ie: pin0 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ie_pin1_Pos                (1UL)                     /*!< GPIO0 high_ie: pin1 (Bit 1)                                 */
#define GPIO0_high_ie_pin1_Msk                (0x2UL)                   /*!< GPIO0 high_ie: pin1 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ie_pin2_Pos                (2UL)                     /*!< GPIO0 high_ie: pin2 (Bit 2)                                 */
#define GPIO0_high_ie_pin2_Msk                (0x4UL)                   /*!< GPIO0 high_ie: pin2 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ie_pin3_Pos                (3UL)                     /*!< GPIO0 high_ie: pin3 (Bit 3)                                 */
#define GPIO0_high_ie_pin3_Msk                (0x8UL)                   /*!< GPIO0 high_ie: pin3 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ie_pin4_Pos                (4UL)                     /*!< GPIO0 high_ie: pin4 (Bit 4)                                 */
#define GPIO0_high_ie_pin4_Msk                (0x10UL)                  /*!< GPIO0 high_ie: pin4 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ie_pin5_Pos                (5UL)                     /*!< GPIO0 high_ie: pin5 (Bit 5)                                 */
#define GPIO0_high_ie_pin5_Msk                (0x20UL)                  /*!< GPIO0 high_ie: pin5 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ie_pin6_Pos                (6UL)                     /*!< GPIO0 high_ie: pin6 (Bit 6)                                 */
#define GPIO0_high_ie_pin6_Msk                (0x40UL)                  /*!< GPIO0 high_ie: pin6 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ie_pin7_Pos                (7UL)                     /*!< GPIO0 high_ie: pin7 (Bit 7)                                 */
#define GPIO0_high_ie_pin7_Msk                (0x80UL)                  /*!< GPIO0 high_ie: pin7 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ie_pin8_Pos                (8UL)                     /*!< GPIO0 high_ie: pin8 (Bit 8)                                 */
#define GPIO0_high_ie_pin8_Msk                (0x100UL)                 /*!< GPIO0 high_ie: pin8 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ie_pin9_Pos                (9UL)                     /*!< GPIO0 high_ie: pin9 (Bit 9)                                 */
#define GPIO0_high_ie_pin9_Msk                (0x200UL)                 /*!< GPIO0 high_ie: pin9 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ie_pin10_Pos               (10UL)                    /*!< GPIO0 high_ie: pin10 (Bit 10)                               */
#define GPIO0_high_ie_pin10_Msk               (0x400UL)                 /*!< GPIO0 high_ie: pin10 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin11_Pos               (11UL)                    /*!< GPIO0 high_ie: pin11 (Bit 11)                               */
#define GPIO0_high_ie_pin11_Msk               (0x800UL)                 /*!< GPIO0 high_ie: pin11 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin12_Pos               (12UL)                    /*!< GPIO0 high_ie: pin12 (Bit 12)                               */
#define GPIO0_high_ie_pin12_Msk               (0x1000UL)                /*!< GPIO0 high_ie: pin12 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin13_Pos               (13UL)                    /*!< GPIO0 high_ie: pin13 (Bit 13)                               */
#define GPIO0_high_ie_pin13_Msk               (0x2000UL)                /*!< GPIO0 high_ie: pin13 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin14_Pos               (14UL)                    /*!< GPIO0 high_ie: pin14 (Bit 14)                               */
#define GPIO0_high_ie_pin14_Msk               (0x4000UL)                /*!< GPIO0 high_ie: pin14 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin15_Pos               (15UL)                    /*!< GPIO0 high_ie: pin15 (Bit 15)                               */
#define GPIO0_high_ie_pin15_Msk               (0x8000UL)                /*!< GPIO0 high_ie: pin15 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin16_Pos               (16UL)                    /*!< GPIO0 high_ie: pin16 (Bit 16)                               */
#define GPIO0_high_ie_pin16_Msk               (0x10000UL)               /*!< GPIO0 high_ie: pin16 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin17_Pos               (17UL)                    /*!< GPIO0 high_ie: pin17 (Bit 17)                               */
#define GPIO0_high_ie_pin17_Msk               (0x20000UL)               /*!< GPIO0 high_ie: pin17 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin18_Pos               (18UL)                    /*!< GPIO0 high_ie: pin18 (Bit 18)                               */
#define GPIO0_high_ie_pin18_Msk               (0x40000UL)               /*!< GPIO0 high_ie: pin18 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin19_Pos               (19UL)                    /*!< GPIO0 high_ie: pin19 (Bit 19)                               */
#define GPIO0_high_ie_pin19_Msk               (0x80000UL)               /*!< GPIO0 high_ie: pin19 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin20_Pos               (20UL)                    /*!< GPIO0 high_ie: pin20 (Bit 20)                               */
#define GPIO0_high_ie_pin20_Msk               (0x100000UL)              /*!< GPIO0 high_ie: pin20 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin21_Pos               (21UL)                    /*!< GPIO0 high_ie: pin21 (Bit 21)                               */
#define GPIO0_high_ie_pin21_Msk               (0x200000UL)              /*!< GPIO0 high_ie: pin21 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin22_Pos               (22UL)                    /*!< GPIO0 high_ie: pin22 (Bit 22)                               */
#define GPIO0_high_ie_pin22_Msk               (0x400000UL)              /*!< GPIO0 high_ie: pin22 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin23_Pos               (23UL)                    /*!< GPIO0 high_ie: pin23 (Bit 23)                               */
#define GPIO0_high_ie_pin23_Msk               (0x800000UL)              /*!< GPIO0 high_ie: pin23 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin24_Pos               (24UL)                    /*!< GPIO0 high_ie: pin24 (Bit 24)                               */
#define GPIO0_high_ie_pin24_Msk               (0x1000000UL)             /*!< GPIO0 high_ie: pin24 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin25_Pos               (25UL)                    /*!< GPIO0 high_ie: pin25 (Bit 25)                               */
#define GPIO0_high_ie_pin25_Msk               (0x2000000UL)             /*!< GPIO0 high_ie: pin25 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin26_Pos               (26UL)                    /*!< GPIO0 high_ie: pin26 (Bit 26)                               */
#define GPIO0_high_ie_pin26_Msk               (0x4000000UL)             /*!< GPIO0 high_ie: pin26 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin27_Pos               (27UL)                    /*!< GPIO0 high_ie: pin27 (Bit 27)                               */
#define GPIO0_high_ie_pin27_Msk               (0x8000000UL)             /*!< GPIO0 high_ie: pin27 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin28_Pos               (28UL)                    /*!< GPIO0 high_ie: pin28 (Bit 28)                               */
#define GPIO0_high_ie_pin28_Msk               (0x10000000UL)            /*!< GPIO0 high_ie: pin28 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin29_Pos               (29UL)                    /*!< GPIO0 high_ie: pin29 (Bit 29)                               */
#define GPIO0_high_ie_pin29_Msk               (0x20000000UL)            /*!< GPIO0 high_ie: pin29 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin30_Pos               (30UL)                    /*!< GPIO0 high_ie: pin30 (Bit 30)                               */
#define GPIO0_high_ie_pin30_Msk               (0x40000000UL)            /*!< GPIO0 high_ie: pin30 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ie_pin31_Pos               (31UL)                    /*!< GPIO0 high_ie: pin31 (Bit 31)                               */
#define GPIO0_high_ie_pin31_Msk               (0x80000000UL)            /*!< GPIO0 high_ie: pin31 (Bitfield-Mask: 0x01)                  */

/* --------------------------------  GPIO0_high_ip  ------------------------------- */
#define GPIO0_high_ip_pin0_Pos                (0UL)                     /*!< GPIO0 high_ip: pin0 (Bit 0)                                 */
#define GPIO0_high_ip_pin0_Msk                (0x1UL)                   /*!< GPIO0 high_ip: pin0 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ip_pin1_Pos                (1UL)                     /*!< GPIO0 high_ip: pin1 (Bit 1)                                 */
#define GPIO0_high_ip_pin1_Msk                (0x2UL)                   /*!< GPIO0 high_ip: pin1 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ip_pin2_Pos                (2UL)                     /*!< GPIO0 high_ip: pin2 (Bit 2)                                 */
#define GPIO0_high_ip_pin2_Msk                (0x4UL)                   /*!< GPIO0 high_ip: pin2 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ip_pin3_Pos                (3UL)                     /*!< GPIO0 high_ip: pin3 (Bit 3)                                 */
#define GPIO0_high_ip_pin3_Msk                (0x8UL)                   /*!< GPIO0 high_ip: pin3 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ip_pin4_Pos                (4UL)                     /*!< GPIO0 high_ip: pin4 (Bit 4)                                 */
#define GPIO0_high_ip_pin4_Msk                (0x10UL)                  /*!< GPIO0 high_ip: pin4 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ip_pin5_Pos                (5UL)                     /*!< GPIO0 high_ip: pin5 (Bit 5)                                 */
#define GPIO0_high_ip_pin5_Msk                (0x20UL)                  /*!< GPIO0 high_ip: pin5 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ip_pin6_Pos                (6UL)                     /*!< GPIO0 high_ip: pin6 (Bit 6)                                 */
#define GPIO0_high_ip_pin6_Msk                (0x40UL)                  /*!< GPIO0 high_ip: pin6 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ip_pin7_Pos                (7UL)                     /*!< GPIO0 high_ip: pin7 (Bit 7)                                 */
#define GPIO0_high_ip_pin7_Msk                (0x80UL)                  /*!< GPIO0 high_ip: pin7 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ip_pin8_Pos                (8UL)                     /*!< GPIO0 high_ip: pin8 (Bit 8)                                 */
#define GPIO0_high_ip_pin8_Msk                (0x100UL)                 /*!< GPIO0 high_ip: pin8 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ip_pin9_Pos                (9UL)                     /*!< GPIO0 high_ip: pin9 (Bit 9)                                 */
#define GPIO0_high_ip_pin9_Msk                (0x200UL)                 /*!< GPIO0 high_ip: pin9 (Bitfield-Mask: 0x01)                   */
#define GPIO0_high_ip_pin10_Pos               (10UL)                    /*!< GPIO0 high_ip: pin10 (Bit 10)                               */
#define GPIO0_high_ip_pin10_Msk               (0x400UL)                 /*!< GPIO0 high_ip: pin10 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin11_Pos               (11UL)                    /*!< GPIO0 high_ip: pin11 (Bit 11)                               */
#define GPIO0_high_ip_pin11_Msk               (0x800UL)                 /*!< GPIO0 high_ip: pin11 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin12_Pos               (12UL)                    /*!< GPIO0 high_ip: pin12 (Bit 12)                               */
#define GPIO0_high_ip_pin12_Msk               (0x1000UL)                /*!< GPIO0 high_ip: pin12 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin13_Pos               (13UL)                    /*!< GPIO0 high_ip: pin13 (Bit 13)                               */
#define GPIO0_high_ip_pin13_Msk               (0x2000UL)                /*!< GPIO0 high_ip: pin13 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin14_Pos               (14UL)                    /*!< GPIO0 high_ip: pin14 (Bit 14)                               */
#define GPIO0_high_ip_pin14_Msk               (0x4000UL)                /*!< GPIO0 high_ip: pin14 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin15_Pos               (15UL)                    /*!< GPIO0 high_ip: pin15 (Bit 15)                               */
#define GPIO0_high_ip_pin15_Msk               (0x8000UL)                /*!< GPIO0 high_ip: pin15 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin16_Pos               (16UL)                    /*!< GPIO0 high_ip: pin16 (Bit 16)                               */
#define GPIO0_high_ip_pin16_Msk               (0x10000UL)               /*!< GPIO0 high_ip: pin16 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin17_Pos               (17UL)                    /*!< GPIO0 high_ip: pin17 (Bit 17)                               */
#define GPIO0_high_ip_pin17_Msk               (0x20000UL)               /*!< GPIO0 high_ip: pin17 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin18_Pos               (18UL)                    /*!< GPIO0 high_ip: pin18 (Bit 18)                               */
#define GPIO0_high_ip_pin18_Msk               (0x40000UL)               /*!< GPIO0 high_ip: pin18 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin19_Pos               (19UL)                    /*!< GPIO0 high_ip: pin19 (Bit 19)                               */
#define GPIO0_high_ip_pin19_Msk               (0x80000UL)               /*!< GPIO0 high_ip: pin19 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin20_Pos               (20UL)                    /*!< GPIO0 high_ip: pin20 (Bit 20)                               */
#define GPIO0_high_ip_pin20_Msk               (0x100000UL)              /*!< GPIO0 high_ip: pin20 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin21_Pos               (21UL)                    /*!< GPIO0 high_ip: pin21 (Bit 21)                               */
#define GPIO0_high_ip_pin21_Msk               (0x200000UL)              /*!< GPIO0 high_ip: pin21 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin22_Pos               (22UL)                    /*!< GPIO0 high_ip: pin22 (Bit 22)                               */
#define GPIO0_high_ip_pin22_Msk               (0x400000UL)              /*!< GPIO0 high_ip: pin22 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin23_Pos               (23UL)                    /*!< GPIO0 high_ip: pin23 (Bit 23)                               */
#define GPIO0_high_ip_pin23_Msk               (0x800000UL)              /*!< GPIO0 high_ip: pin23 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin24_Pos               (24UL)                    /*!< GPIO0 high_ip: pin24 (Bit 24)                               */
#define GPIO0_high_ip_pin24_Msk               (0x1000000UL)             /*!< GPIO0 high_ip: pin24 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin25_Pos               (25UL)                    /*!< GPIO0 high_ip: pin25 (Bit 25)                               */
#define GPIO0_high_ip_pin25_Msk               (0x2000000UL)             /*!< GPIO0 high_ip: pin25 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin26_Pos               (26UL)                    /*!< GPIO0 high_ip: pin26 (Bit 26)                               */
#define GPIO0_high_ip_pin26_Msk               (0x4000000UL)             /*!< GPIO0 high_ip: pin26 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin27_Pos               (27UL)                    /*!< GPIO0 high_ip: pin27 (Bit 27)                               */
#define GPIO0_high_ip_pin27_Msk               (0x8000000UL)             /*!< GPIO0 high_ip: pin27 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin28_Pos               (28UL)                    /*!< GPIO0 high_ip: pin28 (Bit 28)                               */
#define GPIO0_high_ip_pin28_Msk               (0x10000000UL)            /*!< GPIO0 high_ip: pin28 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin29_Pos               (29UL)                    /*!< GPIO0 high_ip: pin29 (Bit 29)                               */
#define GPIO0_high_ip_pin29_Msk               (0x20000000UL)            /*!< GPIO0 high_ip: pin29 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin30_Pos               (30UL)                    /*!< GPIO0 high_ip: pin30 (Bit 30)                               */
#define GPIO0_high_ip_pin30_Msk               (0x40000000UL)            /*!< GPIO0 high_ip: pin30 (Bitfield-Mask: 0x01)                  */
#define GPIO0_high_ip_pin31_Pos               (31UL)                    /*!< GPIO0 high_ip: pin31 (Bit 31)                               */
#define GPIO0_high_ip_pin31_Msk               (0x80000000UL)            /*!< GPIO0 high_ip: pin31 (Bitfield-Mask: 0x01)                  */

/* --------------------------------  GPIO0_low_ie  -------------------------------- */
#define GPIO0_low_ie_pin0_Pos                 (0UL)                     /*!< GPIO0 low_ie: pin0 (Bit 0)                                  */
#define GPIO0_low_ie_pin0_Msk                 (0x1UL)                   /*!< GPIO0 low_ie: pin0 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ie_pin1_Pos                 (1UL)                     /*!< GPIO0 low_ie: pin1 (Bit 1)                                  */
#define GPIO0_low_ie_pin1_Msk                 (0x2UL)                   /*!< GPIO0 low_ie: pin1 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ie_pin2_Pos                 (2UL)                     /*!< GPIO0 low_ie: pin2 (Bit 2)                                  */
#define GPIO0_low_ie_pin2_Msk                 (0x4UL)                   /*!< GPIO0 low_ie: pin2 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ie_pin3_Pos                 (3UL)                     /*!< GPIO0 low_ie: pin3 (Bit 3)                                  */
#define GPIO0_low_ie_pin3_Msk                 (0x8UL)                   /*!< GPIO0 low_ie: pin3 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ie_pin4_Pos                 (4UL)                     /*!< GPIO0 low_ie: pin4 (Bit 4)                                  */
#define GPIO0_low_ie_pin4_Msk                 (0x10UL)                  /*!< GPIO0 low_ie: pin4 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ie_pin5_Pos                 (5UL)                     /*!< GPIO0 low_ie: pin5 (Bit 5)                                  */
#define GPIO0_low_ie_pin5_Msk                 (0x20UL)                  /*!< GPIO0 low_ie: pin5 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ie_pin6_Pos                 (6UL)                     /*!< GPIO0 low_ie: pin6 (Bit 6)                                  */
#define GPIO0_low_ie_pin6_Msk                 (0x40UL)                  /*!< GPIO0 low_ie: pin6 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ie_pin7_Pos                 (7UL)                     /*!< GPIO0 low_ie: pin7 (Bit 7)                                  */
#define GPIO0_low_ie_pin7_Msk                 (0x80UL)                  /*!< GPIO0 low_ie: pin7 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ie_pin8_Pos                 (8UL)                     /*!< GPIO0 low_ie: pin8 (Bit 8)                                  */
#define GPIO0_low_ie_pin8_Msk                 (0x100UL)                 /*!< GPIO0 low_ie: pin8 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ie_pin9_Pos                 (9UL)                     /*!< GPIO0 low_ie: pin9 (Bit 9)                                  */
#define GPIO0_low_ie_pin9_Msk                 (0x200UL)                 /*!< GPIO0 low_ie: pin9 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ie_pin10_Pos                (10UL)                    /*!< GPIO0 low_ie: pin10 (Bit 10)                                */
#define GPIO0_low_ie_pin10_Msk                (0x400UL)                 /*!< GPIO0 low_ie: pin10 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin11_Pos                (11UL)                    /*!< GPIO0 low_ie: pin11 (Bit 11)                                */
#define GPIO0_low_ie_pin11_Msk                (0x800UL)                 /*!< GPIO0 low_ie: pin11 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin12_Pos                (12UL)                    /*!< GPIO0 low_ie: pin12 (Bit 12)                                */
#define GPIO0_low_ie_pin12_Msk                (0x1000UL)                /*!< GPIO0 low_ie: pin12 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin13_Pos                (13UL)                    /*!< GPIO0 low_ie: pin13 (Bit 13)                                */
#define GPIO0_low_ie_pin13_Msk                (0x2000UL)                /*!< GPIO0 low_ie: pin13 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin14_Pos                (14UL)                    /*!< GPIO0 low_ie: pin14 (Bit 14)                                */
#define GPIO0_low_ie_pin14_Msk                (0x4000UL)                /*!< GPIO0 low_ie: pin14 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin15_Pos                (15UL)                    /*!< GPIO0 low_ie: pin15 (Bit 15)                                */
#define GPIO0_low_ie_pin15_Msk                (0x8000UL)                /*!< GPIO0 low_ie: pin15 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin16_Pos                (16UL)                    /*!< GPIO0 low_ie: pin16 (Bit 16)                                */
#define GPIO0_low_ie_pin16_Msk                (0x10000UL)               /*!< GPIO0 low_ie: pin16 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin17_Pos                (17UL)                    /*!< GPIO0 low_ie: pin17 (Bit 17)                                */
#define GPIO0_low_ie_pin17_Msk                (0x20000UL)               /*!< GPIO0 low_ie: pin17 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin18_Pos                (18UL)                    /*!< GPIO0 low_ie: pin18 (Bit 18)                                */
#define GPIO0_low_ie_pin18_Msk                (0x40000UL)               /*!< GPIO0 low_ie: pin18 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin19_Pos                (19UL)                    /*!< GPIO0 low_ie: pin19 (Bit 19)                                */
#define GPIO0_low_ie_pin19_Msk                (0x80000UL)               /*!< GPIO0 low_ie: pin19 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin20_Pos                (20UL)                    /*!< GPIO0 low_ie: pin20 (Bit 20)                                */
#define GPIO0_low_ie_pin20_Msk                (0x100000UL)              /*!< GPIO0 low_ie: pin20 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin21_Pos                (21UL)                    /*!< GPIO0 low_ie: pin21 (Bit 21)                                */
#define GPIO0_low_ie_pin21_Msk                (0x200000UL)              /*!< GPIO0 low_ie: pin21 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin22_Pos                (22UL)                    /*!< GPIO0 low_ie: pin22 (Bit 22)                                */
#define GPIO0_low_ie_pin22_Msk                (0x400000UL)              /*!< GPIO0 low_ie: pin22 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin23_Pos                (23UL)                    /*!< GPIO0 low_ie: pin23 (Bit 23)                                */
#define GPIO0_low_ie_pin23_Msk                (0x800000UL)              /*!< GPIO0 low_ie: pin23 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin24_Pos                (24UL)                    /*!< GPIO0 low_ie: pin24 (Bit 24)                                */
#define GPIO0_low_ie_pin24_Msk                (0x1000000UL)             /*!< GPIO0 low_ie: pin24 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin25_Pos                (25UL)                    /*!< GPIO0 low_ie: pin25 (Bit 25)                                */
#define GPIO0_low_ie_pin25_Msk                (0x2000000UL)             /*!< GPIO0 low_ie: pin25 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin26_Pos                (26UL)                    /*!< GPIO0 low_ie: pin26 (Bit 26)                                */
#define GPIO0_low_ie_pin26_Msk                (0x4000000UL)             /*!< GPIO0 low_ie: pin26 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin27_Pos                (27UL)                    /*!< GPIO0 low_ie: pin27 (Bit 27)                                */
#define GPIO0_low_ie_pin27_Msk                (0x8000000UL)             /*!< GPIO0 low_ie: pin27 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin28_Pos                (28UL)                    /*!< GPIO0 low_ie: pin28 (Bit 28)                                */
#define GPIO0_low_ie_pin28_Msk                (0x10000000UL)            /*!< GPIO0 low_ie: pin28 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin29_Pos                (29UL)                    /*!< GPIO0 low_ie: pin29 (Bit 29)                                */
#define GPIO0_low_ie_pin29_Msk                (0x20000000UL)            /*!< GPIO0 low_ie: pin29 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin30_Pos                (30UL)                    /*!< GPIO0 low_ie: pin30 (Bit 30)                                */
#define GPIO0_low_ie_pin30_Msk                (0x40000000UL)            /*!< GPIO0 low_ie: pin30 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ie_pin31_Pos                (31UL)                    /*!< GPIO0 low_ie: pin31 (Bit 31)                                */
#define GPIO0_low_ie_pin31_Msk                (0x80000000UL)            /*!< GPIO0 low_ie: pin31 (Bitfield-Mask: 0x01)                   */

/* --------------------------------  GPIO0_low_ip  -------------------------------- */
#define GPIO0_low_ip_pin0_Pos                 (0UL)                     /*!< GPIO0 low_ip: pin0 (Bit 0)                                  */
#define GPIO0_low_ip_pin0_Msk                 (0x1UL)                   /*!< GPIO0 low_ip: pin0 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ip_pin1_Pos                 (1UL)                     /*!< GPIO0 low_ip: pin1 (Bit 1)                                  */
#define GPIO0_low_ip_pin1_Msk                 (0x2UL)                   /*!< GPIO0 low_ip: pin1 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ip_pin2_Pos                 (2UL)                     /*!< GPIO0 low_ip: pin2 (Bit 2)                                  */
#define GPIO0_low_ip_pin2_Msk                 (0x4UL)                   /*!< GPIO0 low_ip: pin2 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ip_pin3_Pos                 (3UL)                     /*!< GPIO0 low_ip: pin3 (Bit 3)                                  */
#define GPIO0_low_ip_pin3_Msk                 (0x8UL)                   /*!< GPIO0 low_ip: pin3 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ip_pin4_Pos                 (4UL)                     /*!< GPIO0 low_ip: pin4 (Bit 4)                                  */
#define GPIO0_low_ip_pin4_Msk                 (0x10UL)                  /*!< GPIO0 low_ip: pin4 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ip_pin5_Pos                 (5UL)                     /*!< GPIO0 low_ip: pin5 (Bit 5)                                  */
#define GPIO0_low_ip_pin5_Msk                 (0x20UL)                  /*!< GPIO0 low_ip: pin5 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ip_pin6_Pos                 (6UL)                     /*!< GPIO0 low_ip: pin6 (Bit 6)                                  */
#define GPIO0_low_ip_pin6_Msk                 (0x40UL)                  /*!< GPIO0 low_ip: pin6 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ip_pin7_Pos                 (7UL)                     /*!< GPIO0 low_ip: pin7 (Bit 7)                                  */
#define GPIO0_low_ip_pin7_Msk                 (0x80UL)                  /*!< GPIO0 low_ip: pin7 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ip_pin8_Pos                 (8UL)                     /*!< GPIO0 low_ip: pin8 (Bit 8)                                  */
#define GPIO0_low_ip_pin8_Msk                 (0x100UL)                 /*!< GPIO0 low_ip: pin8 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ip_pin9_Pos                 (9UL)                     /*!< GPIO0 low_ip: pin9 (Bit 9)                                  */
#define GPIO0_low_ip_pin9_Msk                 (0x200UL)                 /*!< GPIO0 low_ip: pin9 (Bitfield-Mask: 0x01)                    */
#define GPIO0_low_ip_pin10_Pos                (10UL)                    /*!< GPIO0 low_ip: pin10 (Bit 10)                                */
#define GPIO0_low_ip_pin10_Msk                (0x400UL)                 /*!< GPIO0 low_ip: pin10 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin11_Pos                (11UL)                    /*!< GPIO0 low_ip: pin11 (Bit 11)                                */
#define GPIO0_low_ip_pin11_Msk                (0x800UL)                 /*!< GPIO0 low_ip: pin11 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin12_Pos                (12UL)                    /*!< GPIO0 low_ip: pin12 (Bit 12)                                */
#define GPIO0_low_ip_pin12_Msk                (0x1000UL)                /*!< GPIO0 low_ip: pin12 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin13_Pos                (13UL)                    /*!< GPIO0 low_ip: pin13 (Bit 13)                                */
#define GPIO0_low_ip_pin13_Msk                (0x2000UL)                /*!< GPIO0 low_ip: pin13 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin14_Pos                (14UL)                    /*!< GPIO0 low_ip: pin14 (Bit 14)                                */
#define GPIO0_low_ip_pin14_Msk                (0x4000UL)                /*!< GPIO0 low_ip: pin14 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin15_Pos                (15UL)                    /*!< GPIO0 low_ip: pin15 (Bit 15)                                */
#define GPIO0_low_ip_pin15_Msk                (0x8000UL)                /*!< GPIO0 low_ip: pin15 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin16_Pos                (16UL)                    /*!< GPIO0 low_ip: pin16 (Bit 16)                                */
#define GPIO0_low_ip_pin16_Msk                (0x10000UL)               /*!< GPIO0 low_ip: pin16 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin17_Pos                (17UL)                    /*!< GPIO0 low_ip: pin17 (Bit 17)                                */
#define GPIO0_low_ip_pin17_Msk                (0x20000UL)               /*!< GPIO0 low_ip: pin17 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin18_Pos                (18UL)                    /*!< GPIO0 low_ip: pin18 (Bit 18)                                */
#define GPIO0_low_ip_pin18_Msk                (0x40000UL)               /*!< GPIO0 low_ip: pin18 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin19_Pos                (19UL)                    /*!< GPIO0 low_ip: pin19 (Bit 19)                                */
#define GPIO0_low_ip_pin19_Msk                (0x80000UL)               /*!< GPIO0 low_ip: pin19 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin20_Pos                (20UL)                    /*!< GPIO0 low_ip: pin20 (Bit 20)                                */
#define GPIO0_low_ip_pin20_Msk                (0x100000UL)              /*!< GPIO0 low_ip: pin20 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin21_Pos                (21UL)                    /*!< GPIO0 low_ip: pin21 (Bit 21)                                */
#define GPIO0_low_ip_pin21_Msk                (0x200000UL)              /*!< GPIO0 low_ip: pin21 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin22_Pos                (22UL)                    /*!< GPIO0 low_ip: pin22 (Bit 22)                                */
#define GPIO0_low_ip_pin22_Msk                (0x400000UL)              /*!< GPIO0 low_ip: pin22 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin23_Pos                (23UL)                    /*!< GPIO0 low_ip: pin23 (Bit 23)                                */
#define GPIO0_low_ip_pin23_Msk                (0x800000UL)              /*!< GPIO0 low_ip: pin23 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin24_Pos                (24UL)                    /*!< GPIO0 low_ip: pin24 (Bit 24)                                */
#define GPIO0_low_ip_pin24_Msk                (0x1000000UL)             /*!< GPIO0 low_ip: pin24 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin25_Pos                (25UL)                    /*!< GPIO0 low_ip: pin25 (Bit 25)                                */
#define GPIO0_low_ip_pin25_Msk                (0x2000000UL)             /*!< GPIO0 low_ip: pin25 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin26_Pos                (26UL)                    /*!< GPIO0 low_ip: pin26 (Bit 26)                                */
#define GPIO0_low_ip_pin26_Msk                (0x4000000UL)             /*!< GPIO0 low_ip: pin26 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin27_Pos                (27UL)                    /*!< GPIO0 low_ip: pin27 (Bit 27)                                */
#define GPIO0_low_ip_pin27_Msk                (0x8000000UL)             /*!< GPIO0 low_ip: pin27 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin28_Pos                (28UL)                    /*!< GPIO0 low_ip: pin28 (Bit 28)                                */
#define GPIO0_low_ip_pin28_Msk                (0x10000000UL)            /*!< GPIO0 low_ip: pin28 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin29_Pos                (29UL)                    /*!< GPIO0 low_ip: pin29 (Bit 29)                                */
#define GPIO0_low_ip_pin29_Msk                (0x20000000UL)            /*!< GPIO0 low_ip: pin29 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin30_Pos                (30UL)                    /*!< GPIO0 low_ip: pin30 (Bit 30)                                */
#define GPIO0_low_ip_pin30_Msk                (0x40000000UL)            /*!< GPIO0 low_ip: pin30 (Bitfield-Mask: 0x01)                   */
#define GPIO0_low_ip_pin31_Pos                (31UL)                    /*!< GPIO0 low_ip: pin31 (Bit 31)                                */
#define GPIO0_low_ip_pin31_Msk                (0x80000000UL)            /*!< GPIO0 low_ip: pin31 (Bitfield-Mask: 0x01)                   */

/* --------------------------------  GPIO0_iof_en  -------------------------------- */
#define GPIO0_iof_en_pin0_Pos                 (0UL)                     /*!< GPIO0 iof_en: pin0 (Bit 0)                                  */
#define GPIO0_iof_en_pin0_Msk                 (0x1UL)                   /*!< GPIO0 iof_en: pin0 (Bitfield-Mask: 0x01)                    */
#define GPIO0_iof_en_pin1_Pos                 (1UL)                     /*!< GPIO0 iof_en: pin1 (Bit 1)                                  */
#define GPIO0_iof_en_pin1_Msk                 (0x2UL)                   /*!< GPIO0 iof_en: pin1 (Bitfield-Mask: 0x01)                    */
#define GPIO0_iof_en_pin2_Pos                 (2UL)                     /*!< GPIO0 iof_en: pin2 (Bit 2)                                  */
#define GPIO0_iof_en_pin2_Msk                 (0x4UL)                   /*!< GPIO0 iof_en: pin2 (Bitfield-Mask: 0x01)                    */
#define GPIO0_iof_en_pin3_Pos                 (3UL)                     /*!< GPIO0 iof_en: pin3 (Bit 3)                                  */
#define GPIO0_iof_en_pin3_Msk                 (0x8UL)                   /*!< GPIO0 iof_en: pin3 (Bitfield-Mask: 0x01)                    */
#define GPIO0_iof_en_pin4_Pos                 (4UL)                     /*!< GPIO0 iof_en: pin4 (Bit 4)                                  */
#define GPIO0_iof_en_pin4_Msk                 (0x10UL)                  /*!< GPIO0 iof_en: pin4 (Bitfield-Mask: 0x01)                    */
#define GPIO0_iof_en_pin5_Pos                 (5UL)                     /*!< GPIO0 iof_en: pin5 (Bit 5)                                  */
#define GPIO0_iof_en_pin5_Msk                 (0x20UL)                  /*!< GPIO0 iof_en: pin5 (Bitfield-Mask: 0x01)                    */
#define GPIO0_iof_en_pin6_Pos                 (6UL)                     /*!< GPIO0 iof_en: pin6 (Bit 6)                                  */
#define GPIO0_iof_en_pin6_Msk                 (0x40UL)                  /*!< GPIO0 iof_en: pin6 (Bitfield-Mask: 0x01)                    */
#define GPIO0_iof_en_pin7_Pos                 (7UL)                     /*!< GPIO0 iof_en: pin7 (Bit 7)                                  */
#define GPIO0_iof_en_pin7_Msk                 (0x80UL)                  /*!< GPIO0 iof_en: pin7 (Bitfield-Mask: 0x01)                    */
#define GPIO0_iof_en_pin8_Pos                 (8UL)                     /*!< GPIO0 iof_en: pin8 (Bit 8)                                  */
#define GPIO0_iof_en_pin8_Msk                 (0x100UL)                 /*!< GPIO0 iof_en: pin8 (Bitfield-Mask: 0x01)                    */
#define GPIO0_iof_en_pin9_Pos                 (9UL)                     /*!< GPIO0 iof_en: pin9 (Bit 9)                                  */
#define GPIO0_iof_en_pin9_Msk                 (0x200UL)                 /*!< GPIO0 iof_en: pin9 (Bitfield-Mask: 0x01)                    */
#define GPIO0_iof_en_pin10_Pos                (10UL)                    /*!< GPIO0 iof_en: pin10 (Bit 10)                                */
#define GPIO0_iof_en_pin10_Msk                (0x400UL)                 /*!< GPIO0 iof_en: pin10 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin11_Pos                (11UL)                    /*!< GPIO0 iof_en: pin11 (Bit 11)                                */
#define GPIO0_iof_en_pin11_Msk                (0x800UL)                 /*!< GPIO0 iof_en: pin11 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin12_Pos                (12UL)                    /*!< GPIO0 iof_en: pin12 (Bit 12)                                */
#define GPIO0_iof_en_pin12_Msk                (0x1000UL)                /*!< GPIO0 iof_en: pin12 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin13_Pos                (13UL)                    /*!< GPIO0 iof_en: pin13 (Bit 13)                                */
#define GPIO0_iof_en_pin13_Msk                (0x2000UL)                /*!< GPIO0 iof_en: pin13 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin14_Pos                (14UL)                    /*!< GPIO0 iof_en: pin14 (Bit 14)                                */
#define GPIO0_iof_en_pin14_Msk                (0x4000UL)                /*!< GPIO0 iof_en: pin14 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin15_Pos                (15UL)                    /*!< GPIO0 iof_en: pin15 (Bit 15)                                */
#define GPIO0_iof_en_pin15_Msk                (0x8000UL)                /*!< GPIO0 iof_en: pin15 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin16_Pos                (16UL)                    /*!< GPIO0 iof_en: pin16 (Bit 16)                                */
#define GPIO0_iof_en_pin16_Msk                (0x10000UL)               /*!< GPIO0 iof_en: pin16 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin17_Pos                (17UL)                    /*!< GPIO0 iof_en: pin17 (Bit 17)                                */
#define GPIO0_iof_en_pin17_Msk                (0x20000UL)               /*!< GPIO0 iof_en: pin17 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin18_Pos                (18UL)                    /*!< GPIO0 iof_en: pin18 (Bit 18)                                */
#define GPIO0_iof_en_pin18_Msk                (0x40000UL)               /*!< GPIO0 iof_en: pin18 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin19_Pos                (19UL)                    /*!< GPIO0 iof_en: pin19 (Bit 19)                                */
#define GPIO0_iof_en_pin19_Msk                (0x80000UL)               /*!< GPIO0 iof_en: pin19 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin20_Pos                (20UL)                    /*!< GPIO0 iof_en: pin20 (Bit 20)                                */
#define GPIO0_iof_en_pin20_Msk                (0x100000UL)              /*!< GPIO0 iof_en: pin20 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin21_Pos                (21UL)                    /*!< GPIO0 iof_en: pin21 (Bit 21)                                */
#define GPIO0_iof_en_pin21_Msk                (0x200000UL)              /*!< GPIO0 iof_en: pin21 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin22_Pos                (22UL)                    /*!< GPIO0 iof_en: pin22 (Bit 22)                                */
#define GPIO0_iof_en_pin22_Msk                (0x400000UL)              /*!< GPIO0 iof_en: pin22 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin23_Pos                (23UL)                    /*!< GPIO0 iof_en: pin23 (Bit 23)                                */
#define GPIO0_iof_en_pin23_Msk                (0x800000UL)              /*!< GPIO0 iof_en: pin23 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin24_Pos                (24UL)                    /*!< GPIO0 iof_en: pin24 (Bit 24)                                */
#define GPIO0_iof_en_pin24_Msk                (0x1000000UL)             /*!< GPIO0 iof_en: pin24 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin25_Pos                (25UL)                    /*!< GPIO0 iof_en: pin25 (Bit 25)                                */
#define GPIO0_iof_en_pin25_Msk                (0x2000000UL)             /*!< GPIO0 iof_en: pin25 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin26_Pos                (26UL)                    /*!< GPIO0 iof_en: pin26 (Bit 26)                                */
#define GPIO0_iof_en_pin26_Msk                (0x4000000UL)             /*!< GPIO0 iof_en: pin26 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin27_Pos                (27UL)                    /*!< GPIO0 iof_en: pin27 (Bit 27)                                */
#define GPIO0_iof_en_pin27_Msk                (0x8000000UL)             /*!< GPIO0 iof_en: pin27 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin28_Pos                (28UL)                    /*!< GPIO0 iof_en: pin28 (Bit 28)                                */
#define GPIO0_iof_en_pin28_Msk                (0x10000000UL)            /*!< GPIO0 iof_en: pin28 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin29_Pos                (29UL)                    /*!< GPIO0 iof_en: pin29 (Bit 29)                                */
#define GPIO0_iof_en_pin29_Msk                (0x20000000UL)            /*!< GPIO0 iof_en: pin29 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin30_Pos                (30UL)                    /*!< GPIO0 iof_en: pin30 (Bit 30)                                */
#define GPIO0_iof_en_pin30_Msk                (0x40000000UL)            /*!< GPIO0 iof_en: pin30 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_en_pin31_Pos                (31UL)                    /*!< GPIO0 iof_en: pin31 (Bit 31)                                */
#define GPIO0_iof_en_pin31_Msk                (0x80000000UL)            /*!< GPIO0 iof_en: pin31 (Bitfield-Mask: 0x01)                   */

/* --------------------------------  GPIO0_iof_sel  ------------------------------- */
#define GPIO0_iof_sel_pin0_Pos                (0UL)                     /*!< GPIO0 iof_sel: pin0 (Bit 0)                                 */
#define GPIO0_iof_sel_pin0_Msk                (0x1UL)                   /*!< GPIO0 iof_sel: pin0 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_sel_pin1_Pos                (1UL)                     /*!< GPIO0 iof_sel: pin1 (Bit 1)                                 */
#define GPIO0_iof_sel_pin1_Msk                (0x2UL)                   /*!< GPIO0 iof_sel: pin1 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_sel_pin2_Pos                (2UL)                     /*!< GPIO0 iof_sel: pin2 (Bit 2)                                 */
#define GPIO0_iof_sel_pin2_Msk                (0x4UL)                   /*!< GPIO0 iof_sel: pin2 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_sel_pin3_Pos                (3UL)                     /*!< GPIO0 iof_sel: pin3 (Bit 3)                                 */
#define GPIO0_iof_sel_pin3_Msk                (0x8UL)                   /*!< GPIO0 iof_sel: pin3 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_sel_pin4_Pos                (4UL)                     /*!< GPIO0 iof_sel: pin4 (Bit 4)                                 */
#define GPIO0_iof_sel_pin4_Msk                (0x10UL)                  /*!< GPIO0 iof_sel: pin4 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_sel_pin5_Pos                (5UL)                     /*!< GPIO0 iof_sel: pin5 (Bit 5)                                 */
#define GPIO0_iof_sel_pin5_Msk                (0x20UL)                  /*!< GPIO0 iof_sel: pin5 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_sel_pin6_Pos                (6UL)                     /*!< GPIO0 iof_sel: pin6 (Bit 6)                                 */
#define GPIO0_iof_sel_pin6_Msk                (0x40UL)                  /*!< GPIO0 iof_sel: pin6 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_sel_pin7_Pos                (7UL)                     /*!< GPIO0 iof_sel: pin7 (Bit 7)                                 */
#define GPIO0_iof_sel_pin7_Msk                (0x80UL)                  /*!< GPIO0 iof_sel: pin7 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_sel_pin8_Pos                (8UL)                     /*!< GPIO0 iof_sel: pin8 (Bit 8)                                 */
#define GPIO0_iof_sel_pin8_Msk                (0x100UL)                 /*!< GPIO0 iof_sel: pin8 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_sel_pin9_Pos                (9UL)                     /*!< GPIO0 iof_sel: pin9 (Bit 9)                                 */
#define GPIO0_iof_sel_pin9_Msk                (0x200UL)                 /*!< GPIO0 iof_sel: pin9 (Bitfield-Mask: 0x01)                   */
#define GPIO0_iof_sel_pin10_Pos               (10UL)                    /*!< GPIO0 iof_sel: pin10 (Bit 10)                               */
#define GPIO0_iof_sel_pin10_Msk               (0x400UL)                 /*!< GPIO0 iof_sel: pin10 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin11_Pos               (11UL)                    /*!< GPIO0 iof_sel: pin11 (Bit 11)                               */
#define GPIO0_iof_sel_pin11_Msk               (0x800UL)                 /*!< GPIO0 iof_sel: pin11 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin12_Pos               (12UL)                    /*!< GPIO0 iof_sel: pin12 (Bit 12)                               */
#define GPIO0_iof_sel_pin12_Msk               (0x1000UL)                /*!< GPIO0 iof_sel: pin12 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin13_Pos               (13UL)                    /*!< GPIO0 iof_sel: pin13 (Bit 13)                               */
#define GPIO0_iof_sel_pin13_Msk               (0x2000UL)                /*!< GPIO0 iof_sel: pin13 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin14_Pos               (14UL)                    /*!< GPIO0 iof_sel: pin14 (Bit 14)                               */
#define GPIO0_iof_sel_pin14_Msk               (0x4000UL)                /*!< GPIO0 iof_sel: pin14 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin15_Pos               (15UL)                    /*!< GPIO0 iof_sel: pin15 (Bit 15)                               */
#define GPIO0_iof_sel_pin15_Msk               (0x8000UL)                /*!< GPIO0 iof_sel: pin15 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin16_Pos               (16UL)                    /*!< GPIO0 iof_sel: pin16 (Bit 16)                               */
#define GPIO0_iof_sel_pin16_Msk               (0x10000UL)               /*!< GPIO0 iof_sel: pin16 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin17_Pos               (17UL)                    /*!< GPIO0 iof_sel: pin17 (Bit 17)                               */
#define GPIO0_iof_sel_pin17_Msk               (0x20000UL)               /*!< GPIO0 iof_sel: pin17 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin18_Pos               (18UL)                    /*!< GPIO0 iof_sel: pin18 (Bit 18)                               */
#define GPIO0_iof_sel_pin18_Msk               (0x40000UL)               /*!< GPIO0 iof_sel: pin18 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin19_Pos               (19UL)                    /*!< GPIO0 iof_sel: pin19 (Bit 19)                               */
#define GPIO0_iof_sel_pin19_Msk               (0x80000UL)               /*!< GPIO0 iof_sel: pin19 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin20_Pos               (20UL)                    /*!< GPIO0 iof_sel: pin20 (Bit 20)                               */
#define GPIO0_iof_sel_pin20_Msk               (0x100000UL)              /*!< GPIO0 iof_sel: pin20 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin21_Pos               (21UL)                    /*!< GPIO0 iof_sel: pin21 (Bit 21)                               */
#define GPIO0_iof_sel_pin21_Msk               (0x200000UL)              /*!< GPIO0 iof_sel: pin21 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin22_Pos               (22UL)                    /*!< GPIO0 iof_sel: pin22 (Bit 22)                               */
#define GPIO0_iof_sel_pin22_Msk               (0x400000UL)              /*!< GPIO0 iof_sel: pin22 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin23_Pos               (23UL)                    /*!< GPIO0 iof_sel: pin23 (Bit 23)                               */
#define GPIO0_iof_sel_pin23_Msk               (0x800000UL)              /*!< GPIO0 iof_sel: pin23 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin24_Pos               (24UL)                    /*!< GPIO0 iof_sel: pin24 (Bit 24)                               */
#define GPIO0_iof_sel_pin24_Msk               (0x1000000UL)             /*!< GPIO0 iof_sel: pin24 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin25_Pos               (25UL)                    /*!< GPIO0 iof_sel: pin25 (Bit 25)                               */
#define GPIO0_iof_sel_pin25_Msk               (0x2000000UL)             /*!< GPIO0 iof_sel: pin25 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin26_Pos               (26UL)                    /*!< GPIO0 iof_sel: pin26 (Bit 26)                               */
#define GPIO0_iof_sel_pin26_Msk               (0x4000000UL)             /*!< GPIO0 iof_sel: pin26 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin27_Pos               (27UL)                    /*!< GPIO0 iof_sel: pin27 (Bit 27)                               */
#define GPIO0_iof_sel_pin27_Msk               (0x8000000UL)             /*!< GPIO0 iof_sel: pin27 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin28_Pos               (28UL)                    /*!< GPIO0 iof_sel: pin28 (Bit 28)                               */
#define GPIO0_iof_sel_pin28_Msk               (0x10000000UL)            /*!< GPIO0 iof_sel: pin28 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin29_Pos               (29UL)                    /*!< GPIO0 iof_sel: pin29 (Bit 29)                               */
#define GPIO0_iof_sel_pin29_Msk               (0x20000000UL)            /*!< GPIO0 iof_sel: pin29 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin30_Pos               (30UL)                    /*!< GPIO0 iof_sel: pin30 (Bit 30)                               */
#define GPIO0_iof_sel_pin30_Msk               (0x40000000UL)            /*!< GPIO0 iof_sel: pin30 (Bitfield-Mask: 0x01)                  */
#define GPIO0_iof_sel_pin31_Pos               (31UL)                    /*!< GPIO0 iof_sel: pin31 (Bit 31)                               */
#define GPIO0_iof_sel_pin31_Msk               (0x80000000UL)            /*!< GPIO0 iof_sel: pin31 (Bitfield-Mask: 0x01)                  */

/* --------------------------------  GPIO0_out_xor  ------------------------------- */
#define GPIO0_out_xor_pin0_Pos                (0UL)                     /*!< GPIO0 out_xor: pin0 (Bit 0)                                 */
#define GPIO0_out_xor_pin0_Msk                (0x1UL)                   /*!< GPIO0 out_xor: pin0 (Bitfield-Mask: 0x01)                   */
#define GPIO0_out_xor_pin1_Pos                (1UL)                     /*!< GPIO0 out_xor: pin1 (Bit 1)                                 */
#define GPIO0_out_xor_pin1_Msk                (0x2UL)                   /*!< GPIO0 out_xor: pin1 (Bitfield-Mask: 0x01)                   */
#define GPIO0_out_xor_pin2_Pos                (2UL)                     /*!< GPIO0 out_xor: pin2 (Bit 2)                                 */
#define GPIO0_out_xor_pin2_Msk                (0x4UL)                   /*!< GPIO0 out_xor: pin2 (Bitfield-Mask: 0x01)                   */
#define GPIO0_out_xor_pin3_Pos                (3UL)                     /*!< GPIO0 out_xor: pin3 (Bit 3)                                 */
#define GPIO0_out_xor_pin3_Msk                (0x8UL)                   /*!< GPIO0 out_xor: pin3 (Bitfield-Mask: 0x01)                   */
#define GPIO0_out_xor_pin4_Pos                (4UL)                     /*!< GPIO0 out_xor: pin4 (Bit 4)                                 */
#define GPIO0_out_xor_pin4_Msk                (0x10UL)                  /*!< GPIO0 out_xor: pin4 (Bitfield-Mask: 0x01)                   */
#define GPIO0_out_xor_pin5_Pos                (5UL)                     /*!< GPIO0 out_xor: pin5 (Bit 5)                                 */
#define GPIO0_out_xor_pin5_Msk                (0x20UL)                  /*!< GPIO0 out_xor: pin5 (Bitfield-Mask: 0x01)                   */
#define GPIO0_out_xor_pin6_Pos                (6UL)                     /*!< GPIO0 out_xor: pin6 (Bit 6)                                 */
#define GPIO0_out_xor_pin6_Msk                (0x40UL)                  /*!< GPIO0 out_xor: pin6 (Bitfield-Mask: 0x01)                   */
#define GPIO0_out_xor_pin7_Pos                (7UL)                     /*!< GPIO0 out_xor: pin7 (Bit 7)                                 */
#define GPIO0_out_xor_pin7_Msk                (0x80UL)                  /*!< GPIO0 out_xor: pin7 (Bitfield-Mask: 0x01)                   */
#define GPIO0_out_xor_pin8_Pos                (8UL)                     /*!< GPIO0 out_xor: pin8 (Bit 8)                                 */
#define GPIO0_out_xor_pin8_Msk                (0x100UL)                 /*!< GPIO0 out_xor: pin8 (Bitfield-Mask: 0x01)                   */
#define GPIO0_out_xor_pin9_Pos                (9UL)                     /*!< GPIO0 out_xor: pin9 (Bit 9)                                 */
#define GPIO0_out_xor_pin9_Msk                (0x200UL)                 /*!< GPIO0 out_xor: pin9 (Bitfield-Mask: 0x01)                   */
#define GPIO0_out_xor_pin10_Pos               (10UL)                    /*!< GPIO0 out_xor: pin10 (Bit 10)                               */
#define GPIO0_out_xor_pin10_Msk               (0x400UL)                 /*!< GPIO0 out_xor: pin10 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin11_Pos               (11UL)                    /*!< GPIO0 out_xor: pin11 (Bit 11)                               */
#define GPIO0_out_xor_pin11_Msk               (0x800UL)                 /*!< GPIO0 out_xor: pin11 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin12_Pos               (12UL)                    /*!< GPIO0 out_xor: pin12 (Bit 12)                               */
#define GPIO0_out_xor_pin12_Msk               (0x1000UL)                /*!< GPIO0 out_xor: pin12 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin13_Pos               (13UL)                    /*!< GPIO0 out_xor: pin13 (Bit 13)                               */
#define GPIO0_out_xor_pin13_Msk               (0x2000UL)                /*!< GPIO0 out_xor: pin13 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin14_Pos               (14UL)                    /*!< GPIO0 out_xor: pin14 (Bit 14)                               */
#define GPIO0_out_xor_pin14_Msk               (0x4000UL)                /*!< GPIO0 out_xor: pin14 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin15_Pos               (15UL)                    /*!< GPIO0 out_xor: pin15 (Bit 15)                               */
#define GPIO0_out_xor_pin15_Msk               (0x8000UL)                /*!< GPIO0 out_xor: pin15 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin16_Pos               (16UL)                    /*!< GPIO0 out_xor: pin16 (Bit 16)                               */
#define GPIO0_out_xor_pin16_Msk               (0x10000UL)               /*!< GPIO0 out_xor: pin16 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin17_Pos               (17UL)                    /*!< GPIO0 out_xor: pin17 (Bit 17)                               */
#define GPIO0_out_xor_pin17_Msk               (0x20000UL)               /*!< GPIO0 out_xor: pin17 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin18_Pos               (18UL)                    /*!< GPIO0 out_xor: pin18 (Bit 18)                               */
#define GPIO0_out_xor_pin18_Msk               (0x40000UL)               /*!< GPIO0 out_xor: pin18 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin19_Pos               (19UL)                    /*!< GPIO0 out_xor: pin19 (Bit 19)                               */
#define GPIO0_out_xor_pin19_Msk               (0x80000UL)               /*!< GPIO0 out_xor: pin19 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin20_Pos               (20UL)                    /*!< GPIO0 out_xor: pin20 (Bit 20)                               */
#define GPIO0_out_xor_pin20_Msk               (0x100000UL)              /*!< GPIO0 out_xor: pin20 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin21_Pos               (21UL)                    /*!< GPIO0 out_xor: pin21 (Bit 21)                               */
#define GPIO0_out_xor_pin21_Msk               (0x200000UL)              /*!< GPIO0 out_xor: pin21 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin22_Pos               (22UL)                    /*!< GPIO0 out_xor: pin22 (Bit 22)                               */
#define GPIO0_out_xor_pin22_Msk               (0x400000UL)              /*!< GPIO0 out_xor: pin22 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin23_Pos               (23UL)                    /*!< GPIO0 out_xor: pin23 (Bit 23)                               */
#define GPIO0_out_xor_pin23_Msk               (0x800000UL)              /*!< GPIO0 out_xor: pin23 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin24_Pos               (24UL)                    /*!< GPIO0 out_xor: pin24 (Bit 24)                               */
#define GPIO0_out_xor_pin24_Msk               (0x1000000UL)             /*!< GPIO0 out_xor: pin24 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin25_Pos               (25UL)                    /*!< GPIO0 out_xor: pin25 (Bit 25)                               */
#define GPIO0_out_xor_pin25_Msk               (0x2000000UL)             /*!< GPIO0 out_xor: pin25 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin26_Pos               (26UL)                    /*!< GPIO0 out_xor: pin26 (Bit 26)                               */
#define GPIO0_out_xor_pin26_Msk               (0x4000000UL)             /*!< GPIO0 out_xor: pin26 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin27_Pos               (27UL)                    /*!< GPIO0 out_xor: pin27 (Bit 27)                               */
#define GPIO0_out_xor_pin27_Msk               (0x8000000UL)             /*!< GPIO0 out_xor: pin27 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin28_Pos               (28UL)                    /*!< GPIO0 out_xor: pin28 (Bit 28)                               */
#define GPIO0_out_xor_pin28_Msk               (0x10000000UL)            /*!< GPIO0 out_xor: pin28 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin29_Pos               (29UL)                    /*!< GPIO0 out_xor: pin29 (Bit 29)                               */
#define GPIO0_out_xor_pin29_Msk               (0x20000000UL)            /*!< GPIO0 out_xor: pin29 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin30_Pos               (30UL)                    /*!< GPIO0 out_xor: pin30 (Bit 30)                               */
#define GPIO0_out_xor_pin30_Msk               (0x40000000UL)            /*!< GPIO0 out_xor: pin30 (Bitfield-Mask: 0x01)                  */
#define GPIO0_out_xor_pin31_Pos               (31UL)                    /*!< GPIO0 out_xor: pin31 (Bit 31)                               */
#define GPIO0_out_xor_pin31_Msk               (0x80000000UL)            /*!< GPIO0 out_xor: pin31 (Bitfield-Mask: 0x01)                  */


/* ================================================================================ */
/* ================         struct 'UART0' Position & Mask         ================ */
/* ================================================================================ */


/* --------------------------------  UART0_txdata  -------------------------------- */
#define UART0_txdata_data_Pos                 (0UL)                     /*!< UART0 txdata: data (Bit 0)                                  */
#define UART0_txdata_data_Msk                 (0xffUL)                  /*!< UART0 txdata: data (Bitfield-Mask: 0xff)                    */
#define UART0_txdata_full_Pos                 (31UL)                    /*!< UART0 txdata: full (Bit 31)                                 */
#define UART0_txdata_full_Msk                 (0x80000000UL)            /*!< UART0 txdata: full (Bitfield-Mask: 0x01)                    */

/* --------------------------------  UART0_rxdata  -------------------------------- */
#define UART0_rxdata_data_Pos                 (0UL)                     /*!< UART0 rxdata: data (Bit 0)                                  */
#define UART0_rxdata_data_Msk                 (0xffUL)                  /*!< UART0 rxdata: data (Bitfield-Mask: 0xff)                    */
#define UART0_rxdata_empty_Pos                (31UL)                    /*!< UART0 rxdata: empty (Bit 31)                                */
#define UART0_rxdata_empty_Msk                (0x80000000UL)            /*!< UART0 rxdata: empty (Bitfield-Mask: 0x01)                   */

/* --------------------------------  UART0_txctrl  -------------------------------- */
#define UART0_txctrl_enable_Pos               (0UL)                     /*!< UART0 txctrl: enable (Bit 0)                                */
#define UART0_txctrl_enable_Msk               (0x1UL)                   /*!< UART0 txctrl: enable (Bitfield-Mask: 0x01)                  */
#define UART0_txctrl_nstop_Pos                (1UL)                     /*!< UART0 txctrl: nstop (Bit 1)                                 */
#define UART0_txctrl_nstop_Msk                (0x2UL)                   /*!< UART0 txctrl: nstop (Bitfield-Mask: 0x01)                   */
#define UART0_txctrl_counter_Pos              (16UL)                    /*!< UART0 txctrl: counter (Bit 16)                              */
#define UART0_txctrl_counter_Msk              (0x70000UL)               /*!< UART0 txctrl: counter (Bitfield-Mask: 0x07)                 */

/* --------------------------------  UART0_rxctrl  -------------------------------- */
#define UART0_rxctrl_enable_Pos               (0UL)                     /*!< UART0 rxctrl: enable (Bit 0)                                */
#define UART0_rxctrl_enable_Msk               (0x1UL)                   /*!< UART0 rxctrl: enable (Bitfield-Mask: 0x01)                  */
#define UART0_rxctrl_counter_Pos              (16UL)                    /*!< UART0 rxctrl: counter (Bit 16)                              */
#define UART0_rxctrl_counter_Msk              (0x70000UL)               /*!< UART0 rxctrl: counter (Bitfield-Mask: 0x07)                 */

/* ----------------------------------  UART0_ie  ---------------------------------- */
#define UART0_ie_txwm_Pos                     (0UL)                     /*!< UART0 ie: txwm (Bit 0)                                      */
#define UART0_ie_txwm_Msk                     (0x1UL)                   /*!< UART0 ie: txwm (Bitfield-Mask: 0x01)                        */
#define UART0_ie_rxwm_Pos                     (1UL)                     /*!< UART0 ie: rxwm (Bit 1)                                      */
#define UART0_ie_rxwm_Msk                     (0x2UL)                   /*!< UART0 ie: rxwm (Bitfield-Mask: 0x01)                        */

/* ----------------------------------  UART0_ip  ---------------------------------- */
#define UART0_ip_txwm_Pos                     (0UL)                     /*!< UART0 ip: txwm (Bit 0)                                      */
#define UART0_ip_txwm_Msk                     (0x1UL)                   /*!< UART0 ip: txwm (Bitfield-Mask: 0x01)                        */
#define UART0_ip_rxwm_Pos                     (1UL)                     /*!< UART0 ip: rxwm (Bit 1)                                      */
#define UART0_ip_rxwm_Msk                     (0x2UL)                   /*!< UART0 ip: rxwm (Bitfield-Mask: 0x01)                        */

/* ----------------------------------  UART0_div  --------------------------------- */
#define UART0_div_value_Pos                   (0UL)                     /*!< UART0 div: value (Bit 0)                                    */
#define UART0_div_value_Msk                   (0xffffUL)                /*!< UART0 div: value (Bitfield-Mask: 0xffff)                    */


/* ================================================================================ */
/* ================         struct 'QSPI0' Position & Mask         ================ */
/* ================================================================================ */


/* --------------------------------  QSPI0_sckdiv  -------------------------------- */
#define QSPI0_sckdiv_div_Pos                  (0UL)                     /*!< QSPI0 sckdiv: div (Bit 0)                                   */
#define QSPI0_sckdiv_div_Msk                  (0xfffUL)                 /*!< QSPI0 sckdiv: div (Bitfield-Mask: 0xfff)                    */

/* --------------------------------  QSPI0_sckmode  ------------------------------- */
#define QSPI0_sckmode_pha_Pos                 (0UL)                     /*!< QSPI0 sckmode: pha (Bit 0)                                  */
#define QSPI0_sckmode_pha_Msk                 (0x1UL)                   /*!< QSPI0 sckmode: pha (Bitfield-Mask: 0x01)                    */
#define QSPI0_sckmode_pol_Pos                 (1UL)                     /*!< QSPI0 sckmode: pol (Bit 1)                                  */
#define QSPI0_sckmode_pol_Msk                 (0x2UL)                   /*!< QSPI0 sckmode: pol (Bitfield-Mask: 0x01)                    */

/* --------------------------------  QSPI0_csmode  -------------------------------- */
#define QSPI0_csmode_mode_Pos                 (0UL)                     /*!< QSPI0 csmode: mode (Bit 0)                                  */
#define QSPI0_csmode_mode_Msk                 (0x3UL)                   /*!< QSPI0 csmode: mode (Bitfield-Mask: 0x03)                    */

/* --------------------------------  QSPI0_delay0  -------------------------------- */
#define QSPI0_delay0_cssck_Pos                (0UL)                     /*!< QSPI0 delay0: cssck (Bit 0)                                 */
#define QSPI0_delay0_cssck_Msk                (0xffUL)                  /*!< QSPI0 delay0: cssck (Bitfield-Mask: 0xff)                   */
#define QSPI0_delay0_sckcs_Pos                (16UL)                    /*!< QSPI0 delay0: sckcs (Bit 16)                                */
#define QSPI0_delay0_sckcs_Msk                (0xff0000UL)              /*!< QSPI0 delay0: sckcs (Bitfield-Mask: 0xff)                   */

/* --------------------------------  QSPI0_delay1  -------------------------------- */
#define QSPI0_delay1_intercs_Pos              (0UL)                     /*!< QSPI0 delay1: intercs (Bit 0)                               */
#define QSPI0_delay1_intercs_Msk              (0xffUL)                  /*!< QSPI0 delay1: intercs (Bitfield-Mask: 0xff)                 */
#define QSPI0_delay1_interxfr_Pos             (16UL)                    /*!< QSPI0 delay1: interxfr (Bit 16)                             */
#define QSPI0_delay1_interxfr_Msk             (0xff0000UL)              /*!< QSPI0 delay1: interxfr (Bitfield-Mask: 0xff)                */

/* ----------------------------------  QSPI0_fmt  --------------------------------- */
#define QSPI0_fmt_proto_Pos                   (0UL)                     /*!< QSPI0 fmt: proto (Bit 0)                                    */
#define QSPI0_fmt_proto_Msk                   (0x3UL)                   /*!< QSPI0 fmt: proto (Bitfield-Mask: 0x03)                      */
#define QSPI0_fmt_endian_Pos                  (2UL)                     /*!< QSPI0 fmt: endian (Bit 2)                                   */
#define QSPI0_fmt_endian_Msk                  (0x4UL)                   /*!< QSPI0 fmt: endian (Bitfield-Mask: 0x01)                     */
#define QSPI0_fmt_dir_Pos                     (3UL)                     /*!< QSPI0 fmt: dir (Bit 3)                                      */
#define QSPI0_fmt_dir_Msk                     (0x8UL)                   /*!< QSPI0 fmt: dir (Bitfield-Mask: 0x01)                        */
#define QSPI0_fmt_len_Pos                     (16UL)                    /*!< QSPI0 fmt: len (Bit 16)                                     */
#define QSPI0_fmt_len_Msk                     (0xf0000UL)               /*!< QSPI0 fmt: len (Bitfield-Mask: 0x0f)                        */

/* --------------------------------  QSPI0_txdata  -------------------------------- */
#define QSPI0_txdata_data_Pos                 (0UL)                     /*!< QSPI0 txdata: data (Bit 0)                                  */
#define QSPI0_txdata_data_Msk                 (0xffUL)                  /*!< QSPI0 txdata: data (Bitfield-Mask: 0xff)                    */
#define QSPI0_txdata_full_Pos                 (31UL)                    /*!< QSPI0 txdata: full (Bit 31)                                 */
#define QSPI0_txdata_full_Msk                 (0x80000000UL)            /*!< QSPI0 txdata: full (Bitfield-Mask: 0x01)                    */

/* --------------------------------  QSPI0_rxdata  -------------------------------- */
#define QSPI0_rxdata_data_Pos                 (0UL)                     /*!< QSPI0 rxdata: data (Bit 0)                                  */
#define QSPI0_rxdata_data_Msk                 (0xffUL)                  /*!< QSPI0 rxdata: data (Bitfield-Mask: 0xff)                    */
#define QSPI0_rxdata_empty_Pos                (31UL)                    /*!< QSPI0 rxdata: empty (Bit 31)                                */
#define QSPI0_rxdata_empty_Msk                (0x80000000UL)            /*!< QSPI0 rxdata: empty (Bitfield-Mask: 0x01)                   */

/* --------------------------------  QSPI0_txmark  -------------------------------- */
#define QSPI0_txmark_txmark_Pos               (0UL)                     /*!< QSPI0 txmark: txmark (Bit 0)                                */
#define QSPI0_txmark_txmark_Msk               (0x7UL)                   /*!< QSPI0 txmark: txmark (Bitfield-Mask: 0x07)                  */

/* --------------------------------  QSPI0_rxmark  -------------------------------- */
#define QSPI0_rxmark_rxmark_Pos               (0UL)                     /*!< QSPI0 rxmark: rxmark (Bit 0)                                */
#define QSPI0_rxmark_rxmark_Msk               (0x7UL)                   /*!< QSPI0 rxmark: rxmark (Bitfield-Mask: 0x07)                  */

/* ---------------------------------  QSPI0_fctrl  -------------------------------- */
#define QSPI0_fctrl_en_Pos                    (0UL)                     /*!< QSPI0 fctrl: en (Bit 0)                                     */
#define QSPI0_fctrl_en_Msk                    (0x1UL)                   /*!< QSPI0 fctrl: en (Bitfield-Mask: 0x01)                       */

/* ---------------------------------  QSPI0_ffmt  --------------------------------- */
#define QSPI0_ffmt_cmd_en_Pos                 (0UL)                     /*!< QSPI0 ffmt: cmd_en (Bit 0)                                  */
#define QSPI0_ffmt_cmd_en_Msk                 (0x1UL)                   /*!< QSPI0 ffmt: cmd_en (Bitfield-Mask: 0x01)                    */
#define QSPI0_ffmt_addr_len_Pos               (1UL)                     /*!< QSPI0 ffmt: addr_len (Bit 1)                                */
#define QSPI0_ffmt_addr_len_Msk               (0xeUL)                   /*!< QSPI0 ffmt: addr_len (Bitfield-Mask: 0x07)                  */
#define QSPI0_ffmt_pad_cnt_Pos                (4UL)                     /*!< QSPI0 ffmt: pad_cnt (Bit 4)                                 */
#define QSPI0_ffmt_pad_cnt_Msk                (0xf0UL)                  /*!< QSPI0 ffmt: pad_cnt (Bitfield-Mask: 0x0f)                   */
#define QSPI0_ffmt_cmd_proto_Pos              (8UL)                     /*!< QSPI0 ffmt: cmd_proto (Bit 8)                               */
#define QSPI0_ffmt_cmd_proto_Msk              (0x300UL)                 /*!< QSPI0 ffmt: cmd_proto (Bitfield-Mask: 0x03)                 */
#define QSPI0_ffmt_addr_proto_Pos             (10UL)                    /*!< QSPI0 ffmt: addr_proto (Bit 10)                             */
#define QSPI0_ffmt_addr_proto_Msk             (0xc00UL)                 /*!< QSPI0 ffmt: addr_proto (Bitfield-Mask: 0x03)                */
#define QSPI0_ffmt_data_proto_Pos             (12UL)                    /*!< QSPI0 ffmt: data_proto (Bit 12)                             */
#define QSPI0_ffmt_data_proto_Msk             (0x3000UL)                /*!< QSPI0 ffmt: data_proto (Bitfield-Mask: 0x03)                */
#define QSPI0_ffmt_cmd_code_Pos               (16UL)                    /*!< QSPI0 ffmt: cmd_code (Bit 16)                               */
#define QSPI0_ffmt_cmd_code_Msk               (0xff0000UL)              /*!< QSPI0 ffmt: cmd_code (Bitfield-Mask: 0xff)                  */
#define QSPI0_ffmt_pad_code_Pos               (24UL)                    /*!< QSPI0 ffmt: pad_code (Bit 24)                               */
#define QSPI0_ffmt_pad_code_Msk               (0xff000000UL)            /*!< QSPI0 ffmt: pad_code (Bitfield-Mask: 0xff)                  */

/* ----------------------------------  QSPI0_ie  ---------------------------------- */
#define QSPI0_ie_txwm_Pos                     (0UL)                     /*!< QSPI0 ie: txwm (Bit 0)                                      */
#define QSPI0_ie_txwm_Msk                     (0x1UL)                   /*!< QSPI0 ie: txwm (Bitfield-Mask: 0x01)                        */
#define QSPI0_ie_rxwm_Pos                     (1UL)                     /*!< QSPI0 ie: rxwm (Bit 1)                                      */
#define QSPI0_ie_rxwm_Msk                     (0x2UL)                   /*!< QSPI0 ie: rxwm (Bitfield-Mask: 0x01)                        */

/* ----------------------------------  QSPI0_ip  ---------------------------------- */
#define QSPI0_ip_txwm_Pos                     (0UL)                     /*!< QSPI0 ip: txwm (Bit 0)                                      */
#define QSPI0_ip_txwm_Msk                     (0x1UL)                   /*!< QSPI0 ip: txwm (Bitfield-Mask: 0x01)                        */
#define QSPI0_ip_rxwm_Pos                     (1UL)                     /*!< QSPI0 ip: rxwm (Bit 1)                                      */
#define QSPI0_ip_rxwm_Msk                     (0x2UL)                   /*!< QSPI0 ip: rxwm (Bitfield-Mask: 0x01)                        */


/* ================================================================================ */
/* ================          struct 'PWM0' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  PWM0_cfg  ---------------------------------- */
#define PWM0_cfg_scale_Pos                    (0UL)                     /*!< PWM0 cfg: scale (Bit 0)                                     */
#define PWM0_cfg_scale_Msk                    (0xfUL)                   /*!< PWM0 cfg: scale (Bitfield-Mask: 0x0f)                       */
#define PWM0_cfg_sticky_Pos                   (8UL)                     /*!< PWM0 cfg: sticky (Bit 8)                                    */
#define PWM0_cfg_sticky_Msk                   (0x100UL)                 /*!< PWM0 cfg: sticky (Bitfield-Mask: 0x01)                      */
#define PWM0_cfg_zerocmp_Pos                  (9UL)                     /*!< PWM0 cfg: zerocmp (Bit 9)                                   */
#define PWM0_cfg_zerocmp_Msk                  (0x200UL)                 /*!< PWM0 cfg: zerocmp (Bitfield-Mask: 0x01)                     */
#define PWM0_cfg_deglitch_Pos                 (10UL)                    /*!< PWM0 cfg: deglitch (Bit 10)                                 */
#define PWM0_cfg_deglitch_Msk                 (0x400UL)                 /*!< PWM0 cfg: deglitch (Bitfield-Mask: 0x01)                    */
#define PWM0_cfg_enalways_Pos                 (12UL)                    /*!< PWM0 cfg: enalways (Bit 12)                                 */
#define PWM0_cfg_enalways_Msk                 (0x1000UL)                /*!< PWM0 cfg: enalways (Bitfield-Mask: 0x01)                    */
#define PWM0_cfg_enoneshot_Pos                (13UL)                    /*!< PWM0 cfg: enoneshot (Bit 13)                                */
#define PWM0_cfg_enoneshot_Msk                (0x2000UL)                /*!< PWM0 cfg: enoneshot (Bitfield-Mask: 0x01)                   */
#define PWM0_cfg_cmp0center_Pos               (16UL)                    /*!< PWM0 cfg: cmp0center (Bit 16)                               */
#define PWM0_cfg_cmp0center_Msk               (0x10000UL)               /*!< PWM0 cfg: cmp0center (Bitfield-Mask: 0x01)                  */
#define PWM0_cfg_cmp1center_Pos               (17UL)                    /*!< PWM0 cfg: cmp1center (Bit 17)                               */
#define PWM0_cfg_cmp1center_Msk               (0x20000UL)               /*!< PWM0 cfg: cmp1center (Bitfield-Mask: 0x01)                  */
#define PWM0_cfg_cmp2center_Pos               (18UL)                    /*!< PWM0 cfg: cmp2center (Bit 18)                               */
#define PWM0_cfg_cmp2center_Msk               (0x40000UL)               /*!< PWM0 cfg: cmp2center (Bitfield-Mask: 0x01)                  */
#define PWM0_cfg_cmp3center_Pos               (19UL)                    /*!< PWM0 cfg: cmp3center (Bit 19)                               */
#define PWM0_cfg_cmp3center_Msk               (0x80000UL)               /*!< PWM0 cfg: cmp3center (Bitfield-Mask: 0x01)                  */
#define PWM0_cfg_cmp0gang_Pos                 (24UL)                    /*!< PWM0 cfg: cmp0gang (Bit 24)                                 */
#define PWM0_cfg_cmp0gang_Msk                 (0x1000000UL)             /*!< PWM0 cfg: cmp0gang (Bitfield-Mask: 0x01)                    */
#define PWM0_cfg_cmp1gang_Pos                 (25UL)                    /*!< PWM0 cfg: cmp1gang (Bit 25)                                 */
#define PWM0_cfg_cmp1gang_Msk                 (0x2000000UL)             /*!< PWM0 cfg: cmp1gang (Bitfield-Mask: 0x01)                    */
#define PWM0_cfg_cmp2gang_Pos                 (26UL)                    /*!< PWM0 cfg: cmp2gang (Bit 26)                                 */
#define PWM0_cfg_cmp2gang_Msk                 (0xfc000000UL)            /*!< PWM0 cfg: cmp2gang (Bitfield-Mask: 0x3f)                    */
#define PWM0_cfg_cmp3gang_Pos                 (27UL)                    /*!< PWM0 cfg: cmp3gang (Bit 27)                                 */
#define PWM0_cfg_cmp3gang_Msk                 (0x8000000UL)             /*!< PWM0 cfg: cmp3gang (Bitfield-Mask: 0x01)                    */
#define PWM0_cfg_cmp0ip_Pos                   (28UL)                    /*!< PWM0 cfg: cmp0ip (Bit 28)                                   */
#define PWM0_cfg_cmp0ip_Msk                   (0x10000000UL)            /*!< PWM0 cfg: cmp0ip (Bitfield-Mask: 0x01)                      */
#define PWM0_cfg_cmp1ip_Pos                   (29UL)                    /*!< PWM0 cfg: cmp1ip (Bit 29)                                   */
#define PWM0_cfg_cmp1ip_Msk                   (0x20000000UL)            /*!< PWM0 cfg: cmp1ip (Bitfield-Mask: 0x01)                      */
#define PWM0_cfg_cmp2ip_Pos                   (30UL)                    /*!< PWM0 cfg: cmp2ip (Bit 30)                                   */
#define PWM0_cfg_cmp2ip_Msk                   (0x40000000UL)            /*!< PWM0 cfg: cmp2ip (Bitfield-Mask: 0x01)                      */
#define PWM0_cfg_cmp3ip_Pos                   (31UL)                    /*!< PWM0 cfg: cmp3ip (Bit 31)                                   */
#define PWM0_cfg_cmp3ip_Msk                   (0x80000000UL)            /*!< PWM0 cfg: cmp3ip (Bitfield-Mask: 0x01)                      */

/* ----------------------------------  PWM0_cmp0  --------------------------------- */
#define PWM0_cmp0_value_Pos                   (0UL)                     /*!< PWM0 cmp0: value (Bit 0)                                    */
#define PWM0_cmp0_value_Msk                   (0xffffUL)                /*!< PWM0 cmp0: value (Bitfield-Mask: 0xffff)                    */

/* ----------------------------------  PWM0_cmp1  --------------------------------- */
#define PWM0_cmp1_value_Pos                   (0UL)                     /*!< PWM0 cmp1: value (Bit 0)                                    */
#define PWM0_cmp1_value_Msk                   (0xffffUL)                /*!< PWM0 cmp1: value (Bitfield-Mask: 0xffff)                    */

/* ----------------------------------  PWM0_cmp2  --------------------------------- */
#define PWM0_cmp2_value_Pos                   (0UL)                     /*!< PWM0 cmp2: value (Bit 0)                                    */
#define PWM0_cmp2_value_Msk                   (0xffffUL)                /*!< PWM0 cmp2: value (Bitfield-Mask: 0xffff)                    */

/* ----------------------------------  PWM0_cmp3  --------------------------------- */
#define PWM0_cmp3_value_Pos                   (0UL)                     /*!< PWM0 cmp3: value (Bit 0)                                    */
#define PWM0_cmp3_value_Msk                   (0xffffUL)                /*!< PWM0 cmp3: value (Bitfield-Mask: 0xffff)                    */


/* ================================================================================ */
/* ================          struct 'I2C0' Position & Mask         ================ */
/* ================================================================================ */


/* --------------------------------  I2C0_prer_lo  -------------------------------- */
#define I2C0_prer_lo_value_Pos                (0UL)                     /*!< I2C0 prer_lo: value (Bit 0)                                 */
#define I2C0_prer_lo_value_Msk                (0xffUL)                  /*!< I2C0 prer_lo: value (Bitfield-Mask: 0xff)                   */

/* --------------------------------  I2C0_prer_hi  -------------------------------- */
#define I2C0_prer_hi_value_Pos                (0UL)                     /*!< I2C0 prer_hi: value (Bit 0)                                 */
#define I2C0_prer_hi_value_Msk                (0xffUL)                  /*!< I2C0 prer_hi: value (Bitfield-Mask: 0xff)                   */

/* ----------------------------------  I2C0_ctr  ---------------------------------- */
#define I2C0_ctr_ien_Pos                      (6UL)                     /*!< I2C0 ctr: ien (Bit 6)                                       */
#define I2C0_ctr_ien_Msk                      (0x40UL)                  /*!< I2C0 ctr: ien (Bitfield-Mask: 0x01)                         */
#define I2C0_ctr_en_Pos                       (7UL)                     /*!< I2C0 ctr: en (Bit 7)                                        */
#define I2C0_ctr_en_Msk                       (0x80UL)                  /*!< I2C0 ctr: en (Bitfield-Mask: 0x01)                          */

/* --------------------------------  I2C0_txr_rxr  -------------------------------- */
#define I2C0_txr_rxr_data_Pos                 (0UL)                     /*!< I2C0 txr_rxr: data (Bit 0)                                  */
#define I2C0_txr_rxr_data_Msk                 (0xffUL)                  /*!< I2C0 txr_rxr: data (Bitfield-Mask: 0xff)                    */

/* -----------------------------------  I2C0_cr  ---------------------------------- */
#define I2C0_cr_iack_Pos                      (0UL)                     /*!< I2C0 cr: iack (Bit 0)                                       */
#define I2C0_cr_iack_Msk                      (0x1UL)                   /*!< I2C0 cr: iack (Bitfield-Mask: 0x01)                         */
#define I2C0_cr_ack_Pos                       (3UL)                     /*!< I2C0 cr: ack (Bit 3)                                        */
#define I2C0_cr_ack_Msk                       (0x8UL)                   /*!< I2C0 cr: ack (Bitfield-Mask: 0x01)                          */
#define I2C0_cr_wr_Pos                        (4UL)                     /*!< I2C0 cr: wr (Bit 4)                                         */
#define I2C0_cr_wr_Msk                        (0x10UL)                  /*!< I2C0 cr: wr (Bitfield-Mask: 0x01)                           */
#define I2C0_cr_rd_Pos                        (5UL)                     /*!< I2C0 cr: rd (Bit 5)                                         */
#define I2C0_cr_rd_Msk                        (0x20UL)                  /*!< I2C0 cr: rd (Bitfield-Mask: 0x01)                           */
#define I2C0_cr_sto_Pos                       (6UL)                     /*!< I2C0 cr: sto (Bit 6)                                        */
#define I2C0_cr_sto_Msk                       (0x40UL)                  /*!< I2C0 cr: sto (Bitfield-Mask: 0x01)                          */
#define I2C0_cr_sta_Pos                       (7UL)                     /*!< I2C0 cr: sta (Bit 7)                                        */
#define I2C0_cr_sta_Msk                       (0x80UL)                  /*!< I2C0 cr: sta (Bitfield-Mask: 0x01)                          */

/* -----------------------------------  I2C0_sr  ---------------------------------- */
#define I2C0_sr_if_Pos                        (0UL)                     /*!< I2C0 sr: if (Bit 0)                                         */
#define I2C0_sr_if_Msk                        (0x1UL)                   /*!< I2C0 sr: if (Bitfield-Mask: 0x01)                           */
#define I2C0_sr_tip_Pos                       (1UL)                     /*!< I2C0 sr: tip (Bit 1)                                        */
#define I2C0_sr_tip_Msk                       (0x2UL)                   /*!< I2C0 sr: tip (Bitfield-Mask: 0x01)                          */
#define I2C0_sr_al_Pos                        (5UL)                     /*!< I2C0 sr: al (Bit 5)                                         */
#define I2C0_sr_al_Msk                        (0x20UL)                  /*!< I2C0 sr: al (Bitfield-Mask: 0x01)                           */
#define I2C0_sr_busy_Pos                      (6UL)                     /*!< I2C0 sr: busy (Bit 6)                                       */
#define I2C0_sr_busy_Msk                      (0x40UL)                  /*!< I2C0 sr: busy (Bitfield-Mask: 0x01)                         */
#define I2C0_sr_rx_ack_Pos                    (7UL)                     /*!< I2C0 sr: rx_ack (Bit 7)                                     */
#define I2C0_sr_rx_ack_Msk                    (0x80UL)                  /*!< I2C0 sr: rx_ack (Bitfield-Mask: 0x01)                       */


/* ================================================================================ */
/* ================         struct 'UART1' Position & Mask         ================ */
/* ================================================================================ */


/* --------------------------------  UART1_txdata  -------------------------------- */
#define UART1_txdata_data_Pos                 (0UL)                     /*!< UART1 txdata: data (Bit 0)                                  */
#define UART1_txdata_data_Msk                 (0xffUL)                  /*!< UART1 txdata: data (Bitfield-Mask: 0xff)                    */
#define UART1_txdata_full_Pos                 (31UL)                    /*!< UART1 txdata: full (Bit 31)                                 */
#define UART1_txdata_full_Msk                 (0x80000000UL)            /*!< UART1 txdata: full (Bitfield-Mask: 0x01)                    */

/* --------------------------------  UART1_rxdata  -------------------------------- */
#define UART1_rxdata_data_Pos                 (0UL)                     /*!< UART1 rxdata: data (Bit 0)                                  */
#define UART1_rxdata_data_Msk                 (0xffUL)                  /*!< UART1 rxdata: data (Bitfield-Mask: 0xff)                    */
#define UART1_rxdata_empty_Pos                (31UL)                    /*!< UART1 rxdata: empty (Bit 31)                                */
#define UART1_rxdata_empty_Msk                (0x80000000UL)            /*!< UART1 rxdata: empty (Bitfield-Mask: 0x01)                   */

/* --------------------------------  UART1_txctrl  -------------------------------- */
#define UART1_txctrl_enable_Pos               (0UL)                     /*!< UART1 txctrl: enable (Bit 0)                                */
#define UART1_txctrl_enable_Msk               (0x1UL)                   /*!< UART1 txctrl: enable (Bitfield-Mask: 0x01)                  */
#define UART1_txctrl_nstop_Pos                (1UL)                     /*!< UART1 txctrl: nstop (Bit 1)                                 */
#define UART1_txctrl_nstop_Msk                (0x2UL)                   /*!< UART1 txctrl: nstop (Bitfield-Mask: 0x01)                   */
#define UART1_txctrl_counter_Pos              (16UL)                    /*!< UART1 txctrl: counter (Bit 16)                              */
#define UART1_txctrl_counter_Msk              (0x70000UL)               /*!< UART1 txctrl: counter (Bitfield-Mask: 0x07)                 */

/* --------------------------------  UART1_rxctrl  -------------------------------- */
#define UART1_rxctrl_enable_Pos               (0UL)                     /*!< UART1 rxctrl: enable (Bit 0)                                */
#define UART1_rxctrl_enable_Msk               (0x1UL)                   /*!< UART1 rxctrl: enable (Bitfield-Mask: 0x01)                  */
#define UART1_rxctrl_counter_Pos              (16UL)                    /*!< UART1 rxctrl: counter (Bit 16)                              */
#define UART1_rxctrl_counter_Msk              (0x70000UL)               /*!< UART1 rxctrl: counter (Bitfield-Mask: 0x07)                 */

/* ----------------------------------  UART1_ie  ---------------------------------- */
#define UART1_ie_txwm_Pos                     (0UL)                     /*!< UART1 ie: txwm (Bit 0)                                      */
#define UART1_ie_txwm_Msk                     (0x1UL)                   /*!< UART1 ie: txwm (Bitfield-Mask: 0x01)                        */
#define UART1_ie_rxwm_Pos                     (1UL)                     /*!< UART1 ie: rxwm (Bit 1)                                      */
#define UART1_ie_rxwm_Msk                     (0x2UL)                   /*!< UART1 ie: rxwm (Bitfield-Mask: 0x01)                        */

/* ----------------------------------  UART1_ip  ---------------------------------- */
#define UART1_ip_txwm_Pos                     (0UL)                     /*!< UART1 ip: txwm (Bit 0)                                      */
#define UART1_ip_txwm_Msk                     (0x1UL)                   /*!< UART1 ip: txwm (Bitfield-Mask: 0x01)                        */
#define UART1_ip_rxwm_Pos                     (1UL)                     /*!< UART1 ip: rxwm (Bit 1)                                      */
#define UART1_ip_rxwm_Msk                     (0x2UL)                   /*!< UART1 ip: rxwm (Bitfield-Mask: 0x01)                        */

/* ----------------------------------  UART1_div  --------------------------------- */
#define UART1_div_value_Pos                   (0UL)                     /*!< UART1 div: value (Bit 0)                                    */
#define UART1_div_value_Msk                   (0xffffUL)                /*!< UART1 div: value (Bitfield-Mask: 0xffff)                    */


/* ================================================================================ */
/* ================         struct 'QSPI1' Position & Mask         ================ */
/* ================================================================================ */


/* --------------------------------  QSPI1_sckdiv  -------------------------------- */
#define QSPI1_sckdiv_div_Pos                  (0UL)                     /*!< QSPI1 sckdiv: div (Bit 0)                                   */
#define QSPI1_sckdiv_div_Msk                  (0xfffUL)                 /*!< QSPI1 sckdiv: div (Bitfield-Mask: 0xfff)                    */

/* --------------------------------  QSPI1_sckmode  ------------------------------- */
#define QSPI1_sckmode_pha_Pos                 (0UL)                     /*!< QSPI1 sckmode: pha (Bit 0)                                  */
#define QSPI1_sckmode_pha_Msk                 (0x1UL)                   /*!< QSPI1 sckmode: pha (Bitfield-Mask: 0x01)                    */
#define QSPI1_sckmode_pol_Pos                 (1UL)                     /*!< QSPI1 sckmode: pol (Bit 1)                                  */
#define QSPI1_sckmode_pol_Msk                 (0x2UL)                   /*!< QSPI1 sckmode: pol (Bitfield-Mask: 0x01)                    */

/* --------------------------------  QSPI1_csmode  -------------------------------- */
#define QSPI1_csmode_mode_Pos                 (0UL)                     /*!< QSPI1 csmode: mode (Bit 0)                                  */
#define QSPI1_csmode_mode_Msk                 (0x3UL)                   /*!< QSPI1 csmode: mode (Bitfield-Mask: 0x03)                    */

/* --------------------------------  QSPI1_delay0  -------------------------------- */
#define QSPI1_delay0_cssck_Pos                (0UL)                     /*!< QSPI1 delay0: cssck (Bit 0)                                 */
#define QSPI1_delay0_cssck_Msk                (0xffUL)                  /*!< QSPI1 delay0: cssck (Bitfield-Mask: 0xff)                   */
#define QSPI1_delay0_sckcs_Pos                (16UL)                    /*!< QSPI1 delay0: sckcs (Bit 16)                                */
#define QSPI1_delay0_sckcs_Msk                (0xff0000UL)              /*!< QSPI1 delay0: sckcs (Bitfield-Mask: 0xff)                   */

/* --------------------------------  QSPI1_delay1  -------------------------------- */
#define QSPI1_delay1_intercs_Pos              (0UL)                     /*!< QSPI1 delay1: intercs (Bit 0)                               */
#define QSPI1_delay1_intercs_Msk              (0xffUL)                  /*!< QSPI1 delay1: intercs (Bitfield-Mask: 0xff)                 */
#define QSPI1_delay1_interxfr_Pos             (16UL)                    /*!< QSPI1 delay1: interxfr (Bit 16)                             */
#define QSPI1_delay1_interxfr_Msk             (0xff0000UL)              /*!< QSPI1 delay1: interxfr (Bitfield-Mask: 0xff)                */

/* ----------------------------------  QSPI1_fmt  --------------------------------- */
#define QSPI1_fmt_proto_Pos                   (0UL)                     /*!< QSPI1 fmt: proto (Bit 0)                                    */
#define QSPI1_fmt_proto_Msk                   (0x3UL)                   /*!< QSPI1 fmt: proto (Bitfield-Mask: 0x03)                      */
#define QSPI1_fmt_endian_Pos                  (2UL)                     /*!< QSPI1 fmt: endian (Bit 2)                                   */
#define QSPI1_fmt_endian_Msk                  (0x4UL)                   /*!< QSPI1 fmt: endian (Bitfield-Mask: 0x01)                     */
#define QSPI1_fmt_dir_Pos                     (3UL)                     /*!< QSPI1 fmt: dir (Bit 3)                                      */
#define QSPI1_fmt_dir_Msk                     (0x8UL)                   /*!< QSPI1 fmt: dir (Bitfield-Mask: 0x01)                        */
#define QSPI1_fmt_len_Pos                     (16UL)                    /*!< QSPI1 fmt: len (Bit 16)                                     */
#define QSPI1_fmt_len_Msk                     (0xf0000UL)               /*!< QSPI1 fmt: len (Bitfield-Mask: 0x0f)                        */

/* --------------------------------  QSPI1_txdata  -------------------------------- */
#define QSPI1_txdata_data_Pos                 (0UL)                     /*!< QSPI1 txdata: data (Bit 0)                                  */
#define QSPI1_txdata_data_Msk                 (0xffUL)                  /*!< QSPI1 txdata: data (Bitfield-Mask: 0xff)                    */
#define QSPI1_txdata_full_Pos                 (31UL)                    /*!< QSPI1 txdata: full (Bit 31)                                 */
#define QSPI1_txdata_full_Msk                 (0x80000000UL)            /*!< QSPI1 txdata: full (Bitfield-Mask: 0x01)                    */

/* --------------------------------  QSPI1_rxdata  -------------------------------- */
#define QSPI1_rxdata_data_Pos                 (0UL)                     /*!< QSPI1 rxdata: data (Bit 0)                                  */
#define QSPI1_rxdata_data_Msk                 (0xffUL)                  /*!< QSPI1 rxdata: data (Bitfield-Mask: 0xff)                    */
#define QSPI1_rxdata_empty_Pos                (31UL)                    /*!< QSPI1 rxdata: empty (Bit 31)                                */
#define QSPI1_rxdata_empty_Msk                (0x80000000UL)            /*!< QSPI1 rxdata: empty (Bitfield-Mask: 0x01)                   */

/* --------------------------------  QSPI1_txmark  -------------------------------- */
#define QSPI1_txmark_txmark_Pos               (0UL)                     /*!< QSPI1 txmark: txmark (Bit 0)                                */
#define QSPI1_txmark_txmark_Msk               (0x7UL)                   /*!< QSPI1 txmark: txmark (Bitfield-Mask: 0x07)                  */

/* --------------------------------  QSPI1_rxmark  -------------------------------- */
#define QSPI1_rxmark_rxmark_Pos               (0UL)                     /*!< QSPI1 rxmark: rxmark (Bit 0)                                */
#define QSPI1_rxmark_rxmark_Msk               (0x7UL)                   /*!< QSPI1 rxmark: rxmark (Bitfield-Mask: 0x07)                  */

/* ---------------------------------  QSPI1_fctrl  -------------------------------- */
#define QSPI1_fctrl_en_Pos                    (0UL)                     /*!< QSPI1 fctrl: en (Bit 0)                                     */
#define QSPI1_fctrl_en_Msk                    (0x1UL)                   /*!< QSPI1 fctrl: en (Bitfield-Mask: 0x01)                       */

/* ---------------------------------  QSPI1_ffmt  --------------------------------- */
#define QSPI1_ffmt_cmd_en_Pos                 (0UL)                     /*!< QSPI1 ffmt: cmd_en (Bit 0)                                  */
#define QSPI1_ffmt_cmd_en_Msk                 (0x1UL)                   /*!< QSPI1 ffmt: cmd_en (Bitfield-Mask: 0x01)                    */
#define QSPI1_ffmt_addr_len_Pos               (1UL)                     /*!< QSPI1 ffmt: addr_len (Bit 1)                                */
#define QSPI1_ffmt_addr_len_Msk               (0xeUL)                   /*!< QSPI1 ffmt: addr_len (Bitfield-Mask: 0x07)                  */
#define QSPI1_ffmt_pad_cnt_Pos                (4UL)                     /*!< QSPI1 ffmt: pad_cnt (Bit 4)                                 */
#define QSPI1_ffmt_pad_cnt_Msk                (0xf0UL)                  /*!< QSPI1 ffmt: pad_cnt (Bitfield-Mask: 0x0f)                   */
#define QSPI1_ffmt_cmd_proto_Pos              (8UL)                     /*!< QSPI1 ffmt: cmd_proto (Bit 8)                               */
#define QSPI1_ffmt_cmd_proto_Msk              (0x300UL)                 /*!< QSPI1 ffmt: cmd_proto (Bitfield-Mask: 0x03)                 */
#define QSPI1_ffmt_addr_proto_Pos             (10UL)                    /*!< QSPI1 ffmt: addr_proto (Bit 10)                             */
#define QSPI1_ffmt_addr_proto_Msk             (0xc00UL)                 /*!< QSPI1 ffmt: addr_proto (Bitfield-Mask: 0x03)                */
#define QSPI1_ffmt_data_proto_Pos             (12UL)                    /*!< QSPI1 ffmt: data_proto (Bit 12)                             */
#define QSPI1_ffmt_data_proto_Msk             (0x3000UL)                /*!< QSPI1 ffmt: data_proto (Bitfield-Mask: 0x03)                */
#define QSPI1_ffmt_cmd_code_Pos               (16UL)                    /*!< QSPI1 ffmt: cmd_code (Bit 16)                               */
#define QSPI1_ffmt_cmd_code_Msk               (0xff0000UL)              /*!< QSPI1 ffmt: cmd_code (Bitfield-Mask: 0xff)                  */
#define QSPI1_ffmt_pad_code_Pos               (24UL)                    /*!< QSPI1 ffmt: pad_code (Bit 24)                               */
#define QSPI1_ffmt_pad_code_Msk               (0xff000000UL)            /*!< QSPI1 ffmt: pad_code (Bitfield-Mask: 0xff)                  */

/* ----------------------------------  QSPI1_ie  ---------------------------------- */
#define QSPI1_ie_txwm_Pos                     (0UL)                     /*!< QSPI1 ie: txwm (Bit 0)                                      */
#define QSPI1_ie_txwm_Msk                     (0x1UL)                   /*!< QSPI1 ie: txwm (Bitfield-Mask: 0x01)                        */
#define QSPI1_ie_rxwm_Pos                     (1UL)                     /*!< QSPI1 ie: rxwm (Bit 1)                                      */
#define QSPI1_ie_rxwm_Msk                     (0x2UL)                   /*!< QSPI1 ie: rxwm (Bitfield-Mask: 0x01)                        */

/* ----------------------------------  QSPI1_ip  ---------------------------------- */
#define QSPI1_ip_txwm_Pos                     (0UL)                     /*!< QSPI1 ip: txwm (Bit 0)                                      */
#define QSPI1_ip_txwm_Msk                     (0x1UL)                   /*!< QSPI1 ip: txwm (Bitfield-Mask: 0x01)                        */
#define QSPI1_ip_rxwm_Pos                     (1UL)                     /*!< QSPI1 ip: rxwm (Bit 1)                                      */
#define QSPI1_ip_rxwm_Msk                     (0x2UL)                   /*!< QSPI1 ip: rxwm (Bitfield-Mask: 0x01)                        */


/* ================================================================================ */
/* ================          struct 'PWM1' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  PWM1_cfg  ---------------------------------- */
#define PWM1_cfg_scale_Pos                    (0UL)                     /*!< PWM1 cfg: scale (Bit 0)                                     */
#define PWM1_cfg_scale_Msk                    (0xfUL)                   /*!< PWM1 cfg: scale (Bitfield-Mask: 0x0f)                       */
#define PWM1_cfg_sticky_Pos                   (8UL)                     /*!< PWM1 cfg: sticky (Bit 8)                                    */
#define PWM1_cfg_sticky_Msk                   (0x100UL)                 /*!< PWM1 cfg: sticky (Bitfield-Mask: 0x01)                      */
#define PWM1_cfg_zerocmp_Pos                  (9UL)                     /*!< PWM1 cfg: zerocmp (Bit 9)                                   */
#define PWM1_cfg_zerocmp_Msk                  (0x200UL)                 /*!< PWM1 cfg: zerocmp (Bitfield-Mask: 0x01)                     */
#define PWM1_cfg_deglitch_Pos                 (10UL)                    /*!< PWM1 cfg: deglitch (Bit 10)                                 */
#define PWM1_cfg_deglitch_Msk                 (0x400UL)                 /*!< PWM1 cfg: deglitch (Bitfield-Mask: 0x01)                    */
#define PWM1_cfg_enalways_Pos                 (12UL)                    /*!< PWM1 cfg: enalways (Bit 12)                                 */
#define PWM1_cfg_enalways_Msk                 (0x1000UL)                /*!< PWM1 cfg: enalways (Bitfield-Mask: 0x01)                    */
#define PWM1_cfg_enoneshot_Pos                (13UL)                    /*!< PWM1 cfg: enoneshot (Bit 13)                                */
#define PWM1_cfg_enoneshot_Msk                (0x2000UL)                /*!< PWM1 cfg: enoneshot (Bitfield-Mask: 0x01)                   */
#define PWM1_cfg_cmp0center_Pos               (16UL)                    /*!< PWM1 cfg: cmp0center (Bit 16)                               */
#define PWM1_cfg_cmp0center_Msk               (0x10000UL)               /*!< PWM1 cfg: cmp0center (Bitfield-Mask: 0x01)                  */
#define PWM1_cfg_cmp1center_Pos               (17UL)                    /*!< PWM1 cfg: cmp1center (Bit 17)                               */
#define PWM1_cfg_cmp1center_Msk               (0x20000UL)               /*!< PWM1 cfg: cmp1center (Bitfield-Mask: 0x01)                  */
#define PWM1_cfg_cmp2center_Pos               (18UL)                    /*!< PWM1 cfg: cmp2center (Bit 18)                               */
#define PWM1_cfg_cmp2center_Msk               (0x40000UL)               /*!< PWM1 cfg: cmp2center (Bitfield-Mask: 0x01)                  */
#define PWM1_cfg_cmp3center_Pos               (19UL)                    /*!< PWM1 cfg: cmp3center (Bit 19)                               */
#define PWM1_cfg_cmp3center_Msk               (0x80000UL)               /*!< PWM1 cfg: cmp3center (Bitfield-Mask: 0x01)                  */
#define PWM1_cfg_cmp0gang_Pos                 (24UL)                    /*!< PWM1 cfg: cmp0gang (Bit 24)                                 */
#define PWM1_cfg_cmp0gang_Msk                 (0x1000000UL)             /*!< PWM1 cfg: cmp0gang (Bitfield-Mask: 0x01)                    */
#define PWM1_cfg_cmp1gang_Pos                 (25UL)                    /*!< PWM1 cfg: cmp1gang (Bit 25)                                 */
#define PWM1_cfg_cmp1gang_Msk                 (0x2000000UL)             /*!< PWM1 cfg: cmp1gang (Bitfield-Mask: 0x01)                    */
#define PWM1_cfg_cmp2gang_Pos                 (26UL)                    /*!< PWM1 cfg: cmp2gang (Bit 26)                                 */
#define PWM1_cfg_cmp2gang_Msk                 (0xfc000000UL)            /*!< PWM1 cfg: cmp2gang (Bitfield-Mask: 0x3f)                    */
#define PWM1_cfg_cmp3gang_Pos                 (27UL)                    /*!< PWM1 cfg: cmp3gang (Bit 27)                                 */
#define PWM1_cfg_cmp3gang_Msk                 (0x8000000UL)             /*!< PWM1 cfg: cmp3gang (Bitfield-Mask: 0x01)                    */
#define PWM1_cfg_cmp0ip_Pos                   (28UL)                    /*!< PWM1 cfg: cmp0ip (Bit 28)                                   */
#define PWM1_cfg_cmp0ip_Msk                   (0x10000000UL)            /*!< PWM1 cfg: cmp0ip (Bitfield-Mask: 0x01)                      */
#define PWM1_cfg_cmp1ip_Pos                   (29UL)                    /*!< PWM1 cfg: cmp1ip (Bit 29)                                   */
#define PWM1_cfg_cmp1ip_Msk                   (0x20000000UL)            /*!< PWM1 cfg: cmp1ip (Bitfield-Mask: 0x01)                      */
#define PWM1_cfg_cmp2ip_Pos                   (30UL)                    /*!< PWM1 cfg: cmp2ip (Bit 30)                                   */
#define PWM1_cfg_cmp2ip_Msk                   (0x40000000UL)            /*!< PWM1 cfg: cmp2ip (Bitfield-Mask: 0x01)                      */
#define PWM1_cfg_cmp3ip_Pos                   (31UL)                    /*!< PWM1 cfg: cmp3ip (Bit 31)                                   */
#define PWM1_cfg_cmp3ip_Msk                   (0x80000000UL)            /*!< PWM1 cfg: cmp3ip (Bitfield-Mask: 0x01)                      */

/* ----------------------------------  PWM1_cmp0  --------------------------------- */
#define PWM1_cmp0_value_Pos                   (0UL)                     /*!< PWM1 cmp0: value (Bit 0)                                    */
#define PWM1_cmp0_value_Msk                   (0xffffUL)                /*!< PWM1 cmp0: value (Bitfield-Mask: 0xffff)                    */

/* ----------------------------------  PWM1_cmp1  --------------------------------- */
#define PWM1_cmp1_value_Pos                   (0UL)                     /*!< PWM1 cmp1: value (Bit 0)                                    */
#define PWM1_cmp1_value_Msk                   (0xffffUL)                /*!< PWM1 cmp1: value (Bitfield-Mask: 0xffff)                    */

/* ----------------------------------  PWM1_cmp2  --------------------------------- */
#define PWM1_cmp2_value_Pos                   (0UL)                     /*!< PWM1 cmp2: value (Bit 0)                                    */
#define PWM1_cmp2_value_Msk                   (0xffffUL)                /*!< PWM1 cmp2: value (Bitfield-Mask: 0xffff)                    */

/* ----------------------------------  PWM1_cmp3  --------------------------------- */
#define PWM1_cmp3_value_Pos                   (0UL)                     /*!< PWM1 cmp3: value (Bit 0)                                    */
#define PWM1_cmp3_value_Msk                   (0xffffUL)                /*!< PWM1 cmp3: value (Bitfield-Mask: 0xffff)                    */


/* ================================================================================ */
/* ================         struct 'QSPI2' Position & Mask         ================ */
/* ================================================================================ */


/* --------------------------------  QSPI2_sckdiv  -------------------------------- */
#define QSPI2_sckdiv_div_Pos                  (0UL)                     /*!< QSPI2 sckdiv: div (Bit 0)                                   */
#define QSPI2_sckdiv_div_Msk                  (0xfffUL)                 /*!< QSPI2 sckdiv: div (Bitfield-Mask: 0xfff)                    */

/* --------------------------------  QSPI2_sckmode  ------------------------------- */
#define QSPI2_sckmode_pha_Pos                 (0UL)                     /*!< QSPI2 sckmode: pha (Bit 0)                                  */
#define QSPI2_sckmode_pha_Msk                 (0x1UL)                   /*!< QSPI2 sckmode: pha (Bitfield-Mask: 0x01)                    */
#define QSPI2_sckmode_pol_Pos                 (1UL)                     /*!< QSPI2 sckmode: pol (Bit 1)                                  */
#define QSPI2_sckmode_pol_Msk                 (0x2UL)                   /*!< QSPI2 sckmode: pol (Bitfield-Mask: 0x01)                    */

/* --------------------------------  QSPI2_csmode  -------------------------------- */
#define QSPI2_csmode_mode_Pos                 (0UL)                     /*!< QSPI2 csmode: mode (Bit 0)                                  */
#define QSPI2_csmode_mode_Msk                 (0x3UL)                   /*!< QSPI2 csmode: mode (Bitfield-Mask: 0x03)                    */

/* --------------------------------  QSPI2_delay0  -------------------------------- */
#define QSPI2_delay0_cssck_Pos                (0UL)                     /*!< QSPI2 delay0: cssck (Bit 0)                                 */
#define QSPI2_delay0_cssck_Msk                (0xffUL)                  /*!< QSPI2 delay0: cssck (Bitfield-Mask: 0xff)                   */
#define QSPI2_delay0_sckcs_Pos                (16UL)                    /*!< QSPI2 delay0: sckcs (Bit 16)                                */
#define QSPI2_delay0_sckcs_Msk                (0xff0000UL)              /*!< QSPI2 delay0: sckcs (Bitfield-Mask: 0xff)                   */

/* --------------------------------  QSPI2_delay1  -------------------------------- */
#define QSPI2_delay1_intercs_Pos              (0UL)                     /*!< QSPI2 delay1: intercs (Bit 0)                               */
#define QSPI2_delay1_intercs_Msk              (0xffUL)                  /*!< QSPI2 delay1: intercs (Bitfield-Mask: 0xff)                 */
#define QSPI2_delay1_interxfr_Pos             (16UL)                    /*!< QSPI2 delay1: interxfr (Bit 16)                             */
#define QSPI2_delay1_interxfr_Msk             (0xff0000UL)              /*!< QSPI2 delay1: interxfr (Bitfield-Mask: 0xff)                */

/* ----------------------------------  QSPI2_fmt  --------------------------------- */
#define QSPI2_fmt_proto_Pos                   (0UL)                     /*!< QSPI2 fmt: proto (Bit 0)                                    */
#define QSPI2_fmt_proto_Msk                   (0x3UL)                   /*!< QSPI2 fmt: proto (Bitfield-Mask: 0x03)                      */
#define QSPI2_fmt_endian_Pos                  (2UL)                     /*!< QSPI2 fmt: endian (Bit 2)                                   */
#define QSPI2_fmt_endian_Msk                  (0x4UL)                   /*!< QSPI2 fmt: endian (Bitfield-Mask: 0x01)                     */
#define QSPI2_fmt_dir_Pos                     (3UL)                     /*!< QSPI2 fmt: dir (Bit 3)                                      */
#define QSPI2_fmt_dir_Msk                     (0x8UL)                   /*!< QSPI2 fmt: dir (Bitfield-Mask: 0x01)                        */
#define QSPI2_fmt_len_Pos                     (16UL)                    /*!< QSPI2 fmt: len (Bit 16)                                     */
#define QSPI2_fmt_len_Msk                     (0xf0000UL)               /*!< QSPI2 fmt: len (Bitfield-Mask: 0x0f)                        */

/* --------------------------------  QSPI2_txdata  -------------------------------- */
#define QSPI2_txdata_data_Pos                 (0UL)                     /*!< QSPI2 txdata: data (Bit 0)                                  */
#define QSPI2_txdata_data_Msk                 (0xffUL)                  /*!< QSPI2 txdata: data (Bitfield-Mask: 0xff)                    */
#define QSPI2_txdata_full_Pos                 (31UL)                    /*!< QSPI2 txdata: full (Bit 31)                                 */
#define QSPI2_txdata_full_Msk                 (0x80000000UL)            /*!< QSPI2 txdata: full (Bitfield-Mask: 0x01)                    */

/* --------------------------------  QSPI2_rxdata  -------------------------------- */
#define QSPI2_rxdata_data_Pos                 (0UL)                     /*!< QSPI2 rxdata: data (Bit 0)                                  */
#define QSPI2_rxdata_data_Msk                 (0xffUL)                  /*!< QSPI2 rxdata: data (Bitfield-Mask: 0xff)                    */
#define QSPI2_rxdata_empty_Pos                (31UL)                    /*!< QSPI2 rxdata: empty (Bit 31)                                */
#define QSPI2_rxdata_empty_Msk                (0x80000000UL)            /*!< QSPI2 rxdata: empty (Bitfield-Mask: 0x01)                   */

/* --------------------------------  QSPI2_txmark  -------------------------------- */
#define QSPI2_txmark_txmark_Pos               (0UL)                     /*!< QSPI2 txmark: txmark (Bit 0)                                */
#define QSPI2_txmark_txmark_Msk               (0x7UL)                   /*!< QSPI2 txmark: txmark (Bitfield-Mask: 0x07)                  */

/* --------------------------------  QSPI2_rxmark  -------------------------------- */
#define QSPI2_rxmark_rxmark_Pos               (0UL)                     /*!< QSPI2 rxmark: rxmark (Bit 0)                                */
#define QSPI2_rxmark_rxmark_Msk               (0x7UL)                   /*!< QSPI2 rxmark: rxmark (Bitfield-Mask: 0x07)                  */

/* ---------------------------------  QSPI2_fctrl  -------------------------------- */
#define QSPI2_fctrl_en_Pos                    (0UL)                     /*!< QSPI2 fctrl: en (Bit 0)                                     */
#define QSPI2_fctrl_en_Msk                    (0x1UL)                   /*!< QSPI2 fctrl: en (Bitfield-Mask: 0x01)                       */

/* ---------------------------------  QSPI2_ffmt  --------------------------------- */
#define QSPI2_ffmt_cmd_en_Pos                 (0UL)                     /*!< QSPI2 ffmt: cmd_en (Bit 0)                                  */
#define QSPI2_ffmt_cmd_en_Msk                 (0x1UL)                   /*!< QSPI2 ffmt: cmd_en (Bitfield-Mask: 0x01)                    */
#define QSPI2_ffmt_addr_len_Pos               (1UL)                     /*!< QSPI2 ffmt: addr_len (Bit 1)                                */
#define QSPI2_ffmt_addr_len_Msk               (0xeUL)                   /*!< QSPI2 ffmt: addr_len (Bitfield-Mask: 0x07)                  */
#define QSPI2_ffmt_pad_cnt_Pos                (4UL)                     /*!< QSPI2 ffmt: pad_cnt (Bit 4)                                 */
#define QSPI2_ffmt_pad_cnt_Msk                (0xf0UL)                  /*!< QSPI2 ffmt: pad_cnt (Bitfield-Mask: 0x0f)                   */
#define QSPI2_ffmt_cmd_proto_Pos              (8UL)                     /*!< QSPI2 ffmt: cmd_proto (Bit 8)                               */
#define QSPI2_ffmt_cmd_proto_Msk              (0x300UL)                 /*!< QSPI2 ffmt: cmd_proto (Bitfield-Mask: 0x03)                 */
#define QSPI2_ffmt_addr_proto_Pos             (10UL)                    /*!< QSPI2 ffmt: addr_proto (Bit 10)                             */
#define QSPI2_ffmt_addr_proto_Msk             (0xc00UL)                 /*!< QSPI2 ffmt: addr_proto (Bitfield-Mask: 0x03)                */
#define QSPI2_ffmt_data_proto_Pos             (12UL)                    /*!< QSPI2 ffmt: data_proto (Bit 12)                             */
#define QSPI2_ffmt_data_proto_Msk             (0x3000UL)                /*!< QSPI2 ffmt: data_proto (Bitfield-Mask: 0x03)                */
#define QSPI2_ffmt_cmd_code_Pos               (16UL)                    /*!< QSPI2 ffmt: cmd_code (Bit 16)                               */
#define QSPI2_ffmt_cmd_code_Msk               (0xff0000UL)              /*!< QSPI2 ffmt: cmd_code (Bitfield-Mask: 0xff)                  */
#define QSPI2_ffmt_pad_code_Pos               (24UL)                    /*!< QSPI2 ffmt: pad_code (Bit 24)                               */
#define QSPI2_ffmt_pad_code_Msk               (0xff000000UL)            /*!< QSPI2 ffmt: pad_code (Bitfield-Mask: 0xff)                  */

/* ----------------------------------  QSPI2_ie  ---------------------------------- */
#define QSPI2_ie_txwm_Pos                     (0UL)                     /*!< QSPI2 ie: txwm (Bit 0)                                      */
#define QSPI2_ie_txwm_Msk                     (0x1UL)                   /*!< QSPI2 ie: txwm (Bitfield-Mask: 0x01)                        */
#define QSPI2_ie_rxwm_Pos                     (1UL)                     /*!< QSPI2 ie: rxwm (Bit 1)                                      */
#define QSPI2_ie_rxwm_Msk                     (0x2UL)                   /*!< QSPI2 ie: rxwm (Bitfield-Mask: 0x01)                        */

/* ----------------------------------  QSPI2_ip  ---------------------------------- */
#define QSPI2_ip_txwm_Pos                     (0UL)                     /*!< QSPI2 ip: txwm (Bit 0)                                      */
#define QSPI2_ip_txwm_Msk                     (0x1UL)                   /*!< QSPI2 ip: txwm (Bitfield-Mask: 0x01)                        */
#define QSPI2_ip_rxwm_Pos                     (1UL)                     /*!< QSPI2 ip: rxwm (Bit 1)                                      */
#define QSPI2_ip_rxwm_Msk                     (0x2UL)                   /*!< QSPI2 ip: rxwm (Bitfield-Mask: 0x01)                        */


/* ================================================================================ */
/* ================          struct 'PWM2' Position & Mask         ================ */
/* ================================================================================ */


/* ----------------------------------  PWM2_cfg  ---------------------------------- */
#define PWM2_cfg_scale_Pos                    (0UL)                     /*!< PWM2 cfg: scale (Bit 0)                                     */
#define PWM2_cfg_scale_Msk                    (0xfUL)                   /*!< PWM2 cfg: scale (Bitfield-Mask: 0x0f)                       */
#define PWM2_cfg_sticky_Pos                   (8UL)                     /*!< PWM2 cfg: sticky (Bit 8)                                    */
#define PWM2_cfg_sticky_Msk                   (0x100UL)                 /*!< PWM2 cfg: sticky (Bitfield-Mask: 0x01)                      */
#define PWM2_cfg_zerocmp_Pos                  (9UL)                     /*!< PWM2 cfg: zerocmp (Bit 9)                                   */
#define PWM2_cfg_zerocmp_Msk                  (0x200UL)                 /*!< PWM2 cfg: zerocmp (Bitfield-Mask: 0x01)                     */
#define PWM2_cfg_deglitch_Pos                 (10UL)                    /*!< PWM2 cfg: deglitch (Bit 10)                                 */
#define PWM2_cfg_deglitch_Msk                 (0x400UL)                 /*!< PWM2 cfg: deglitch (Bitfield-Mask: 0x01)                    */
#define PWM2_cfg_enalways_Pos                 (12UL)                    /*!< PWM2 cfg: enalways (Bit 12)                                 */
#define PWM2_cfg_enalways_Msk                 (0x1000UL)                /*!< PWM2 cfg: enalways (Bitfield-Mask: 0x01)                    */
#define PWM2_cfg_enoneshot_Pos                (13UL)                    /*!< PWM2 cfg: enoneshot (Bit 13)                                */
#define PWM2_cfg_enoneshot_Msk                (0x2000UL)                /*!< PWM2 cfg: enoneshot (Bitfield-Mask: 0x01)                   */
#define PWM2_cfg_cmp0center_Pos               (16UL)                    /*!< PWM2 cfg: cmp0center (Bit 16)                               */
#define PWM2_cfg_cmp0center_Msk               (0x10000UL)               /*!< PWM2 cfg: cmp0center (Bitfield-Mask: 0x01)                  */
#define PWM2_cfg_cmp1center_Pos               (17UL)                    /*!< PWM2 cfg: cmp1center (Bit 17)                               */
#define PWM2_cfg_cmp1center_Msk               (0x20000UL)               /*!< PWM2 cfg: cmp1center (Bitfield-Mask: 0x01)                  */
#define PWM2_cfg_cmp2center_Pos               (18UL)                    /*!< PWM2 cfg: cmp2center (Bit 18)                               */
#define PWM2_cfg_cmp2center_Msk               (0x40000UL)               /*!< PWM2 cfg: cmp2center (Bitfield-Mask: 0x01)                  */
#define PWM2_cfg_cmp3center_Pos               (19UL)                    /*!< PWM2 cfg: cmp3center (Bit 19)                               */
#define PWM2_cfg_cmp3center_Msk               (0x80000UL)               /*!< PWM2 cfg: cmp3center (Bitfield-Mask: 0x01)                  */
#define PWM2_cfg_cmp0gang_Pos                 (24UL)                    /*!< PWM2 cfg: cmp0gang (Bit 24)                                 */
#define PWM2_cfg_cmp0gang_Msk                 (0x1000000UL)             /*!< PWM2 cfg: cmp0gang (Bitfield-Mask: 0x01)                    */
#define PWM2_cfg_cmp1gang_Pos                 (25UL)                    /*!< PWM2 cfg: cmp1gang (Bit 25)                                 */
#define PWM2_cfg_cmp1gang_Msk                 (0x2000000UL)             /*!< PWM2 cfg: cmp1gang (Bitfield-Mask: 0x01)                    */
#define PWM2_cfg_cmp2gang_Pos                 (26UL)                    /*!< PWM2 cfg: cmp2gang (Bit 26)                                 */
#define PWM2_cfg_cmp2gang_Msk                 (0xfc000000UL)            /*!< PWM2 cfg: cmp2gang (Bitfield-Mask: 0x3f)                    */
#define PWM2_cfg_cmp3gang_Pos                 (27UL)                    /*!< PWM2 cfg: cmp3gang (Bit 27)                                 */
#define PWM2_cfg_cmp3gang_Msk                 (0x8000000UL)             /*!< PWM2 cfg: cmp3gang (Bitfield-Mask: 0x01)                    */
#define PWM2_cfg_cmp0ip_Pos                   (28UL)                    /*!< PWM2 cfg: cmp0ip (Bit 28)                                   */
#define PWM2_cfg_cmp0ip_Msk                   (0x10000000UL)            /*!< PWM2 cfg: cmp0ip (Bitfield-Mask: 0x01)                      */
#define PWM2_cfg_cmp1ip_Pos                   (29UL)                    /*!< PWM2 cfg: cmp1ip (Bit 29)                                   */
#define PWM2_cfg_cmp1ip_Msk                   (0x20000000UL)            /*!< PWM2 cfg: cmp1ip (Bitfield-Mask: 0x01)                      */
#define PWM2_cfg_cmp2ip_Pos                   (30UL)                    /*!< PWM2 cfg: cmp2ip (Bit 30)                                   */
#define PWM2_cfg_cmp2ip_Msk                   (0x40000000UL)            /*!< PWM2 cfg: cmp2ip (Bitfield-Mask: 0x01)                      */
#define PWM2_cfg_cmp3ip_Pos                   (31UL)                    /*!< PWM2 cfg: cmp3ip (Bit 31)                                   */
#define PWM2_cfg_cmp3ip_Msk                   (0x80000000UL)            /*!< PWM2 cfg: cmp3ip (Bitfield-Mask: 0x01)                      */

/* ----------------------------------  PWM2_cmp0  --------------------------------- */
#define PWM2_cmp0_value_Pos                   (0UL)                     /*!< PWM2 cmp0: value (Bit 0)                                    */
#define PWM2_cmp0_value_Msk                   (0xffffUL)                /*!< PWM2 cmp0: value (Bitfield-Mask: 0xffff)                    */

/* ----------------------------------  PWM2_cmp1  --------------------------------- */
#define PWM2_cmp1_value_Pos                   (0UL)                     /*!< PWM2 cmp1: value (Bit 0)                                    */
#define PWM2_cmp1_value_Msk                   (0xffffUL)                /*!< PWM2 cmp1: value (Bitfield-Mask: 0xffff)                    */

/* ----------------------------------  PWM2_cmp2  --------------------------------- */
#define PWM2_cmp2_value_Pos                   (0UL)                     /*!< PWM2 cmp2: value (Bit 0)                                    */
#define PWM2_cmp2_value_Msk                   (0xffffUL)                /*!< PWM2 cmp2: value (Bitfield-Mask: 0xffff)                    */

/* ----------------------------------  PWM2_cmp3  --------------------------------- */
#define PWM2_cmp3_value_Pos                   (0UL)                     /*!< PWM2 cmp3: value (Bit 0)                                    */
#define PWM2_cmp3_value_Msk                   (0xffffUL)                /*!< PWM2 cmp3: value (Bitfield-Mask: 0xffff)                    */



/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */

#define CLINT_BASE                      0x02000000UL
#define PLIC_BASE                       0x0C000000UL
#define WDOG_BASE                       0x10000000UL
#define RTC_BASE                        0x10000000UL
#define AONCLK_BASE                     0x10000000UL
#define BACKUP_BASE                     0x10000000UL
#define PMU_BASE                        0x10000000UL
#define PRCI_BASE                       0x10008000UL
#define OTP_BASE                        0x10010000UL
#define GPIO0_BASE                      0x10012000UL
#define UART0_BASE                      0x10013000UL
#define QSPI0_BASE                      0x10014000UL
#define PWM0_BASE                       0x10015000UL
#define I2C0_BASE                       0x10016000UL
#define UART1_BASE                      0x10023000UL
#define QSPI1_BASE                      0x10024000UL
#define PWM1_BASE                       0x10025000UL
#define QSPI2_BASE                      0x10034000UL
#define PWM2_BASE                       0x10035000UL


/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

#define CLINT                           ((CLINT_Type              *) CLINT_BASE)
#define PLIC                            ((PLIC_Type               *) PLIC_BASE)
#define WDOG                            ((WDOG_Type               *) WDOG_BASE)
#define RTC                             ((RTC_Type                *) RTC_BASE)
#define AONCLK                          ((AONCLK_Type             *) AONCLK_BASE)
#define BACKUP                          ((BACKUP_Type             *) BACKUP_BASE)
#define PMU                             ((PMU_Type                *) PMU_BASE)
#define PRCI                            ((PRCI_Type               *) PRCI_BASE)
#define OTP                             ((OTP_Type                *) OTP_BASE)
#define GPIO0                           ((GPIO0_Type              *) GPIO0_BASE)
#define UART0                           ((UART0_Type              *) UART0_BASE)
#define QSPI0                           ((QSPI0_Type              *) QSPI0_BASE)
#define PWM0                            ((PWM0_Type               *) PWM0_BASE)
#define I2C0                            ((I2C0_Type               *) I2C0_BASE)
#define UART1                           ((UART0_Type              *) UART1_BASE)
#define QSPI1                           ((QSPI0_Type              *) QSPI1_BASE)
#define PWM1                            ((PWM0_Type               *) PWM1_BASE)
#define QSPI2                           ((QSPI0_Type              *) QSPI2_BASE)
#define PWM2                            ((PWM0_Type               *) PWM2_BASE)


/** @} */ /* End of group Device_Peripheral_Registers */
/** @} */ /* End of group FE310 */
/** @} */ /* End of group SiFive */

#ifdef __cplusplus
}
#endif


#endif  /* FE310_H */

