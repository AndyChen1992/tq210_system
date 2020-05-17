/*
 *  Copyright (C) 2008-2009 Samsung Electronics
 *  Minkyu Kang <mk7.kang@samsung.com>
 *  Kyungmin Park <kyungmin.park@samsung.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/gpio.h>
#include <asm/arch/mmc.h>
#include <power/pmic.h>
#include <usb/s3c_udc.h>
#include <asm/arch/cpu.h>
#include <power/max8998_pmic.h>
#include <samsung/misc.h>
#include <usb.h>
#include <usb_mass_storage.h>
#include <asm/arch/clock.h>	
#include <asm/arch/cpu.h>


/* Uart regs */
#define GPA0CON		*((volatile unsigned int *)0xE0200000)
#define ULCON0 		*((volatile unsigned int *)0xE2900000)
#define UCON0 		*((volatile unsigned int *)0xE2900004)
#define UFCON0 		*((volatile unsigned int *)0xE2900008)
#define UTRSTAT0 	*((volatile unsigned int *)0xE2900010)
#define UTXH0  		*((volatile unsigned int *)0xE2900020)
#define URXH0 		*((volatile unsigned int *)0xE2900024)
#define UBRDIV0 	*((volatile unsigned int *)0xE2900028)
#define UDIVSLOT0	*((volatile unsigned int *)0xE290002C)

/* GPIO regs of led1 and led2 */
#define GPC0CON		*((volatile unsigned int *)0xE0200060)
#define GPC0DAT		*((volatile unsigned int *)0xE0200064)

struct s5pv210_dmc0 {
        unsigned int    concontrol;
        unsigned int    memcontrol;
        unsigned int    memconfig0;
        unsigned int    memconfig1;
        unsigned int    directcmd;
        unsigned int    prechconfig;
        unsigned int    phycontrol0;
        unsigned int    phycontrol1;
        unsigned char   res1[0x08];
        unsigned int    pwrdnconfig;
        unsigned char   res2[0x04];
        unsigned int    timingaref;
        unsigned int    timingrow;
        unsigned int    timingdata;
        unsigned int    timingpower;
        unsigned int    phystatus;
        unsigned int    chip0status;
        unsigned int    chip1status;
        unsigned int    arefstatus;
        unsigned int    mrstatus;
        unsigned int    phytest0;
        unsigned int    phytest1;
};

struct s5pv210_dmc1 {
        unsigned int    concontrol;
        unsigned int    memcontrol;
        unsigned int    memconfig0;
        unsigned int    memconfig1;
        unsigned int    directcmd;
        unsigned int    prechconfig;
        unsigned int    phycontrol0;
        unsigned int    phycontrol1;
        unsigned char   res1[0x08];
        unsigned int    pwrdnconfig;
        unsigned char   res2[0x04];
        unsigned int    timingaref;
        unsigned int    timingrow;
        unsigned int    timingdata;
        unsigned int    timingpower;
        unsigned int    phystatus;
        unsigned int    chip0status;
        unsigned int    chip1status;
        unsigned int    arefstatus;
        unsigned int    mrstatus;
        unsigned int    phytest0;
        unsigned int    phytest1;
};

void led1_on(void)
{
	GPC0CON = 1<<12;
	GPC0DAT = 1<<3;
}

void led2_on(void)
{
	GPC0CON |= 1<<16;
	GPC0DAT |= 1<<4;
}

/* UART0初始化 */
void uart_init(void)
{
	/*
	** 配置GPA0_0为UART_0_RXD
	** 配置GPA0_1为UART_0_TXD
	*/
	GPA0CON &= ~0xFF;
	GPA0CON |= 0x22;

	/* 8-bits/One stop bit/No parity/Normal mode operation */
	ULCON0 = 0x3 | (0 << 2) | (0 << 3) | (0 << 6);

	/* Interrupt request or polling mode/Normal transmit/Normal operation/PCLK/*/
	UCON0 = 1 | (1 << 2) | (0 << 10);

	/* 静止FIFO */
	UFCON0 = 0;

	/*
	** 波特率计算：115200bps
	** PCLK = 66MHz
	** DIV_VAL = (66000000/(115200 x 16))-1 = 35.8 - 1 = 34.8
	** UBRDIV0 = 34(DIV_VAL的整数部分)
	** (num of 1's in UDIVSLOTn)/16 = 0.8
	** (num of 1's in UDIVSLOTn) = 12
	** UDIVSLOT0 = 0xDDDD (查表)
	*/
	UBRDIV0 = 34;
	UDIVSLOT0 = 0xDDDD;
}

