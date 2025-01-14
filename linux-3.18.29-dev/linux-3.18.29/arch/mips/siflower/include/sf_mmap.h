/**************************************************************************
 *
 *  BRIEF MODULE DESCRIPTION
 *     register definition for Siflower SF-series SoC
 *
 *  Copyright 2015 Siflower Inc.
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License along
 *  with this program; if not, write  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *
 **************************************************************************
 */

#ifndef __SIFLOWER_MMAP__
#define __SIFLOWER_MMAP__

/*****************************************************************************************
*                                                                                        *
*  SF memory map address                                                                 *
*                                                                                        *
******************************************************************************************/
#define SIFLOWER_NPU_BASE                 0xB0000000
#define SIFLOWER_GMAC_BASE                0xB0800000
#define SIFLOWER_WIFI1_BASE               0xB1000000//wifi 2.4G
#define SIFLOWER_WIFI2_BASE               0xB1400000//wifi 5.0G
#define SIFLOWER_GDMA_BASE                0xB1800000
#define SIFLOWER_SCDMA_BASE               0xB1C00000
#define SIFLOWER_USB_BASE                 0xB7400000
#define SIFLOWER_EMMC_BASE                0xB7600000
#define SIFLOWER_SDIO_BASE                0xB7800000
#define SIFLOWER_CATRF_BASE               0xB7A00000
#define SIFLOWER_I2S_BASE                 0xB8000000
#define SIFLOWER_I2C_BASE                 0xB8100000
#define SIFLOWER_I2C_OFFSET               0x1000
#define SIFLOWER_SPI_BASE                 0xB8200000
#define SIFLOWER_SPI_OFFSET               0x1000
#define SIFLOWER_UART_BASE                0xB8300000
#define SIFLOWER_UART_OFFSET              0x1000
#define SIFLOWER_PCM_BASE                 0xB8400000
#define SIFLOWER_PCM_OFFSET               0x1000
#define SIFLOWER_PWM_BASE                 0xB8500000
#define SIFLOWER_PWM_OFFSET               0x1000
#define SIFLOWER_TIMER_BASE               0xB8600000
#define SIFLOWER_TIMER_OFFSET             0x1000
#define SIFLOWER_WDT_BASE                 0xB8700000
#define SIFLOWER_SPDIF_BASE               0xB8800000
#define SIFLOWER_GPIO_BASE                0xB9D00000
#define SIFLOWER_SYSCTL_BASE              0xB9E00000
#define SIFLOWER_DDR_CTL_BASE             0xB9F00000
#define SIFLOWER_DDR_PHY_BASE             0xB9F80000

//IRAM MAP
#ifdef WIFI_24G
#define SIFLOWER_IRAM_BASE                0xBC018000
#else
#define SIFLOWER_IRAM_BASE                0xBC000000
#endif

#if (defined(WIFI_24G) || defined(WIFI_5G))
#define SIFLOWER_IRAM_SIZE                0x18000
#else
#define SIFLOWER_IRAM_SIZE                0x30000
#endif

//in any case,simulaiton log always save at the last 32 byte,becase we use shadow ram for log, not real space.
#define SIFLOWER_LOG_SIZE                 (32)

#ifdef WIFI_5G
#define SIFLOWER_SIM_LOG_BASE             (SIFLOWER_IRAM_BASE + (SIFLOWER_IRAM_SIZE * 2) - SIFLOWER_LOG_SIZE)
#define SIFLOWER_SIM_LOG_TRIG             (SIFLOWER_IRAM_BASE + (SIFLOWER_IRAM_SIZE * 2) - 1)
#else
#define SIFLOWER_SIM_LOG_BASE             (SIFLOWER_IRAM_BASE + SIFLOWER_IRAM_SIZE - SIFLOWER_LOG_SIZE)
#define SIFLOWER_SIM_LOG_TRIG             (SIFLOWER_IRAM_BASE + SIFLOWER_IRAM_SIZE - 1)
#endif

//in any case,hardwre memory operation code set at the last fix addr,becase we use shadow ram for log, not real space.
#define SIFLOWER_HW_COPY_SIZE             (32)
#define SIFLOWER_HW_COPY_BASE			  (SIFLOWER_SIM_LOG_BASE - SIFLOWER_HW_COPY_SIZE)


#if (defined(DDR) && defined(BOOT_DDR))
//boot from ddr,not iram
#define SIFLOWER_STACK_SIZE               (0x20000)//stack upgrade low addrres. 64K
#define SIFLOWER_STACK_BASE               (SIFLOWER_IRAM_BASE + 0x1000) //this is an temp sp point,befort ddr intit
#define SIFLOWER_STACK_BASE1              (0xa0030000) //this is an common sp point,after ddr init
#define SIFLOWER_DATA_BASE                (0xa0040000)

#define SIFLOWER_INT_CONTEXT_SIZE         (256)//for interrupt context
#define SIFLOWER_INT_CONTEXT_BASE         (0xa0000000)

#define SIFLOWER_IRAM_RESERVE_SIZE        (736)//resver for msic
#define SIFLOWER_IRAM_RESVERVE_BASE       (0xa0001000)

#else

#define SIFLOWER_IRAM_RESERVE_SIZE        (704)//resver for msic
#define SIFLOWER_IRAM_RESVERVE_BASE       (SIFLOWER_IRAM_BASE + SIFLOWER_IRAM_SIZE - SIFLOWER_LOG_SIZE- SIFLOWER_HW_COPY_SIZE - SIFLOWER_IRAM_RESERVE_SIZE)

#define SIFLOWER_INT_CONTEXT_SIZE         (256)//for interrupt context
#define SIFLOWER_INT_CONTEXT_BASE         (SIFLOWER_STACK_BASE + 4)

#ifdef WIFI
#define SIFLOWER_STACK_SIZE               (0x800000)//stack upgrade low addrres.
#define SIFLOWER_STACK_BASE               (0xaf000000)
#else
#define SIFLOWER_STACK_SIZE               (0x8000)//stack upgrade low addrres.
#define SIFLOWER_STACK_BASE               (SIFLOWER_IRAM_RESVERVE_BASE - SIFLOWER_INT_CONTEXT_SIZE)
#endif /* WIFI */
#endif


//hardware memory copy or set key addr
//0x0000_0077 - copy memory data from source address to destination address
//0x0000_0088 - load memory data from source file to destination address
//0x0000_0099 - save memory data from source address to destination file
#define SIFLOWER_HW_COPY_TIRG             (SIFLOWER_HW_COPY_BASE + 16 )
#define SIFLOWER_HW_COPY_SRC              (SIFLOWER_HW_COPY_BASE + 16 + 4)//Source Address
#define SIFLOWER_HW_COPY_DST              (SIFLOWER_HW_COPY_BASE + 16 + 8)//Destination Address
#define SIFLOWER_HW_COPY_LEN              (SIFLOWER_HW_COPY_BASE + 16 + 12)//Data Length (Byte)


/*****************************************************************************************
*                                                                                        *
*  SF Interrupt Controller                                                               *
*                                                                                        *
******************************************************************************************/
#define SIFLOWER_NPU_HIF_IRQ             16
#define SIFLOWER_NPU_RES1_IRQ            17
#define SIFLOWER_NPU_RES2_IRQ            18
#define SIFLOWER_NPU_RES3_IRQ            19
#define SIFLOWER_NPU_RES4_IRQ            20
#define SIFLOWER_NPU_RES5_IRQ            21
#define SIFLOWER_NPU_RES6_IRQ            22
#define SIFLOWER_NPU_RES7_IRQ            23
#define SIFLOWER_NPU_BMU_IRQ             24
#define SIFLOWER_NPU_PHY1_IRQ            25
#define SIFLOWER_NPU_PHY2_IRQ            26
#define SIFLOWER_NPU_PHY3_IRQ            27
#define SIFLOWER_NPU_PHY4_IRQ            28
#define SIFLOWER_NPU_PHY5_IRQ            29

#define SIFLOWER_EMAC_SBD_IRQ            32
#define SIFLOWER_EMAC_LPI_IRQ            33
#define SIFLOWER_EMAC_PMT_IRQ            34

#define SIFLOWER_WIFI_INTC_CPU_SINGLE	 48
//WIFI Inter Processor Communication
#define SIFLOWER_WIFI_INTC_IPC_HOST      49

//WIFI End Of Transfer interrupts: Last fragment of the channel link list has been processed
#define SIFLOWER_WIFI_INTC_DMA_CH0_EOT   50
#define SIFLOWER_WIFI_INTC_DMA_CH1_EOT   51
#define SIFLOWER_WIFI_INTC_DMA_CH2_EOT   52
#define SIFLOWER_WIFI_INTC_DMA_CH3_EOT   53

#define SIFLOWER_WIFI_INTC_LLI0          54
#define SIFLOWER_WIFI_INTC_LLI1          55
#define SIFLOWER_WIFI_INTC_LLI2          56
#define SIFLOWER_WIFI_INTC_LLI3          57
#define SIFLOWER_WIFI_INTC_LLI4          58
#define SIFLOWER_WIFI_INTC_LLI5          59
#define SIFLOWER_WIFI_INTC_LLI6          60
#define SIFLOWER_WIFI_INTC_LLI7          61
#define SIFLOWER_WIFI_INTC_LLI8          62
#define SIFLOWER_WIFI_INTC_LLI9          63

