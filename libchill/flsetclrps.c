/* Implement POWERSET runtime actions for CHILL.
   Copyright (C) 1992,1993 Free Software Foundation, Inc.
   Author: Wilfried Moser, et al

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

#define __CHILL_LIB__

#include "config.h"
#include <stdio.h>
#include "powerset.h"

/*
 * function __flsetclrpowerset
 *
 * parameters:
 *	ps		powerset
 *	bitlength	length of powerset
 *
 * returns:
 *	int		-1 .. nothing found
 *			>= 0 .. index of last set bit
 * exceptions:
 *  none
 *
 * abstract:
 *  Find last bit set in a powerset and return the corresponding value
 *  in *out and clear this bit. Return 0 for no more found, else 1.
 *
 */
int
__flsetclrpowerset (ps, bitlength, first_bit)
     SET_WORD      *ps;
     unsigned long  bitlength;
     int first_bit;
{
  register int bitno;

#ifndef USE_CHARS
  if (bitlength <= SET_CHAR_SIZE)
    {
      for (bitno = bitlength - 1; bitno >= first_bit; bitno--)
	if (GET_BIT_IN_CHAR (*((SET_CHAR *)ps), bitno))
	  break;
      return bitno < first_bit ? -1 : bitno;
    }
  else if (bitlength <= SET_SHORT_SIZE)
    {
      for (bitno = bitlength - 1; bitno >= first_bit; bitno--)
	if (GET_BIT_IN_SHORT (*((SET_SHORT *)ps), bitno))
	  break;
      return bitno < first_bit ? -1 : bitno;
    }
  else
#endif
    {
      SET_WORD *p, c;
      bitno = bitlength - 1;
      if (bitno < first_bit)
	return -1;
      p = &ps[(unsigned) bitno / SET_WORD_SIZE];
      c = *p;
      if (((unsigned) bitlength % SET_WORD_SIZE) != 0)
	MASK_UNUSED_WORD_BITS(&c, (unsigned) bitlength % SET_WORD_SIZE);
      if (c)
	goto found;
      else
	bitno -= ((unsigned) bitno % SET_WORD_SIZE) + 1;
      while (bitno >= first_bit)
	{
	  c = *--p;
	  if (c)
	    goto found;
	  bitno -= SET_WORD_SIZE;
	}
      return -1;
    found:
      for (; bitno >= first_bit; bitno--)
	{
	  if (GET_BIT_IN_WORD (c, (unsigned) bitno % SET_WORD_SIZE))
	    return bitno;
	}
      return -1;
    }
}
