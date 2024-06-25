// libUSB driver for the ch347 in i2c mode
//
// Copyright 2011 asbokid <ballymunboy@gmail.com>
#ifndef __CH347_I2C_H__
#define __CH347_I2C_H__

#include <stdint.h>
#ifdef _WIN32
typedef int(__stdcall  * pCH347OpenDevice)(unsigned long iIndex);

typedef int(__stdcall * pCH347CloseDevice)(unsigned long iIndex);
typedef unsigned long(__stdcall * pCH347SetTimeout)(
	unsigned long iIndex,        /* Specify equipment serial number */
	unsigned long iWriteTimeout, /* Specifies the timeout period for USB
					write out data blocks, in milliseconds
					mS, and 0xFFFFFFFF specifies no timeout
					(default) */
	unsigned long iReadTimeout); /* Specifies the timeout period for USB
					reading data blocks, in milliseconds mS,
					and 0xFFFFFFFF specifies no timeout
					(default) */

typedef unsigned long(__stdcall * pCH347WriteData)(
	unsigned long iIndex,         /* Specify equipment serial number */
	void *oBuffer,                /* Point to a buffer large enough to hold
					 the descriptor */
	unsigned long *ioLength);     /* Pointing to the length unit, the input
					 is the length to be read, and the
					 return is the actual read length */

typedef unsigned long(__stdcall * pCH347ReadData)(
	unsigned long iIndex,          /* Specify equipment serial number */
	void *oBuffer,                 /* Point to a buffer large enough to
					  hold the descriptor */
	unsigned long *ioLength);      /* Pointing to the length unit, the input
					  is the length to be read, and the
					  return is the actual read length */
#endif

#define MAX_EEPROM_SIZE			131072 /* For 24c1024*/

#define EEPROM_I2C_BUS_ADDRESS		0x50

#define BULK_WRITE_ENDPOINT         0x06      
#define BULK_READ_ENDPOINT          0x86     
#define DEFAULT_INTERFACE           0x02

#define DEFAULT_CONFIGURATION		0x01
#define DEFAULT_TIMEOUT			3000    // 300mS for USB timeouts

#define IN_BUF_SZ			0x100
#define EEPROM_WRITE_BUF_SZ		0x2b   // only for 24c64 / 24c32 ??
#define EEPROM_READ_BULKIN_BUF_SZ	0x20
#define EEPROM_READ_BULKOUT_BUF_SZ	0x65

/* Based on (closed-source) DLL V1.9 for USB by WinChipHead (c) 2005.
   Supports USB chips: ch347, ch347A
   This can be a problem for copyright, sure asbokid can't release this part on any GPL licence*/

#define	mch347_PACKET_LENGTH		32      /* wMaxPacketSize 0x0020  1x 32 bytes, unused on the source */
#define	mch347_PKT_LEN_SHORT		8       /* wMaxPacketSize 0x0008  1x 8 bytes, unused on the source */

#define	mch347_ENDP_INTER_UP		0x81    /* bEndpointAddress 0x81  EP 1 IN (Interrupt), unused on the source */
#define	mch347_ENDP_INTER_DOWN		0x01    /* This endpoint isn't list on my lsusb -v output, unused on the source */
#define	mch347_ENDP_DATA_UP		0x82    /* ==BULK_READ_ENDPOINT  Why repeat it? */
#define	mch347_ENDP_DATA_DOWN		0x02    /* ==BULK_WRITE_ENDPOINT Why repeat it? */

#define	mch347_VENDOR_READ		0xC0    /* Unused on the source */
#define	mch347_VENDOR_WRITE		0x40    /* Unused on the source */

#define	mch347_PARA_INIT		0xB1    /* Unused on the source */
#define	mch347_I2C_STATUS		0x52    /* Unused on the source */
#define	mch347_I2C_COMMAND		0x53    /* Unused on the source */