#define SIFLOWER_WIFI_INTC_CPU_SINGLE_5G    64
//WIFI Inter Processor Communication
#define SIFLOWER_WIFI_INTC_IPC_HOST_5G      65
//WIFI End Of Transfer interrupts: Last fragment of the channel link list has been processed
#define SIFLOWER_WIFI_INTC_DMA_CH0_EOT_5G   66
#define SIFLOWER_WIFI_INTC_DMA_CH1_EOT_5G   67
#define SIFLOWER_WIFI_INTC_DMA_CH2_EOT_5G   68
#define SIFLOWER_WIFI_INTC_DMA_CH3_EOT_5G   69
#define SIFLOWER_WIFI_INTC_LLI0_5G          70
#define SIFLOWER_WIFI_INTC_LLI1_5G          71
#define SIFLOWER_WIFI_INTC_LLI2_5G          72
#define SIFLOWER_WIFI_INTC_LLI3_5G          73
#define SIFLOWER_WIFI_INTC_LLI4_5G          74
#define SIFLOWER_WIFI_INTC_LLI5_5G          75
#define SIFLOWER_WIFI_INTC_LLI6_5G          76
#define SIFLOWER_WIFI_INTC_LLI7_5G          77
#define SIFLOWER_WIFI_INTC_LLI8_5G          78
#define SIFLOWER_WIFI_INTC_LLI9_5G          79

#define SIFLOWER_GDMA_IRQ0               80
#define SIFLOWER_GDMA_IRQ1               81
#define SIFLOWER_GDMA_IRQ2               82
#define SIFLOWER_GDMA_IRQ3               83
#define SIFLOWER_GDMA_IRQ4               84
#define SIFLOWER_GDMA_IRQ5               85
#define SIFLOWER_GDMA_IRQ6               86
#define SIFLOWER_GDMA_IRQ7               87
#define SIFLOWER_GDMA_IRQ8               88
#define SIFLOWER_GDMA_IRQ9               89
#define SIFLOWER_GDMA_IRQ10              90
#define SIFLOWER_GDMA_IRQ11              91
#define SIFLOWER_GDMA_ABR_IRQ            92

//WIFI LLI interrupts: Specific fragment of link list item has been processed
#define SIFLOWER_WIFI_INTC_LLI10         96
#define SIFLOWER_WIFI_INTC_LLI11         97
#define SIFLOWER_WIFI_INTC_LLI12         98
#define SIFLOWER_WIFI_INTC_LLI13         99
#define SIFLOWER_WIFI_INTC_LLI14         100
#define SIFLOWER_WIFI_INTC_LLI15         101

//WIFI DMA
#define SIFLOWER_WIFI_INTC_DMA_BUSERR    102
#define SIFLOWER_WIFI_INTC_DMA_CH4_EOT   103
// MAC HW
#define SIFLOWER_WIFI_INTC_MACTIMER      104
#define SIFLOWER_WIFI_INTC_MACOTHER      105
#define SIFLOWER_WIFI_INTC_MACRX         106
#define SIFLOWER_WIFI_INTC_MACTX         107
#define SIFLOWER_WIFI_INTC_MACINTGEN     108
#define SIFLOWER_WIFI_INTC_MACPROT       109

//WIFI Inter Processor Communication
#define SIFLOWER_WIFI_INTC_IPC0          110
#define SIFLOWER_WIFI_INTC_IPC1          111

//WIFI LLI interrupts: Specific fragment of link list item has been processed
#define SIFLOWER_WIFI_INTC_LLI10_5G         112
#define SIFLOWER_WIFI_INTC_LLI11_5G         113
#define SIFLOWER_WIFI_INTC_LLI12_5G         114
#define SIFLOWER_WIFI_INTC_LLI13_5G         115
#define SIFLOWER_WIFI_INTC_LLI14_5G         116
#define SIFLOWER_WIFI_INTC_LLI15_5G         117

//WIFI DMA
#define SIFLOWER_WIFI_INTC_DMA_BUSERR_5G    118
#define SIFLOWER_WIFI_INTC_DMA_CH4_EOT_5G   119

// MAC HW
#define SIFLOWER_WIFI_INTC_MACTIMER_5G      120
#define SIFLOWER_WIFI_INTC_MACOTHER_5G      121
#define SIFLOWER_WIFI_INTC_MACRX_5G         122
#define SIFLOWER_WIFI_INTC_MACTX_5G         123
#define SIFLOWER_WIFI_INTC_MACINTGEN_5G     124
#define SIFLOWER_WIFI_INTC_MACPROT_5G       125

//WIFI Inter Processor Communication
#define SIFLOWER_WIFI_INTC_IPC0_5G          126
#define SIFLOWER_WIFI_INTC_IPC1_5G          127

#define SIFLOWER_USB_IRQ                 128

#define SIFLOWER_SDIO0_IRQ               144
#define SIFLOWER_SDIO1_IRQ               160

//WIFI Inter Processor Communication
#define SIFLOWER_WIFI_INTC_IPC2          200
#define SIFLOWER_WIFI_INTC_IPC3          201

//WIFI IQ TEST ENGINE buffer full interruption
#define SIFLOWER_WIFI_INTC_IQR_LOWRAM_FULL   192
#define SIFLOWER_WIFI_INTC_IQR_HIGHRAM_FULL  193
#define SIFLOWER_WIFI_INTC_IQP_LOWRAM_FULL   194
#define SIFLOWER_WIFI_INTC_IQP_HIGHRAM_FULL  195

//WIFI PHY HW
#define SIFLOWER_WIFI_INTC_MODEM         202
#define SIFLOWER_WIFI_INTC_RC            203

//WIFI Inter Processor Communication
#define SIFLOWER_WIFI_INTC_IPC2_5G          204
#define SIFLOWER_WIFI_INTC_IPC3_5G          205

//WIFI PHY HW
#define SIFLOWER_WIFI_INTC_MODEM_5G         206
#define SIFLOWER_WIFI_INTC_RC_5G            207

#define SIFLOWER_I2S_M_IRQ	             208
#define SIFLOWER_I2S_S_IRQ	             211

#define SIFLOWER_I2C0_IRQ	  	         217
#define SIFLOWER_I2C1_IRQ	             218
#define SIFLOWER_I2C2_IRQ	             219

#define SIFLOWER_SPI0_IRQ                223
#define SIFLOWER_SPI1_IRQ                224
#define SIFLOWER_SPI2_IRQ                225
#define SIFLOWER_UART0_IRQ	             226
#define SIFLOWER_UART1_IRQ	             227
#define SIFLOWER_UART2_IRQ	             228
#define SIFLOWER_UART3_IRQ	             229
#define SIFLOWER_PCM0_IRQ                230
#define SIFLOWER_PCM1_IRQ                231
#define SIFLOWER_PWM0_IRQ                232
#define SIFLOWER_PWM1_IRQ                233
#define SIFLOWER_TIMER00_IRQ             234
#define SIFLOWER_TIMER01_IRQ             235
#define SIFLOWER_TIMER10_IRQ             236
#define SIFLOWER_TIMER11_IRQ             237
#define SIFLOWER_WDT_IRQ                 238
#define SIFLOWER_SPDIF_IRQ	             239

#define SIFLOWER_GPIO_GRA_IRQ            245//for all gpios
#define SIFLOWER_GPIO_GR0_IRQ            246
#define SIFLOWER_GPIO_GR1_IRQ            247
#define SIFLOWER_GPIO_GR2_IRQ            248
#define SIFLOWER_GPIO_GR3_IRQ            249
#define SIFLOWER_GPIO_GR4_IRQ            250
#define SIFLOWER_GPIO_GR5_IRQ            251
#define SIFLOWER_GPIO_GR6_IRQ            252
#define SIFLOWER_GPIO_GR7_IRQ            253
#define SIFLOWER_GPIO_GR8_IRQ            254
#define SIFLOWER_GPIO_GR9_IRQ            255




/*****************************************************************************************
*                                                                                        *
*  SF System Manager                                                                     *
*                                                                                        *
******************************************************************************************/
//CM_PwrOn_n
#define CORE_CM_PWRON_N                  (SIFLOWER_SYSCTL_BASE + 0x0000)

//SI_CPCReset
#define CORE_CPC_RESET                   (SIFLOWER_SYSCTL_BASE + 0x0004)

//bit4		 for SI_CM_PwrUp
//bit3-bit2  = 0
//bit1       for SI1_PwrUp
//bit0       for SI0_PwrUp
#define CORE_POWER_CTRL                  (SIFLOWER_SYSCTL_BASE + 0x0010)

//SI_PwrOn_Reset
#define CORE_PWRON_RESET                 (SIFLOWER_SYSCTL_BASE + 0x001C)

//core cold powerup
//bit3-bit2 for SI1_ColdPwrUp
//bit1-bit0 for SI0_ColdPwrUp
#define CORE_CLOD_POWERUP                (SIFLOWER_SYSCTL_BASE + 0x0020)