static void uart_send_byte(unsigned char byte)
{
	while (!(UTRSTAT0 & (1 << 2)));	/* 等待发送缓冲区为空 */
	UTXH0 = byte;					/* 发送一字节数据 */		
}

void my_putchar(int c)
{
	uart_send_byte(c);
	/* 如果只写'\n'，只是换行，而不会跳到下一行开头 */
	if (c == '\n')
		uart_send_byte('\r');
}

void print_str(char *str)
{
	char *p = str;
	while (*p)
		my_putchar(*p++);
	my_putchar('\n');
}

#ifndef CONFIG_SPL_BUILD
DECLARE_GLOBAL_DATA_PTR;

u32 get_board_rev(void)
{
	return 0;
}

int board_init(void)
{
	/* Set Initial global variables */
	gd->bd->bi_arch_number = MACH_TYPE_GONI;
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;

	return 0;
}

#ifdef CONFIG_SYS_I2C_INIT_BOARD
void i2c_init_board(void)
{
	gpio_request(S5PC110_GPIO_J43, "i2c_clk");
	gpio_request(S5PC110_GPIO_J40, "i2c_data");
	gpio_direction_output(S5PC110_GPIO_J43, 1);
	gpio_direction_output(S5PC110_GPIO_J40, 1);
}
#endif

#if 0
int power_init_board(void)
{
	int ret;

	/*
	 * For PMIC the I2C bus is named as I2C5, but it is connected
	 * to logical I2C adapter 0
	 */
	ret = pmic_init(I2C_0);
	if (ret)
		return ret;

	return 0;
}
#endif

int dram_init(void)
{
	gd->ram_size = PHYS_SDRAM_1_SIZE;

	return 0;
}

void dram_init_banksize(void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
	
#ifdef 	defined(PHYS_SDRAM_2) && defined(PHYS_SDRAM_2_SIZE)
	gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
	gd->bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;
#endif	
}

#ifdef CONFIG_DISPLAY_BOARDINFO
int checkboard(void)
{
	puts("Board:\tGoni\n");
	return 0;
}
#endif

#ifdef CONFIG_GENERIC_MMC
int board_mmc_init(bd_t *bis)
{
	int i, ret, ret_sd = 0;

	/* MASSMEMORY_EN: XMSMDATA7: GPJ2[7] output high */
	gpio_request(S5PC110_GPIO_J27, "massmemory_en");
	gpio_direction_output(S5PC110_GPIO_J27, 1);

	/*
	 * MMC0 GPIO
	 * GPG0[0]	SD_0_CLK
	 * GPG0[1]	SD_0_CMD
	 * GPG0[2]	SD_0_CDn	-> Not used
	 * GPG0[3:6]	SD_0_DATA[0:3]
	 */
	for (i = S5PC110_GPIO_G00; i < S5PC110_GPIO_G07; i++) {
		if (i == S5PC110_GPIO_G02)
			continue;
		/* GPG0[0:6] special function 2 */
		gpio_cfg_pin(i, 0x2);
		/* GPG0[0:6] pull disable */
		gpio_set_pull(i, S5P_GPIO_PULL_NONE);
		/* GPG0[0:6] drv 4x */
		gpio_set_drv(i, S5P_GPIO_DRV_4X);
	}

	ret = s5p_mmc_init(0, 4);
	if (ret)
		error("MMC: Failed to init MMC:0.\n");

	/*
	 * SD card (T_FLASH) detect and init
	 * T_FLASH_DETECT: EINT28: GPH3[4] input mode
	 */
	gpio_request(S5PC110_GPIO_H34, "t_flash_detect");
	gpio_cfg_pin(S5PC110_GPIO_H34, S5P_GPIO_INPUT);
	gpio_set_pull(S5PC110_GPIO_H34, S5P_GPIO_PULL_UP);

	if (!gpio_get_value(S5PC110_GPIO_H34)) {
		for (i = S5PC110_GPIO_G20; i < S5PC110_GPIO_G27; i++) {
			if (i == S5PC110_GPIO_G22)
				continue;

			/* GPG2[0:6] special function 2 */
			gpio_cfg_pin(i, 0x2);
			/* GPG2[0:6] pull disable */
			gpio_set_pull(i, S5P_GPIO_PULL_NONE);
			/* GPG2[0:6] drv 4x */
			gpio_set_drv(i, S5P_GPIO_DRV_4X);
		}

		ret_sd = s5p_mmc_init(2, 4);
		if (ret_sd)
			error("MMC: Failed to init SD card (MMC:2).\n");
	}

	return ret & ret_sd;
}
#endif