#define	mch347_PARA_CMD_R0		0xAC    /* Unused on the source */
#define	mch347_PARA_CMD_R1		0xAD    /* Unused on the source */
#define	mch347_PARA_CMD_W0		0xA6    /* Unused on the source */
#define	mch347_PARA_CMD_W1		0xA7    /* Unused on the source */
#define	mch347_PARA_CMD_STS		0xA0    /* Unused on the source */

#define	mch347_CMD_SET_OUTPUT		0xA1    /* Unused on the source */
#define	mch347_CMD_IO_ADDR		0xA2    /* Unused on the source */
#define	mch347_CMD_PRINT_OUT		0xA3    /* Unused on the source */
#define	mch347_CMD_SPI_STREAM		0xA8    /* Unused on the source */
#define	mch347_CMD_SIO_STREAM		0xA9    /* Unused on the source */
#define	mch347_CMD_I2C_STREAM		0xAA
#define	mch347_CMD_UIO_STREAM		0xAB    /* Unused on the source */

#define	mch347_BUF_CLEAR		0xB2    /* Unused on the source */
#define	mch347_I2C_CMD_X		0x54    /* Unused on the source */
#define	mch347_DELAY_MS		0x5E    /* Unused on the source */
#define	mch347_GET_VER			0x5F    /* Unused on the source */

#define	mch347_EPP_IO_MAX		( mch347_PACKET_LENGTH - 1 )    /* Unused on the source */
#define	mch347_EPP_IO_MAX		0xFF    /* Unused on the source */

#define	mch347_CMD_IO_ADDR_W		0x00    /* Unused on the source */
#define	mch347_CMD_IO_ADDR_R		0x80    /* Unused on the source */

#define	mch347_CMD_I2C_STM_STA		0x74
#define	mch347_CMD_I2C_STM_STO		0x75
#define	mch347_CMD_I2C_STM_OUT		0x80
#define	mch347_CMD_I2C_STM_IN		0xC0
#define	mch347_CMD_I2C_STM_MAX		( min( 0x3F, mch347_PACKET_LENGTH ) )   /* Unused on the source */
#define	mch347_CMD_I2C_STM_SET		0x63
#define	mch347_CMD_I2C_STM_US		0x40    /* Unused on the source */
#define	mch347_CMD_I2C_STM_MS		0x50    /* Unused on the source */
#define	mch347_CMD_I2C_STM_DLY		0x0F    /* Unused on the source */
#define	mch347_CMD_I2C_STM_END		0x00

#define	mch347_CMD_UIO_STM_IN		0x00    /* Unused on the source */
#define	mch347_CMD_UIO_STM_DIR		0x40    /* Unused on the source */
#define	mch347_CMD_UIO_STM_OUT		0x80    /* Unused on the source */
#define	mch347_CMD_UIO_STM_US		0xC0    /* Unused on the source */
#define	mch347_CMD_UIO_STM_END		0x20    /* Unused on the source */

#define	mch347_PARA_MODE_EPP		0x00    /* Unused on the source */
#define	mch347_PARA_MODE_EPP17		0x00    /* Unused on the source */
#define	mch347_PARA_MODE_EPP19		0x01    /* Unused on the source */
#define	mch347_PARA_MODE_MEM		0x02    /* Unused on the source */

/* End of part based on (closed-source) DLL V1.9 for USB by WinChipHead (c) 2005.
   Since is largely unused we can replace it */


#define CH347_I2C_LOW_SPEED		0 // low speed - 20kHz
#define CH347_I2C_STANDARD_SPEED	1 // standard speed - 100kHz
#define CH347_I2C_FAST_SPEED		2 // fast speed - 400kHz
#define CH347_I2C_HIGH_SPEED		3 // high speed - 750kHz

#define CH347_EEPROM_READ_CMD_SZ	0x65 /* Same size for all 24cXX read setup and next packets*/

/* CH341a READ EEPROM setup packet for the 24c01
   this needs putting into a struct to allow convenient access to individual elements*/