//SI_WDTReset[7:0]
#define CORE_WDG_RESET                   (SIFLOWER_SYSCTL_BASE + 0x0024)

//SI_L2_ClkRatio
#define CORE_L2_CLK_RATIO                (SIFLOWER_SYSCTL_BASE + 0x0038)

//SI_L2_SetClkRatio
#define CORE_L2_SET_CLK_RATIO            (SIFLOWER_SYSCTL_BASE + 0x003C)

//bit4      for SI0_DisableVPE
//bit3-bit0 for SI0_DisableTCs
#define CORE0_VPE_TC_DISABLE             (SIFLOWER_SYSCTL_BASE + 0x004C)
#define CORE1_VPE_TC_DISABLE             (SIFLOWER_SYSCTL_BASE + 0x0050)

//SI*_Vpe0MaxTC[3:0]
#define CORE0_VPE0_MAX_TC                (SIFLOWER_SYSCTL_BASE + 0x0054)
#define CORE1_VPE0_MAX_TC                (SIFLOWER_SYSCTL_BASE + 0x0058)

//for irom ctrl
#define IROM_SOFT_RESET                  (SIFLOWER_SYSCTL_BASE + 0x0800)
#define IROM_CLK_EN                      (SIFLOWER_SYSCTL_BASE + 0x0804)
#define IROM_SOFT_BOE                    (SIFLOWER_SYSCTL_BASE + 0x080C)

//before cpu up,irom use 12M,then use cpu clk. this reg can be set in irom fix code
#define IROM_BOOT_CLK_SEL                (SIFLOWER_SYSCTL_BASE + 0x2028)

#define SOFT_REBOOT                      (SIFLOWER_SYSCTL_BASE + 0x2030)
#define SYS_EVTS_MASK70                  (SIFLOWER_SYSCTL_BASE + 0x2034)
#define SYS_EVTS_MASK158                 (SIFLOWER_SYSCTL_BASE + 0x2038)
#define SYS_EVTS_MASK2316                (SIFLOWER_SYSCTL_BASE + 0x203C)
#define SYS_EVTS_MASK3124                (SIFLOWER_SYSCTL_BASE + 0x2040)
#define SYS_EVTS_MASK3932                (SIFLOWER_SYSCTL_BASE + 0x2044)
#define SYS_EVTS_MASK4740                (SIFLOWER_SYSCTL_BASE + 0x2048)
#define SYS_EVTS_MASK5548                (SIFLOWER_SYSCTL_BASE + 0x204C)
#define SYS_EVTS_MASK6356                (SIFLOWER_SYSCTL_BASE + 0x2050)

//int_laram1_sel,  int_laram0_sel  bit3-bit2 LA mode 0->iram 1->LA
//fram1_sel,       fram0_sel       bit1-bit0 share/iram mode 0->iram 1->share
#define WIFI_SHARE_RAM_SEL               (SIFLOWER_SYSCTL_BASE + 0x242C)
//int_player1_sel, int_player0_sel,int_recorder1_sel, int_recorder0_sel
#define WIFI_SYSM_IQ_ENGINE_SEL          (SIFLOWER_SYSCTL_BASE + 0x2430)
//int_rp_enable, int_bb_sel
#define WIFI_SYSM_IQ_ENGINE_CONF         (SIFLOWER_SYSCTL_BASE + 0x2434)

//cpu sys manager module
#define CPU_SYSM_RESET                   (SIFLOWER_SYSCTL_BASE + 0x2C28)

//ddr sys manager module
#define MPU_SYSM_RESET                   (SIFLOWER_SYSCTL_BASE + 0x2C2C)

//irom sys manager module
#define IROM_SYSM_RESET                  (SIFLOWER_SYSCTL_BASE + 0x2C34)

//irom sys manager module --not use
#define BROM_SYSM_RESET                  (SIFLOWER_SYSCTL_BASE + 0x2C3C)

//iram sys manager module --not use
#define MPOL_SYSM_RESET                  (SIFLOWER_SYSCTL_BASE + 0x2C40)

//clock sys manager module --not use
#define CM_SYSM_RESET                    (SIFLOWER_SYSCTL_BASE + 0x2DF0)

//io sys manager module
#define IO_SYSM_RESET                    (SIFLOWER_SYSCTL_BASE + 0x2DF4)

//ddr
#define MEM_RESET                        (SIFLOWER_SYSCTL_BASE + 0x2DC8)

//cpu --in irom fixed code
#define CPU_RESET                        (SIFLOWER_SYSCTL_BASE + 0x2DCC)

#define BUS1_RESET                       (SIFLOWER_SYSCTL_BASE + 0x2DD0)
#define BUS2_RESET                       (SIFLOWER_SYSCTL_BASE + 0x2DD4)
#define BUS3_RESET                       (SIFLOWER_SYSCTL_BASE + 0x2DD8)
#define BUS4_RESET                       (SIFLOWER_SYSCTL_BASE + 0x2DDC)
#define BUS5_RESET                       (SIFLOWER_SYSCTL_BASE + 0x2DE0)
#define BUS6_RESET                       (SIFLOWER_SYSCTL_BASE + 0x2DE4)
#define BUS7_RESET                       (SIFLOWER_SYSCTL_BASE + 0x2DE8)
#define BUS8_RESET                       (SIFLOWER_SYSCTL_BASE + 0x2DEC)

//iram sys manager module
#define IRAM_SYSM_RESET                  (SIFLOWER_SYSCTL_BASE + 0x2C30)
#define IRAM_SOFT_RESET                  (SIFLOWER_SYSCTL_BASE + 0x0C00)
#define IRAM_SOFT_CLK_EN                 (SIFLOWER_SYSCTL_BASE + 0x0C04)
#define IRAM_SOFT_BOE                    (SIFLOWER_SYSCTL_BASE + 0x0C0C)
#define IRAM_SOFT_RESET1                 (SIFLOWER_SYSCTL_BASE + 0x0C1C)
#define IRAM_SOFT_CLK_EN1                (SIFLOWER_SYSCTL_BASE + 0x0C20)

//NPU
#define NPU_SYSM_RESET                   (SIFLOWER_SYSCTL_BASE + 0x2C44)
#define NPU_SOFT_RESET                   (SIFLOWER_SYSCTL_BASE + 0x4000)
#define NPU_SOFT_CLK_EN                  (SIFLOWER_SYSCTL_BASE + 0x4004)
#define NPU_SOFT_BOE                     (SIFLOWER_SYSCTL_BASE + 0x400C)
#define NPU_HW_RST_PGM_EN                (SIFLOWER_SYSCTL_BASE + 0x40CC)

//OMINI PHY
#define OMINI_PHY_ENABLE                 (SIFLOWER_SYSCTL_BASE + 0x4040)
#define OMINI_PHY_CFG_POWERDOWN          (SIFLOWER_SYSCTL_BASE + 0x4044)
#define OMINI_PHY_CFG_POWERUP_RESET      (SIFLOWER_SYSCTL_BASE + 0x4048)

#define OMINI_PHY1_CFG_ADDR              (SIFLOWER_SYSCTL_BASE + 0x404C)
#define OMINI_PHY2_CFG_ADDR              (SIFLOWER_SYSCTL_BASE + 0x4050)
#define OMINI_PHY3_CFG_ADDR              (SIFLOWER_SYSCTL_BASE + 0x4054)
#define OMINI_PHY4_CFG_ADDR              (SIFLOWER_SYSCTL_BASE + 0x4058)
#define OMINI_PHY5_CFG_ADDR              (SIFLOWER_SYSCTL_BASE + 0x405C)

#define OMINI_PHY1_CFG_FX_PLL_MODE       (SIFLOWER_SYSCTL_BASE + 0x4060)
#define OMINI_PHY2_CFG_FX_PLL_MODE       (SIFLOWER_SYSCTL_BASE + 0x4064)
#define OMINI_PHY3_CFG_FX_PLL_MODE       (SIFLOWER_SYSCTL_BASE + 0x4068)
#define OMINI_PHY4_CFG_FX_PLL_MODE       (SIFLOWER_SYSCTL_BASE + 0x406C)
#define OMINI_PHY5_CFG_FX_PLL_MODE       (SIFLOWER_SYSCTL_BASE + 0x4070)

#define OMINI_PHY_CFG_CLK_FREQ           (SIFLOWER_SYSCTL_BASE + 0x4074)
#define OMINI_PHY_CFG_CLK_REF_SEL        (SIFLOWER_SYSCTL_BASE + 0x4078)

#define OMINI_PHY1_CFG_PHY_ID_LOW8       (SIFLOWER_SYSCTL_BASE + 0x407C)
#define OMINI_PHY1_CFG_PHY_ID_HIGH8      (SIFLOWER_SYSCTL_BASE + 0x4080)
#define OMINI_PHY1_CFG_MODEL_NR          (SIFLOWER_SYSCTL_BASE + 0x4084)
#define OMINI_PHY1_CFG_REV_NR            (SIFLOWER_SYSCTL_BASE + 0x4088)