#ifdef CONFIG_USB_GADGET
static int s5pc1xx_phy_control(int on)
{
	int ret;
	static int status;
	struct pmic *p = pmic_get("MAX8998_PMIC");
	if (!p)
		return -ENODEV;

	if (pmic_probe(p))
		return -1;

	if (on && !status) {
		ret = pmic_set_output(p, MAX8998_REG_ONOFF1,
				      MAX8998_LDO3, LDO_ON);
		ret = pmic_set_output(p, MAX8998_REG_ONOFF2,
				      MAX8998_LDO8, LDO_ON);
		if (ret) {
			puts("MAX8998 LDO setting error!\n");
			return -1;
		}
		status = 1;
	} else if (!on && status) {
		ret = pmic_set_output(p, MAX8998_REG_ONOFF1,
				      MAX8998_LDO3, LDO_OFF);
		ret = pmic_set_output(p, MAX8998_REG_ONOFF2,
				      MAX8998_LDO8, LDO_OFF);
		if (ret) {
			puts("MAX8998 LDO setting error!\n");
			return -1;
		}
		status = 0;
	}
	udelay(10000);

	return 0;
}

struct s3c_plat_otg_data s5pc110_otg_data = {
	.phy_control = s5pc1xx_phy_control,
	.regs_phy = S5PC110_PHY_BASE,
	.regs_otg = S5PC110_OTG_BASE,
	.usb_phy_ctrl = S5PC110_USB_PHY_CONTROL,
};

int board_usb_init(int index, enum usb_init_type init)
{
	debug("USB_udc_probe\n");
	return s3c_udc_probe(&s5pc110_otg_data);
}
#endif

#ifdef CONFIG_MISC_INIT_R
int misc_init_r(void)
{
#ifdef CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG
	set_board_info();
#endif
	return 0;
}
#endif