#define CH347_EEPROM_24c01_READ_SETUP_CMD "\xaa\x74\x82\xa0\x00\x74\x81\xa1\xe0\x00\x0f\x00\x06\x04\x00\x00" \
                                          "\x00\x00\x00\x00\x01\x00\x00\x00\x11\x4d\x40\x77\xcd\xab\xba\xdc" \
                                          "\xaa\xe0\x00\x00\xc4\xf1\x12\x00\x11\x4d\x40\x77\xf0\xf1\x12\x00" \
                                          "\xd9\x8b\x41\x7e\x00\xd0\xfd\x7f\xf0\xf1\x12\x00\x5a\x88\x41\x7e" \
                                          "\xaa\xe0\x00\x00\x2a\x88\x41\x7e\x06\x04\x00\x00\x11\x4d\x40\x77" \
                                          "\xe8\xf3\x12\x00\x14\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00" \
                                          "\xaa\xdf\xc0\x75\x00"
/* please see file /wiresharkusbsniffing/sniffed.txt
   this is the read setup packet for 24c01

0040  aa 74 82 a0 00 74 81 a1  e0 00 0f 00 06 04 00 00   .t...t.. ........
0050  00 00 00 00 01 00 00 00  11 4d 40 77 cd ab ba dc   ........ .M@w....
0060  aa e0 00 00 c4 f1 12 00  11 4d 40 77 f0 f1 12 00   ........ .M@w....
0070  d9 8b 41 7e 00 d0 fd 7f  f0 f1 12 00 5a 88 41 7e   ..A~.... ....Z.A~
0080  aa e0 00 00 2a 88 41 7e  06 04 00 00 11 4d 40 77   ....*.A~ .....M@w
0090  e8 f3 12 00 14 00 00 00  01 00 00 00 00 00 00 00   ........ ........
00a0  aa df c0 75 00                                     ...u.
*/

/* CH341a READ EEPROM next packet for 24c01  (no packets!!!)*/


/* CH341a READ EEPROM setup packet for the 24c02
   this needs putting into a struct to allow convenient access to individual elements*/
#define CH347_EEPROM_24c02_READ_SETUP_CMD "\xaa\x74\x82\xa0\x00\x74\x81\xa1\xe0\x00\x10\x00\x06\x04\x00\x00" \
                                          "\x00\x00\x00\x00\x02\x00\x00\x00\x11\x4d\x40\x77\xcd\xab\xba\xdc" \
                                          "\xaa\xe0\x00\x00\xc4\xf1\x12\x00\x11\x4d\x40\x77\xf0\xf1\x12\x00" \
                                          "\xd9\x8b\x41\x7e\x00\xf0\xfd\x7f\xf0\xf1\x12\x00\x5a\x88\x41\x7e" \
                                          "\xaa\xe0\x00\x00\x2a\x88\x41\x7e\x06\x04\x00\x00\x11\x4d\x40\x77" \
                                          "\xe8\xf3\x12\x00\x14\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00" \
                                          "\xaa\xdf\xc0\x75\x00"
/* please see file /wiresharkusbsniffing/sniffed.txt
   this is the read setup packet for 24c02

0040  aa 74 82 a0 00 74 81 a1  e0 00 10 00 06 04 00 00   .t...t.. ........
0050  00 00 00 00 02 00 00 00  11 4d 40 77 cd ab ba dc   ........ .M@w....
0060  aa e0 00 00 c4 f1 12 00  11 4d 40 77 f0 f1 12 00   ........ .M@w....
0070  d9 8b 41 7e 00 f0 fd 7f  f0 f1 12 00 5a 88 41 7e   ..A~.... ....Z.A~
0080  aa e0 00 00 2a 88 41 7e  06 04 00 00 11 4d 40 77   ....*.A~ .....M@w
0090  e8 f3 12 00 14 00 00 00  01 00 00 00 00 00 00 00   ........ ........
00a0  aa df c0 75 00                                     ...u.
*/