#define OMINI_PHY2_CFG_PHY_ID_LOW8       (SIFLOWER_SYSCTL_BASE + 0x408C)
#define OMINI_PHY2_CFG_PHY_ID_HIGH8      (SIFLOWER_SYSCTL_BASE + 0x4090)
#define OMINI_PHY2_CFG_MODEL_NR          (SIFLOWER_SYSCTL_BASE + 0x4094)
#define OMINI_PHY2_CFG_REV_NR            (SIFLOWER_SYSCTL_BASE + 0x4098)

#define OMINI_PHY3_CFG_PHY_ID_LOW8       (SIFLOWER_SYSCTL_BASE + 0x409C)
#define OMINI_PHY3_CFG_PHY_ID_HIGH8      (SIFLOWER_SYSCTL_BASE + 0x40A0)
#define OMINI_PHY3_CFG_MODEL_NR          (SIFLOWER_SYSCTL_BASE + 0x40A4)
#define OMINI_PHY3_CFG_REV_NR            (SIFLOWER_SYSCTL_BASE + 0x40A8)

#define OMINI_PHY4_CFG_PHY_ID_LOW8       (SIFLOWER_SYSCTL_BASE + 0x40AC)
#define OMINI_PHY4_CFG_PHY_ID_HIGH8      (SIFLOWER_SYSCTL_BASE + 0x40B0)
#define OMINI_PHY4_CFG_MODEL_NR          (SIFLOWER_SYSCTL_BASE + 0x40B4)
#define OMINI_PHY4_CFG_REV_NR            (SIFLOWER_SYSCTL_BASE + 0x40B8)

#define OMINI_PHY5_CFG_PHY_ID_LOW8       (SIFLOWER_SYSCTL_BASE + 0x40BC)
#define OMINI_PHY5_CFG_PHY_ID_HIGH8      (SIFLOWER_SYSCTL_BASE + 0x40C0)
#define OMINI_PHY5_CFG_MODEL_NR          (SIFLOWER_SYSCTL_BASE + 0x40C4)
#define OMINI_PHY5_CFG_REV_NR            (SIFLOWER_SYSCTL_BASE + 0x40C8)

//GMAC
#define EMAC_SYSM_RESETN                 (SIFLOWER_SYSCTL_BASE + 0x2C48)
#define EMAC_SOFT_RESET                  (SIFLOWER_SYSCTL_BASE + 0x4400)
#define EMAC_SOFT_CLKGATE_EN             (SIFLOWER_SYSCTL_BASE + 0x4404)
#define EMAC_SOFT_BOE                    (SIFLOWER_SYSCTL_BASE + 0x440C)
#define EMAC_PHY_INTF_SEL_I              (SIFLOWER_SYSCTL_BASE + 0x4440)
#define EMAC_CLK_TX_I_DLY                (SIFLOWER_SYSCTL_BASE + 0x4444)
#define EMAC_CLK_PHY_RX_I_DLY            (SIFLOWER_SYSCTL_BASE + 0x4448)
#define EMAC_CLK_PHY_RX_I_DLY_EN         (SIFLOWER_SYSCTL_BASE + 0x444c)


//WIFI DMA
#define SCDMA_SYSM_RESET                 (SIFLOWER_SYSCTL_BASE + 0x2C70)  //[0:0] Active Low
#define SCDMA_SOFT_RESET                 (SIFLOWER_SYSCTL_BASE + 0x8C00)  //[2:0] Active High
#define SCDMA_SOFT_CLK_EN                (SIFLOWER_SYSCTL_BASE + 0x8C04)  //[2:0] Active High
#define SCDMA_SOFT_BOE                   (SIFLOWER_SYSCTL_BASE + 0x8C0C)  //[1:0] Active High

//WIFI1 2.4G
#define WIFI_1_SYSM_RESET                (SIFLOWER_SYSCTL_BASE + 0x2C64)  //[0:0] Active Low
#define WIFI_1_SOFT_RESET                (SIFLOWER_SYSCTL_BASE + 0x8000)  //[2:0] Active High
#define WIFI_1_SOFT_CLK_EN               (SIFLOWER_SYSCTL_BASE + 0x8004)  //[7:0] Active High
#define WIFI_1_SOFT_BOE                  (SIFLOWER_SYSCTL_BASE + 0x800C)  //[1:0] Active High
// wifi2.4 iqdump for simulation
#define WIFI_1_LA_CLK_SEL                (SIFLOWER_SYSCTL_BASE + 0x8040)
#define WIFI_1_IQ_GEN_DUMP_EN            (SIFLOWER_SYSCTL_BASE + 0x8044)
#define WIFI_1_IQ_DUMP_LENGTH_0          (SIFLOWER_SYSCTL_BASE + 0x8048)
#define WIFI_1_IQ_DUMP_LENGTH_1          (SIFLOWER_SYSCTL_BASE + 0x804C)
#define WIFI_1_IQ_DUMP_LENGTH_2          (SIFLOWER_SYSCTL_BASE + 0x8050)
#define WIFI_1_IQ_DUMP_LENGTH_3          (SIFLOWER_SYSCTL_BASE + 0x8054)
#define WIFI_1_IQ_GEN_LENGTH_0           (SIFLOWER_SYSCTL_BASE + 0x8058)
#define WIFI_1_IQ_GEN_LENGTH_1           (SIFLOWER_SYSCTL_BASE + 0x805C)
#define WIFI_1_IQ_GEN_LENGTH_2           (SIFLOWER_SYSCTL_BASE + 0x8060)
#define WIFI_1_IQ_GEN_LENGTH_3           (SIFLOWER_SYSCTL_BASE + 0x8064)
// wifi2.4G iq test engine
#define WIFI_1_IQ_ENGINE_RECORD_MODE     (SIFLOWER_SYSCTL_BASE + 0x3800)
#define WIFI_1_IQ_ENGINE_RECORD_TRIGGER  (SIFLOWER_SYSCTL_BASE + 0x3804)
#define WIFI_1_IQ_ENGINE_RECORD_DMAREQ   (SIFLOWER_SYSCTL_BASE + 0x3808)
#define WIFI_1_IQ_ENGINE_RECORD_DMAACK   (SIFLOWER_SYSCTL_BASE + 0x380C)
#define WIFI_1_IQ_ENGINE_RECORD_OFFSET_0 (SIFLOWER_SYSCTL_BASE + 0x3810)
#define WIFI_1_IQ_ENGINE_RECORD_OFFSET_1 (SIFLOWER_SYSCTL_BASE + 0x3814)
#define WIFI_1_IQ_ENGINE_RECORD_OFFSET_2 (SIFLOWER_SYSCTL_BASE + 0x3818)
#define WIFI_1_IQ_ENGINE_RECORD_OFFSET_3 (SIFLOWER_SYSCTL_BASE + 0x381C)
#define WIFI_1_IQ_ENGINE_RECORD_LENGTH_0 (SIFLOWER_SYSCTL_BASE + 0x3820)
#define WIFI_1_IQ_ENGINE_RECORD_LENGTH_1 (SIFLOWER_SYSCTL_BASE + 0x3824)
#define WIFI_1_IQ_ENGINE_RECORD_LENGTH_2 (SIFLOWER_SYSCTL_BASE + 0x3828)
#define WIFI_1_IQ_ENGINE_RECORD_LENGTH_3 (SIFLOWER_SYSCTL_BASE + 0x382C)
#define WIFI_1_IQ_ENGINE_RECORD_DMAADEAD (SIFLOWER_SYSCTL_BASE + 0x3830)

#define WIFI_1_IQ_ENGINE_PLAYER_MODE     (SIFLOWER_SYSCTL_BASE + 0x3A00)
#define WIFI_1_IQ_ENGINE_PLAYER_TRIGGER  (SIFLOWER_SYSCTL_BASE + 0x3A04)
#define WIFI_1_IQ_ENGINE_PLAYER_DMAREQ   (SIFLOWER_SYSCTL_BASE + 0x3A08)
#define WIFI_1_IQ_ENGINE_PLAYER_DMAACK   (SIFLOWER_SYSCTL_BASE + 0x3A0C)
#define WIFI_1_IQ_ENGINE_PLAYER_OFFSET_0 (SIFLOWER_SYSCTL_BASE + 0x3A10)
#define WIFI_1_IQ_ENGINE_PLAYER_OFFSET_1 (SIFLOWER_SYSCTL_BASE + 0x3A14)
#define WIFI_1_IQ_ENGINE_PLAYER_OFFSET_2 (SIFLOWER_SYSCTL_BASE + 0x3A18)
#define WIFI_1_IQ_ENGINE_PLAYER_OFFSET_3 (SIFLOWER_SYSCTL_BASE + 0x3A1C)
#define WIFI_1_IQ_ENGINE_PLAYER_LENGTH_0 (SIFLOWER_SYSCTL_BASE + 0x3A20)
#define WIFI_1_IQ_ENGINE_PLAYER_LENGTH_1 (SIFLOWER_SYSCTL_BASE + 0x3A24)
#define WIFI_1_IQ_ENGINE_PLAYER_LENGTH_2 (SIFLOWER_SYSCTL_BASE + 0x3A28)
#define WIFI_1_IQ_ENGINE_PLAYER_LENGTH_3 (SIFLOWER_SYSCTL_BASE + 0x3A2C)
#define WIFI_1_IQ_ENGINE_PLAYER_DMAADEAD (SIFLOWER_SYSCTL_BASE + 0x3A30)


