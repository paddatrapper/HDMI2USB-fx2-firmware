/*
 * Copyright (C) 2009-2012 Chris McClelland
 * Copyright (C) 2017 Kyle Robbertze <krobbertze@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <fx2regs.h>
#include <makestuff.h>
#include "debug.h"

__sbit __at 0xB3 USART; // Port D3
#define BAUD 32

void usartInit(void) {
	USART = 1;
	OED |= 0xff; //0x80;
}

void usartSendByte(uint8 c) {
	(void)c; /* argument passed in DPL */
	__asm
		mov a, dpl
		mov r1, #9
		clr c
	loop:
		mov _USART, c
		rrc a
		mov r0, #BAUD
		djnz r0, .
		nop
		djnz r1, loop

		;; Stop bit
		setb _USART
		mov r0, #BAUD
		djnz r0, .
	__endasm;
}
void usartSendByteHex(uint8 byte) {
	__xdata uint8 ch;
	ch = (byte >> 4) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = byte & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
}
void usartSendWordHex(uint16 word) {
	__xdata uint8 ch;
	ch = (word >> 12) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 8) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 4) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 0) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
}
void usartSendLongHex(uint32 word) {
	__xdata uint8 ch;
	ch = (word >> 28) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 24) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 20) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 16) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 12) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 8) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 4) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
	ch = (word >> 0) & 0x0F;
	ch += (ch < 10 ) ? '0' : 'A' - 10;
	usartSendByte(ch);
}
void usartSendString(const char *s) {
	while ( *s ) {
		usartSendByte(*s++);
	}
}