/* CH341a READ EEPROM next packet for 24c02  (one packet)*/
#define CH347_EEPROM_24c02_READ_NEXT_CMD "\xaa\x74\x82\xa0\x80\x74\x81\xa1\xe0\x00\x00\x00\x10\x00\x00\x00" \
                                         "\x00\x00\x00\x00\x8c\xf1\x12\x00\x01\x00\x00\x00\x00\x00\x00\x00" \
                                         "\xaa\xe0\x00\x00\x4c\xf1\x12\x00\x5d\x22\xd7\x5a\xdc\xf1\x12\x00" \
                                         "\x8f\x04\x44\x7e\x30\x88\x41\x7e\xff\xff\xff\xff\x2a\x88\x41\x7e" \
                                         "\xaa\xe0\x00\x7e\x00\x00\x00\x00\x69\x0e\x3c\x00\xe4\x00\x18\x00" \
                                         "\x0f\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x8c\xe8\x67\x00" \
                                         "\xaa\xdf\xc0\x75\x00"
/* please see file /wiresharkusbsniffing/sniffed.txt
   this is the read next packet for 24c02  (one packet)

0040  aa 74 82 a0 80 74 81 a1  e0 00 00 00 10 00 00 00   .t...t.. ........
0050  00 00 00 00 8c f1 12 00  01 00 00 00 00 00 00 00   ........ ........
0060  aa e0 00 00 4c f1 12 00  5d 22 d7 5a dc f1 12 00   ....L... ]".Z....
0070  8f 04 44 7e 30 88 41 7e  ff ff ff ff 2a 88 41 7e   ..D~0.A~ ....*.A~
0080  aa e0 00 7e 00 00 00 00  69 0e 3c 00 e4 00 18 00   ...~.... i.<.....
0090  0f 00 00 00 00 00 00 00  00 00 00 00 8c e8 67 00   ........ ......g.
00a0  aa df c0 75 00                                     ...u.
*/


/* CH341a READ EEPROM setup packet for the 24c04
   this needs putting into a struct to allow convenient access to individual elements*/
#define CH347_EEPROM_24c04_READ_SETUP_CMD "\xaa\x74\x82\xa0\x00\x74\x81\xa1\xe0\x00\x11\x00\x06\x04\x00\x00" \
                                          "\x00\x00\x00\x00\x04\x00\x00\x00\x11\x4d\x40\x77\xcd\xab\xba\xdc" \
                                          "\xaa\xe0\x00\x00\xc4\xf1\x12\x00\x11\x4d\x40\x77\xf0\xf1\x12\x00" \
                                          "\xd9\x8b\x41\x7e\x00\xd0\xfd\x7f\xf0\xf1\x12\x00\x5a\x88\x41\x7e" \
                                          "\xaa\xe0\x00\x00\x2a\x88\x41\x7e\x06\x04\x00\x00\x11\x4d\x40\x77" \
                                          "\xe8\xf3\x12\x00\x14\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00" \
                                          "\xaa\xdf\xc0\x75\x00"
/* please see file /wiresharkusbsniffing/sniffed.txt
   this is the read setup packet for 24c04

0040  aa 74 82 a0 00 74 81 a1  e0 00 11 00 06 04 00 00   .t...t.. ........
0050  00 00 00 00 04 00 00 00  11 4d 40 77 cd ab ba dc   ........ .M@w....
0060  aa e0 00 00 c4 f1 12 00  11 4d 40 77 f0 f1 12 00   ........ .M@w....
0070  d9 8b 41 7e 00 d0 fd 7f  f0 f1 12 00 5a 88 41 7e   ..A~.... ....Z.A~
0080  aa e0 00 00 2a 88 41 7e  06 04 00 00 11 4d 40 77   ....*.A~ .....M@w
0090  e8 f3 12 00 14 00 00 00  01 00 00 00 00 00 00 00   ........ ........
00a0  aa df c0 75 00                                     ...u.
*/