//WIFI2 5.0G
#define WIFI_2_SYSM_RESET                (SIFLOWER_SYSCTL_BASE + 0x2C68)  //[0:0] Active Low
#define WIFI_2_SOFT_RESET                (SIFLOWER_SYSCTL_BASE + 0x8400)  //[2:0] Active High
#define WIFI_2_SOFT_CLK_EN               (SIFLOWER_SYSCTL_BASE + 0x8404)  //[7:0] Active High
#define WIFI_2_SOFT_BOE                  (SIFLOWER_SYSCTL_BASE + 0x840C)  //[1:0] Active High
// wifi5G iqdump for simulation
#define WIFI_2_LA_CLK_SEL                (SIFLOWER_SYSCTL_BASE + 0x8440)
#define WIFI_2_IQ_GEN_DUMP_EN            (SIFLOWER_SYSCTL_BASE + 0x8444)
#define WIFI_2_IQ_DUMP_LENGTH_0          (SIFLOWER_SYSCTL_BASE + 0x8448)
#define WIFI_2_IQ_DUMP_LENGTH_1          (SIFLOWER_SYSCTL_BASE + 0x844C)
#define WIFI_2_IQ_DUMP_LENGTH_2          (SIFLOWER_SYSCTL_BASE + 0x8450)
#define WIFI_2_IQ_DUMP_LENGTH_3          (SIFLOWER_SYSCTL_BASE + 0x8454)
#define WIFI_2_IQ_GEN_LENGTH_0           (SIFLOWER_SYSCTL_BASE + 0x8458)
#define WIFI_2_IQ_GEN_LENGTH_1           (SIFLOWER_SYSCTL_BASE + 0x845C)
#define WIFI_2_IQ_GEN_LENGTH_2           (SIFLOWER_SYSCTL_BASE + 0x8460)
#define WIFI_2_IQ_GEN_LENGTH_3           (SIFLOWER_SYSCTL_BASE + 0x8464)
// wifi5G iq test engine
#define WIFI_2_IQ_ENGINE_RECORD_MODE     (SIFLOWER_SYSCTL_BASE + 0x3900)
#define WIFI_2_IQ_ENGINE_RECORD_TRIGGER  (SIFLOWER_SYSCTL_BASE + 0x3904)
#define WIFI_2_IQ_ENGINE_RECORD_DMAREQ   (SIFLOWER_SYSCTL_BASE + 0x3908)
#define WIFI_2_IQ_ENGINE_RECORD_DMAACK   (SIFLOWER_SYSCTL_BASE + 0x390C)
#define WIFI_2_IQ_ENGINE_RECORD_OFFSET_0 (SIFLOWER_SYSCTL_BASE + 0x3910)
#define WIFI_2_IQ_ENGINE_RECORD_OFFSET_1 (SIFLOWER_SYSCTL_BASE + 0x3914)
#define WIFI_2_IQ_ENGINE_RECORD_OFFSET_2 (SIFLOWER_SYSCTL_BASE + 0x3918)
#define WIFI_2_IQ_ENGINE_RECORD_OFFSET_3 (SIFLOWER_SYSCTL_BASE + 0x391C)
#define WIFI_2_IQ_ENGINE_RECORD_LENGTH_0 (SIFLOWER_SYSCTL_BASE + 0x3920)
#define WIFI_2_IQ_ENGINE_RECORD_LENGTH_1 (SIFLOWER_SYSCTL_BASE + 0x3924)
#define WIFI_2_IQ_ENGINE_RECORD_LENGTH_2 (SIFLOWER_SYSCTL_BASE + 0x3928)
#define WIFI_2_IQ_ENGINE_RECORD_LENGTH_3 (SIFLOWER_SYSCTL_BASE + 0x392C)
#define WIFI_2_IQ_ENGINE_RECORD_DMAADEAD (SIFLOWER_SYSCTL_BASE + 0x3930)

#define WIFI_2_IQ_ENGINE_PLAYER_MODE     (SIFLOWER_SYSCTL_BASE + 0x3B00)
#define WIFI_2_IQ_ENGINE_PLAYER_TRIGGER  (SIFLOWER_SYSCTL_BASE + 0x3B04)
#define WIFI_2_IQ_ENGINE_PLAYER_DMAREQ   (SIFLOWER_SYSCTL_BASE + 0x3B08)
#define WIFI_2_IQ_ENGINE_PLAYER_DMAACK   (SIFLOWER_SYSCTL_BASE + 0x3B0C)
#define WIFI_2_IQ_ENGINE_PLAYER_OFFSET_0 (SIFLOWER_SYSCTL_BASE + 0x3B10)
#define WIFI_2_IQ_ENGINE_PLAYER_OFFSET_1 (SIFLOWER_SYSCTL_BASE + 0x3B14)
#define WIFI_2_IQ_ENGINE_PLAYER_OFFSET_2 (SIFLOWER_SYSCTL_BASE + 0x3B18)
#define WIFI_2_IQ_ENGINE_PLAYER_OFFSET_3 (SIFLOWER_SYSCTL_BASE + 0x3B1C)
#define WIFI_2_IQ_ENGINE_PLAYER_LENGTH_0 (SIFLOWER_SYSCTL_BASE + 0x3B20)
#define WIFI_2_IQ_ENGINE_PLAYER_LENGTH_1 (SIFLOWER_SYSCTL_BASE + 0x3B24)
#define WIFI_2_IQ_ENGINE_PLAYER_LENGTH_2 (SIFLOWER_SYSCTL_BASE + 0x3B28)
#define WIFI_2_IQ_ENGINE_PLAYER_LENGTH_3 (SIFLOWER_SYSCTL_BASE + 0x3B2C)
#define WIFI_2_IQ_ENGINE_PLAYER_DMAADEAD (SIFLOWER_SYSCTL_BASE + 0x3B30)


//DMA
#define DMA_SYSM_RESET                   (SIFLOWER_SYSCTL_BASE + 0x2C6C)
#define DMA_SOFT_RESET                   (SIFLOWER_SYSCTL_BASE + 0x8800)
#define DMA_SOFT_CLK_EN                  (SIFLOWER_SYSCTL_BASE + 0x8804)
#define DMA_SOFT_BOE                     (SIFLOWER_SYSCTL_BASE + 0x880C)
#define DMA_BOOT_MANAGER_NS              (SIFLOWER_SYSCTL_BASE + 0x8840) //[0:0] Active High
#define DMA_BOOT_FROM_PC                 (SIFLOWER_SYSCTL_BASE + 0x8844) //[0:0] Active High
#define DMA_BOOT_IRQ_NS70                (SIFLOWER_SYSCTL_BASE + 0x8848) //[7:0] Active High
#define DMA_BOOT_IRQ_NS158               (SIFLOWER_SYSCTL_BASE + 0x884C) //[15:8] Active High
#define DMA_BOOT_IRQ_NS2316              (SIFLOWER_SYSCTL_BASE + 0x8850) //[23:16] Active High
#define DMA_BOOT_PERIPH_NS70             (SIFLOWER_SYSCTL_BASE + 0x8854) //[7:0] Active High
#define DMA_BOOT_PERIPH_NS158            (SIFLOWER_SYSCTL_BASE + 0x8858) //[15:8] Active High
#define DMA_BOOT_PERIPH_NS2316           (SIFLOWER_SYSCTL_BASE + 0x885C) //[23:16] Active High
#define DMA_BOOT_ADDR70                  (SIFLOWER_SYSCTL_BASE + 0x8860) //[7:0] Active High
#define DMA_BOOT_ADDR158                 (SIFLOWER_SYSCTL_BASE + 0x8864) //[15:8] Active High
#define DMA_BOOT_ADDR2316                (SIFLOWER_SYSCTL_BASE + 0x8868) //[23:16] Active High
#define DMA_BOOT_ADDR3124                (SIFLOWER_SYSCTL_BASE + 0x886C) //[31:24] Active High


//usb
#define USB_SYSM_RESET                   (SIFLOWER_SYSCTL_BASE + 0x2C8C)
#define USB_SOFT_RESET                   (SIFLOWER_SYSCTL_BASE + 0xC800)
#define USB_SOFT_CLK_EN                  (SIFLOWER_SYSCTL_BASE + 0xC804)
#define USB_SOFT_BOE                     (SIFLOWER_SYSCTL_BASE + 0xC80C)
#define USB_SLEEPM0                      (SIFLOWER_SYSCTL_BASE + 0xC844)
#define USB_DEBUG_EN                     (SIFLOWER_SYSCTL_BASE + 0xC88C)

//SDIO & EMMC
#define EMMC_SYSM_RESET                  (SIFLOWER_SYSCTL_BASE + 0x2C90)
#define EMMC_SOFT_RESET                  (SIFLOWER_SYSCTL_BASE + 0xCC00)
#define EMMC_SOFT_CLK_EN                 (SIFLOWER_SYSCTL_BASE + 0xCC04)
#define EMMC_SOFT_BOE                    (SIFLOWER_SYSCTL_BASE + 0xCC0C)