#else /* CONFIG_SPL_BUILD */
void clock_init(void)
{	
	u32 val = 0;
	
	struct s5pv210_clock *const clock = (struct s5pv210_clock *)samsung_get_base_clock();
	
	/* 1.设置PLL锁定值 */
	writel(0xFFFF, &clock->apll_lock);
	writel(0xFFFF, &clock->mpll_lock);
	writel(0xFFFF, &clock->epll_lock);
	writel(0xFFFF, &clock->vpll_lock);
	
	/* 2.设置PLL的PMS值(使用芯片手册推荐的值)，并使能PLL */
	/*	 	P	  	    M   		  S		     EN	*/
	writel((3  << 8) | (125 << 16) | (1 << 0) | (1 << 31), &clock->apll_con0);	/* FOUT_APLL = 1000MHz */
	writel((12 << 8) | (667 << 16) | (1 << 0) | (1 << 31), &clock->mpll_con); 	/* FOUT_MPLL = 667MHz */
	writel((3  << 8) | (48  << 16) | (2 << 0) | (1 << 31), &clock->epll_con0);	/* FOUT_EPLL = 96MHz */
	writel((6  << 8) | (108 << 16) | (3 << 0) | (1 << 31), &clock->vpll_con);	/* FOUT_VPLL = 54MHz */
	
	/* 3.等待PLL锁定 */
	while (!(readl(&clock->apll_con0) & (1 << 29)));
	while (!(readl(&clock->mpll_con) & (1 << 29)));
	while (!(readl(&clock->apll_con0) & (1 << 29)));
	while (!(readl(&clock->epll_con0) & (1 << 29)));
	while (!(readl(&clock->vpll_con) & (1 << 29)));

	/* 
	** 4.设置系统时钟源，选择PLL为时钟输出 */
	/* MOUT_MSYS = SCLKAPLL = FOUT_APLL = 1000MHz
	** MOUT_DSYS = SCLKMPLL = FOUT_MPLL = 667MHz
	** MOUT_PSYS = SCLKMPLL = FOUT_MPLL = 667MHz
	** ONENAND = HCLK_PSYS
	*/
	writel((1 << 0) | (1 << 4) | (1 << 8) | (1 << 12), &clock->src0);
	
	/* 4.设置其他模块的时钟源 */

	/* 6.设置系统时钟分频值 */
	val = 	(0 << 0)  |	/* APLL_RATIO = 0, freq(ARMCLK) = MOUT_MSYS / (APLL_RATIO + 1) = 1000MHz */
			(4 << 4)  |	/* A2M_RATIO = 4, freq(A2M) = SCLKAPLL / (A2M_RATIO + 1) = 200MHz */
			(4 << 8)  |	/* HCLK_MSYS_RATIO = 4, freq(HCLK_MSYS) = ARMCLK / (HCLK_MSYS_RATIO + 1) = 200MHz */
			(1 << 12) |	/* PCLK_MSYS_RATIO = 1, freq(PCLK_MSYS) = HCLK_MSYS / (PCLK_MSYS_RATIO + 1) = 100MHz */
			(3 << 16) | /* HCLK_DSYS_RATIO = 3, freq(HCLK_DSYS) = MOUT_DSYS / (HCLK_DSYS_RATIO + 1) = 166MHz */
			(1 << 20) | /* PCLK_DSYS_RATIO = 1, freq(PCLK_DSYS) = HCLK_DSYS / (PCLK_DSYS_RATIO + 1) = 83MHz */
			(4 << 24) |	/* HCLK_PSYS_RATIO = 4, freq(HCLK_PSYS) = MOUT_PSYS / (HCLK_PSYS_RATIO + 1) = 133MHz */
			(1 << 28);	/* PCLK_PSYS_RATIO = 1, freq(PCLK_PSYS) = HCLK_PSYS / (PCLK_PSYS_RATIO + 1) = 66MHz */
	writel(val, &clock->div0);
	
	/* 7.设置其他模块的时钟分频值 */
}

