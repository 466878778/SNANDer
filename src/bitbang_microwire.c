/*  Copyright (C) 2005-2021 Mokrushin I.V. aka McMCC mcmcc@mail.ru
    A simple bitbang protocol for Microwire 8-pin serial EEPROMs
    (93XX devices). Support organization 8bit and 16bit(8bit emulation).

    bitbang_microwire.c

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                */
/* ------------------------------------------------------------------------- */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bitbang_microwire.h"

struct gpio_cmd bb_func;
static unsigned char data = 0;

static void delay_ms(int n)
{
#if 0 /* ifndef _WINDOWS */
	int i;
	for(i = 0; i < (n * 100000); i++);
#else
	usleep(n);
#endif
}

static void data_1()
{
	data = data | DI;
	if (bb_func.gpio_setbits)
		bb_func.gpio_setbits(data);
}

static void data_0()
{
	data = data & (~DI);
	if (bb_func.gpio_setbits)
		bb_func.gpio_setbits(data);
}

static void org_1()
{
#if 0
	data = data | ORG; /* 16bit */
	if (bb_func.gpio_setbits)
		bb_func.gpio_setbits(data);
#endif
}

static void org_0()
{
#if 0
	data = data & (~ORG); /* 8bit */
	if (bb_func.gpio_setbits)
		bb_func.gpio_setbits(data);
#endif
}

static void csel_1()
{
	data = data | CSEL;
	if (bb_func.gpio_setbits)
		bb_func.gpio_setbits(data);
}

static void csel_0()
{
	data = data & (~CSEL);
	if (bb_func.gpio_setbits)
		bb_func.gpio_setbits(data);
}

static void clock_1()
{
	data = data | CLK;
	if (bb_func.gpio_setbits)
		bb_func.gpio_setbits(data);
}

static void clock_0()
{
	data = data & (~CLK);
	if (bb_func.gpio_setbits)
		bb_func.gpio_setbits(data);
}

static unsigned int get_data()
{
	unsigned char b = 0;
	if (bb_func.gpio_getbits)
		bb_func.gpio_getbits(&b);
	return ((b & DO) == DO);
}

static int addr_nbits(int size)
{
	int i;
	i = 0;

	while (size > 0)
	{
		size = size >> 1;
		if (size)
			i++;
	}
	if (i < 6) /* Fix for 93C06 */
		i = 6;

	return i;
}

static int convert_size(int eeprom_size)
{
	int k;
	org_0();
	delay_ms(1);
	k = 1;

	if (org)
	{
		org_1();
		delay_ms(1);
		k = 2;
	}
	eeprom_size = eeprom_size / k;

	return eeprom_size;
}

static void send_to_di(unsigned char val, int nbit)
{
	int b, i;
	i = 0;

	while (i < nbit)
	{
		b = val & (1 << (nbit - 1));
		clock_0();
		if (b)
			data_1();
		else
			data_0();
		delay_ms(1);
		clock_1();
		delay_ms(1);
		i++;
		val = (val & ((1 << (nbit - 1)) - 1)) * 2;
	}
}

static unsigned char get_from_do()
{
	unsigned char val;
	int b, i;
	i = 0;
	val = 0;
	while (i < 8)
	{
		val = val * 2;
		clock_0();
		delay_ms(1);
		b = get_data();
		clock_1();
		delay_ms(1);
		i++;
		val += b;
	}
	return val;
}

static void enable_write_3wire(int num_bit)
{
	csel_0();
	clock_0();
	delay_ms(1);
	data_1();
	csel_1();
	delay_ms(1);
	clock_1();
	delay_ms(1);

	send_to_di(3, 4);
	send_to_di(0, num_bit - 2);

	data_0();
	delay_ms(1);
	csel_0();
	delay_ms(1);
}

static void disable_write_3wire(int num_bit)
{
	csel_1();
	delay_ms(1);
	clock_0();
	delay_ms(1);
	data_1();
	delay_ms(1);
	clock_1();
	delay_ms(1);
	send_to_di(0, 4);
	send_to_di(0, num_bit - 2);
	csel_0();
	delay_ms(1);
}