#define SDIO_SYSM_RESET                  (SIFLOWER_SYSCTL_BASE + 0x2C94)
#define SDIO_SOFT_RESET                  (SIFLOWER_SYSCTL_BASE + 0xD000)
#define SDIO_SOFT_CLK_EN                 (SIFLOWER_SYSCTL_BASE + 0xD004)
#define SDIO_SOFT_BOE                    (SIFLOWER_SYSCTL_BASE + 0xD00C)

//catena rf modem
#define CATIP_SYSM_RESET                 (SIFLOWER_SYSCTL_BASE + 0x2C98)
#define CATIP_SOFT_RESET                 (SIFLOWER_SYSCTL_BASE + 0xD400)
#define CATIP_SOFT_CLK_EN                (SIFLOWER_SYSCTL_BASE + 0xD404)
#define CATIP_SOFT_BOE                   (SIFLOWER_SYSCTL_BASE + 0xD40C)

//SATA
#define SATA_SYSM_RESET                  (SIFLOWER_SYSCTL_BASE + 0x2C68)
#define SATA_SOFT_RESET                  (SIFLOWER_SYSCTL_BASE + 0x8400)
#define SATA_SOFT_CLK_EN                 (SIFLOWER_SYSCTL_BASE + 0x8404)
#define SATA_SOFT_BOE                    (SIFLOWER_SYSCTL_BASE + 0x840C)
#define SATA_PHY_RESET                   (SIFLOWER_SYSCTL_BASE + 0x8440)
#define SATA_PHY_READY                   (SIFLOWER_SYSCTL_BASE + 0x8444)

//APB bus reset reg
#define PBUS_RESET                       (SIFLOWER_SYSCTL_BASE + 0x2DC4)
#define PBUS_SYSM_RESET                  (SIFLOWER_SYSCTL_BASE + 0x2C38)

//apb modules manager
#define IIS_SYSM_RESET                   (SIFLOWER_SYSCTL_BASE + 0x02D44)
#define IIS_SOFT_RESET                   (SIFLOWER_SYSCTL_BASE + 0x24000)
#define IIS_SOFT_CLK_EN                  (SIFLOWER_SYSCTL_BASE + 0x24004)
#define IIS_SOFT_BOE                     (SIFLOWER_SYSCTL_BASE + 0x2400C)

#define IIC_SYSM_RESET                   (SIFLOWER_SYSCTL_BASE + 0x02D48)
#define IIC_SOFT_RESET                   (SIFLOWER_SYSCTL_BASE + 0x24400)
#define IIC_SOFT_CLK_EN                  (SIFLOWER_SYSCTL_BASE + 0x24404)
#define IIC_SOFT_BOE                     (SIFLOWER_SYSCTL_BASE + 0x2440C)

#define SPI_SYSM_RESET                   (SIFLOWER_SYSCTL_BASE + 0x02D4C)
#define SPI_SOFT_RESET                   (SIFLOWER_SYSCTL_BASE + 0x24800)
#define SPI_SOFT_CLK_EN                  (SIFLOWER_SYSCTL_BASE + 0x24804)
#define SPI_SOFT_BOE                     (SIFLOWER_SYSCTL_BASE + 0x2480C)
#define SPI0_CS_SEL	                     (SIFLOWER_SYSCTL_BASE + 0x24840)
#define SSP_FSSOUT_NTXDOE_SEL            (SIFLOWER_SYSCTL_BASE + 0x24844)

#define UART_SYSM_RESET                  (SIFLOWER_SYSCTL_BASE + 0x02D50)
#define UART_SOFT_RESET                  (SIFLOWER_SYSCTL_BASE + 0x24C00)
#define UART_SOFT_CLK_EN                 (SIFLOWER_SYSCTL_BASE + 0x24C04)
#define UART_SOFT_BOE                    (SIFLOWER_SYSCTL_BASE + 0x24C0C)

#define PCM_SYSM_RESET                   (SIFLOWER_SYSCTL_BASE + 0x02D54)
#define PCM_SOFT_RESET                   (SIFLOWER_SYSCTL_BASE + 0x25000)
#define PCM_SOFT_CLK_EN                  (SIFLOWER_SYSCTL_BASE + 0x25004)
#define PCM_SOFT_BOE                     (SIFLOWER_SYSCTL_BASE + 0x2500C)

#define PWM_SYSM_RESET                   (SIFLOWER_SYSCTL_BASE + 0x02D58)
#define PWM_SOFT_RESET                   (SIFLOWER_SYSCTL_BASE + 0x25400)
#define PWM_SOFT_CLK_EN                  (SIFLOWER_SYSCTL_BASE + 0x25404)
#define PWM_SOFT_BOE                     (SIFLOWER_SYSCTL_BASE + 0x2540C)

#define TIMER_SYSM_RESET                 (SIFLOWER_SYSCTL_BASE + 0x02D5C)
#define TIMER_SOFT_RESET                 (SIFLOWER_SYSCTL_BASE + 0x25800)
#define TIMER_SOFT_CLK_EN                (SIFLOWER_SYSCTL_BASE + 0x25804)
#define TIMER_SOFT_BOE                   (SIFLOWER_SYSCTL_BASE + 0x2580C)

#define WDT_SYSM_RESET                   (SIFLOWER_SYSCTL_BASE + 0x02D60)
#define WDT_SOFT_RESET                   (SIFLOWER_SYSCTL_BASE + 0x25C00)
#define WDT_SOFT_CLK_EN                  (SIFLOWER_SYSCTL_BASE + 0x25C04)
#define WDT_SOFT_BOE                     (SIFLOWER_SYSCTL_BASE + 0x25C0C)

#define SPDIF_SYSM_RESET                 (SIFLOWER_SYSCTL_BASE + 0x02D64)
#define SPDIF_SOFT_RESET                 (SIFLOWER_SYSCTL_BASE + 0x26000)
#define SPDIF_SOFT_CLK_EN                (SIFLOWER_SYSCTL_BASE + 0x26004)
#define SPDIF_SOFT_BOE                   (SIFLOWER_SYSCTL_BASE + 0x2600C)

#define GPIO_SYSM_RESET                  (SIFLOWER_SYSCTL_BASE + 0x02DB8)
#define GPIO_SOFT_RESET                  (SIFLOWER_SYSCTL_BASE + 0x2B400)
#define GPIO_SOFT_CLK_EN                 (SIFLOWER_SYSCTL_BASE + 0x2B404)
#define GPIO_SOFT_BOE                    (SIFLOWER_SYSCTL_BASE + 0x2B40C)

#define PAD_SW_IE_EN                     (SIFLOWER_SYSCTL_BASE + 0x3FEA0)


/*****************************************************************************************
*                                                                                        *
*  SF Clock System Manager                                                               *
*                                                                                        *
******************************************************************************************/

/***********************************************************************************************

XXX_PLL_POWER  power down signals for PLL
bit[5]:int_dsmpd
bit[4]:int_dacpd
bit[3]:int_fout4phased
bit[2]:int_foutpostdivpd
bit[1]:int_foutvcopd
bit[0]:int_pd

XXX_PLL_PARA70 bit7--bit0 parameter signals for PLL

XXX_PLL_CONFIG
bit[5]: load enable signal for int_pll_para
bit[4]: clock gating signal for pll_clk_out
bit[3]: select clock signal from pll_clk_out and reference clock
bit[2:1] 00 : reference clock = ext_osc_clk_12MHz 01 : reference clock = ext_osc_clk_40MHz
         10 : reference clock = ext_clk 11 : reference clock = ext_clk
bit[0]: bypass signal for PLL

************************************************************************************************/

#define CPU_PLL_POWER             (SIFLOWER_SYSCTL_BASE + 0x1000)
#define CPU_PLL_PARA70            (SIFLOWER_SYSCTL_BASE + 0x1004)
#define CPU_PLL_PARA158           (SIFLOWER_SYSCTL_BASE + 0x1008)
#define CPU_PLL_PARA2316          (SIFLOWER_SYSCTL_BASE + 0x100C)
#define CPU_PLL_PARA3124          (SIFLOWER_SYSCTL_BASE + 0x1010)
#define CPU_PLL_PARA3932          (SIFLOWER_SYSCTL_BASE + 0x1014)
#define CPU_PLL_PARA4740          (SIFLOWER_SYSCTL_BASE + 0x1018)
#define CPU_PLL_CONFIG            (SIFLOWER_SYSCTL_BASE + 0x101C)

#define DDR_PLL_POWER             (SIFLOWER_SYSCTL_BASE + 0x1040)
#define DDR_PLL_PARA70            (SIFLOWER_SYSCTL_BASE + 0x1044)
#define DDR_PLL_PARA158           (SIFLOWER_SYSCTL_BASE + 0x1048)
#define DDR_PLL_PARA2316          (SIFLOWER_SYSCTL_BASE + 0x104C)
#define DDR_PLL_PARA3124          (SIFLOWER_SYSCTL_BASE + 0x1050)
#define DDR_PLL_PARA3932          (SIFLOWER_SYSCTL_BASE + 0x1054)
#define DDR_PLL_PARA4740          (SIFLOWER_SYSCTL_BASE + 0x1058)
#define DDR_PLL_CONFIG            (SIFLOWER_SYSCTL_BASE + 0x105C)