void ddr_init(void)
{
	struct s5pv210_dmc0 *const dmc0 = (struct s5pv210_dmc0 *)samsung_get_base_dmc0();
	struct s5pv210_dmc1 *const dmc1 = (struct s5pv210_dmc1 *)samsung_get_base_dmc1();
	
	/* DMC0 */
	writel(0x00101000, &dmc0->phycontrol0);
	writel(0x00101002, &dmc0->phycontrol0);			/* DLL on */
	writel(0x00000086, &dmc0->phycontrol1);
	writel(0x00101003, &dmc0->phycontrol0);			/* DLL start */
	
	while ((readl(&dmc0->phystatus) & 0x7) != 0x7); /* wait DLL locked */

	writel(0x0FFF2350, &dmc0->concontrol);			/* Auto Refresh Counter should be off */
	writel(0x00202430, &dmc0->memcontrol);			/* Dynamic power down should be off */
	writel(0x20E01323, &dmc0->memconfig0);
	
	writel(0xFF000000, &dmc0->prechconfig);
	writel(0xFFFF00FF, &dmc0->pwrdnconfig);
	
	writel(0x00000618, &dmc0->timingaref);			/* 7.8us * 200MHz = 1560 = 0x618  */
	writel(0x19233309, &dmc0->timingrow);
	writel(0x23240204, &dmc0->timingdata);
	writel(0x09C80232, &dmc0->timingpower);
	
	writel(0x07000000, &dmc0->directcmd);			/* NOP */
	writel(0x01000000, &dmc0->directcmd);			/* PALL */
	writel(0x00020000, &dmc0->directcmd);			/* EMRS2 */
	writel(0x00030000, &dmc0->directcmd);			/* EMRS3 */
	writel(0x00010400, &dmc0->directcmd);			/* EMRS enable DLL */
	writel(0x00000542, &dmc0->directcmd);			/* DLL reset */
	writel(0x01000000, &dmc0->directcmd); 			/* PALL */
	writel(0x05000000, &dmc0->directcmd);			/* auto refresh */
	writel(0x05000000, &dmc0->directcmd);			/* auto refresh */
	writel(0x00000442, &dmc0->directcmd);			/* DLL unreset */
	writel(0x00010780, &dmc0->directcmd);			/* OCD default */
	writel(0x00010400, &dmc0->directcmd);			/* OCD exit */
	
	writel(0x0FF02030, &dmc0->concontrol);			/* auto refresh on */
	writel(0xFFFF00FF, &dmc0->pwrdnconfig);
	writel(0x00202400, &dmc0->memcontrol);

	/* DMC1 */
	writel(0x00101000, &dmc1->phycontrol0);
	writel(0x00101002, &dmc1->phycontrol0);			/* DLL on */
	writel(0x00000086, &dmc1->phycontrol1);
	writel(0x00101003, &dmc1->phycontrol0);			/* DLL start */

	while ((readl(&dmc1->phystatus) & 0x7) != 0x7); /* wait DLL locked */

	writel(0x0FFF2350, &dmc1->concontrol);			/* Auto Refresh Counter should be off */
	writel(0x00202430, &dmc1->memcontrol);			/* Dynamic power down should be off */
	writel(0x40E01323, &dmc1->memconfig0);
	
	writel(0xFF000000, &dmc1->prechconfig);
	writel(0xFFFF00FF, &dmc1->pwrdnconfig);
	
	writel(0x00000618, &dmc1->timingaref);			/* 7.8us * 200MHz = 1560 = 0x618  */
	writel(0x19233309, &dmc1->timingrow);
	writel(0x23240204, &dmc1->timingdata);
	writel(0x09C80232, &dmc1->timingpower);
	
	writel(0x07000000, &dmc1->directcmd);			/* NOP */
	writel(0x01000000, &dmc1->directcmd);			/* PALL */
	writel(0x00020000, &dmc1->directcmd);			/* EMRS2 */
	writel(0x00030000, &dmc1->directcmd);			/* EMRS3 */
	writel(0x00010400, &dmc1->directcmd);			/* EMRS enable DLL */
	writel(0x00000542, &dmc1->directcmd);			/* DLL reset */
	writel(0x01000000, &dmc1->directcmd); 			/* PALL */
	writel(0x05000000, &dmc1->directcmd);			/* auto refresh */
	writel(0x05000000, &dmc1->directcmd);			/* auto refresh */
	writel(0x00000442, &dmc1->directcmd);			/* DLL unreset */
	writel(0x00010780, &dmc1->directcmd);			/* OCD default */
	writel(0x00010400, &dmc1->directcmd);			/* OCD exit */
	
	writel(0x0FF02030, &dmc1->concontrol);			/* auto refresh on */
	writel(0xFFFF00FF, &dmc1->pwrdnconfig);
	writel(0x00202400, &dmc1->memcontrol);
}

void copy_bl2_to_ram(void)
{
/*
** ch:  通道
** sb:  起始块
** bs:  块大小
** dst: 目的地
** i: 	是否初始化
*/
#define CopySDMMCtoMem(ch, sb, bs, dst, i) \
	(((unsigned char(*)(int, unsigned int, unsigned short, unsigned int*, unsigned char))\
	(*((unsigned int *)0xD0037F98)))(ch, sb, bs, dst, i))

	unsigned char ch = 0;	
	unsigned int V210_SDMMC_BASE = *(volatile unsigned int *)(0xD0037488);	// V210_SDMMC_BASE		
	
	/* 参考S5PV210手册7.9.1 SD/MMC REGISTER MAP */
	if (V210_SDMMC_BASE == 0xEB000000) {
		ch = 0;
	} else if (V210_SDMMC_BASE == 0xEB200000) {
		ch = 2;		
	}
	
	CopySDMMCtoMem(ch, 32, 700, (unsigned int *)CONFIG_SYS_SDRAM_BASE, 0);
	
	led2_on();
}

#endif