static void chip_busy(void)
{
	printf("Error: Always BUSY! Communication problem...The broken microwire chip?\n");
}

void Erase_EEPROM_3wire(int size_eeprom)
{
	int i, num_bit;

	size_eeprom = convert_size(size_eeprom);
	num_bit = addr_nbits(size_eeprom);

	enable_write_3wire(num_bit);
	csel_0();
	clock_0();
	delay_ms(1);
	data_1();
	csel_1();
	delay_ms(1);
	clock_1();
	delay_ms(1);

	send_to_di(2, 4);
	send_to_di(0, num_bit - 2);
	clock_0();
	data_0();
	delay_ms(1);
	csel_0();
	delay_ms(1);
	csel_1();
	delay_ms(1);
	clock_1();
	delay_ms(1);
	i = 0;
	while (!get_data() && i < 10000)
	{
		clock_0();
		delay_ms(1);
		clock_1();
		delay_ms(1);
		i++;
	}
	
	if (i == 10000)
	{
		chip_busy();
		return;
	}

	csel_0();
	delay_ms(1);
	clock_0();
	delay_ms(1);
	clock_1();
	delay_ms(1);

	disable_write_3wire(num_bit);
}

int Read_EEPROM_3wire(unsigned char *buffer, int size_eeprom)
{
	int address, num_bit, l;

	size_eeprom = convert_size(size_eeprom);
	num_bit = addr_nbits(size_eeprom);

	address = 0;

	for (l = 0; l < size_eeprom; l++)
	{
		csel_0();
		clock_0();
		delay_ms(1);
		data_1();
		csel_1();
		delay_ms(1);
		clock_1();
		delay_ms(1);

		send_to_di(2, 2);
		send_to_di(l, num_bit);

		data_0();
		clock_0();
		delay_ms(1);
		clock_1();
		delay_ms(1);
		buffer[address] = get_from_do();
		if (org)
		{
			address++;
			buffer[address] = get_from_do();
		}
		csel_0();
		delay_ms(1);
		clock_0();
		delay_ms(1);
		clock_1();
		delay_ms(1);
		address++;
		if (l % (org ? 16 : 8)) {
			printf(".");
			fflush(stdout);
		}
	}
	printf("\n");
	return 0;
}

int Write_EEPROM_3wire(unsigned char *buffer, int size_eeprom)
{
	int i, l, address, num_bit;

	size_eeprom = convert_size(size_eeprom);
	num_bit = addr_nbits(size_eeprom);

	enable_write_3wire(num_bit);
	address = 0;

	for (l = 0; l < size_eeprom; l++)
	{
		csel_0();
		clock_0();
		delay_ms(1);
		data_1();
		csel_1();
		delay_ms(1);
		clock_1();
		delay_ms(1);
		send_to_di(1, 2);
		send_to_di(l, num_bit);
		send_to_di(buffer[address], 8);
		if (org)
		{
			address++;
			send_to_di(buffer[address], 8);
		}
		clock_0();
		data_0();
		delay_ms(1);
		csel_0();
		delay_ms(1);
		csel_1();
		delay_ms(1);
		clock_1();
		delay_ms(1);
		i = 0;
		while (!get_data() && i < 10000)
		{
			clock_0();
			delay_ms(1);
			clock_1();
			delay_ms(1);
			i++;
		}
		if (i == 10000)
		{
			printf("\n");
			chip_busy();
			return -1;
		}

		csel_0();
		delay_ms(1);
		clock_0();
		delay_ms(1);
		clock_1();
		delay_ms(1);
		address++;
		if (l % (org ? 16 : 8)) {
			printf(".");
			fflush(stdout);
		}
	}
	printf("\n");
	disable_write_3wire(num_bit);

	return 0;
}

int deviceSize_3wire(char *eepromname)
{
	int i;

	for (i = 0; mw_eepromlist[i].size; i++) {
		if (strstr(mw_eepromlist[i].name, eepromname)) {
			return (mw_eepromlist[i].size);
		}
	}

	return -1;
}
/* End of [bitbang_microwire.c] package */