#define CMN_PLL_POWER             (SIFLOWER_SYSCTL_BASE + 0x1080)
#define CMN_PLL_PARA70            (SIFLOWER_SYSCTL_BASE + 0x1084)
#define CMN_PLL_PARA158           (SIFLOWER_SYSCTL_BASE + 0x1088)
#define CMN_PLL_PARA2316          (SIFLOWER_SYSCTL_BASE + 0x108C)
#define CMN_PLL_PARA3124          (SIFLOWER_SYSCTL_BASE + 0x1090)
#define CMN_PLL_PARA3932          (SIFLOWER_SYSCTL_BASE + 0x1094)
#define CMN_PLL_PARA4740          (SIFLOWER_SYSCTL_BASE + 0x1098)
#define CMN_PLL_CONFIG            (SIFLOWER_SYSCTL_BASE + 0x109C)

#define SPC_PLL_POWER             (SIFLOWER_SYSCTL_BASE + 0x10C0)
#define SPC_PLL_PARA70            (SIFLOWER_SYSCTL_BASE + 0x10C4)
#define SPC_PLL_PARA158           (SIFLOWER_SYSCTL_BASE + 0x10C8)
#define SPC_PLL_PARA2316          (SIFLOWER_SYSCTL_BASE + 0x10CC)
#define SPC_PLL_PARA3124          (SIFLOWER_SYSCTL_BASE + 0x10D0)
#define SPC_PLL_PARA3932          (SIFLOWER_SYSCTL_BASE + 0x10D4)
#define SPC_PLL_PARA4740          (SIFLOWER_SYSCTL_BASE + 0x10D8)
#define SPC_PLL_CONFIG            (SIFLOWER_SYSCTL_BASE + 0x10DC)


/***************************************************************************************************************

XXX_XN_CLK_CONFIG
use_nco[3] 0 : clk_out = div_clk 1 : clk_out = nco_div_clk
src_sel[2:0] 000 : mux_clk_s2 = pll_cpu_clk 001 : mux_clk_s2 = pll_ddr_clk 010 : mux_clk_s2 = pll_cmn_clk
             011 : mux_clk_s2 = pll_spc_clk 100 : mux_clk_s2 = ext_clk 101 : mux_clk_s2 = ext_osc_clk_12MHz
             110 : mux_clk_s2 = ext_osc_clk_40MHz 111 : mux_clk_s2 = 0

XXX_XN_CLK_DIV
clk_ratio[7:0] clock ratio for div_clk from mux_clk_s2

XXX_XN_CLK_NCO_DIV
clk_nco_v[7:0] acc value for nco_div_clk from mux_clk_s2

XXX_XN_CLK_ENABLE
clock_enable[0:0] clock enable for both clk_out and xn_div_clk_out

XXX_XN_CLK_XN_DIV
xn_div_clk_ratio[1:0] clock ratio for xn_div_clk_out from clk_out

******************************************************************************************************************/

#define BUS1_XN_CLK_CONFIG        (SIFLOWER_SYSCTL_BASE + 0x1400)
#define BUS1_XN_CLK_DIV           (SIFLOWER_SYSCTL_BASE + 0x1404)
#define BUS1_XN_CLK_NCO_DIV       (SIFLOWER_SYSCTL_BASE + 0x1408)
#define BUS1_XN_CLK_ENABLE        (SIFLOWER_SYSCTL_BASE + 0x140C)
#define BUS1_XN_CLK_XN_DIV        (SIFLOWER_SYSCTL_BASE + 0x1410)

#define BUS2_XN_CLK_CONFIG        (SIFLOWER_SYSCTL_BASE + 0x1420)
#define BUS2_XN_CLK_DIV           (SIFLOWER_SYSCTL_BASE + 0x1424)
#define BUS2_XN_CLK_NCO_DIV       (SIFLOWER_SYSCTL_BASE + 0x1428)
#define BUS2_XN_CLK_ENABLE        (SIFLOWER_SYSCTL_BASE + 0x142C)
#define BUS2_XN_CLK_XN_DIV        (SIFLOWER_SYSCTL_BASE + 0x1430)

#define BUS3_XN_CLK_CONFIG        (SIFLOWER_SYSCTL_BASE + 0x1440)
#define BUS3_XN_CLK_DIV           (SIFLOWER_SYSCTL_BASE + 0x1444)
#define BUS3_XN_CLK_NCO_DIV       (SIFLOWER_SYSCTL_BASE + 0x1448)
#define BUS3_XN_CLK_ENABLE        (SIFLOWER_SYSCTL_BASE + 0x144C)
#define BUS3_XN_CLK_XN_DIV        (SIFLOWER_SYSCTL_BASE + 0x1450)

#define BUS4_XN_CLK_CONFIG        (SIFLOWER_SYSCTL_BASE + 0x1460)
#define BUS4_XN_CLK_DIV           (SIFLOWER_SYSCTL_BASE + 0x1464)
#define BUS4_XN_CLK_NCO_DIV       (SIFLOWER_SYSCTL_BASE + 0x1468)
#define BUS4_XN_CLK_ENABLE        (SIFLOWER_SYSCTL_BASE + 0x146C)
#define BUS4_XN_CLK_XN_DIV        (SIFLOWER_SYSCTL_BASE + 0x1470)

#define BUS5_XN_CLK_CONFIG        (SIFLOWER_SYSCTL_BASE + 0x1480)
#define BUS5_XN_CLK_DIV           (SIFLOWER_SYSCTL_BASE + 0x1484)
#define BUS5_XN_CLK_NCO_DIV       (SIFLOWER_SYSCTL_BASE + 0x1488)
#define BUS5_XN_CLK_ENABLE        (SIFLOWER_SYSCTL_BASE + 0x148C)
#define BUS5_XN_CLK_XN_DIV        (SIFLOWER_SYSCTL_BASE + 0x1490)

#define BUS6_XN_CLK_CONFIG        (SIFLOWER_SYSCTL_BASE + 0x14A0)
#define BUS6_XN_CLK_DIV           (SIFLOWER_SYSCTL_BASE + 0x14A4)
#define BUS6_XN_CLK_NCO_DIV       (SIFLOWER_SYSCTL_BASE + 0x14A8)
#define BUS6_XN_CLK_ENABLE        (SIFLOWER_SYSCTL_BASE + 0x14AC)
#define BUS6_XN_CLK_XN_DIV        (SIFLOWER_SYSCTL_BASE + 0x14B0)

#define BUS7_XN_CLK_CONFIG        (SIFLOWER_SYSCTL_BASE + 0x14C0)
#define BUS7_XN_CLK_DIV           (SIFLOWER_SYSCTL_BASE + 0x14C4)
#define BUS7_XN_CLK_NCO_DIV       (SIFLOWER_SYSCTL_BASE + 0x14C8)
#define BUS7_XN_CLK_ENABLE        (SIFLOWER_SYSCTL_BASE + 0x14CC)
#define BUS7_XN_CLK_XN_DIV        (SIFLOWER_SYSCTL_BASE + 0x14D0)

#define BUS8_XN_CLK_CONFIG        (SIFLOWER_SYSCTL_BASE + 0x14E0)
#define BUS8_XN_CLK_DIV           (SIFLOWER_SYSCTL_BASE + 0x14E4)
#define BUS8_XN_CLK_NCO_DIV       (SIFLOWER_SYSCTL_BASE + 0x14E8)
#define BUS8_XN_CLK_ENABLE        (SIFLOWER_SYSCTL_BASE + 0x14EC)
#define BUS8_XN_CLK_XN_DIV        (SIFLOWER_SYSCTL_BASE + 0x14F0)

#define CPU_CLK_CONFIG            (SIFLOWER_SYSCTL_BASE + 0x1500)
#define CPU_CLK_DIV               (SIFLOWER_SYSCTL_BASE + 0x1504)
#define CPU_CLK_NCO_DIV           (SIFLOWER_SYSCTL_BASE + 0x1508)
#define CPU_CLK_ENABLE            (SIFLOWER_SYSCTL_BASE + 0x150C)
#define CPU_CLK_XN_DIV            (SIFLOWER_SYSCTL_BASE + 0x1510)

#define PBUS_CLK_CONFIG           (SIFLOWER_SYSCTL_BASE + 0x1520)
#define PBUS_CLK_DIV              (SIFLOWER_SYSCTL_BASE + 0x1524)
#define PBUS_CLK_NCO_DIV          (SIFLOWER_SYSCTL_BASE + 0x1528)
#define PBUS_CLK_ENABLE           (SIFLOWER_SYSCTL_BASE + 0x152C)
#define PBUS_CLK_XN_DIV           (SIFLOWER_SYSCTL_BASE + 0x1530)

#define MEM_PHY_CLK_CONFIG        (SIFLOWER_SYSCTL_BASE + 0x1540)
#define MEM_PHY_CLK_DIV           (SIFLOWER_SYSCTL_BASE + 0x1544)
#define MEM_PHY_CLK_NCO_DIV       (SIFLOWER_SYSCTL_BASE + 0x1548)
#define MEM_PHY_CLK_ENABLE        (SIFLOWER_SYSCTL_BASE + 0x154C)
#define MEM_PHY_CLK_XN_DIV        (SIFLOWER_SYSCTL_BASE + 0x1550)