/* CH341a READ EEPROM next packet for 24c04  (three packets)*/
#define CH347_EEPROM_24c04_READ_NEXT_CMD "\xaa\x74\x82\xa0\x80\x74\x81\xa1\xe0\x00\x00\x00\x10\x00\x00\x00" \
                                         "\x00\x00\x00\x00\x8c\xf1\x12\x00\x01\x00\x00\x00\x00\x00\x00\x00" \
                                         "\xaa\xe0\x00\x00\x4c\xf1\x12\x00\x5d\x22\xd7\x5a\xdc\xf1\x12\x00" \
                                         "\x8f\x04\x44\x7e\x30\x88\x41\x7e\xff\xff\xff\xff\x2a\x88\x41\x7e" \
                                         "\xaa\xe0\x00\x7e\x00\x00\x00\x00\x69\x0e\x3c\x00\xde\x00\x16\x00" \
                                         "\x0f\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x8c\xe8\x67\x00" \
                                         "\xaa\xdf\xc0\x75\x00"
/* please see file /wiresharkusbsniffing/sniffed.txt
   this is the first read next packet for 24c04  (three different packets)

0040  aa 74 82 a0 80 74 81 a1  e0 00 00 00 10 00 00 00   .t...t.. ........
0050  00 00 00 00 8c f1 12 00  01 00 00 00 00 00 00 00   ........ ........
0060  aa e0 00 00 4c f1 12 00  5d 22 d7 5a dc f1 12 00   ....L... ]".Z....
0070  8f 04 44 7e 30 88 41 7e  ff ff ff ff 2a 88 41 7e   ..D~0.A~ ....*.A~
0080  aa e0 00 7e 00 00 00 00  69 0e 3c 00 de 00 16 00   ...~.... i.<.....
0090  0f 00 00 00 00 00 00 00  00 00 00 00 8c e8 67 00   ........ ......g.
00a0  aa df c0 75 00                                     ...u.
*/


/* CH341a READ EEPROM setup packet for the 24c08
   this needs putting into a struct to allow convenient access to individual elements*/
#define CH347_EEPROM_24c08_READ_SETUP_CMD "\xaa\x74\x82\xa0\x00\x74\x81\xa1\xe0\x00\x16\x00\x06\x04\x00\x00" \
                                          "\x00\x00\x00\x00\x08\x00\x00\x00\x11\x4d\x40\x77\xcd\xab\xba\xdc" \
                                          "\xaa\xe0\x00\x00\xc4\xf1\x12\x00\x11\x4d\x40\x77\xf0\xf1\x12\x00" \
                                          "\xd9\x8b\x41\x7e\x00\xd0\xfd\x7f\xf0\xf1\x12\x00\x5a\x88\x41\x7e" \
                                          "\xaa\xe0\x00\x00\x2a\x88\x41\x7e\x06\x04\x00\x00\x11\x4d\x40\x77" \
                                          "\xe8\xf3\x12\x00\x14\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00" \
                                          "\xaa\xdf\xc0\x75\x00"
/* please see file /wiresharkusbsniffing/sniffed.txt
   this is the read setup packet for 24c08

0040  aa 74 82 a0 00 74 81 a1  e0 00 16 00 06 04 00 00   .t...t.. ........
0050  00 00 00 00 08 00 00 00  11 4d 40 77 cd ab ba dc   ........ .M@w....
0060  aa e0 00 00 c4 f1 12 00  11 4d 40 77 f0 f1 12 00   ........ .M@w....
0070  d9 8b 41 7e 00 d0 fd 7f  f0 f1 12 00 5a 88 41 7e   ..A~.... ....Z.A~
0080  aa e0 00 00 2a 88 41 7e  06 04 00 00 11 4d 40 77   ....*.A~ .....M@w
0090  e8 f3 12 00 14 00 00 00  01 00 00 00 00 00 00 00   ........ ........
00a0  aa df c0 75 00                                     ...u.
*/

/* CH341a READ EEPROM next packet for 24c08  (seven packets)*/
#define CH347_EEPROM_24c08_READ_NEXT_CMD "\xaa\x74\x82\xa0\x80\x74\x81\xa1\xe0\x00\x00\x00\x10\x00\x00\x00" \
                                         "\x00\x00\x00\x00\x8c\xf1\x12\x00\x01\x00\x00\x00\x00\x00\x00\x00" \
                                         "\xaa\xe0\x00\x00\x4c\xf1\x12\x00\x5d\x22\xd7\x5a\xdc\xf1\x12\x00" \
                                         "\x8f\x04\x44\x7e\x30\x88\x41\x7e\xff\xff\xff\xff\x2a\x88\x41\x7e" \
                                         "\xaa\xe0\x00\x7e\x00\x00\x00\x00\x69\x0e\x3c\x00\x00\x01\x1a\x00" \
                                         "\x0f\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x8c\xe8\x67\x00" \
                                         "\xaa\xdf\xc0\x75\x00"