#define AUDIO_EXTCLK_CONFIG       (SIFLOWER_SYSCTL_BASE + 0x1560)
#define AUDIO_EXTCLK_DIV          (SIFLOWER_SYSCTL_BASE + 0x1564)
#define AUDIO_EXTCLK_NCO_DIV      (SIFLOWER_SYSCTL_BASE + 0x1568)
#define AUDIO_EXTCLK_ENABLE       (SIFLOWER_SYSCTL_BASE + 0x156C)
#define AUDIO_EXTCLK_XN_DIV       (SIFLOWER_SYSCTL_BASE + 0x1570)

#define UART_EXTCLK_CONFIG        (SIFLOWER_SYSCTL_BASE + 0x1580)
#define UART_EXTCLK_DIV           (SIFLOWER_SYSCTL_BASE + 0x1584)
#define UART_EXTCLK_NCO_DIV       (SIFLOWER_SYSCTL_BASE + 0x1588)
#define UART_EXTCLK_ENABLE        (SIFLOWER_SYSCTL_BASE + 0x158C)
#define UART_EXTCLK_XN_DIV        (SIFLOWER_SYSCTL_BASE + 0x1590)

#define SPDIF_EXTCLK_CONFIG       (SIFLOWER_SYSCTL_BASE + 0x15A0)
#define SPDIF_EXTCLK_DIV          (SIFLOWER_SYSCTL_BASE + 0x15A4)
#define SPDIF_EXTCLK_NCO_DIV      (SIFLOWER_SYSCTL_BASE + 0x15A8)
#define SPDIF_EXTCLK_ENABLE       (SIFLOWER_SYSCTL_BASE + 0x15AC)
#define SPDIF_EXTCLK_XN_DIV       (SIFLOWER_SYSCTL_BASE + 0x15B0)

#define SDHC_EXT_CLK_CONFIG       (SIFLOWER_SYSCTL_BASE + 0x15C0)
#define SDHC_EXT_CLK_DIV          (SIFLOWER_SYSCTL_BASE + 0x15C4)
#define SDHC_EXT_CLK_NCO_DIV      (SIFLOWER_SYSCTL_BASE + 0x15C8)
#define SDHC_EXT_CLK_ENABLE       (SIFLOWER_SYSCTL_BASE + 0x15CC)
#define SDHC_EXT_CLK_XN_DIV       (SIFLOWER_SYSCTL_BASE + 0x15D0)

#define EMMC_EXT_CLK_CONFIG       (SIFLOWER_SYSCTL_BASE + 0x15E0)
#define EMMC_EXT_CLK_DIV          (SIFLOWER_SYSCTL_BASE + 0x15E4)
#define EMMC_EXT_CLK_NCO_DIV      (SIFLOWER_SYSCTL_BASE + 0x15E8)
#define EMMC_EXT_CLK_ENABLE       (SIFLOWER_SYSCTL_BASE + 0x15EC)
#define EMMC_EXT_CLK_XN_DIV       (SIFLOWER_SYSCTL_BASE + 0x15F0)

#define ETH_REF_CLK_CONFIG        (SIFLOWER_SYSCTL_BASE + 0x1600)
#define ETH_REF_CLK_DIV           (SIFLOWER_SYSCTL_BASE + 0x1604)
#define ETH_REF_CLK_NCO_DIV       (SIFLOWER_SYSCTL_BASE + 0x1608)
#define ETH_REF_CLK_ENABLE        (SIFLOWER_SYSCTL_BASE + 0x160C)
#define ETH_REF_CLK_XN_DIV        (SIFLOWER_SYSCTL_BASE + 0x1610)

#define ETH_BYP_REF_CLK_CONFIG    (SIFLOWER_SYSCTL_BASE + 0x1620)
#define ETH_BYP_REF_CLK_DIV       (SIFLOWER_SYSCTL_BASE + 0x1624)
#define ETH_BYP_REF_CLK_NCO_DIV   (SIFLOWER_SYSCTL_BASE + 0x1628)
#define ETH_BYP_REF_CLK_ENABLE    (SIFLOWER_SYSCTL_BASE + 0x162C)
#define ETH_BYP_REF_CLK_XN_DIV    (SIFLOWER_SYSCTL_BASE + 0x1630)

#define ETH_TSU_CLK_CONFIG        (SIFLOWER_SYSCTL_BASE + 0x1640)
#define ETH_TSU_CLK_DIV           (SIFLOWER_SYSCTL_BASE + 0x1644)
#define ETH_TSU_CLK_NCO_DIV       (SIFLOWER_SYSCTL_BASE + 0x1648)
#define ETH_TSU_CLK_ENABLE        (SIFLOWER_SYSCTL_BASE + 0x164C)
#define ETH_TSU_CLK_XN_DIV        (SIFLOWER_SYSCTL_BASE + 0x1650)

#define COMBO_REF_CLK_CONFIG      (SIFLOWER_SYSCTL_BASE + 0x1660)
#define COMBO_REF_CLK_DIV         (SIFLOWER_SYSCTL_BASE + 0x1664)
#define COMBO_REF_CLK_NCO_DIV     (SIFLOWER_SYSCTL_BASE + 0x1668)
#define COMBO_REF_CLK_ENABLE      (SIFLOWER_SYSCTL_BASE + 0x166C)
#define COMBO_REF_CLK_XN_DIV      (SIFLOWER_SYSCTL_BASE + 0x1670)

#define PCIE_AUX_CLK_CONFIG       (SIFLOWER_SYSCTL_BASE + 0x1680)
#define PCIE_AUX_CLK_DIV          (SIFLOWER_SYSCTL_BASE + 0x1684)
#define PCIE_AUX_CLK_NCO_DIV      (SIFLOWER_SYSCTL_BASE + 0x1688)
#define PCIE_AUX_CLK_ENABLE       (SIFLOWER_SYSCTL_BASE + 0x168C)
#define PCIE_AUX_CLK_XN_DIV       (SIFLOWER_SYSCTL_BASE + 0x1690)

#define SATA_PMALIVE_CLK_CONFIG   (SIFLOWER_SYSCTL_BASE + 0x16A0)
#define SATA_PMALIVE_CLK_DIV      (SIFLOWER_SYSCTL_BASE + 0x16A4)
#define SATA_PMALIVE_CLK_NCO_DIV  (SIFLOWER_SYSCTL_BASE + 0x16A8)
#define SATA_PMALIVE_CLK_ENABLE   (SIFLOWER_SYSCTL_BASE + 0x16AC)
#define SATA_PMALIVE_CLK_XN_DIV   (SIFLOWER_SYSCTL_BASE + 0x16B0)

#define WLAN24_MAC_WT_CLK_CONFIG  (SIFLOWER_SYSCTL_BASE + 0x16C0)
#define WLAN24_MAC_WT_CLK_DIV     (SIFLOWER_SYSCTL_BASE + 0x16C4)
#define WLAN24_MAC_WT_CLK_NCO_DIV (SIFLOWER_SYSCTL_BASE + 0x16C8)
#define WLAN24_MAC_WT_CLK_ENABLE  (SIFLOWER_SYSCTL_BASE + 0x16CC)
#define WLAN24_MAC_WT_CLK_XN_DIV  (SIFLOWER_SYSCTL_BASE + 0x16D0)

#define WLAN5_MAC_WT_CLK_CONFIG   (SIFLOWER_SYSCTL_BASE + 0x16E0)
#define WLAN5_MAC_WT_CLK_DIV      (SIFLOWER_SYSCTL_BASE + 0x16E4)
#define WLAN5_MAC_WT_CLK_NCO_DIV  (SIFLOWER_SYSCTL_BASE + 0x16E8)
#define WLAN5_MAC_WT_CLK_ENABLE   (SIFLOWER_SYSCTL_BASE + 0x16EC)
#define WLAN5_MAC_WT_CLK_XN_DIV   (SIFLOWER_SYSCTL_BASE + 0x16F0)

#define USBPHY_REF_CLK_CONFIG     (SIFLOWER_SYSCTL_BASE + 0x1700)
#define USBPHY_REF_CLK_DIV        (SIFLOWER_SYSCTL_BASE + 0x1704)
#define USBPHY_REF_CLK_NCO_DIV    (SIFLOWER_SYSCTL_BASE + 0x1708)
#define USBPHY_REF_CLK_ENABLE     (SIFLOWER_SYSCTL_BASE + 0x170C)
#define USBPHY_REF_CLK_XN_DIV     (SIFLOWER_SYSCTL_BASE + 0x1710)

#define TCLK_CONFIG               (SIFLOWER_SYSCTL_BASE + 0x1720)
#define TCLK_DIV                  (SIFLOWER_SYSCTL_BASE + 0x1724)
#define TCLK_NCO_DIV              (SIFLOWER_SYSCTL_BASE + 0x1728)
#define TCLK_ENABLE               (SIFLOWER_SYSCTL_BASE + 0x172C)
#define TCLK_XN_DIV               (SIFLOWER_SYSCTL_BASE + 0x1730)

#endif // __SIFLOWER_MMAP__