/* please see file /wiresharkusbsniffing/sniffed.txt
   this is the first read next packet for 24c08  (seven different packets)

0040  aa 74 82 a0 80 74 81 a1  e0 00 00 00 10 00 00 00   .t...t.. ........
0050  00 00 00 00 8c f1 12 00  01 00 00 00 00 00 00 00   ........ ........
0060  aa e0 00 00 4c f1 12 00  5d 22 d7 5a dc f1 12 00   ....L... ]".Z....
0070  8f 04 44 7e 30 88 41 7e  ff ff ff ff 2a 88 41 7e   ..D~0.A~ ....*.A~
0080  aa e0 00 7e 00 00 00 00  69 0e 3c 00 00 01 1a 00   ...~.... i.<.....
0090  0f 00 00 00 00 00 00 00  00 00 00 00 8c e8 67 00   ........ ......g.
00a0  aa df c0 75 00                                     ...u.
*/


/* CH341a READ EEPROM setup packet for the 24c16
   this needs putting into a struct to allow convenient access to individual elements*/
#define CH347_EEPROM_24c16_READ_SETUP_CMD "\xaa\x74\x82\xa0\x00\x74\x81\xa1\xe0\x00\x0e\x00\x06\x04\x00\x00" \
                                          "\x00\x00\x00\x00\x10\x00\x00\x00\x11\x4d\x40\x77\xcd\xab\xba\xdc" \
                                          "\xaa\xe0\x00\x00\xc4\xf1\x12\x00\x11\x4d\x40\x77\xf0\xf1\x12\x00" \
                                          "\xd9\x8b\x41\x7e\x00\xe0\xfd\x7f\xf0\xf1\x12\x00\x5a\x88\x41\x7e" \
                                          "\xaa\xe0\x00\x00\x2a\x88\x41\x7e\x06\x04\x00\x00\x11\x4d\x40\x77" \
                                          "\xe8\xf3\x12\x00\x14\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00" \
                                          "\xaa\xdf\xc0\x75\x00"
/* please see file /wiresharkusbsniffing/sniffed.txt
   this is the read setup packet for 24c16

0040  aa 74 82 a0 00 74 81 a1  e0 00 0e 00 06 04 00 00   .t...t.. ........
0050  00 00 00 00 10 00 00 00  11 4d 40 77 cd ab ba dc   ........ .M@w....
0060  aa e0 00 00 c4 f1 12 00  11 4d 40 77 f0 f1 12 00   ........ .M@w....
0070  d9 8b 41 7e 00 e0 fd 7f  f0 f1 12 00 5a 88 41 7e   ..A~.... ....Z.A~
0080  aa e0 00 00 2a 88 41 7e  06 04 00 00 11 4d 40 77   ....*.A~ .....M@w
0090  e8 f3 12 00 14 00 00 00  01 00 00 00 00 00 00 00   ........ ........
00a0  aa df c0 75 00                                     ...u.
*/

/* CH341a READ EEPROM next packet for 24c16*/
#define CH347_EEPROM_24c16_READ_NEXT_CMD "\xaa\x74\x82\xa0\x80\x74\x81\xa1\xe0\x00\x00\x00\x10\x00\x00\x00" \
                                         "\x00\x00\x00\x00\x8c\xf1\x12\x00\x01\x00\x00\x00\x00\x00\x00\x00" \
                                         "\xaa\xe0\x00\x00\x4c\xf1\x12\x00\x5d\x22\xd7\x5a\xdc\xf1\x12\x00" \
                                         "\x8f\x04\x44\x7e\x30\x88\x41\x7e\xff\xff\xff\xff\x2a\x88\x41\x7e" \
                                         "\xaa\xe0\x00\x7e\x00\x00\x00\x00\x69\x0e\x3c\x00\xfa\x00\x31\x00" \
                                         "\x0f\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x8c\xe8\x67\x00" \
                                         "\xaa\xdf\xc0\x75\x00"
/* please see file /wiresharkusbsniffing/sniffed.txt
   this is the first read next packet for 24c16  (fifteen different packets)

0040  aa 74 82 a0 80 74 81 a1  e0 00 00 00 10 00 00 00   .t...t.. ........
0050  00 00 00 00 8c f1 12 00  01 00 00 00 00 00 00 00   ........ ........
0060  aa e0 00 00 4c f1 12 00  5d 22 d7 5a dc f1 12 00   ....L... ]".Z....
0070  8f 04 44 7e 30 88 41 7e  ff ff ff ff 2a 88 41 7e   ..D~0.A~ ....*.A~
0080  aa e0 00 7e 00 00 00 00  69 0e 3c 00 fa 00 31 00   ...~.... i.<...1.
0090  0f 00 00 00 00 00 00 00  00 00 00 00 8c e8 67 00   ........ ......g.
00a0  aa df c0 75 00                                     ...u.
*/


/* CH341a READ EEPROM setup packet for the 24c64
   this needs putting into a struct to allow convenient access to individual elements*/
#define CH347_EEPROM_24c64_READ_SETUP_CMD "\xaa\x74\x83\xa0\x00\x00\x74\x81\xa1\xe0\x00\x00\x06\x04\x00\x00" \
                                          "\x00\x00\x00\x00\x40\x00\x00\x00\x11\x4d\x40\x77\xcd\xab\xba\xdc" \
                                          "\xaa\xe0\x00\x00\xc4\xf1\x12\x00\x11\x4d\x40\x77\xf0\xf1\x12\x00" \
                                          "\xd9\x8b\x41\x7e\x00\xf0\xfd\x7f\xf0\xf1\x12\x00\x5a\x88\x41\x7e" \
                                          "\xaa\xe0\x00\x00\x2a\x88\x41\x7e\x06\x04\x00\x00\x11\x4d\x40\x77" \
                                          "\xe8\xf3\x12\x00\x14\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00" \
                                          "\xaa\xdf\xc0\x75\x00"
/* please see file /wiresharkusbsniffing/sniffed.txt
   this is the read setup packet for 24c64

0040  aa 74 83 a0 00 00 74 81  a1 e0 00 00 06 04 00 00   .t....t. ........
0050  00 00 00 00 40 00 00 00  11 4d 40 77 cd ab ba dc   ....@... .M@w....
0060  aa e0 00 00 c4 f1 12 00  11 4d 40 77 f0 f1 12 00   ........ .M@w....
0070  d9 8b 41 7e 00 e0 fd 7f  f0 f1 12 00 5a 88 41 7e   ..A~.... ....Z.A~
0080  aa e0 00 00 2a 88 41 7e  06 04 00 00 11 4d 40 77   ....*.A~ .....M@w
0090  e8 f3 12 00 14 00 00 00  01 00 00 00 00 00 00 00   ........ ........
00a0  aa df c0 75 00                                       ...u.
*/

/* CH341a READ EEPROM next packet for 24c64  (63 packets)*/
#define CH347_EEPROM_24c64_READ_NEXT_CMD  "\xaa\x74\x83\xa0\x00\x00\x74\x81\xa1\xe0\x00\x00\x10\x00\x00\x00" \
                                          "\x00\x00\x00\x00\x8c\xf1\x12\x00\x01\x00\x00\x00\x00\x00\x00\x00" \
                                          "\xaa\xe0\x00\x00\x4c\xf1\x12\x00\x5d\x22\xd7\x5a\xdc\xf1\x12\x00" \
                                          "\x8f\x04\x44\x7e\x30\x88\x41\x7e\xff\xff\xff\xff\x2a\x88\x41\x7e" \
                                          "\xaa\xe0\x00\x7e\x00\x00\x00\x00\x69\x0e\x3c\x00\x12\x01\x19\x00" \
                                          "\x0f\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x9c\x2e\x68\x00" \
                                          "\xaa\xdf\xc0\x75\x00"
/* please see file /wiresharkusbsniffing/sniffed.txt
   this is the first read next packet for 24c64  (63 different packets)

0040  aa 74 83 a0 00 80 74 81  a1 e0 00 00 10 00 00 00   .t....t. ........
0050  00 00 00 00 8c f1 12 00  01 00 00 00 00 00 00 00   ........ ........
0060  aa e0 00 00 4c f1 12 00  5d 22 d7 5a dc f1 12 00   ....L... ]".Z....
0070  8f 04 44 7e 30 88 41 7e  ff ff ff ff 2a 88 41 7e   ..D~0.A~ ....*.A~
0080  aa e0 00 7e 00 00 00 00  69 0e 3c 00 3a 01 1b 00   ...~.... i.<.:...
0090  0f 00 00 00 00 00 00 00  00 00 00 00 8c e8 67 00   ........ ......g.
00a0  aa df c0 75 00                                     ...u.
*/

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define TRUE	1
#define FALSE	0

struct EEPROM {
	char *name;
	uint32_t size;
	uint16_t page_size;
	uint8_t addr_size; // Length of addres in bytes
	uint8_t i2c_addr_mask;
};

const static struct EEPROM eepromlist[] = {
	{ "24c01",   128,     8,  1, 0x00 }, // 16 pages of 8 bytes each = 128 bytes
	{ "24c02",   256,     8,  1, 0x00 }, // 32 pages of 8 bytes each = 256 bytes
	{ "24c04",   512,    16,  1, 0x01 }, // 32 pages of 16 bytes each = 512 bytes
	{ "24c08",   1024,   16,  1, 0x03 }, // 64 pages of 16 bytes each = 1024 bytes
	{ "24c16",   2048,   16,  1, 0x07 }, // 128 pages of 16 bytes each = 2048 bytes
	{ "24c32",   4096,   32,  2, 0x00 }, // 32kbit = 4kbyte
	{ "24c64",   8192,   32,  2, 0x00 },
	{ "24c128",  16384,  32/*64*/,  2, 0x00 },
	{ "24c256",  32768,  32/*64*/,  2, 0x00 },
	{ "24c512",  65536,  32/*128*/, 2, 0x00 },
	{ "24c1024", 131072, 32/*128*/, 2, 0x01 },
	{ 0, 0, 0, 0 }
};

struct i2c_msg {
        uint16_t addr;     /* slave address                        */
        uint16_t flags;
#define I2C_M_RD                0x0001  /* read data, from slave to master */
                                        /* I2C_M_RD is guaranteed to be 0x0001! */
#define I2C_M_TEN               0x0010  /* this is a ten bit chip address */
#define I2C_M_DMA_SAFE          0x0200  /* the buffer of this message is DMA safe */
                                        /* makes only sense in kernelspace */
                                        /* userspace buffers are copied anyway */
#define I2C_M_RECV_LEN          0x0400  /* length will be first received byte */
#define I2C_M_NO_RD_ACK         0x0800  /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_IGNORE_NAK        0x1000  /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_REV_DIR_ADDR      0x2000  /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_NOSTART           0x4000  /* if I2C_FUNC_NOSTART */
#define I2C_M_STOP              0x8000  /* if I2C_FUNC_PROTOCOL_MANGLING */
        uint16_t len;              /* msg length                           */
        uint8_t *buf;              /* pointer to msg data                  */
};


int32_t ch347readEEPROM(uint8_t *buf, uint32_t bytes, struct EEPROM *eeprom_info);
int32_t ch347writeEEPROM(uint8_t *buf, uint32_t bytes, struct EEPROM *eeprom_info);
int32_t parseEEPsize(char *eepromname, struct EEPROM *eeprom);
int32_t ch347i2cConfig(int speed);
#endif /* __CH347_I2C_H__ */
